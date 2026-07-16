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
DIM, MAGENTA = ui.DIM, ui.MAGENTA


def load_stats():
    if os.path.isfile(STATS_FILE):
        with open(STATS_FILE) as f:
            stats = json.load(f)
    else:
        stats = {"exercises": {}, "picks": 0, "current": None}
    stats.setdefault("total_seconds", 0.0)
    return stats


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


def redo_pool(pool, stats):
    """Exercices déjà tentés mais pas encore acquis — ◐ en cours et
    ○ à retravailler — triés par niveau croissant."""
    return [n for n in sorted(pool, key=lambda n: (pool[n]["level"], n))
            if status_of(stats["exercises"].get(n)) in ("wip", "todo")]


def next_redo(pool, stats, exclude=None):
    """Prochain exo à rattraper, différent du dernier si possible."""
    names = redo_pool(pool, stats)
    others = [n for n in names if n != exclude]
    if others:
        return others[0]
    return names[0] if names else None


def advance(pool, stats, rattrapage, just_done=None):
    """Choisit le prochain exercice après une réussite ou un skip.
    En rattrapage, enchaîne sur le prochain non-acquis ; quand il n'en
    reste plus, fête l'événement et repasse en entraînement normal."""
    if rattrapage:
        nxt = next_redo(pool, stats, exclude=just_done)
        if nxt:
            return nxt, "rattrapage", True
        ui.celebrate("RATTRAPAGE TERMINÉ — tout est acquis")
        print(f" {DIM}Retour à l'entraînement normal.{RESET}\n")
    name, reason = pick_exercise(pool, stats)
    return name, reason, False


def choose_redo(pool, stats):
    """Affiche la liste des exos à rattraper et renvoie le nom choisi
    (ou None si liste vide / annulation)."""
    names = redo_pool(pool, stats)
    if not names:
        print(f"\n {GREEN}Rien à rattraper : tout ce que tu as touché "
              f"est déjà acquis ! 🎉{RESET}\n")
        return None
    print(f"\n {BOLD}Exercices à rattraper{RESET}  "
          f"{DIM}◐ en cours · ○ à retravailler{RESET}\n")
    for i, n in enumerate(names, 1):
        e = stats["exercises"][n]
        best = ex.fmt_duration(e["best_time"]) if e["best_time"] else "—"
        print(f"  {DIM}[{i:>2}]{RESET} {pastille(e)} {BOLD}{n:<24}{RESET}"
              f"{DIM}niv {pool[n]['level']:>2}   {RESET}"
              f"{GREEN}{e['passes']}✓{RESET} {RED}{e['fails']}✗{RESET}"
              f"   {DIM}best {best}{RESET}")
    try:
        ans = input(f"\n {CYAN}{BOLD}Numéro à refaire "
                    f"(entrée = annuler) ❯{RESET} ").strip()
    except (EOFError, KeyboardInterrupt):
        return None
    if ans.isdigit() and 1 <= int(ans) <= len(names):
        return names[int(ans) - 1]
    return None


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
    if fresh:
        ex.auto_open_next(os.path.join(WORKDIR, meta["name"]))
    best = ex.fmt_duration(e["best_time"]) if e["best_time"] else "—"
    ex.show_subject(meta, f"record {best}", where="entrainement")
    print(f" {YELLOW}◆{RESET} {reason}   "
          f"{ui.DIM}historique : {e['passes']}✓ {e['fails']}✗ "
          f"{e['skips']}→{RESET}\n")
    return meta


PASTILLE = {
    "done":  (GREEN, "●"),
    "wip":   (YELLOW, "◐"),
    "todo":  (RED, "○"),
    "never": (DIM, "·"),
}


def status_of(e):
    if e is None or (e["passes"] == 0 and e["fails"] == 0
                     and e["skips"] == 0):
        return "never"
    if acquired(e):
        return "done"
    if e["passes"] > 0:
        return "wip"
    return "todo"  # tenté mais jamais réussi


def pastille(e):
    color, glyph = PASTILLE[status_of(e)]
    return f"{color}{glyph}{RESET}"


def next_target(pool, stats):
    """L'exercice le plus utile à travailler maintenant."""
    ordered = sorted(pool, key=lambda n: (pool[n]["level"], n))
    for n in ordered:
        if status_of(stats["exercises"].get(n)) == "never":
            return n, f"niveau {pool[n]['level']}, jamais fait"
    wip = [n for n in ordered
           if not acquired(stats["exercises"][n])]
    if wip:
        wip.sort(key=lambda n: (-stats["exercises"][n]["fails"],
                                pool[n]["level"]))
        return wip[0], f"niveau {pool[wip[0]]['level']}, en cours"
    return None, None


