# Exercise authoring format

Each exercise lives in `data/exercises/<name>/` and contains:

## meta.json
```json
{
  "name": "<name>",
  "level": <1-20>,
  "type": "program" | "function",
  "files": ["<name>.c"],
  "allowed_functions": ["write"],
  "tests": [ {"args": ["arg1", "arg2"]}, ... ]
}
```
- `type: "program"`: the student writes a full program with `main`. The grader
  compiles the student's file and `ref.c` identically, runs both with each
  `tests[i].args` as argv, and diffs stdout byte-for-byte. Provide 6-12 tests
  covering edge cases: no argument, empty string `""`, whitespace-only,
  wrong number of args (0, 2, 3 args), special chars, long input.
  A test may also have `"stdin": "..."` if the program reads stdin.
- `type: "function"`: the student writes only the function (no main). Provide a
  `driver.c` containing `main` plus the function prototype; it must exercise
  the function on 8-20 deterministic cases (edge cases included: empty string,
  0, negative numbers, INT_MIN/INT_MAX where relevant, NULL is NOT tested)
  and print results with printf. The same driver is linked against `ref.c`
  and against the student's file; outputs are diffed. No `tests` field needed.
- `allowed_functions`: functions the STUDENT may call (checked with nm on the
  student's object only — the driver may use anything). Typical values:
  `["write"]` for display programs, `[]` for pure functions,
  `["malloc", "free"]` for allocating functions.

## subject.txt
Real 42 exam format, in English:
```
Assignment name  : <name>
Expected files   : <name>.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that ...

Examples:

$> ./<name> "input" | cat -e
output$
```
For functions, give the exact prototype. For list exercises, include the full
`ft_list.h` content in the subject and list it in Expected files.

## ref.c
Reference solution in strict 42 Norm style (tabs, snake_case, while loops,
declarations at top). MUST compile clean with `cc -Wall -Wextra -Werror` and
use only the allowed functions. For `function` type: no main.

## driver.c (function type only)
- Includes the prototype directly (do NOT include a student header, except
  list exercises which include "ft_list.h" shipped in the exercise dir).
- Deterministic output, no randomness, no timing.
- Print each case on its own line, e.g. `printf("case 3: [%s]\n", result);`
- For malloc-returning functions, print the returned content (and free it).
- Compiled with `-Wall -Wextra` (not -Werror) and `-I <exercise dir>`.

## Validation (mandatory)
From the repo root run:
```
python3 validate.py <name1> <name2> ...
```
Every exercise you author must print `OK`. Fix and re-run until they all pass.

## Study the three exemplars before writing anything
- `data/exercises/ft_print_alphabet/` (program, no args)
- `data/exercises/first_word/` (program with argv tests)
- `data/exercises/ft_strlen/` (function with driver)
