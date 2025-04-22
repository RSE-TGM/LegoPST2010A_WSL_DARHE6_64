Fantastico che funzioni! Rendiamolo parametrico.

Useremo le variabili di `awk` passate tramite l'opzione `-v` sulla riga di comando.

Ecco lo script `add_cast_v3.awk` modificato:

```awk
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
```

**Come Usarlo:**

1.  **Salva** lo script come `add_cast_v3.awk`.
2.  **Esegui** usando l'opzione `-v` per passare i parametri:

    *   **Aggiungere `(char*)` a `set_something`, non sostituire esistenti:**
        ```bash
        awk -v func_name="set_something" -v cast_type="char" -v replace_existing=0 \
            -f add_cast_v3.awk nome_file_originale > nome_file_modificato
        ```

    *   **Aggiungere `(void*)` a `get_something`, non sostituire esistenti:**
        ```bash
        awk -v func_name="get_something" -v cast_type="void" -v replace_existing=0 \
            -f add_cast_v3.awk nome_file_originale > nome_file_modificato
        ```

    *   **Forzare `(char*)` per `set_something`, sostituendo anche `(char*)` o `(void*)` esistenti:**
        ```bash
        awk -v func_name="set_something" -v cast_type="char" -v replace_existing=1 \
            -f add_cast_v3.awk nome_file_originale > nome_file_modificato
        ```

    *   **Per applicare a tutti i file `.c` (richiede GNU awk per `-i inplace`):**
        ```bash
        # Esempio: Aggiungere (char*) a set_something, non sostituire
        find . -type f -name '*.c' -exec awk -i inplace \
             -v func_name="set_something" -v cast_type="char" -v replace_existing=0 \
             -f add_cast_v3.awk {} \;
        ```

        *(Se non hai GNU awk, usa il ciclo `while read` con file temporanei come mostrato nell'esempio precedente).*

**Spiegazione delle Modifiche:**

1.  **Variabili Parametriche:** Aggiunte `func_name`, `cast_type`, `replace_existing` nel blocco `BEGIN` con valori di default. Questi vengono sovrascritti se passi `-v` sulla riga di comando.
2.  **Costruzione Pattern Dinamica:** I pattern regex `func_start_pattern`, `existing_cast_pattern`, ecc., vengono costruiti usando la variabile `func_name`.
3.  **`target_cast`:** Viene costruita la stringa del cast desiderato (`(char*)` o `(void*)`) basata su `cast_type`.
4.  **`replace_existing` Flag:** Questa variabile (0 o 1) controlla se si deve tentare di sostituire un cast esistente.
5.  **`needs_replace` Flag:** Simile a `needs_cast`, ma indica se è stata trovata una corrispondenza che richiede la sostituzione (in base a `replace_existing`).
6.  **Funzione `replace_cast`:** Aggiunta una nuova funzione helper che usa `gsub` (global substitution) e un pattern specifico (`replace_pattern`) per sostituire un cast `(char*)` o `(void*)` esistente con il `target_cast`. `replace_pattern` usa gruppi di cattura per isolare le parti prima e dopo il cast da sostituire.
7.  **Logica Aggiornata:** La logica principale ora controlla prima se esiste un cast `(char*)` o `(void*)`.
    *   Se esiste e `replace_existing` è 1, imposta `needs_replace=1`.
    *   Se esiste e `replace_existing` è 0, imposta `needs_cast=0` e `needs_replace=0`.
    *   Se non esiste cast char/void ma esistono parentesi generiche, imposta `needs_cast=0` e `needs_replace=0` (non tocca).
    *   Se non esiste nulla, `needs_cast=1` e `needs_replace=0`.
8.  **Applicazione Modifiche:** Quando viene trovata la fine della funzione, viene chiamato `replace_cast(buffer)` se `needs_replace` è vero, oppure `insert_cast(buffer)` se `needs_cast` è vero. Altrimenti, il buffer viene stampato com'è.
9.  **Debug Output:** Aggiunto output su `stderr` nel blocco `BEGIN` per mostrare la configurazione con cui sta girando lo script.

Questo script è più flessibile ma anche più complesso. **Testalo accuratamente** con vari input e combinazioni di parametri per assicurarti che faccia esattamente ciò che desideri.


DRY RUN

Ottima idea fare un "dry run" prima di modificare effettivamente i file! Ci sono diversi modi per simulare cosa farebbe il comando `find ... -exec awk -i inplace ...` senza alterare i file originali.

Ecco alcuni metodi, dal più semplice al più completo:

**Metodo 1: Stampare i Comandi che Verrebbero Eseguiti**

Questo è il modo più semplice per vedere quali file verrebbero processati e con quale comando `awk`. Non mostra l'output modificato, ma conferma che `find` seleziona i file giusti e costruisce il comando `awk` correttamente.

```bash
find /percorso/tua/directory -type f -name '*.c' -print -exec printf "awk -v func_name=... -v cast_type=... -v replace_existing=... -f script.awk '%s'\n" {} \;
```

**Spiegazione:**

*   `find ... -print`: Stampa il nome di ogni file `.c` trovato.
*   `-exec printf "..." {} \;`: Per ogni file trovato (`{}`), esegue il comando `printf`.
    *   `"awk -v ... -f script.awk '%s'\n"`: È la stringa di formato per `printf`. Contiene il comando `awk` che *vorresti* eseguire. **Devi inserire i valori corretti per `-v func_name=...`, `-v cast_type=...`, `-v replace_existing=...` e il nome corretto del tuo script `awk`**.
    *   `'%s'`: È il segnaposto in `printf` dove verrà inserito il nome del file (`{}`).
    *   `\n`: Aggiunge un newline per leggibilità.

**Esempio Concreto:**

```bash
# Esempio dry run per aggiungere (char*) a set_something, non sostituire
find . -type f -name '*.c' -print -exec printf "awk -v func_name='set_something' -v cast_type='char' -v replace_existing=0 -f add_cast_v5.awk '%s'\n" {} \;
```

L'output sarà una lista di nomi di file, ognuno seguito dal comando `awk` che verrebbe applicato a quel file.

**Metodo 2: Eseguire `awk` Senza `-i inplace` e Mostrare le Differenze**

Questo metodo esegue effettivamente lo script `awk` su ogni file, ma invece di modificare il file, confronta l'output dello script con il file originale usando `diff`. Mostra solo le righe che *cambierebbero*.

```bash
find /percorso/tua/directory -type f -name '*.c' -print -exec sh -c '
    # Definisci qui i parametri e lo script awk
    FUNC_NAME="set_something"
    CAST_TYPE="char"
    REPLACE_EXISTING=0
    AWK_SCRIPT="add_cast_v5.awk"
    FNAME="{}" # Nome file passato da find

    # Esegui awk e confronta con diff
    # diff -u mostra le differenze in formato unificato (leggibile)
    awk -v func_name="$FUNC_NAME" -v cast_type="$CAST_TYPE" \
        -v replace_existing="$REPLACE_EXISTING" \
        -f "$AWK_SCRIPT" "$FNAME" | diff -u "$FNAME" -
' \;
```

**Spiegazione:**

*   `find ... -print`: Stampa il nome del file.
*   `-exec sh -c '...' \;`: Esegue uno script di shell (`sh -c '...'`) per ogni file. Questo permette di eseguire comandi più complessi.
    *   **`FUNC_NAME=...`, `CAST_TYPE=...`, ecc.:** Imposta le variabili all'interno dello script di shell. **Modificale con i tuoi valori!**
    *   **`FNAME="{}"`**: Cattura il nome del file passato da `find`.
    *   **`awk ... "$FNAME"`**: Esegue lo script `awk` sul file, passando i parametri tramite `-v`. L'output di `awk` viene mandato tramite pipe (`|`) a `diff`.
    *   **`| diff -u "$FNAME" -`**: Esegue `diff`.
        *   `-u`: Opzione per formato unificato.
        *   `"$FNAME"`: Il primo file da confrontare (l'originale).
        *   `-`: Il secondo "file" da confrontare. Il trattino `-` dice a `diff` di leggere il secondo input dallo standard input, che in questo caso è l'output della pipe da `awk` (il file come *sarebbe* modificato).

**Output:** Vedrai solo i blocchi `diff` per i file che contengono modifiche. Le righe precedute da `-` sono quelle originali, quelle precedute da `+` sono quelle modificate. Se un file non viene modificato, non vedrai alcun output `diff` per esso (solo il suo nome stampato da `-print`).

**Metodo 3: Salvare l'Output Modificato in File Temporanei (Più Completo)**

Questo è il "dry run" più fedele, perché crea effettivamente i file modificati (ma con nomi diversi) così puoi ispezionarli completamente.

```bash
# Crea una directory temporanea per i risultati
mkdir /tmp/awk_dry_run_output

find /percorso/tua/directory -type f -name '*.c' -exec sh -c '
    # Parametri e script
    FUNC_NAME="set_something"
    CAST_TYPE="char"
    REPLACE_EXISTING=0
    AWK_SCRIPT="add_cast_v5.awk"
    FNAME="{}"

    # Costruisci il percorso di output mantenendo la struttura delle directory
    # Rimuovi il percorso iniziale e aggiungi il prefisso temporaneo
    OUT_FNAME="/tmp/awk_dry_run_output/${FNAME#/percorso/tua/directory/}"
    # Crea la directory di output se non esiste
    mkdir -p "$(dirname "$OUT_FNAME")"

    # Esegui awk e salva l output
    echo "Processing $FNAME -> $OUT_FNAME" >&2 # Messaggio su stderr
    awk -v func_name="$FUNC_NAME" -v cast_type="$CAST_TYPE" \
        -v replace_existing="$REPLACE_EXISTING" \
        -f "$AWK_SCRIPT" "$FNAME" > "$OUT_FNAME"

' \;

echo "Dry run completato. I file modificati (se presenti) sono in /tmp/awk_dry_run_output"
echo "Puoi confrontarli con: diff -r /percorso/tua/directory /tmp/awk_dry_run_output"
```

**Spiegazione:**

*   `mkdir /tmp/awk_dry_run_output`: Crea una directory per contenere i risultati.
*   `find ... -exec sh -c '...' \;`: Come prima, esegue uno script di shell per file.
*   **`OUT_FNAME=...`**: Costruisce il nome del file di output nella directory temporanea. `${FNAME#/percorso/tua/directory/}` rimuove il prefisso del percorso originale per ricreare la struttura relativa in `/tmp/awk_dry_run_output`. **Assicurati che `/percorso/tua/directory/` qui corrisponda esattamente al percorso usato nel `find` e termini con `/`**.
*   **`mkdir -p "$(dirname "$OUT_FNAME")"`**: Crea le sottodirectory necessarie nella directory temporanea.
*   **`awk ... > "$OUT_FNAME"`**: Esegue `awk` e reindirizza l'output nel file corrispondente nella directory temporanea.
*   **`echo "Processing..." >&2`**: Stampa un messaggio di avanzamento sullo standard error.
*   **Comando `diff -r` finale:** Alla fine viene suggerito come confrontare ricorsivamente la directory originale con quella temporanea per vedere tutte le differenze.

**Quale Metodo Usare?**

*   **Metodo 1:** Veloce, buono per verificare che `find` selezioni i file giusti e il comando `awk` sia costruito correttamente. Non verifica l'effetto dello script `awk`.
*   **Metodo 2:** Ottimo per vedere rapidamente *quali* righe cambierebbero e *come*. Ideale per modifiche piccole e mirate.
*   **Metodo 3:** Il più completo. Simula l'intero processo creando i file modificati in un'area separata. Ti permette di ispezionare i file risultanti nel dettaglio e usare `diff -r` per un confronto completo. È il più sicuro prima di una modifica "in-place" su larga scala.

Scegli il metodo che ti dà maggiore confidenza in base alla complessità della modifica e alla dimensione del progetto. Per una modifica potenzialmente complessa come questa, il **Metodo 3** è probabilmente il più indicato.
