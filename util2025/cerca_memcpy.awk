# Salva come find_memcpy_brace_v3.awk
# Esegui: awk -f find_memcpy_brace_v3.awk *.c

BEGIN {
    prev_memcpy_line = ""
    prev_memcpy_lineno = 0
    in_multiline_comment = 0
}

{
    current_line_orig = $0 # Memorizza riga originale per output
    current_line = $0      # Copia su cui lavorare
    current_lineno = FNR

    # 1. Gestione Commenti Multi-riga (come in v2)
    if (in_multiline_comment) {
        if (current_line ~ /\*\//) {
            in_multiline_comment = 0
            sub(/.*\*\//, "", current_line)
            if (current_line ~ /^[[:space:]]*$/) { next }
        } else {
            next
        }
    }
    if (current_line ~ /\/\*/ && ! (current_line ~ /\*\// && index(current_line, "/*") < index(current_line, "*/"))) {
         original_before_comment = current_line
         sub(/\/\*.*/, "", current_line)
         if (current_line !~ /[^[:space:]]/) {
             # Se non c'è codice prima di /*, ma commento non finisce,
             # imposta flag e salta il resto dell'analisi per questa riga
             in_multiline_comment = 1
             # Resetta il check memcpy se era attivo, il commento interrompe
             prev_memcpy_line = ""
             prev_memcpy_lineno = 0
             next
         }
         # Se c'è codice prima, processalo e imposta flag per dopo
         in_multiline_comment = 1
         # NON fare next qui, continua a processare la parte prima di /*
    }
    # Rimuovi commenti su riga singola /* ... */ e //
    gsub(/\/\*.*?\*\//, " ", current_line);
    sub(/\/\/.*$/, "", current_line);

    # 2. Ignora righe vuote risultanti
    if (current_line ~ /^[[:space:]]*$/) {
        # Non resettare prev_memcpy_line
        next
    }

    # --- Logica Principale ---

    # 3. Controlla se la RIGA CORRENTE (pulita) inizia con {
    #    E se stavamo aspettando una graffa dopo un memcpy
    if (prev_memcpy_line != "" && current_line ~ /^[[:space:]]*\{/) {
        print "POTENTIAL ISSUE FOUND (Missing semicolon before brace?):"
        print "  " FILENAME ":" prev_memcpy_lineno ": " prev_memcpy_line
        print "  " FILENAME ":" current_lineno ": " $0 # Stampa riga originale con {
        print "---"
        # Resetta dopo aver segnalato
        prev_memcpy_line = ""
        prev_memcpy_lineno = 0
        next
    }

    # 4. Se la riga precedente era sospetta, ma questa non è una graffa,
    #    decidi se resettare o meno. Non resettare se sembra una dichiarazione
    #    o una direttiva #. Resetta per altre istruzioni di codice.
    if (prev_memcpy_line != "") {
        # Pattern euristico per dichiarazioni comuni o direttive
        # (tipi base, struct, enum, typedef, extern, static, #)
        if (current_line ~ /^[[:space:]]*(int|void|char|float|double|long|short|unsigned|signed|struct|enum|typedef|extern|static|#)/ ) {
            # Probabilmente una dichiarazione o preprocessore, NON resettare ancora.
            # Potrebbe essere il caso dell'esempio: memcpy() \n int x \n { ...
            # print "DEBUG: Declaration/preprocessor line " FNR ", preserving memcpy check" > "/dev/stderr"
            ; # No action, mantieni prev_memcpy_line
        } else {
            # Altro tipo di codice (assegnazione, chiamata funzione, if, while, etc.)
            # Questo interrompe la sequenza sospetta. Resetta.
             # print "DEBUG: Resetting memcpy check after code line " FNR > "/dev/stderr"
             prev_memcpy_line = ""
             prev_memcpy_lineno = 0
        }
    }

    # 5. Controlla se QUESTA riga (pulita) è un nuovo memcpy sospetto
    #    (contiene memcpy(...) e non finisce con ;)
    #    Questo viene fatto *dopo* il check di reset eventuale sopra.
    if (current_line ~ /memcpy\s*\([^)]*\)/ && current_line !~ /;\s*$/) {
        # Trovata una riga sospetta, memorizza la riga ORIGINALE
        prev_memcpy_line = $0 # Memorizza originale
        prev_memcpy_lineno = current_lineno
        # print "DEBUG: Found potential memcpy line " FNR ": " $0 > "/dev/stderr"
    }
}

END {
    # Questo END block non è strettamente necessario per il rilevamento,
    # ma può segnalare se il file finisce con un memcpy sospetto non risolto.
    if (prev_memcpy_line != "") {
        print "WARNING: File " FILENAME " ended with potential unclosed memcpy issue at line " prev_memcpy_lineno ":" > "/dev/stderr"
        print "  " prev_memcpy_line > "/dev/stderr"
    }
}

