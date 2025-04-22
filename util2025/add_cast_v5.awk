# Salva come add_cast_v5.awk
BEGIN {
    in_func = 0
    buffer = ""

    # Default values
    if (func_name == "") func_name = "set_something"
    if (cast_type == "") cast_type = "char"
    if (replace_existing == "") replace_existing = 0

    target_cast = "(" cast_type "*)"
    func_start_pattern = func_name "[[:space:]]*\\("

    # Pattern REGEX SOLO per cercare un cast (char* o void*) esistente
    # DOPO la seconda virgola. Più semplice possibile.
    existing_cast_regex = ",[^,]*,[[:space:]\n]*\\((char|void)\\*\\)"
    # Pattern REGEX SOLO per cercare parentesi generica DOPO la seconda virgola
    existing_paren_regex = ",[^,]*,[[:space:]\n]*\\("

    print "# AWK Script V5 Config:" > "/dev/stderr"
    print "# Target function: " func_name > "/dev/stderr"
    print "# Target cast    : " target_cast > "/dev/stderr"
    print "# Replace existing: " replace_existing > "/dev/stderr"
}

# Funzione helper per trovare l'indice del carattere *dopo* la N-esima virgola
function find_nth_comma_pos(text, n,    i, count, pos) { # Variabili locali awk
    count = 0
    for (i = 1; i <= length(text); ++i) {
        if (substr(text, i, 1) == ",") {
            count++
            if (count == n) {
                return i + 1
            }
        }
    }
    return 0 # Non trovata
}

# Funzione helper per trovare l'indice del primo carattere non-spazio/newline
function find_first_nonspace(text, start_pos,   i) {
     for (i = start_pos; i <= length(text); ++i) {
         if (substr(text, i, 1) ~ /[^[:space:]\n]/) {
             return i
         }
     }
     return 0 # Non trovato (o solo spazi/newline)
}

{ # Blocco principale per ogni riga
    current_line = $0
    if (!in_func) {
        if (match($0, func_start_pattern)) {
            buffer = $0
            if (match(buffer, /\)/)) {
                # Finisce sulla stessa riga -> Processa subito
                process_buffer()
                buffer = ""
                in_func = 0
            } else {
                # Inizio multi-riga
                in_func = 1
            }
        } else {
            # Riga normale
            print current_line
        }
    } else {
        # Dentro una funzione multi-riga
        buffer = buffer "\n" $0
        if (match(buffer, /\)/)) {
            # Fine funzione multi-riga trovata -> Processa
            process_buffer()
            buffer = ""
            in_func = 0
        }
    }
}

END {
    if (in_func && buffer != "") {
        print "# WARNING: File ended while inside a function call:" > "/dev/stderr"
        print buffer # Stampa non processato
    }
}

# Funzione per processare il buffer accumulato
function process_buffer(   has_existing_cast, has_existing_paren, comma2_pos, arg3_start_pos, prefix, suffix, cast_to_replace_regex) {

    has_existing_cast = match(buffer, existing_cast_regex)
    has_existing_paren = match(buffer, existing_paren_regex)

    if (has_existing_cast) {
        # Trovato cast (char*) o (void*)
        if (replace_existing == 1) {
            # Sostituisci usando gsub in modo mirato
            # Costruisci il regex specifico per il cast da rimpiazzare
            cast_to_replace_regex = "\\([[:space:]]*(char|void)[[:space:]]*\\*[[:space:]]*\\)"
            gsub(cast_to_replace_regex, target_cast, buffer)
            print "# INFO V5: Replaced existing cast in:" > "/dev/stderr"
            # print buffer > "/dev/stderr" # Debug
        } else {
            # Non fare nulla
             print "# INFO V5: Existing cast found, not replacing:" > "/dev/stderr"
             # print buffer > "/dev/stderr" # Debug
        }
    } else if (has_existing_paren) {
        # Trovata parentesi generica dopo la seconda virgola, non fare nulla
        print "# INFO V5: Existing parentheses found, not adding cast:" > "/dev/stderr"
        # print buffer > "/dev/stderr" # Debug
    } else {
        # Nessun cast o parentesi trovati, aggiungi il cast
        comma2_pos = find_nth_comma_pos(buffer, 2)
        if (comma2_pos > 0) {
            arg3_start_pos = find_first_nonspace(buffer, comma2_pos)
            if (arg3_start_pos > 0) {
                prefix = substr(buffer, 1, arg3_start_pos - 1) # Parte prima dell'arg3
                suffix = substr(buffer, arg3_start_pos)        # Arg3 e il resto
                buffer = prefix target_cast " " suffix         # Inserisci cast e uno spazio
                print "# INFO V5: Added cast to:" > "/dev/stderr"
                # print buffer > "/dev/stderr" # Debug
            } else {
                 print "# WARNING V5: No non-space found after second comma:" > "/dev/stderr"
                 # print buffer > "/dev/stderr" # Debug
            }
        } else {
             print "# WARNING V5: Could not find second comma:" > "/dev/stderr"
             # print buffer > "/dev/stderr" # Debug
        }
    }

    # Stampa il buffer finale (modificato o no)
    print buffer
}

