#!/bin/bash

# Controlla se la variabile d'ambiente LEGOROOT è impostata
if [ -z "$LEGOROOT" ]; then
  echo "Errore: La variabile d'ambiente LEGOROOT non è impostata." >&2
  echo "Impostala alla directory radice del progetto prima di eseguire questo script." >&2
  exit 1
fi

# Nome del file da leggere, costruito a partire da LEGOROOT
VERSION_FILE="$LEGOROOT/version.h"

# -- NUOVA SEZIONE: CONTROLLO E GENERAZIONE AUTOMATICA --
# Verifica se il file esiste.
if [ ! -f "$VERSION_FILE" ]; then
  echo "Info: Il file di versione '$VERSION_FILE' non è stato trovato."
  echo "Info: Tento di generarlo ora eseguendo 'make'..."
  
  # Cambia directory verso la radice del progetto per eseguire 'make'
  # Il Makefile sa dove creare version.h, quindi non dobbiamo specificare il path
  # L'opzione -C esegue make in quella directory
  if ! make -s -C "$LEGOROOT" -f Makefile.mk version.h; then
    echo "Errore: Impossibile generare '$VERSION_FILE'." >&2
    echo "Assicurati che 'git' e 'make' siano installati e che '$LEGOROOT' sia la directory corretta." >&2
    exit 1
  fi
  echo "Info: File '$VERSION_FILE' generato con successo."
fi
# -- FINE NUOVA SEZIONE --

# A questo punto, il file dovrebbe esistere
if [ ! -f "$VERSION_FILE" ]; then
  # Questo è un controllo di sicurezza extra
  echo "Errore: Non è stato possibile trovare o creare '$VERSION_FILE'." >&2
  exit 1
fi

echo "------- Ambiente LegoPST---------"
echo "LEGOROOT: $LEGOROOT"
echo "File: $VERSION_FILE"
echo "--------------------------------"

# Usa awk per processare il file e mostrare le informazioni
awk '
  /^#define / {
    nome_macro = $2
    valore = ""
    for (i = 3; i <= NF; i++) {
      valore = valore (i == 3 ? "" : " ") $i
    }
    
    # Rimuovi le virgolette dal valore per una visualizzazione più pulita
    gsub(/"/, "", valore)

    # Stampa in un formato più leggibile
    if (nome_macro == "GIT_VERSION_STRING") {
        printf "%-20s: %s\n", "Versione Git", valore
    } else if (nome_macro == "BUILD_NUMBER") {
        printf "%-20s: %s\n", "Numero Build", valore
    } else if (nome_macro == "BUILD_DATE_STRING") {
        printf "%-20s: %s\n", "Data Build", valore
    }
  }
' "$VERSION_FILE"

echo "--------------------------------"
exit 0
