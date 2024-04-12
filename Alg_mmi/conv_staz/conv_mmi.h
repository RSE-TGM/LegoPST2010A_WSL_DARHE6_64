#define MAX_LUN_RIGA_ELENCO_WID		4000
#define WIDTH_COMPOSITE		DIM_UNITSTAZ
#define HEIGHT_COMPOSITE	DIM_UNITSTAZ
#define BORDER_COMPOSITE	1
#define SFONDO_LABEL  "#cc00e500cb00"
#define SFONDO_WINDOW "#cc00e500ff00"
#define SFONDO_STAZ   "#d500e500d500"
#define FONT_PICCOLO  "fixed"
#define FONT_GRANDE   "-adobe-times-bold-r-normal--25-180-100-100-p-132-iso8859-1"

struct conv_colori_st{
	char *old_colore;
	char *colore;
	char *colore_blink;
	};
typedef struct conv_colori_st CONV_COLORI;


static CONV_COLORI conv_colori[]={
	{"NERO","black","white"},
	{"BIANCO","white","black"},
	{"GIALLO","#e400c4008800","#ff00ff000000"},
	{"VERDE","#00008a000000","#0000ff000000"},
	{"ROSSO","#b30000000000","#ff0032000000"},
	{"GRIGIO","#5c005c005c00","#cb00cb00cb00"},
	{"BLU","#000000007600","#0000e500ff00"},
	{NULL,NULL,NULL}
	};

