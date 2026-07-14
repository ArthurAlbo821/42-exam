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
	# le shell de connexion de l'utilisateur, pas celui qui exécute ce script
	case "$(basename "${SHELL:-/bin/zsh}")" in
	bash) RC="$HOME/.bashrc" ;;
	*) RC="$HOME/.zshrc" ;;
	esac
	if ! grep -qs '^[^#]*\.local/bin' "$RC"; then
		printf '\nexport PATH="$HOME/.local/bin:$PATH"\n' >>"$RC"
		echo "✔ PATH mis à jour dans $RC"
	fi
	echo "→ Ouvre un nouveau terminal (ou : source $RC) puis tape : 42exam"
	;;
esac
