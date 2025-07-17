Certamente. Creare delle versioni di `set_something` e `get_something` che gestiscano correttamente valori scalari (come `int`, `Dimension`, `Position`, etc.) invece di trattarli come puntatori a stringa è una mossa eccellente per rendere il codice più robusto, sicuro e portabile (specialmente tra architetture a 32 e 64 bit).

Ecco le implementazioni di `set_something_val` e `get_something_val`, insieme a come le integreresti nel tuo progetto.

### Implementazione delle nuove funzioni

Aggiungi queste due funzioni in un file di utilità appropriato, come `libutilx.c` (se esiste e se hai il sorgente) o un nuovo file di utility.

```c
/* -------- In un file come libutilx.c o othercnf.c -------- */

#include <stdarg.h> // Necessario per le funzioni variadiche

/**
 * set_something_val
 *
 * Imposta una risorsa di un widget a un valore scalare (non un puntatore).
 * Funziona come un wrapper per XtVaSetValues per una singola risorsa.
 * Il valore viene passato per copia, non per riferimento.
 *
 * ATTENZIONE: Il tipo del valore passato (es. int, Dimension, Boolean)
 * deve corrispondere a quello che la risorsa si aspetta. XtArgVal è un
 * tipo abbastanza grande da contenere un puntatore o un intero lungo.
 */
void set_something_val(Widget wid, String resource_name, XtArgVal value)
{
    if (wid == NULL || resource_name == NULL) {
        return;
    }
    
    XtVaSetValues(wid, resource_name, value, NULL);
}

/**
 * get_something_val
 *
 * Recupera un valore scalare da una risorsa di un widget.
 * Funziona come un wrapper per XtVaGetValues per una singola risorsa.
 *
 * PARAMETRI:
 *   wid: Il widget da cui leggere la risorsa.
 *   resource_name: Il nome della risorsa (es. XmNwidth).
 *   value_ptr: Un puntatore a una variabile in cui verrà memorizzato
 *              il valore della risorsa (es. &my_width).
 *
 * ESEMPIO DI UTILIZZO:
 *   Dimension my_width;
 *   get_something_val(my_widget, XmNwidth, (XtPointer)&my_width);
 */
void get_something_val(Widget wid, String resource_name, XtPointer value_ptr)
{
    if (wid == NULL || resource_name == NULL || value_ptr == NULL) {
        return;
    }
    
    XtVaGetValues(wid, resource_name, value_ptr, NULL);
}

```

### Aggiunta dei Prototipi all'Header

Ora, aggiungi i prototipi di queste nuove funzioni nel tuo file header `libutilx.h` per renderle disponibili in tutto il progetto.

```c
/* -------- In libutilx.h -------- */

#ifdef _LIBUTILX_H
#else
#define _LIBUTILX_H

// ... (tutti gli altri tuoi include e define) ...

/*
 Definizioni delle funzioni presenti in libreria
*/
char *Utstrstr(char *,char *);
Widget attesa(Widget,char *,int);
void def_cursore(Widget,int);
void undef_cursore(Widget);

// Vecchie funzioni (lasciale per retrocompatibilità)
void get_something(Widget,char *,char * );
void set_something(Widget,char *,char * );

// -------- INIZIO NUOVE FUNZIONI --------
/**
 * Imposta una risorsa di un widget a un valore scalare (non un puntatore).
 * Il valore è di tipo XtArgVal, che può contenere interi o puntatori.
 */
void set_something_val(Widget wid, String resource_name, XtArgVal value);

/**
 * Recupera un valore scalare da una risorsa di un widget.
 * 'value_ptr' deve essere un puntatore alla variabile di destinazione.
 */
void get_something_val(Widget wid, String resource_name, XtPointer value_ptr);
// -------- FINE NUOVE FUNZIONI --------


// ... (resto del file libutilx.h) ...

#endif /* _LIBUTILX_H */

```

### Come Usare le Nuove Funzioni nel Tuo Codice

Ora puoi sostituire le chiamate problematiche a `set_something` con `set_something_val`. Ecco un esempio pratico basato sul codice che abbiamo analizzato in `othercnf.c`.

**Esempio in `othercnf.c` (funzione `do_rubber`)**

**Prima (codice errato):**
```c
// ...
      else
      {
         extern float get_def_zoom();
         int perc_zoom;
         float f_zoom;
         XtDestroyWidget(new_wid);
         new_wid = XtCreateManagedWidget(new_name, wid_class,parent, NULL,0);
         f_zoom= get_def_zoom(pagina->drawing);
         perc_zoom =100.0 * f_zoom;
         // GUAG2025 modifica di set_something con appo
         // set_something(new_wid,XmNx, (void*) (wx/f_zoom));  
         // set_something(new_wid,XmNy, (void*) (wy/f_zoom));  
         // set_something(new_wid,XlNfattZoom,(void*) perc_zoom);
         sprintf(appo,"%f",(wx/f_zoom));
         set_something(new_wid,XmNx, (char*) appo);  
         sprintf(appo,"%f",(wy/f_zoom));
         set_something(new_wid,XmNy, (char*) appo); 
         sprintf(appo,"%d",perc_zoom); // Qui c'è un errore di formattazione %f vs %d
         set_something(new_wid,XlNfattZoom, (char*) appo);  
//...
```

