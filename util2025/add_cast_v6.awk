# Salva come add_cast_v6.awk
# Esegui con:
# awk -v func_name="set_something" -v target_cast_str="(char*)" -v replace_existing=0 -f add_cast_v6.awk IN > OUT
# awk -v func_name="set_something" -v target_cast_str="(float)" -v replace_existing=1 -f add_cast_v6.awk IN > OUT

BEGIN {
    in_func = 0
    buffer = ""

    # Default values
    if (func_name == "") func_name = "set_something"
    # Ora passiamo la stringa completa del cast, con le parentesi
    if (target_cast_str == "") target_cast_str = "(char*)"
    if (replace_existing == "") replace_existing = 0

    # Pattern per l'inizio della funzione target
    func_start_pattern = func_name "[[:space:]]*\\("

    # Pattern REGEX per cercare un QUALSIASI cast/parentesi (...) esistente
    # DOPO la seconda virgola. Cerca: virgola, spazi, '(', ..., ')', spazi...
    # Il contenuto tra parentesi può essere quasi qualsiasi cosa che non sia ')'
    # ma che assomigli vagamente a un tipo C (include * e spazi).
    existing_cast_regex = ",[[:space:]\n]*\\([[:alnum:]_*[:space:]]+\\)[[:space:]]*[^[:space:],)]"
    # Pattern REGEX per cercare parentesi generica DOPO la seconda virgola (più semplice)
    existing_paren_regex = ",[^,]*,[[:space:]\n]*\\("

    # Pattern REGEX per la *sostituzione* di un cast esistente (identifica il cast da rimuovere)
    # Cattura: 1=Prima del cast esistente, 2=Cast esistente (...), 3=Dopo il cast esistente
    replace_pattern = "(" func_name "[[:space:]]*\\([^,]*,[^,]*,[[:space:]\n]*)(\\([[:alnum:]_*[:space:]]+\\)[[:space:]\n]*)([^)]*\\))"

    print "# AWK Script V6 Config:" > "/dev/stderr"
    print "# Target function : " func_name > "/dev/stderr"
    print "# Target cast str : " target_cast_str > "/dev/stderr"
    print "# Replace existing: " replace_existing > "/dev/stderr"
}

# Funzione helper per trovare l'indice del carattere *dopo* la N-esima virgola
function find_nth_comma_pos(text, n,    i, count, pos) {
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
function process_buffer(   has_existing_cast, comma2_pos, arg3_start_pos, prefix, suffix, match_data ) {

    # Usiamo il regex più generico per vedere se c'è un blocco (...) dopo la 2a virgola
    has_existing_cast = match(buffer, existing_cast_regex)

    if (has_existing_cast) {
        # Trovato un blocco (...) che sembra un cast
        if (replace_existing == 1) {
            # Sostituisci il primo blocco (...) dopo la seconda virgola
            # Usiamo sub() perché vogliamo sostituire solo la *prima* occorrenza
            # trovata che assomiglia a un cast. gsub() sostituirebbe tutto.
            # Il pattern cerca: virgola, spazi, APRI_P, qualsiasi_cosa_non_CHIUDI_P, CHIUDI_P, spazi
            if (sub(/,[[:space:]\n]*\([[:alnum:]_*[:space:]]+\)[[:space:]]*/, ", " target_cast_str " ", buffer)) {
                 print "# INFO V6: Replaced existing cast in:" > "/dev/stderr"
                 # print buffer > "/dev/stderr" # Debug
            } else {
                 print "# WARNING V6: gsub failed to replace existing cast in:" > "/dev/stderr"
                 # print buffer > "/dev/stderr" # Debug
            }
        } else {
            # Non sostituire, stampa com'è
             print "# INFO V6: Existing cast/parentheses found, not replacing:" > "/dev/stderr"
             # print buffer > "/dev/stderr" # Debug
        }
    } else {
        # Nessun blocco (...) trovato all'inizio del 3° arg, aggiungi il cast
        comma2_pos = find_nth_comma_pos(buffer, 2)
        if (comma2_pos > 0) {
            arg3_start_pos = find_first_nonspace(buffer, comma2_pos)
            if (arg3_start_pos > 0) {
                prefix = substr(buffer, 1, arg3_start_pos - 1) # Parte prima dell'arg3 (incl. spazi dopo virgola)
                suffix = substr(buffer, arg3_start_pos)        # Arg3 e il resto
                buffer = prefix target_cast_str " " suffix     # Inserisci cast target e uno spazio
                print "# INFO V6: Added cast to:" > "/dev/stderr"
                # print buffer > "/dev/stderr" # Debug
            } else {
                 print "# WARNING V6: No non-space found after second comma:" > "/dev/stderr"
                 # print buffer > "/dev/stderr" # Debug
            }
        } else {
             print "# WARNING V6: Could not find second comma:" > "/dev/stderr"
             # print buffer > "/dev/stderr" # Debug
        }
    }

    # Stampa il buffer finale (modificato o no)
    print buffer
}

