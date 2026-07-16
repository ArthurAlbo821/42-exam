#!/usr/bin/env python3
"""ExamShell — 42 Piscine Final Exam simulator.

20 levels, one random exercise per level, 5 points each (100 total).
Work in rendu/<exercise>/, then type `grademe` to run the moulinette.
"""

import json
import os
import random
import shutil
import subprocess
import sys
import time

import ui

ROOT = os.path.dirname(os.path.abspath(__file__))
EXERCISES_DIR = os.path.join(ROOT, "data", "exercises")
RENDU_DIR = os.path.join(ROOT, "rendu")
EXAM_ARCHIVE_DIR = os.path.join(ROOT, ".exam_archive")
BUILD_DIR = os.path.join(ROOT, ".build-%d" % os.getpid())
STATE_FILE = os.path.join(ROOT, ".exam_state.json")
HISTORY_FILE = os.path.join(ROOT, "history.txt")

# 4h by default; the real final exam lasts 8h: EXAM_HOURS=8 ./exam
EXAM_DURATION = int(float(os.environ.get("EXAM_HOURS", "4")) * 3600)
TOTAL_LEVELS = 20
POINTS_PER_LEVEL = 5
TEST_TIMEOUT = 10  # seconds per test run

CC = "cc"
CFLAGS = ["-Wall", "-Wextra", "-Werror"]

# Symbols the compiler may emit on its own; never counted as cheating.
BASE_ALLOWED_SYMBOLS = {
    "___stack_chk_fail", "___stack_chk_guard", "___memset_chk",
    "___strcpy_chk", "___strcat_chk", "___sprintf_chk", "___bzero",
    "___assert_rtn", "dyld_stub_binder", "_memset", "_memcpy", "_memmove",
    "__memset", "__memcpy", "__memmove", "__bzero",
    "___chkstk_darwin",
}

GREEN = "\033[32m"
RED = "\033[31m"
YELLOW = "\033[33m"
CYAN = "\033[36m"
BOLD = "\033[1m"
RESET = "\033[0m"


# ---------------------------------------------------------------- exercises

def load_exercises():
    """Return {name: meta} for every exercise in data/exercises/."""
    pool = {}
    if not os.path.isdir(EXERCISES_DIR):
        return pool
    for name in sorted(os.listdir(EXERCISES_DIR)):
        meta_path = os.path.join(EXERCISES_DIR, name, "meta.json")
        if not os.path.isfile(meta_path):
            continue
        with open(meta_path) as f:
            meta = json.load(f)
        meta["dir"] = os.path.join(EXERCISES_DIR, name)
        pool[meta["name"]] = meta
    return pool


def exercises_by_level(pool):
    levels = {}
    for meta in pool.values():
        levels.setdefault(meta["level"], []).append(meta["name"])
    return levels


# ------------------------------------------------------------------- state

def load_state():
    if os.path.isfile(STATE_FILE):
        with open(STATE_FILE) as f:
            return json.load(f)
    return None


def save_state(state):
    with open(STATE_FILE, "w") as f:
        json.dump(state, f, indent=2)


def new_state(duration=None):
    return {
        "level": 1,
        "score": 0,
        "elapsed": 0.0,          # seconds spent in previous sessions
        "duration": duration or EXAM_DURATION,
        "assigned": {},          # level (str) -> exercise name
        "passed": [],
        "attempts": {},          # exercise name -> tries
        "finished": False,
    }


class Clock:
    """Exam timer that only ticks while the program is running."""

    def __init__(self, state):
        self.base = state["elapsed"]
        self.duration = state.get("duration", EXAM_DURATION)
        self.started = time.monotonic()

    def elapsed(self):
        return self.base + (time.monotonic() - self.started)

    def remaining(self):
        return max(0.0, self.duration - self.elapsed())


def fmt_duration(seconds):
    seconds = int(seconds)
    h, rem = divmod(seconds, 3600)
    m, s = divmod(rem, 60)
    return f"{h:02d}:{m:02d}:{s:02d}"


# --------------------------------------------------------------- rendering

def banner(text, color=CYAN):
    line = "=" * 66
    print(f"{color}{line}\n{text.center(66)}\n{line}{RESET}")


