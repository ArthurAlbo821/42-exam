#!/usr/bin/env python3
"""Drill mode — grind the 60-point zone (levels 1-12) until it's automatic.

Weakness-first rotation: never-seen exercises come first (easiest levels
first), then the ones you failed or solved slowly. Mastered exercises
("acquired": 2 passes, at least 1 on the first grademe) come back once
every 6 picks so you don't get rusty. Each exercise is timed; your best
time is recorded. Old solutions are archived so every rep starts clean.
"""

import json
import os
import random
import shutil
import time

import examshell as ex
import ui

DRILL_LEVEL_MAX = 12
REVIEW_EVERY = 6  # every Nth pick is a review of an acquired exercise

# exercises requiring structs / linked lists (C08) — excluded from both zones
STRUCT_EXOS = {
    "ft_list_size", "ft_list_push_front", "ft_list_foreach",
    "ft_list_remove_if", "cycle_detector", "sort_list", "flood_fill",
}
ZONES = {
    "60": "ZONE 60 POINTS (niveaux 1-12)",
    "malloc": "ZONE ÉTENDUE (tout sauf C08)",
}
STATS_FILE = os.path.join(ex.ROOT, ".drill_stats.json")
ARCHIVE_DIR = os.path.join(ex.ROOT, ".drill_archive")
WORKDIR = os.path.join(ex.ROOT, "entrainement")  # séparé du rendu/ d'examen

BOLD, GREEN, RED, YELLOW, CYAN, RESET = (
    ex.BOLD, ex.GREEN, ex.RED, ex.YELLOW, ex.CYAN, ex.RESET)


def load_stats():
    if os.path.isfile(STATS_FILE):
        with open(STATS_FILE) as f:
            return json.load(f)
    return {"exercises": {}, "picks": 0, "current": None}


def save_stats(stats):
    with open(STATS_FILE, "w") as f:
        json.dump(stats, f, indent=2)


def entry(stats, name):
    return stats["exercises"].setdefault(name, {
        "passes": 0, "fails": 0, "skips": 0,
        "first_try": 0, "best_time": None, "last_pick": 0,
    })


def acquired(e):
    return e["passes"] >= 2 and e["first_try"] >= 1


def drill_pool(pool, zone="60"):
    if zone == "malloc":
        return {name: meta for name, meta in pool.items()
                if name not in STRUCT_EXOS}
    return {name: meta for name, meta in pool.items()
            if meta["level"] <= DRILL_LEVEL_MAX}


def pick_exercise(pool, stats):
    """Weakness-first pick; every REVIEW_EVERY picks, review an acquired one."""
    names = list(pool)
    never = [n for n in names if n not in stats["exercises"]]
    seen = [n for n in names if n in stats["exercises"]]
    weak = [n for n in seen if not acquired(stats["exercises"][n])]
    done = [n for n in seen if acquired(stats["exercises"][n])]

    if done and stats["picks"] % REVIEW_EVERY == REVIEW_EVERY - 1:
        return random.choice(done), "révision (exercice acquis)"
    if never:
        lowest = min(pool[n]["level"] for n in never)
        return (random.choice([n for n in never
                               if pool[n]["level"] == lowest]),
                "jamais fait")
    if weak:
        def weakness(n):
            e = stats["exercises"][n]
            return (-(e["fails"] + e["skips"] - e["passes"]), e["last_pick"])
        weak.sort(key=weakness)
        return random.choice(weak[:3]), "à consolider"
    return random.choice(names), "tout est acquis — révision libre 💪"


def archive_exercise(name):
    """Move entrainement/<name> to the archive (drill keeps only the
    current exercise visible)."""
    src = os.path.join(WORKDIR, name)
    if not os.path.isdir(src):
        return
    os.makedirs(ARCHIVE_DIR, exist_ok=True)
    n = 1
    while os.path.isdir(os.path.join(ARCHIVE_DIR, f"{name}-{n}")):
        n += 1
    shutil.move(src, os.path.join(ARCHIVE_DIR, f"{name}-{n}"))


