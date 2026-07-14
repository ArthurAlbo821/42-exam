"""Terminal UI helpers for the exam simulator — pure ANSI, zero deps."""

import sys
import threading
import time

RESET = "\033[0m"
BOLD = "\033[1m"
DIM = "\033[2m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
CYAN = "\033[36m"
MAGENTA = "\033[35m"

W = 62  # inner width of frames and bars alignment

BANNER = r"""
    ██╗  ██╗██████╗   ███████╗██╗  ██╗ █████╗ ███╗   ███╗
    ██║  ██║╚════██╗  ██╔════╝╚██╗██╔╝██╔══██╗████╗ ████║
    ███████║ █████╔╝  █████╗   ╚███╔╝ ███████║██╔████╔██║
    ╚════██║██╔═══╝   ██╔══╝   ██╔██╗ ██╔══██║██║╚██╔╝██║
         ██║███████╗  ███████╗██╔╝ ██╗██║  ██║██║ ╚═╝ ██║
         ╚═╝╚══════╝  ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝"""


def show_banner(subtitle):
    print(f"{CYAN}{BANNER}{RESET}")
    print(f"{DIM}{subtitle.center(W)}{RESET}\n")


def frame(left, right=""):
    """Rounded one-line frame:  ╭───╮ │ left     right │ ╰───╯"""
    gap = W - 2 - len(left) - len(right)
    if gap < 1:
        left = left[:W - 4 - len(right)] + "…"
        gap = W - 2 - len(left) - len(right)
    print(f"{CYAN}╭{'─' * (W - 2)}╮{RESET}")
    print(f"{CYAN}│{RESET} {BOLD}{left}{RESET}{' ' * (gap - 2)}"
          f"{DIM}{right}{RESET} {CYAN}│{RESET}")
    print(f"{CYAN}╰{'─' * (W - 2)}╯{RESET}")


def hr():
    print(f"{DIM}{'─' * W}{RESET}")


def _bar_color(ratio):
    if ratio >= 0.999:
        return MAGENTA
    if ratio >= 0.6:
        return GREEN
    if ratio >= 0.3:
        return YELLOW
    return RED


def bar(label, value, total, width=24, suffix=None):
    ratio = 0 if total == 0 else min(1.0, value / total)
    filled = round(ratio * width)
    color = _bar_color(ratio)
    suffix = suffix if suffix is not None else f"{value}/{total}"
    print(f" {BOLD}{label:<6}{RESET}{color}{'█' * filled}{RESET}"
          f"{DIM}{'░' * (width - filled)}{RESET}  {BOLD}{suffix}{RESET}")


def dots(label, value, total, suffix=None):
    color = _bar_color(0 if total == 0 else value / total)
    suffix = suffix if suffix is not None else f"{value}/{total}"
    print(f" {BOLD}{label:<6}{RESET}{color}{'●' * value}{RESET}"
          f"{DIM}{'○' * (total - value)}{RESET}  {BOLD}{suffix}{RESET}")


class Spinner:
    """`with Spinner('label'):` — braille animation while a block runs."""

    FRAMES = "⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏"

    def __init__(self, label):
        self.label = label
        self.enabled = sys.stdout.isatty()
        self._stop = threading.Event()
        self._thread = None

    def _spin(self):
        i = 0
        while not self._stop.is_set():
            frame = self.FRAMES[i % len(self.FRAMES)]
            sys.stdout.write(f"\r {CYAN}{frame}{RESET} {self.label}…")
            sys.stdout.flush()
            self._stop.wait(0.08)
            i += 1

    def __enter__(self):
        if self.enabled:
            self._thread = threading.Thread(target=self._spin, daemon=True)
            self._thread.start()
        else:
            print(f" {CYAN}·{RESET} {self.label}…")
        return self

    def __exit__(self, *exc):
        if self.enabled:
            self._stop.set()
            self._thread.join()
            sys.stdout.write("\r\033[K")
            sys.stdout.flush()
        return False


def ok(message, points=""):
    pts = f"{GREEN}{BOLD}{points}{RESET}" if points else ""
    gap = W - 7 - len(message) - len(points)
    print(f"\n {GREEN}{BOLD}✔ OK{RESET} · {message}{' ' * max(1, gap)}{pts}")


def ko(title):
    print(f"\n {RED}{BOLD}✘ KO{RESET} · {RED}{title}{RESET}")


def failure_detail(detail):
    """Colorized diff: expected in green, student output in red."""
    mode = None
    is_diff = "Expected output:" in detail or detail.startswith("--- ")
    for line in detail.splitlines():
        if line.startswith("--- "):
            mode = None
            print(f"\n {DIM}──{RESET} {BOLD}{line[4:]}{RESET}")
        elif line == "Expected output:":
            mode = "exp"
            print(f"   {GREEN}attendu{RESET}")
        elif line == "Your output:":
            mode = "got"
            print(f"   {RED}ta sortie{RESET}")
        elif mode == "exp":
            print(f"   {GREEN}│{RESET} {line}")
        elif mode == "got":
            print(f"   {RED}│{RESET} {line}")
        elif is_diff:
            print(f"   {line}")
        else:
            print(f"   {DIM}{line}{RESET}")


def celebrate(message):
    stars = "✦ ✦ ✦"
    line = f"{stars}  {message}  {stars}"
    print(f"\n{MAGENTA}{BOLD}{line.center(W)}{RESET}")
    print(f"{MAGENTA}{('─' * len(line)).center(W)}{RESET}\n")