def show_subject(meta, right="", where="rendu"):
    subject_path = os.path.join(meta["dir"], "subject.txt")
    with open(subject_path) as f:
        subject = f.read()
    print()
    ui.frame(f"LEVEL {meta['level']} · {meta['name']}", right)
    print()
    print(subject)
    ui.hr()
    print(f" {YELLOW}▸{RESET} Code dans {BOLD}{where}/{meta['name']}/{RESET}"
          f"   {ui.DIM}(sujet + fichiers .c déjà créés){RESET}")
    if _vscode_active:
        print(f" {ui.GREEN}▸{RESET} VS Code a basculé sur ce nouvel "
              f"exercice.\n")
    else:
        print(f" {ui.CYAN}▸ Tape {BOLD}code{RESET}{ui.CYAN} + Entrée pour "
              f"ouvrir cet exercice dans VS Code.{RESET}\n")


def install_exercise(meta, workdir=None):
    """Prepare the exercise folder: subject.txt + empty expected files."""
    dest = os.path.join(workdir or RENDU_DIR, meta["name"])
    os.makedirs(dest, exist_ok=True)
    shutil.copy(os.path.join(meta["dir"], "subject.txt"),
                os.path.join(dest, "subject.txt"))
    for f in meta["files"]:
        path = os.path.join(dest, f)
        if not os.path.isfile(path):
            open(path, "a").close()


# Set once the student has opened VS Code from the shell; only then do we
# auto-swap the window to the next exercise (so people using another editor
# are never interrupted).
_vscode_active = False


