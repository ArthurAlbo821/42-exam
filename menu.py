#!/usr/bin/env python3
"""42exam — arrow-key launcher menu for the exam simulator."""

import os
import sys
import termios
import tty

import drill
import examshell as ex
import ui

CYAN, BOLD, DIM, RESET = ui.CYAN, ui.BOLD, ui.DIM, ui.RESET


# ------------------------------------------------------------------ input

def read_key():
    fd = sys.stdin.fileno()
    old = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        ch = sys.stdin.read(1)
        if ch == "\x1b":                       # escape sequence
            if sys.stdin.read(1) == "[":
                return {"A": "up", "B": "down"}.get(sys.stdin.read(1), "")
            return "esc"
        if ch in ("\r", "\n"):
            return "enter"
        if ch in ("\x03", "\x04"):             # ctrl-c / ctrl-d
            raise KeyboardInterrupt
        return ch.lower()
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old)


def choose(title, items):
    """Arrow-key menu. items = [(icon, label, description)].
    Returns the selected index, or None on q/esc.
    Falls back to a numbered menu when stdin isn't a terminal."""
    if not sys.stdin.isatty():
        return choose_numbered(title, items)
    idx = 0
    print(f"  {BOLD}{title}{RESET}\n")
    first = True
    while True:
        if not first:
            sys.stdout.write(f"\033[{len(items) + 2}A")
        first = False
        for i, (icon, label, desc) in enumerate(items):
            marker = f"{CYAN}{BOLD}❯{RESET}" if i == idx else " "
            name = (f"{BOLD}{label}{RESET}" if i == idx
                    else f"{DIM}{label}{RESET}")
            pad = " " * max(1, 18 - len(label))
            sys.stdout.write(f"\033[K  {marker} {icon}  {name}{pad}"
                             f"{DIM}{desc}{RESET}\n")
        sys.stdout.write(f"\033[K\n\033[K  {DIM}↑↓ naviguer · "
                         f"entrée valider · q quitter{RESET}\n")
        sys.stdout.flush()
        key = read_key()
        if key == "up":
            idx = (idx - 1) % len(items)
        elif key == "down":
            idx = (idx + 1) % len(items)
        elif key == "enter":
            print()
            return idx
        elif key in ("q", "esc"):
            print()
            return None


def choose_numbered(title, items):
    print(f"  {BOLD}{title}{RESET}\n")
    for i, (icon, label, desc) in enumerate(items, 1):
        print(f"  [{i}] {icon}  {label} — {DIM}{desc}{RESET}")
    try:
        answer = input(f"\n  {DIM}Ton choix (q pour quitter) :{RESET} ")
    except (EOFError, KeyboardInterrupt):
        return None
    answer = answer.strip().lower()
    if answer.isdigit() and 1 <= int(answer) <= len(items):
        return int(answer) - 1
    return None


def pause():
    try:
        input(f"\n  {DIM}Entrée pour revenir au menu…{RESET}")
    except (EOFError, KeyboardInterrupt):
        pass


# ------------------------------------------------------------------ menus

def exam_menu():
    state = ex.load_state()
    in_progress = state and not state["finished"]
    if in_progress:
        duration = state.get("duration", ex.EXAM_DURATION)
        left = ex.fmt_duration(max(0, duration - state["elapsed"]))
        items = [
            ("⏵", "Reprendre", f"{state['score']}/100 · niveau "
             f"{state['level']} · {left} restant"),
            ("✚", "Nouvel examen", "repartir de zéro (nouveau tirage)"),
            ("↩", "Retour", ""),
        ]
        pick = choose("Un examen est en cours :", items)
        if pick == 0:
            ex.run_resume()
            return True
        if pick != 1:
            return False
    items = [
        ("🌊", "Examen 4h", "format révision (défaut)"),
        ("🔥", "Examen 8h", "conditions réelles du vrai final"),
        ("↩", "Retour", ""),
    ]
    pick = choose("Durée de l'examen ?", items)
    if pick == 0:
        ex.run_new(4 * 3600)
        return True
    elif pick == 1:
        ex.run_new(8 * 3600)
        return True
    return False


def drill_menu():
    items = [
        ("🎯", "Zone 60 points", "niveaux 1-12, l'objectif piscine"),
        ("🚀", "Zone étendue", "tout sauf C08 (jamais de listes chaînées)"),
        ("↩", "Retour", ""),
    ]
    pick = choose("Quelle zone d'entraînement ?", items)
    if pick == 0:
        drill.repl("60")
        return True
    elif pick == 1:
        drill.repl("malloc")
        return True
    return False


def stats_screen():
    pool = drill.drill_pool(ex.load_exercises(), "60")
    stats = drill.load_stats()
    drill.show_stats(pool, stats, "60")
    if os.path.isfile(ex.HISTORY_FILE):
        ui.frame("HISTORIQUE DES EXAMENS")
        print()
        with open(ex.HISTORY_FILE) as f:
            for line in f:
                print(f"  {line.rstrip()}")
    else:
        print(f"  {DIM}Aucun examen terminé pour l'instant.{RESET}")
    pause()


def main():
    while True:
        os.system("clear" if sys.stdout.isatty() else "true")
        ui.show_banner("PISCINE FINAL EXAM · SIMULATOR")
        items = [
            ("🏊", "Examen blanc", "simulation complète · 100 pts · chrono"),
            ("💪", "Entraînement", "en boucle · faiblesses d'abord · records"),
            ("📊", "Statistiques", "maîtrise, records, historique des scores"),
            ("✕", "Quitter", ""),
        ]
        pick = choose("Que veux-tu faire ?", items)
        if pick == 0:
            if exam_menu():
                pause()
        elif pick == 1:
            if drill_menu():
                pause()
        elif pick == 2:
            stats_screen()
        else:
            print(f"  {DIM}À bientôt — bon courage pour l'examen !{RESET}\n")
            return


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print()
