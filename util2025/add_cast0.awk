# Salva come add_cast_v2.awk
BEGIN {
  in_func = 0
  buffer = ""
  needs_cast = 0 # Flag per sapere se il buffer corrente necessita del cast
}

# Funzione helper per trovare la posizione N-esima di una virgola
# Ritorna l'indice del carattere *dopo* la virgola, o 0 se non trovata
function find_nth_comma_pos(text, n) {
    count = 0
    pos = 0
    last_pos = 0
    while ((pos = index(substr(text, last_pos + 1), ",")) > 0) {
        last_pos += pos
        count++
        if (count == n) {
            return last_pos + 1 # Posizione *dopo* la N-esima virgola
        }
    }
    return 0 # Non trovata
}

{
  current_line = $0
  if (!in_func) {
    if (match($0, /set_something[[:space:]]*\(/)) {
      buffer = $0
      needs_cast = 1 # Assumiamo inizialmente che serva il cast

      # Controlla subito se ha già un cast (char* o void*) o parentesi generica
      if (match(buffer, /set_something[[:space:]]*\([^,]*,[^,]*,[[:space:]\n]*\((char|void)\*\)/) || \
          match(buffer, /set_something[[:space:]]*\([^,]*,[^,]*,[[:space:]\n]*\([^)]*\)[[:space:]\n]*\)/)) {
          needs_cast = 0 # Trovato cast/parentesi, non modificare
      }

      if (match(buffer, /\)/)) {
         # Finisce sulla stessa riga
         if (needs_cast) {
             comma2_pos = find_nth_comma_pos(buffer, 2)
             if (comma2_pos > 0) {
                 # Inserisci il cast dopo la seconda virgola e spazi
                 prefix = substr(buffer, 1, comma2_pos)
                 # Trova il primo carattere non-spazio dopo la virgola
                 remainder = substr(buffer, comma2_pos)
                 start_arg3 = match(remainder, /[^[:space:]]/)
                 if (start_arg3 > 0) {
                     prefix = prefix substr(remainder, 1, RSTART - 1) # Include gli spazi
                     suffix = substr(remainder, RSTART)
                     buffer = prefix "(char*)" suffix
                 } else {
                     # Caso strano: solo spazi dopo la virgola? Non modificare
                     needs_cast = 0
                 }
             } else {
                 # Meno di 2 virgole? Strano, non modificare
                 needs_cast = 0
             }
         }
         print buffer
         buffer = ""
         in_func = 0
         needs_cast = 0
      } else {
         # Non finisce qui
         in_func = 1
         # Needs_cast rimane impostato da sopra
      }
    } else {
      # Riga normale
      print current_line
    }
  } else {
    # Dentro una funzione multi-riga
    buffer = buffer "\n" $0
    if (match(buffer, /\)/)) {
      # Fine funzione multi-riga trovata
      # Il flag needs_cast è stato impostato quando abbiamo trovato l'inizio
      if (needs_cast) {
          comma2_pos = find_nth_comma_pos(buffer, 2)
          if (comma2_pos > 0) {
              prefix = substr(buffer, 1, comma2_pos)
              remainder = substr(buffer, comma2_pos)
              start_arg3 = match(remainder, /[^[:space:]\n]/) # Cerca primo non-spazio/newline
              if (start_arg3 > 0) {
                  prefix = prefix substr(remainder, 1, RSTART - 1)
                  suffix = substr(remainder, RSTART)
                  buffer = prefix "(char*)" suffix
              } else {
                   needs_cast = 0 # Non modificare
              }
          } else {
               needs_cast = 0 # Non modificare
          }
      }
      # Stampa buffer (modificato o no) e resetta
      print buffer
      buffer = ""
      in_func = 0
      needs_cast = 0
    }
  }
}

END {
    if (in_func && buffer != "") {
        # Se il file finisce inaspettatamente, stampa il buffer non modificato
        # o applica logica simile a sopra se necessario (ma è un caso limite)
        print buffer
    }
}