def show_stats(pool, stats, zone="60"):
    ex_stats = stats["exercises"]
    total = len(pool)
    got = sum(1 for n in pool
              if acquired(ex_stats.get(n, {"passes": 0, "first_try": 0})))
    levels = sorted({pool[n]["level"] for n in pool})
    by_level = {l: sorted(n for n in pool if pool[n]["level"] == l)
                for l in levels}
    mastered = sum(1 for l in levels
                   if all(status_of(ex_stats.get(n)) == "done"
                          for n in by_level[l]))

    print()
    ui.frame("MAÎTRISE · " + ZONES[zone].split(" (")[0],
             f"{got}/{total} acquis")
    print()

    # --- bandeau de synthèse -------------------------------------------
    pct = 0 if total == 0 else round(100 * got / total)
    ui.bar("ACQUIS", got, total, suffix=f"{got}/{total} · {pct}%")
    print(f" {BOLD}Niveaux maîtrisés{RESET} : {mastered}/{len(levels)}"
          f"   {GREEN}→ {mastered * 5} pts garantis à l'examen{RESET}")
    print(f" {DIM}un exercice est « acquis » après 2 réussites "
          f"dont 1 du premier coup{RESET}\n")

    tname, treason = next_target(pool, stats)
    if tname:
        print(f" {CYAN}◆ Prochaine cible{RESET} : {BOLD}{tname}{RESET} "
              f"{DIM}({treason}){RESET}")
    else:
        print(f" {GREEN}◆ Tout est acquis dans cette zone ! 🎉{RESET}")

    weak = sorted((n for n in pool if ex_stats.get(n, {}).get("fails", 0)),
                  key=lambda n: -ex_stats[n]["fails"])[:3]
    if weak:
        parts = " · ".join(f"{n} {RED}{ex_stats[n]['fails']}✗{RESET}"
                           for n in weak)
        print(f" {CYAN}◆ Points faibles{RESET}  : {parts}")

    best_times = [ex_stats[n]["best_time"] for n in pool
                  if ex_stats.get(n, {}).get("best_time")]
    avg = (f"  ·  meilleur temps moyen "
           f"{ex.fmt_duration(sum(best_times) / len(best_times))}"
           if best_times else "")
    print(f" {CYAN}◆ Temps total{RESET}     : "
          f"{ex.fmt_duration(stats.get('total_seconds', 0))}{avg}\n")

    # --- grille par niveau ---------------------------------------------
    print(f" {DIM}┄ Grille  {PASTILLE['done'][0]}●{RESET}{DIM} acquis  "
          f"{PASTILLE['wip'][0]}◐{RESET}{DIM} en cours  "
          f"{PASTILLE['todo'][0]}○{RESET}{DIM} à retravailler  "
          f"·  jamais fait ┄{RESET}")
    for l in levels:
        cells = " ".join(pastille(ex_stats.get(n)) for n in by_level[l])
        done = sum(1 for n in by_level[l]
                   if status_of(ex_stats.get(n)) == "done")
        n_lvl = len(by_level[l])
        tick = f"{GREEN}✓{RESET}" if done == n_lvl else " "
        print(f" {BOLD}L{l:>2}{RESET}  {cells}"
              f"{'  ' * (11 - n_lvl)}   {DIM}{done}/{n_lvl}{RESET} {tick}")

    # --- détail des exercices déjà travaillés --------------------------
    worked = [n for n in sorted(pool, key=lambda n: (pool[n]["level"], n))
              if status_of(ex_stats.get(n)) != "never"]
    if worked:
        print(f"\n {DIM}┄ Exercices travaillés ┄{RESET}")
        for n in worked:
            e = ex_stats[n]
            best = (f"best {ex.fmt_duration(e['best_time'])}"
                    if e["best_time"] else "")
            print(f" {pastille(e)} {BOLD}{n:<26}{RESET}"
                  f"{GREEN}{e['passes']}✓{RESET} {RED}{e['fails']}✗{RESET}"
                  f"   {DIM}{best}{RESET}")
    print()


