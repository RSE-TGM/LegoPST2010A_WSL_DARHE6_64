# Salva come add_cast_v3.awk
# Esegui con:
# awk -v func_name="set_something" -v cast_type="char" -v replace_existing=0 -f add_cast_v3.awk IN > OUT
# awk -v func_name="get_something" -v cast_type="void" -v replace_existing=1 -f add_cast_v3.awk IN > OUT

BEGIN {
  in_func = 0
  buffer = ""
  needs_cast = 0
  needs_replace = 0 # Nuovo flag per sapere se sostituire un cast esistente

  # --- Valori di Default (se non passati con -v) ---
  if (func_name == "") func_name = "set_something" # Nome funzione target
  if (cast_type == "") cast_type = "char"          # Tipo di cast da aggiungere/usare ('char' o 'void')
  if (replace_existing == "") replace_existing = 0 # Flag: 0=non sostituire esistenti, 1=sostituisci

  # Costruisci il cast desiderato
  target_cast = "(" cast_type "*)"

  # Pattern per cercare l'inizio della funzione target
  func_start_pattern = func_name "[[:space:]]*\\("

  # Pattern REGEX per cercare un cast esistente (char* o void*) all'inizio del 3° arg
  existing_cast_pattern = func_name "[[:space:]]*\\([^,]*,[^,]*,[[:space:]\n]*\\((char|void)\\*\\)"
  # Pattern REGEX per cercare parentesi generica all'inizio del 3° arg
  existing_paren_pattern = func_name "[[:space:]]*\\([^,]*,[^,]*,[[:space:]\n]*\\([^)]*\\)[[:space:]\n]*\\)"

  # Pattern REGEX per *catturare* un cast esistente (per la sostituzione)
  # Cattura: 1=Prima del cast, 2=Tipo cast esistente, 3=Dopo il cast
  replace_pattern = "(" func_name "[[:space:]]*\\([^,]*,[^,]*,[[:space:]\n]*\\()(" char "|" void ")(\\*\\)[[:space:]\n]*)([^)]*\\))"

  print "# AWK Script Config:" > "/dev/stderr"
  print "# Target function: " func_name > "/dev/stderr"
  print "# Target cast    : " target_cast > "/dev/stderr"
  print "# Replace existing: " replace_existing > "/dev/stderr"

}

# Funzione helper per trovare la posizione N-esima di una virgola
function find_nth_comma_pos(text, n,   count, pos, last_pos) { # Variabili locali awk
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

# Funzione helper per inserire il cast
function insert_cast(text,   comma2_pos, prefix, remainder, start_arg3, suffix) {
    comma2_pos = find_nth_comma_pos(text, 2)
    if (comma2_pos > 0) {
        prefix = substr(text, 1, comma2_pos)
        remainder = substr(text, comma2_pos)
        start_arg3 = match(remainder, /[^[:space:]\n]/) # Cerca primo non-spazio/newline
        if (start_arg3 > 0) {
            prefix = prefix substr(remainder, 1, RSTART - 1) # Include spazi/newline
            suffix = substr(remainder, RSTART)
            return prefix target_cast suffix # Usa target_cast globale
        }
    }
    return text # Non modificato se c'è un problema
}

# Funzione helper per sostituire cast esistente
function replace_cast(text) {
    # Usa il pattern definito nel BEGIN per sostituire
    # \1 è la parte prima del cast, \4 è la parte dopo il cast esistente
    gsub(replace_pattern, "\\1" target_cast "\\4", text)
    return text
}


{ # Blocco principale per ogni riga
  current_line = $0
  if (!in_func) {
    if (match($0, func_start_pattern)) {
      buffer = $0
      needs_cast = 1    # Assumiamo che serva
      needs_replace = 0 # Assumiamo che non serva sostituire

      # Controlla se ha già cast (char/void) o parentesi generica
      has_existing_cast = match(buffer, existing_cast_pattern)
      has_existing_paren = match(buffer, existing_paren_pattern)

      if (has_existing_cast) {
          needs_cast = 0 # Non serve aggiungere
          if (replace_existing == 1) {
              needs_replace = 1 # Ma serve sostituire
          }
      } else if (has_existing_paren) {
          needs_cast = 0 # Ha parentesi generiche, non toccare per sicurezza
          needs_replace = 0
      }
      # Altrimenti needs_cast rimane 1 e needs_replace rimane 0

      if (match(buffer, /\)/)) {
         # Finisce sulla stessa riga
         if (needs_replace) {
             buffer = replace_cast(buffer)
         } else if (needs_cast) {
             buffer = insert_cast(buffer)
         }
         # Stampa buffer (modificato o no) e resetta
         print buffer
         buffer = ""
         in_func = 0
         needs_cast = 0
         needs_replace = 0
      } else {
         # Non finisce qui
         in_func = 1
         # flags needs_cast/needs_replace rimangono impostati
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
      # Il flag needs_cast/needs_replace è stato impostato all'inizio
      if (needs_replace) {
          buffer = replace_cast(buffer)
      } else if (needs_cast) {
          buffer = insert_cast(buffer)
      }
      # Stampa buffer (modificato o no) e resetta
      print buffer
      buffer = ""
      in_func = 0
      needs_cast = 0
      needs_replace = 0
    }
  }
}

END {
    if (in_func && buffer != "") {
        # Potrebbe essere necessario applicare logica replace/insert anche qui
        # ma è più complesso determinare lo stato corretto senza la fine
        print "# WARNING: File ended while inside a function call:" > "/dev/stderr"
        print buffer # Stampa il buffer non processato in questo caso limite
    }
}

