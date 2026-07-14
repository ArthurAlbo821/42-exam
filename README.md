# 42 EXAM — Simulateur d'Examen Final de la Piscine

Un simulateur fidèle de l'examen final de la piscine : 20 niveaux de
difficulté croissante (C00 → C08), un exercice tiré au hasard par niveau,
5 points par exercice, 100 points au total, chrono comme le vrai.

## Installation (2 minutes)

```bash
git clone <url-du-repo> && cd <repo>
./install.sh        # installe la commande globale 42exam (sans sudo)
42exam
```

Sans installation, `./42exam` depuis le dossier du repo marche aussi.
Prérequis : `python3` et `cc` (déjà présents sur les Macs de 42).

Au premier lancement, le programme crée automatiquement tes dossiers de
travail locaux (`rendu/` pour l'examen, `entrainement/` pour le drill,
sessions, stats) — ils restent sur ta machine et ne sont jamais commités.

## Le menu

`42exam` ouvre un menu navigable aux flèches ↑↓ :

- **🏊 Examen blanc** — simulation complète (choix 4h révision ou 8h
  conditions réelles du final ; reprise d'un examen en cours proposée)
- **💪 Entraînement** — répétition en boucle (zone 60 pts niveaux 1-12,
  ou zone étendue : tout sauf les listes chaînées/C08)
- **📊 Statistiques** — tableau de maîtrise, records, historique des scores

Raccourcis directs : `./exam` (examen, `EXAM_HOURS=8` pour 8h) et
`./drill` (entraînement zone 60 pts).

- Un examen en cours est proposé à la reprise au lancement (le timer est en
  pause tant que le programme est fermé).
- Réponds `n` pour démarrer un nouvel examen (nouveau tirage d'exercices).

## Mode entraînement — garantir les 60 points

```bash
./drill
```

Fait tourner en boucle les **49 exercices des niveaux 1-12** (la zone des
60 points, rien au-delà de malloc) avec une rotation « faiblesses d'abord » :

- les exercices jamais faits arrivent en premier (niveaux faciles d'abord),
  puis ceux ratés, passés ou réussis lentement ;
- un exercice **acquis** (2 réussites dont 1 du premier coup) revient en
  révision 1 tirage sur 6 ;
- chaque exercice est **chronométré**, ton record est enregistré ;
- quand un exercice revient, ton ancienne solution est archivée dans
  `.drill_archive/` et tu repars de zéro.

Commandes : `grademe`, `skip` (passe, compte comme faiblesse), `stats`
(tableau de maîtrise ✓/~/✗ des 49 exercices avec tes records), `subject`,
`status`, `exit` (chrono en pause, reprise au prochain lancement).

Objectif : tableau `stats` tout en ✓ — les 60 premiers points de l'examen
deviennent automatiques.

## Déroulement

1. Le sujet du niveau s'affiche dans le terminal, et le dossier de
   l'exercice est préparé : `subject.txt` + fichiers `.c` vides déjà créés.
2. Code ta solution dans `rendu/<nom_exercice>/` (examen) ou
   `entrainement/<nom_exercice>/` (drill). Tape **`code`** dans le terminal
   pour ouvrir l'exercice dans VS Code. Ensuite, à chaque exercice validé,
   VS Code **bascule tout seul** sur le suivant dans la même fenêtre
   (l'ancien exercice disparaît de l'explorateur).
3. Tape `grademe` dans l'examshell :
   - compilation `cc -Wall -Wextra -Werror` (le moindre warning = échec),
   - vérification des fonctions interdites (via `nm`),
   - tests comparés à une solution de référence (diff byte à byte).
4. **OK** → +5 points, niveau suivant. **KO** → le détail de l'échec est
   écrit dans le `trace.txt` du dossier de l'exercice — visible directement
   dans VS Code à côté de ton code, et supprimé dès que ça passe. Corrige et
   retente (essais illimités).

## Commandes de l'examshell

| Commande  | Effet |
|-----------|-------|
| `grademe` | corrige l'exercice en cours |
| `subject` | réaffiche le sujet |
| `code`    | ouvre le dossier de l'exercice dans VS Code |
| `status`  | score, niveau, essais, temps restant |
| `finish`  | termine l'examen et affiche le score final |
| `exit`    | sauvegarde et quitte (timer en pause) |

Un nouvel examen archive l'ancien `rendu/` dans `.exam_archive/` et
repart d'un dossier propre. En drill, `entrainement/` ne contient que
l'exercice en cours (le reste part dans `.drill_archive/`).

## Barème

- 20 niveaux × 5 points = 100 points.
- L'historique de tes examens terminés est dans `history.txt`.

## Le pool d'exercices

89 exercices issus du vrai pool de l'examen (examshell/grademe), vérifiés
contre plusieurs sources publiques (dépôts GitHub du pool réel + récits
d'examens finaux de pisciners), répartis sur 20 niveaux : affichage et
boucles (C00-C01), chaînes et pointeurs (C02-C04), programmes à arguments
(C06), malloc (C07), structures et listes chaînées (C08), jusqu'aux
classiques les plus durs des niveaux hauts du vrai final (`ft_split`,
`sort_list`, `brainfuck`, `rpn_calc`, `infin_mult`, `count_island`).

Pour vérifier l'intégrité du pool : `python3 validate.py`.

## Structure

```
42exam            le menu (aussi installable en commande globale)
examshell.py      le simulateur d'examen
drill.py          le mode entraînement
validate.py       auto-test du pool (les solutions de référence doivent passer)
data/exercises/   un dossier par exercice (sujet, solution de référence, tests)
rendu/            TES solutions d'examen (créé au lancement)
entrainement/     l'exercice de drill en cours (créé au lancement)
history.txt       scores des examens terminés

```