HELP = f"""
Commandes du mode entraînement :
  {BOLD}grademe{RESET}   corrige l'exercice en cours (chronométré)
  {BOLD}skip{RESET}      passe à un autre exercice (compte comme une faiblesse)
  {BOLD}redo{RESET}      liste tes exos non-acquis et enchaîne-les jusqu'à validation
  {BOLD}subject{RESET}   réaffiche le sujet
  {BOLD}code{RESET}      ouvre le dossier de l'exercice dans VS Code
  {BOLD}stats{RESET}     tableau de maîtrise des exercices de la zone
  {BOLD}status{RESET}    exercice en cours, chrono, historique
  {BOLD}finish{RESET}    termine la session avec un récap (chrono en pause)
  {BOLD}help{RESET}      ce message
  {BOLD}exit{RESET}      quitte sans récap (le chrono de l'exo est mis en pause)
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
        trace = ex.write_trace(meta, failure, workdir=WORKDIR)
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
    stats["total_seconds"] = stats.get("total_seconds", 0.0) + elapsed
    stats["current"] = None
    save_stats(stats)
    ex.clear_trace(meta, workdir=WORKDIR)
    archive_exercise(name)  # l'espace drill ne garde que l'exo en cours
    tag = " · du premier coup !" if first_try else ""
    ui.ok(f"{name} réussi{tag}", ex.fmt_duration(elapsed))
    if new_record:
        print(f"\n {YELLOW}🏆 Nouveau record personnel !{RESET}")
    if acquired(e) and not was_acquired:
        ui.celebrate(f"{name.upper()} ACQUIS")
    print()
    return True


def acquired_count(pool, stats):
    return sum(1 for n in pool if n in stats["exercises"]
               and acquired(stats["exercises"][n]))


def finish_session(pool, stats, zone, session_passed, start_acquired,
                   session_start):
    """End the drill session with a recap (finish command)."""
    got = acquired_count(pool, stats)
    print()
    ui.frame("SESSION TERMINÉE",
             ex.fmt_duration(time.monotonic() - session_start))
    print()
    ui.bar("ACQUIS", got, len(pool))
    print(f"\n {BOLD}Réussis cette session :{RESET} {len(session_passed)}"
          + (f"  {ui.DIM}({', '.join(session_passed)}){RESET}"
             if session_passed else ""))
    gained = got - start_acquired
    if gained > 0:
        ui.celebrate(f"+{gained} EXERCICE(S) ACQUIS AUJOURD'HUI")
    print(f"\n {ui.DIM}Progression sauvegardée — "
          f"à la prochaine session !{RESET}\n")


def repl(zone="60", rattrapage=False):
    pool = drill_pool(ex.load_exercises(), zone)
    stats = load_stats()
    ui.show_banner(("RATTRAPAGE · " if rattrapage else "MODE ENTRAÎNEMENT · ")
                   + ZONES[zone])
    start_acquired = acquired_count(pool, stats)
    session_passed = []
    session_start = time.monotonic()
    ui.bar("ACQUIS", start_acquired, len(pool))
    print(f"\n {ui.DIM}Objectif : tout en ✓. "
          f"Tape 'help' pour les commandes.{RESET}\n")

    if rattrapage:
        choice = choose_redo(pool, stats)
        if not choice:
            return
        meta = assign(stats, pool, choice, "rattrapage")
    elif stats["current"] and stats["current"]["name"] in pool:
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
                session_passed.append(meta["name"])
                name, reason, rattrapage = advance(
                    pool, stats, rattrapage, meta["name"])
                meta = assign(stats, pool, name, reason)
                started = time.monotonic()
        elif cmd == "skip":
            e = entry(stats, meta["name"])
            e["skips"] += 1
            cur = stats["current"]
            if cur:
                stats["total_seconds"] = (stats.get("total_seconds", 0.0)
                                          + cur["elapsed"]
                                          + (time.monotonic() - started))
            stats["current"] = None
            save_stats(stats)
            archive_exercise(meta["name"])
            print(f"{YELLOW}{meta['name']} passé — "
                  f"il reviendra en priorité.{RESET}")
            name, reason, rattrapage = advance(
                pool, stats, rattrapage, meta["name"])
            meta = assign(stats, pool, name, reason)
            started = time.monotonic()
        elif cmd == "redo":
            choice = choose_redo(pool, stats)
            if choice:
                cur = stats["current"]
                if cur:
                    stats["total_seconds"] = (stats.get("total_seconds", 0.0)
                                              + cur["elapsed"]
                                              + (time.monotonic() - started))
                stats["current"] = None
                save_stats(stats)
                rattrapage = True
                meta = assign(stats, pool, choice, "rattrapage")
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
        elif cmd in ("finish", "exit", "quit"):
            if stats["current"]:
                stats["current"]["elapsed"] += time.monotonic() - started
            save_stats(stats)
            if cmd == "finish":
                finish_session(pool, stats, zone, session_passed,
                               start_acquired, session_start)
            else:
                print("Progression sauvegardée. À la prochaine session !")
            return
        elif cmd:
            print(f"Commande inconnue '{cmd}'. Tape 'help'.")


if __name__ == "__main__":
    repl()
