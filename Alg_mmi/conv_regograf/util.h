/*
   modulo util.h
   tipo 
   release 1.16
   data 10/19/95
   reserved @(#)util.h	1.16
*/
#define MAXRIGA 200

struct tab_colori_st{
	char *colore;
	};
typedef struct tab_colori_st TAB_COLORI;

static TAB_COLORI tab_colori[]={
/* 0  */        {"#000000000000"},
/* 1  */        {"#ffff00000000"},
/* 2  */        {"#ffffffff0000"},
/* 3  */        {"#0000ffff0000"},
/* 4  */        {"#0000ffffffff"},
/* 5  */        {"#00000000ffff"},
/* 6  */        {"#ffff0000ffff"},
/* 7  */        {"#ffffffffffff"},
/* 8  */        {"@1"}/*{"#575757575757"}*/,
/* 9  */        {"#aaaa00000000"},
/* 0  */        {"#aaaa57570000"},
/* 1  */        {"#0000aaaa0000"},
/* 2  */        {"#0000aaaaaaaa"},
/* 3  */        {"#00000000aaaa"},
/* 4  */        {"#aaaa0000aaaa"},
/* 5  */        {"#aaaaaaaaaaaa"},
/* 6  */        {"#ffffffffffff"},
		{"#575757575757"},
		{"#00000000aaaa"},
		{"#0000aaaa0000"},
		{"#0000aaaaaaaa"},
		{"#aaaa00000000"},
		{"#aaaa0000aaaa"},
		{"#aaaa57570000"},
		{"#aaaaaaaaaaaa"},
		{"#575757575757"},
		{"#00000000ffff"},
		{"#0000ffff0000"},
		{"#0000ffffffff"},
		{"#ffff00000000"},
		{"#ffff0000ffff"},
		{"#ffffffff0000"},
		{"#ffffffffffff"},
	{"cyan"},
	{"red"},
	{"navy"},
	{"red"},
	{"yellow"},
	{"green"},
	{"cyan"},
	{"red"},
	{"navy"},
	{"red"},
	{"yellow"},
	{"green"},
	{"cyan"},
	{"red"},
	{"navy"},
	{"red"},
	{"yellow"},
	{"green"},
	};

#define BACKGROUND	"#000000000000"
#define FOREGROUND	"cyan"

/* definizione valori ASCII per TAG pagine e Regolazioni */

#define ASCII0    48    /* ascii value 0 */
#define ASCII9    57    /* ascii value 9 */
#define ASCIIA    65    /* ascii value A */
#define ASCIIZ    90    /* ascii value Z */
                                                

#define FATTORE_SCALA	8

struct tab_porte_st{
	char nome_icona[10];
	char nome_porta[3];
	char id_porta[4];
	int colore_porta;
	float pos_x;
	float pos_y;
	int rotate;
	int ass_rotate;
	int tipo;
	int layout;
	int interface;
	};
typedef struct tab_porte_st TAB_PORTE;

struct tab_icone_st{
        char nome_icona[10];
        int dim_x;
        int dim_y;
        int pos_x;
        int pos_y;
	char id_i[5];
	char id_m[5];
        };
typedef struct tab_icone_st TAB_ICONE;

struct elenco_porte_st{
	char nome_icona[10];
	char nome_porta[3];
	char id_i[5];
	char id_w[10];
	};
typedef struct elenco_porte_st ELENCO_PORTE;

struct connessioni_st{
	char id_i_1[5];
	char nome_icona_1[10];
	char nome_porta_1[10];
        char nomep1[10];
	char id_i_2[5];
	char nome_icona_2[10];
	char nome_porta_2[10];
        char nomep2[10];
	int colore;
	int num;
	int x[30];
	int y[30];
	};
typedef struct connessioni_st CONNESSIONI;