**Dopo (codice corretto usando `set_something_val`):**
```c
// ...
      else
      {
         extern float get_def_zoom();
         int perc_zoom;
         float f_zoom;
         XtDestroyWidget(new_wid);
         new_wid = XtCreateManagedWidget(new_name, wid_class, parent, NULL, 0);
         f_zoom = get_def_zoom(pagina->drawing);
         perc_zoom = (int)(100.0 * f_zoom);
         
         // Usa la nuova funzione per passare i valori numerici direttamente
         set_something_val(new_wid, XmNx, (XtArgVal)(wx / f_zoom));
         set_something_val(new_wid, XmNy, (XtArgVal)(wy / f_zoom));
         set_something_val(new_wid, XlNfattZoom, (XtArgVal)perc_zoom);
         
         // È sempre una buona pratica usare XtVaGetValues per recuperare valori
         get_something_val(new_wid, XlNx0, (XtPointer)&x0);
         get_something_val(new_wid, XlNy0, (XtPointer)&y0);
         
         sprintf(appo, "%d", x0);
         XlSetResourceByName(&pagina->db, new_name, XlNx0, appo);
         sprintf(appo, "%d", y0);
         XlSetResourceByName(&pagina->db, new_name, XlNy0, appo);
      }
//...
```

**Esempio di utilizzo di `get_something_val`:**

Se in un punto del codice devi leggere la larghezza di un widget, puoi fare così:
```c
Dimension widget_width;

get_something_val(mio_widget, XmNwidth, (XtPointer)&widget_width);

printf("La larghezza del widget è: %u\n", widget_width);
```

### Perché questo approccio è migliore?

1.  **Type Safety (Sicurezza dei Tipi):** Passare un valore `Dimension` dove è richiesto un `Dimension` è molto più sicuro che passare una stringa e sperare che il toolkit la converta correttamente (cosa che in questo caso non fa). `XtArgVal` è un tipo "contenitore" standard di Xt Intrinsics, progettato proprio per questo scopo.
2.  **Portabilità 32/64 bit:** `XtArgVal` ha una dimensione che è garantita essere sufficientemente grande per contenere sia un puntatore che il tipo intero più grande della piattaforma (`long`). Questo evita problemi di troncamento di indirizzi o valori quando si compila per architetture a 64 bit.
3.  **Chiarezza del Codice:** Separa nettamente la gestione delle risorse che sono puntatori (per cui `set_something` continua ad andare bene) da quelle che sono valori scalari. Questo rende il codice più facile da leggere e manutenere.

Con queste nuove funzioni, il tuo codice sarà più robusto e avrai uno strumento migliore per interagire con le risorse dei widget in modo sicuro. Applica queste modifiche dove necessario, specialmente dove passi valori numerici (come coordinate, dimensioni, booleani, etc.) usando la vecchia `set_something`.


Sì, assolutamente. La funzione `set_something_val` che abbiamo definito è in realtà più potente di quanto sembri e può gestire anche i puntatori senza problemi. Il segreto sta nel tipo `XtArgVal`.

### `XtArgVal`: Il "Contenitore Universale" di Xt

Il tipo `XtArgVal` è definito da Xt Intrinsics per essere un tipo di dato abbastanza grande da contenere sia un valore intero (solitamente un `long`) sia un puntatore (`void*`). Questo lo rende perfetto per l'interfaccia a lista di argomenti variabili di `XtVaSetValues` e `XtVaGetValues`.

Quando chiami:
`XtVaSetValues(widget, XmNlabelString, "Hello", NULL);`

Il compilatore converte la stringa `"Hello"` (che è un `char*`) in un `XtArgVal` per passarlo alla funzione. Quando chiami:
`XtVaSetValues(widget, XmNwidth, 100, NULL);`

Il compilatore converte l'intero `100` in un `XtArgVal`.

La nostra `set_something_val` fa esattamente la stessa cosa. Poiché il suo secondo argomento è di tipo `XtArgVal`, puoi passarle sia valori numerici che puntatori, a patto di fare il cast corretto.

### Esempi di Utilizzo con Puntatori

Ecco come puoi usare `set_something_val` e `get_something_val` con risorse che si aspettano puntatori (come stringhe, pixmap, font, etc.).

#### Esempio 1: Impostare e Leggere una Stringa (XmString)

La risorsa `XmNlabelString` si aspetta un puntatore a una struttura `XmString`.