def assign(stats, pool, name, reason, fresh=True):
    meta = pool[name]
    if fresh:
        archive_exercise(name)
    ex.install_exercise(meta, workdir=WORKDIR)
    e = entry(stats, name)
    stats["picks"] += 1
    e["last_pick"] = stats["picks"]
    if stats["current"] is None or stats["current"]["name"] != name:
        stats["current"] = {"name": name, "elapsed": 0.0, "attempts": 0}
    save_stats(stats)
    best = ex.fmt_duration(e["best_time"]) if e["best_time"] else "—"
    ex.show_subject(meta, f"record {best}", where="entrainement")
    print(f" {YELLOW}◆{RESET} {reason}   "
          f"{ui.DIM}historique : {e['passes']}✓ {e['fails']}✗ "
          f"{e['skips']}→{RESET}\n")
    return meta


def fmt_line(name, meta, e):
    if e is None:
        state, color = "· jamais fait", ""
    elif acquired(e):
        state, color = "✓ acquis", GREEN
    elif e["passes"] > 0:
        state, color = "~ en cours", YELLOW
    else:
        state, color = "✗ à travailler", RED
    best = (" best " + ex.fmt_duration(e["best_time"])
            if e and e["best_time"] else "")
    hist = (f"  {e['passes']}✓/{e['fails']}✗/{e['skips']}→"
            if e else "")
    return (f"  {color}{state:<15}{RESET} L{meta['level']:>2} "
            f"{name:<28}{hist}{best}")


def show_stats(pool, stats, zone="60"):
    names = sorted(pool, key=lambda n: (pool[n]["level"], n))
    got = sum(1 for n in names
              if n in stats["exercises"]
              and acquired(stats["exercises"][n]))
    print()
    ui.frame("MAÎTRISE · " + ZONES[zone].split(" (")[0],
             f"{got}/{len(names)} acquis")
    print()
    ui.bar("ACQUIS", got, len(names))
    print(f"\n {ui.DIM}acquis = 2 réussites dont 1 du premier coup ; "
          f"✓/✗/→ = réussites/échecs/passés{RESET}\n")
    for n in names:
        print(fmt_line(n, pool[n], stats["exercises"].get(n)))
    print()


HELP = f"""
Commandes du mode entraînement :
  {BOLD}grademe{RESET}   corrige l'exercice en cours (chronométré)
  {BOLD}skip{RESET}      passe à un autre exercice (compte comme une faiblesse)
  {BOLD}subject{RESET}   réaffiche le sujet
  {BOLD}code{RESET}      ouvre le dossier de l'exercice dans VS Code
  {BOLD}stats{RESET}     tableau de maîtrise des {BOLD}~45{RESET} exercices de la zone 60 pts
  {BOLD}status{RESET}    exercice en cours, chrono, historique
  {BOLD}help{RESET}      ce message
  {BOLD}exit{RESET}      sauvegarde et quitte (le chrono de l'exo est mis en pause)
"""


def grade_current(stats, meta, started):
    name = meta["name"]
    e = entry(stats, name)
    cur = stats["current"]
    cur["attempts"] += 1
    elapsed = cur["elapsed"] + (time.monotonic() - started)
    print()
    try:
        with ui.Spinner(f"compilation & tests de {name} "
                        f"(chrono {ex.fmt_duration(elapsed)})"):
            ex.grade(meta, workdir=WORKDIR)
    except ex.GradeFailure as failure:
        trace = ex.write_trace(meta, failure)
        e["fails"] += 1
        save_stats(stats)
        ui.ko(failure.title)
        ui.failure_detail(failure.detail)
        print(f"\n {ui.DIM}Trace complète : "
              f"{os.path.relpath(trace, ex.ROOT)} — corrige puis retape "
              f"'grademe'.{RESET}\n")
        return False
    first_try = cur["attempts"] == 1
    was_acquired = acquired(e)
    e["passes"] += 1
    if first_try:
        e["first_try"] += 1
    new_record = e["best_time"] is not None and elapsed < e["best_time"]
    if e["best_time"] is None or elapsed < e["best_time"]:
        e["best_time"] = elapsed
    stats["current"] = None
    save_stats(stats)
    archive_exercise(name)  # l'espace drill ne garde que l'exo en cours
    tag = " · du premier coup !" if first_try else ""
    ui.ok(f"{name} réussi{tag}", ex.fmt_duration(elapsed))
    if new_record:
        print(f"\n {YELLOW}🏆 Nouveau record personnel !{RESET}")
    if acquired(e) and not was_acquired:
        ui.celebrate(f"{name.upper()} ACQUIS")
    print()
    return True


