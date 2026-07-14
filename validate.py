#!/usr/bin/env python3
"""Self-test: grade every exercise's reference solution as a student rendu.

Every exercise must pass its own tests, otherwise the pool is broken.
Usage: python3 validate.py [exercise_name ...]
"""

import json
import os
import shutil
import sys

import examshell as ex

ROOT = os.path.dirname(os.path.abspath(__file__))
FAKE_RENDU = os.path.join(ROOT, ".validate_rendu-%d" % os.getpid())


def main():
    pool = ex.load_exercises()
    only = set(sys.argv[1:])
    names = sorted(only or pool)

    ex.RENDU_DIR = FAKE_RENDU
    failed = []
    for name in names:
        meta = pool.get(name)
        if meta is None:
            print(f"?? {name}: not found in pool")
            failed.append(name)
            continue
        rendu = os.path.join(FAKE_RENDU, name)
        shutil.rmtree(rendu, ignore_errors=True)
        os.makedirs(rendu)
        # the reference becomes the student's file(s)
        c_files = [f for f in meta["files"] if f.endswith(".c")]
        if len(c_files) != 1:
            print(f"KO {name}: expected exactly one .c file in meta 'files'")
            failed.append(name)
            continue
        shutil.copy(os.path.join(meta["dir"], "ref.c"),
                    os.path.join(rendu, c_files[0]))
        # non-.c expected files (e.g. ft_list.h) are shipped by the exercise
        for f in meta["files"]:
            if not f.endswith(".c"):
                shutil.copy(os.path.join(meta["dir"], f),
                            os.path.join(rendu, f))
        try:
            ex.grade(meta)
            print(f"OK {name} (level {meta['level']})")
        except ex.GradeFailure as f:
            print(f"KO {name}: {f.title}\n{f.detail[:600]}")
            failed.append(name)

    shutil.rmtree(FAKE_RENDU, ignore_errors=True)
    levels = ex.exercises_by_level(pool)
    print(f"\n{len(names) - len(failed)}/{len(names)} exercises OK")
    empty = [l for l in range(1, ex.TOTAL_LEVELS + 1) if l not in levels]
    if empty:
        print(f"Levels without exercises: {empty}")
    for lvl in sorted(levels):
        print(f"  level {lvl:2d}: {', '.join(sorted(levels[lvl]))}")
    sys.exit(1 if failed else 0)


if __name__ == "__main__":
    main()
