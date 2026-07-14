#!/bin/sh
# Installe la commande globale `42exam` (sans sudo — compatible Macs de 42).
set -e
REPO="$(cd "$(dirname "$0")" && pwd)"
BIN="$HOME/.local/bin"

mkdir -p "$BIN"
ln -sf "$REPO/42exam" "$BIN/42exam"
echo "✔ Commande installée : $BIN/42exam -> $REPO/42exam"

case ":$PATH:" in
*":$BIN:"*)
	echo "✔ $BIN est déjà dans ton PATH."
	echo "→ Tape : 42exam"
	;;
*)
	RC="$HOME/.zshrc"
	[ -n "$BASH_VERSION" ] && RC="$HOME/.bashrc"
	if ! grep -qs '\.local/bin' "$RC"; then
		printf '\nexport PATH="$HOME/.local/bin:$PATH"\n' >>"$RC"
		echo "✔ PATH mis à jour dans $RC"
	fi
	echo "→ Ouvre un nouveau terminal (ou : source $RC) puis tape : 42exam"
	;;
esac