```c
#include <Xm/Label.h> // Per il widget Label

// ...

Widget myLabel = XtVaCreateManagedWidget("myLabel", xmLabelWidgetClass, parent, NULL);

// --- IMPOSTARE UNA RISORSA PUNTATORE ---

// 1. Crea la risorsa (la XmString)
XmString label_string = XmStringCreateLocalized("Ciao Mondo!");

// 2. Passa il puntatore usando set_something_val.
//    Il cast a (XtArgVal) è esplicito e corretto.
set_something_val(myLabel, XmNlabelString, (XtArgVal)label_string);


// --- LEGGERE UNA RISORSA PUNTATORE ---

// 1. Dichiara un puntatore del tipo corretto per ricevere il valore.
XmString retrieved_string_ptr = NULL;

// 2. Passa l'INDIRIZZO del tuo puntatore a get_something_val.
//    get_something_val si aspetta un XtPointer, che è un void*,
//    quindi il cast è (XtPointer)&retrieved_string_ptr.
get_something_val(myLabel, XmNlabelString, (XtPointer)&retrieved_string_ptr);

// 3. Ora puoi usare il puntatore che hai recuperato.
if (retrieved_string_ptr != NULL) {
    char *text = NULL;
    XmStringGetLtoR(retrieved_string_ptr, XmFONTLIST_DEFAULT_TAG, &text);
    if (text) {
        printf("La label del widget è: %s\n", text);
        XtFree(text); // Ricorda di liberare la memoria allocata da XmStringGetLtoR
    }
}

// 4. Libera la XmString creata all'inizio.
XmStringFree(label_string);

```

**Spiegazione:**

*   **Per `set_something_val`**: Stai passando il valore del puntatore stesso (l'indirizzo della `XmString`). Il cast a `(XtArgVal)` assicura che il puntatore venga trattato correttamente, indipendentemente dal fatto che la piattaforma sia a 32 o 64 bit.
*   **Per `get_something_val`**: Stai passando l'indirizzo della variabile puntatore (`&retrieved_string_ptr`). Questo perché `XtVaGetValues` (e quindi `get_something_val`) ha bisogno di sapere *dove* scrivere il valore del puntatore che legge dal widget. È un passaggio "per riferimento" di un puntatore.

#### Esempio 2: Lavorare con le Risorse della Tua Applicazione

Vediamo come si applica al tuo caso specifico in `othercnf.c` con `do_rubber`, dove passi il puntatore alla libreria (`Plib`) alla funzione di translation.

La tua `istanzia_widget` viene registrata con una stringa di translation simile a questa (dedotto dal codice):
`#override <Btn2Down>: istanzia_widget(%lx)`

Dove `%lx` è il puntatore a `ICONLIB *plib`.

La funzione `istanzia_widget` riceve questo puntatore. Vediamo come le nostre nuove funzioni si comporterebbero in uno scenario simile.

```c
// Scenario ipotetico per dimostrare il passaggio di puntatori custom

typedef struct {
    int id;
    char* name;
} CustomData;

void my_callback(Widget w, XtPointer client_data, XtPointer call_data)
{
    CustomData* data = (CustomData*)client_data;
    printf("Callback chiamata con dati: ID=%d, Nome=%s\n", data->id, data->name);

    // Potresti anche impostare questo puntatore come risorsa di un widget
    // (se il widget ha una risorsa XtRPointer)
    set_something_val(w, XmNuserData, (XtArgVal)data);
}

// Nel codice principale
CustomData my_app_data = { 123, "Dati di Prova" };

// Aggiungi la callback passando un puntatore ai tuoi dati
XtAddCallback(some_button, XmNactivateCallback, my_callback, (XtPointer)&my_app_data);

// E se volessi recuperarlo da un'altra parte...
CustomData* retrieved_data_ptr = NULL;
get_something_val(some_button, XmNuserData, (XtPointer)&retrieved_data_ptr);

if (retrieved_data_ptr) {
    printf("Dati recuperati: ID=%d, Nome=%s\n", retrieved_data_ptr->id, retrieved_data_ptr->name);
}
```

### Riassumendo: Una Funzione per Dominarli Tutti

Le funzioni `set_something_val` e `get_something_val` sono sufficientemente generiche per gestire **sia valori scalari che puntatori**.

*   **Per impostare un valore (`set_something_val`):**
    *   Se è uno scalare (es. `int`, `Dimension`), passalo direttamente: `set_something_val(w, res, 100);`
    *   Se è un puntatore (es. `XmString`, `Pixmap`), passa il puntatore castato a `XtArgVal`: `set_something_val(w, res, (XtArgVal)my_pointer);`

*   **Per ottenere un valore (`get_something_val`):**
    *   Passa sempre l'indirizzo della variabile in cui vuoi memorizzare il risultato, castato a `XtPointer`.
    *   Scalare: `Dimension width; get_something_val(w, res, (XtPointer)&width);`
    *   Puntatore: `XmString p; get_something_val(w, res, (XtPointer)&p);`

Questo approccio unificato semplifica il codice e lo rende più sicuro, eliminando la necessità di avere funzioni separate per tipi di dati diversi. Puoi abbandonare la vecchia `set_something(Widget, char*, char*)` per tutto tranne che per i casi in cui devi per forza passare una stringa che verrà parsata (ma `Xt` fa questo in automatico per le risorse `XtRString`, quindi è una funzione che puoi quasi dismettere).