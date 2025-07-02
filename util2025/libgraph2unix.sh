#!/bin/bash


NOME_DIRECTORY_RICHIESTO="libgraph"

NOME_DIRECTORY_CORRENTE=$(basename "$PWD")

# 3. Confronta il nome della directory corrente con quello richiesto.
if [ "$NOME_DIRECTORY_CORRENTE" != "$NOME_DIRECTORY_RICHIESTO" ]; then
  # Se non corrispondono, stampa un messaggio di errore ed esci.
  echo "Errore: Questo script deve essere eseguito dalla directory '$NOME_DIRECTORY_RICHIESTO'." >&2
  echo "Directory corrente: '$NOME_DIRECTORY_CORRENTE'." >&2
  exit 1 # Esce con un codice di errore (qualsiasi valore diverso da 0).
fi

# --- FINE CONTROLLO DIRECTORY ---

# Se il controllo è superato, lo script continua da qui.
echo "Controllo superato. Lo script è in esecuzione nella directory corretta."
find . -name *.txt | xargs dos2unix
find . -name *.i5 | xargs dos2unix
find . -name *.tcl | xargs dos2unix
find . -name *.pi3 | xargs dos2unix
find . -name *.pi4 | xargs dos2unix

echo "Conversione dos2unix completata con successo."
exit 0 # Esce con un codice di successo (0).dos2unix connect.dat  