def repl(zone="60"):
    pool = drill_pool(ex.load_exercises(), zone)
    stats = load_stats()
    ui.show_banner("MODE ENTRAÎNEMENT · " + ZONES[zone])
    got = sum(1 for n in pool if n in stats["exercises"]
              and acquired(stats["exercises"][n]))
    ui.bar("ACQUIS", got, len(pool))
    print(f"\n {ui.DIM}Objectif : tout en ✓. "
          f"Tape 'help' pour les commandes.{RESET}\n")

    if stats["current"] and stats["current"]["name"] in pool:
        name = stats["current"]["name"]
        print(f"Reprise de l'exercice en cours : {BOLD}{name}{RESET} "
              f"(ton code est toujours dans entrainement/{name}/)")
        meta = assign(stats, pool, name, "reprise", fresh=False)
    else:
        name, reason = pick_exercise(pool, stats)
        meta = assign(stats, pool, name, reason)
    started = time.monotonic()

    while True:
        try:
            cmd = input(f"{CYAN}{BOLD}drill ❯{RESET} ").strip().lower()
        except (EOFError, KeyboardInterrupt):
            print()
            cmd = "exit"

        if cmd == "grademe":
            if grade_current(stats, meta, started):
                name, reason = pick_exercise(pool, stats)
                meta = assign(stats, pool, name, reason)
                started = time.monotonic()
        elif cmd == "skip":
            e = entry(stats, meta["name"])
            e["skips"] += 1
            stats["current"] = None
            save_stats(stats)
            archive_exercise(meta["name"])
            print(f"{YELLOW}{meta['name']} passé — "
                  f"il reviendra en priorité.{RESET}")
            name, reason = pick_exercise(pool, stats)
            meta = assign(stats, pool, name, reason)
            started = time.monotonic()
        elif cmd == "subject":
            e = entry(stats, meta["name"])
            best = ex.fmt_duration(e["best_time"]) if e["best_time"] else "—"
            ex.show_subject(meta, f"record {best}", where="entrainement")
        elif cmd == "code":
            ex.open_in_vscode(os.path.join(WORKDIR, meta["name"]))
        elif cmd == "stats":
            show_stats(pool, stats, zone)
        elif cmd == "status":
            e = entry(stats, meta["name"])
            cur = stats["current"]
            elapsed = cur["elapsed"] + (time.monotonic() - started)
            best = ex.fmt_duration(e["best_time"]) if e["best_time"] else "—"
            print(f"\n{BOLD}Exercice :{RESET} {meta['name']} "
                  f"(niveau {meta['level']})")
            print(f"{BOLD}Chrono   :{RESET} {ex.fmt_duration(elapsed)}   "
                  f"{BOLD}Record :{RESET} {best}")
            print(f"{BOLD}Histo    :{RESET} {e['passes']}✓ {e['fails']}✗ "
                  f"{e['skips']}→   essais sur cet exo : {cur['attempts']}\n")
        elif cmd == "help":
            print(HELP)
        elif cmd in ("exit", "quit"):
            if stats["current"]:
                stats["current"]["elapsed"] += time.monotonic() - started
            save_stats(stats)
            print("Progression sauvegardée. À la prochaine session !")
            return
        elif cmd:
            print(f"Commande inconnue '{cmd}'. Tape 'help'.")


if __name__ == "__main__":
    repl()