def open_in_vscode(path, quiet=False):
    """Open `path` in VS Code, reusing the same window (-r) so the previous
    exercise is replaced rather than piling up new windows."""
    global _vscode_active
    if shutil.which("code"):
        subprocess.Popen(["code", "-r", path],
                         stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        _vscode_active = True
        if not quiet:
            print(f"{ui.DIM}Ouvert dans VS Code : "
                  f"{os.path.relpath(path, ROOT)}{RESET}")
        return True
    res = subprocess.run(["open", "-a", "Visual Studio Code", path],
                         capture_output=True)
    if res.returncode == 0:
        _vscode_active = True
        if not quiet:
            print(f"{ui.DIM}Ouvert dans VS Code.{RESET}")
        return True
    if not quiet:
        print(f"{YELLOW}VS Code introuvable — ouvre {path} toi-même "
              f"(installe la commande 'code' via la palette VS Code : "
              f"Cmd+Shift+P → 'Shell Command: Install code command').{RESET}")
    return False


def auto_open_next(path):
    """After a passed exercise, swap the VS Code window to the next one —
    but only if the student has been using VS Code this session."""
    if _vscode_active:
        open_in_vscode(path, quiet=True)


def assign_exercise(state, levels, pool):
    """Return meta of the exercise for the current level, drawing if needed."""
    key = str(state["level"])
    if key not in state["assigned"]:
        candidates = levels.get(state["level"], [])
        if not candidates:
            return None
        state["assigned"][key] = random.choice(candidates)
        save_state(state)
    meta = pool[state["assigned"][key]]
    install_exercise(meta)
    return meta


# ----------------------------------------------------------------- grading

class GradeFailure(Exception):
    def __init__(self, title, detail=""):
        super().__init__(title)
        self.title = title
        self.detail = detail


def run(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True,
                          errors="replace", **kw)


def compile_objects(c_files, out_dir, tag, include=None):
    objects = []
    inc = ["-I", include] if include else []
    for src in c_files:
        obj = os.path.join(out_dir, tag + "_" +
                           os.path.basename(src).replace(".c", ".o"))
        res = run([CC, *CFLAGS, *inc, "-c", src, "-o", obj])
        if res.returncode != 0:
            raise GradeFailure(
                f"Compilation failed ({os.path.basename(src)})",
                res.stderr or res.stdout)
        objects.append(obj)
    return objects


def link(objects, out_path):
    res = run([CC, *CFLAGS, *objects, "-o", out_path])
    if res.returncode != 0:
        raise GradeFailure("Link failed", res.stderr or res.stdout)
    return out_path


def check_forbidden(objects, allowed):
    allowed_syms = set(BASE_ALLOWED_SYMBOLS)
    for fn in allowed:
        allowed_syms.add("_" + fn)
        allowed_syms.add(fn)
    bad = set()
    for obj in objects:
        res = run(["nm", "-u", obj])
        for line in res.stdout.splitlines():
            parts = line.split()
            sym = parts[-1].split("@")[0] if parts else ""
            if sym and sym not in allowed_syms:
                bad.add(sym.lstrip("_"))
    if bad:
        raise GradeFailure(
            "Forbidden function(s) used: " + ", ".join(sorted(bad)),
            "Allowed functions for this exercise: "
            + (", ".join(allowed) if allowed else "(none)"))


def run_binary(path, args=None, stdin_data=None):
    try:
        res = subprocess.run(
            [path] + (args or []), input=stdin_data,
            capture_output=True, text=True, errors="replace",
            timeout=TEST_TIMEOUT)
    except subprocess.TimeoutExpired:
        return None, "TIMEOUT"
    if res.returncode < 0:
        return None, f"CRASH (signal {-res.returncode})"
    return res.stdout, None


def visible(s, limit=400):
    """Make whitespace explicit so diffs are readable, truncate long output."""
    if s is None:
        return "(no output)"
    shown = s if len(s) <= limit else s[:limit] + f"... (+{len(s)-limit} chars)"
    return shown.replace("\n", "$\n").replace("\t", "\\t")


def diff_block(label, expected, got):
    return (f"--- {label}\n"
            f"Expected output:\n{visible(expected)}\n"
            f"Your output:\n{visible(got)}\n")


def grade(meta, workdir=None):
    """Run the moulinette on <workdir>/<name>. Raises GradeFailure on KO."""
    rendu = os.path.join(workdir or RENDU_DIR, meta["name"])
    missing = [f for f in meta["files"]
               if not os.path.isfile(os.path.join(rendu, f))]
    if missing:
        raise GradeFailure(
            "Missing file(s): " + ", ".join(missing),
            f"Expected files in {os.path.relpath(rendu, ROOT)}/: "
            + ", ".join(meta["files"]))

    shutil.rmtree(BUILD_DIR, ignore_errors=True)
    os.makedirs(BUILD_DIR)

    user_srcs = [os.path.join(rendu, f) for f in meta["files"]
                 if f.endswith(".c")]
    include_dir = meta["dir"]  # exercise dir may ship a header for drivers

    user_objs = compile_objects(user_srcs, BUILD_DIR, "user",
                                include=include_dir)
    check_forbidden(user_objs, meta.get("allowed_functions", []))

    ref_src = os.path.join(meta["dir"], "ref.c")

    if meta["type"] == "function":
        driver = os.path.join(meta["dir"], "driver.c")
        driver_obj = os.path.join(BUILD_DIR, "driver.o")
        res = run([CC, "-Wall", "-Wextra", "-I", include_dir,
                   "-c", driver, "-o", driver_obj])
        if res.returncode != 0:
            raise GradeFailure("Internal error: driver build failed",
                               res.stderr)
        ref_obj = os.path.join(BUILD_DIR, "ref.o")
        res = run([CC, "-Wall", "-Wextra", "-I", include_dir,
                   "-c", ref_src, "-o", ref_obj])
        if res.returncode != 0:
            raise GradeFailure("Internal error: ref build failed", res.stderr)

        user_bin = link(user_objs + [driver_obj],
                        os.path.join(BUILD_DIR, "user_bin"))
        ref_bin = link([ref_obj, driver_obj],
                       os.path.join(BUILD_DIR, "ref_bin"))
        tests = [{"args": []}]
    else:  # program
        user_bin = link(user_objs, os.path.join(BUILD_DIR, "user_bin"))
        ref_objs = compile_objects([ref_src], BUILD_DIR, "ref",
                                   include=include_dir)
        ref_bin = link(ref_objs, os.path.join(BUILD_DIR, "ref_bin"))
        tests = meta.get("tests", [{"args": []}])

    failures = []
    for i, test in enumerate(tests, 1):
        args = test.get("args", [])
        stdin_data = test.get("stdin")
        expected, ref_err = run_binary(ref_bin, args, stdin_data)
        if ref_err:
            raise GradeFailure("Internal error: reference program failed",
                               ref_err)
        got, err = run_binary(user_bin, args, stdin_data)
        label = f"test {i}: ./{meta['name']} " + " ".join(
            repr(a) for a in args)
        if stdin_data is not None:
            label += f"  (stdin: {stdin_data!r})"
        if err:
            failures.append(f"--- {label}\nYour program: {err}\n")
        elif got != expected:
            failures.append(diff_block(label, expected, got))
        if len(failures) >= 3:
            break

    if failures:
        raise GradeFailure(
            f"Test(s) failed ({len(failures)} shown, first differences):",
            "\n".join(failures))


def write_trace(meta, failure, workdir=None):
    """Write trace.txt next to the student's code so it shows in VS Code."""
    folder = os.path.join(workdir or RENDU_DIR, meta["name"])
    os.makedirs(folder, exist_ok=True)
    path = os.path.join(folder, "trace.txt")
    with open(path, "w") as f:
        f.write(f"Exercise : {meta['name']} (level {meta['level']})\n")
        f.write(f"Verdict  : KO — {failure.title}\n\n")
        f.write(failure.detail.rstrip() + "\n")
    return path


def clear_trace(meta, workdir=None):
    """A passing exercise must not keep a stale failure trace."""
    path = os.path.join(workdir or RENDU_DIR, meta["name"], "trace.txt")
    if os.path.isfile(path):
        os.remove(path)


# -------------------------------------------------------------------- exam

def finish_exam(state, clock, reason):
    state["finished"] = True
    state["elapsed"] = clock.elapsed()
    save_state(state)
    print()
    ui.frame("EXAM OVER", fmt_duration(clock.elapsed()))
    print(f"\n {reason}\n")
    ui.bar("SCORE", state["score"], 100)
    ui.dots("LEVEL", len(state["passed"]), TOTAL_LEVELS)
    if state["score"] >= 60:
        ui.celebrate("OBJECTIF 60 POINTS ATTEINT")
    if state["passed"]:
        print(f"\n {ui.DIM}Validés : " + ", ".join(state["passed"])
              + RESET)
    with open(HISTORY_FILE, "a") as f:
        f.write(f"{time.strftime('%Y-%m-%d %H:%M')}  "
                f"score={state['score']}/100  "
                f"levels={len(state['passed'])}/{TOTAL_LEVELS}  "
                f"time={fmt_duration(clock.elapsed())}\n")


def cmd_status(state, clock, meta):
    print()
    ui.frame(f"LEVEL {state['level']} · {meta['name'] if meta else '-'}",
             fmt_duration(clock.remaining()) + " restant")
    tries = state["attempts"].get(meta["name"], 0) if meta else 0
    print()
    ui.bar("SCORE", state["score"], 100)
    ui.dots("LEVEL", min(state["level"] - 1, TOTAL_LEVELS), TOTAL_LEVELS)
    print(f"\n {ui.DIM}essais sur cet exercice : {tries}{RESET}\n")


def cmd_grademe(state, clock, meta):
    name = meta["name"]
    state["attempts"][name] = state["attempts"].get(name, 0) + 1
    print()
    try:
        with ui.Spinner(f"compilation & tests de {name}"):
            grade(meta)
    except GradeFailure as failure:
        trace = write_trace(meta, failure)
        save_state(state)
        ui.ko(failure.title)
        ui.failure_detail(failure.detail)
        print(f"\n {ui.DIM}Trace complète : "
              f"{os.path.relpath(trace, ROOT)} — corrige puis retape "
              f"'grademe'.{RESET}\n")
        return False
    clear_trace(meta)
    state["score"] += POINTS_PER_LEVEL
    state["passed"].append(name)
    state["level"] += 1
    save_state(state)
    ui.ok(f"{name} validé", f"+{POINTS_PER_LEVEL} pts")
    print()
    ui.bar("SCORE", state["score"], 100)
    ui.dots("LEVEL", min(state["level"] - 1, TOTAL_LEVELS), TOTAL_LEVELS)
    if state["score"] == 60:
        ui.celebrate("60 POINTS — PISCINE EN POCHE")
    elif state["score"] == 100:
        ui.celebrate("100/100 — PERFECT")
    print()
    return True


HELP = f"""
Commands:
  {BOLD}grademe{RESET}   run the tests on your current exercise
  {BOLD}subject{RESET}   print the current subject again
  {BOLD}code{RESET}      open the current exercise folder in VS Code
  {BOLD}status{RESET}    score, level, attempts, time remaining
  {BOLD}finish{RESET}    end the exam now and see your final score
  {BOLD}help{RESET}      this message
  {BOLD}exit{RESET}      save and leave (the timer pauses until you come back)
"""


def repl(state, pool, levels):
    clock = Clock(state)
    meta = assign_exercise(state, levels, pool)
    if meta is None:
        print("No exercise available for this level — pool incomplete.")
        return
    show_subject(meta, fmt_duration(clock.remaining()) + " restant")
    print(f" {ui.DIM}Tape 'grademe' quand tu es prêt, "
          f"'help' pour les commandes.{RESET}\n")

    while True:
        if clock.remaining() <= 0:
            finish_exam(state, clock, "Time is up!")
            return
        try:
            cmd = input(f"{CYAN}{BOLD}examshell ❯{RESET} ").strip().lower()
        except (EOFError, KeyboardInterrupt):
            print()
            cmd = "exit"

        if cmd == "grademe":
            if cmd_grademe(state, clock, meta):
                if state["level"] > TOTAL_LEVELS:
                    finish_exam(state, clock,
                                "Congratulations, you cleared every level!")
                    return
                meta = assign_exercise(state, levels, pool)
                auto_open_next(os.path.join(RENDU_DIR, meta["name"]))
                show_subject(meta,
                             fmt_duration(clock.remaining()) + " restant")
        elif cmd == "subject":
            show_subject(meta, fmt_duration(clock.remaining()) + " restant")
        elif cmd == "code":
            open_in_vscode(os.path.join(RENDU_DIR, meta["name"]))
        elif cmd == "status":
            cmd_status(state, clock, meta)
        elif cmd == "finish":
            finish_exam(state, clock, "Exam ended by student.")
            return
        elif cmd in ("exit", "quit"):
            state["elapsed"] = clock.elapsed()
            save_state(state)
            print("Progress saved. See you soon!")
            return
        elif cmd == "help":
            print(HELP)
        elif cmd:
            print(f"Unknown command '{cmd}'. Type 'help'.")


def prepare_pool():
    pool = load_exercises()
    if not pool:
        print("No exercises found in data/exercises/ — nothing to do.")
        sys.exit(1)
    levels = exercises_by_level(pool)
    missing_levels = [l for l in range(1, TOTAL_LEVELS + 1)
                      if l not in levels]
    if missing_levels:
        print(f"{YELLOW}Warning: no exercises for level(s) "
              f"{missing_levels} — exam will stop there.{RESET}")
    return pool, levels


def run_new(duration=None):
    """Start a fresh exam (used by ./exam and by the 42exam menu)."""
    pool, levels = prepare_pool()
    state = new_state(duration)
    save_state(state)
    if os.path.isdir(RENDU_DIR) and os.listdir(RENDU_DIR):
        os.makedirs(EXAM_ARCHIVE_DIR, exist_ok=True)
        stamp = time.strftime("%Y-%m-%d_%H%M%S")
        shutil.move(RENDU_DIR, os.path.join(EXAM_ARCHIVE_DIR, stamp))
        print(f"{ui.DIM}Ancien rendu archivé dans "
              f".exam_archive/{stamp}/{RESET}")
    print(f"\n{BOLD}New exam started.{RESET} "
          f"Duration: {fmt_duration(state['duration'])}. "
          f"{TOTAL_LEVELS} levels x {POINTS_PER_LEVEL} pts = 100 pts.")
    print("Good luck!\n")
    repl(state, pool, levels)


def run_resume():
    """Resume the exam in progress (falls back to a new one)."""
    state = load_state()
    if not state or state["finished"]:
        return run_new()
    pool, levels = prepare_pool()
    repl(state, pool, levels)


def main():
    ui.show_banner("PISCINE FINAL EXAM · SIMULATOR")
    state = load_state()
    if state and not state["finished"]:
        duration = state.get("duration", EXAM_DURATION)
        print(f"\nAn exam is in progress: score {state['score']}/100, "
              f"level {state['level']}, "
              f"time left {fmt_duration(max(0, duration - state['elapsed']))}")
        answer = input("Resume it? [Y/n] ").strip().lower()
        if answer not in ("n", "no"):
            return run_resume()
    run_new()


if __name__ == "__main__":
    main()
