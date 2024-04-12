/*
   modulo compstaz.inc
   tipo
   release 1.1
   data 6/15/93
   reserved @(#)compstaz.inc    1.1
*/

typedef struct collega {
  char coll [MAX_COLL] [8];
  } COLLEG_ST;

typedef struct strin_st {
  char *stringa;
  int lun_stringa;
  } STRIN_ST;


#define ERR_DES         0
#define ERR_PAG         1
#define ERR_POS         2
#define ERR_LAB         3
#define ERR_UMIS                4
#define ERR_SCAL                5
#define ERR_SCALERR             6
#define ERR_MINMAX              7
#define ERR_MINMAXERR   8
#define ERR_ASSOC               9
#define ERR_LOGICA              10
#define ERR_STATO               11
#define ERR_ESAMR               12
#define ERR_VALORE              13
#define ERR_VALERR              14
#define ERR_RSTATO              15
#define ERR_RPIU                        16
#define ERR_RMENO               17
#define ERR_RTARGET             18
#define ERR_TARGET              19
#define ERR_DESVAL              20
#define ERR_GRUP1               21
#define ERR_GRUP2               22
#define ERR_OGGETTO             23
#define ERR_COLORE              24
#define ERR_ETIC                25
#define ERR_INPUT               26
#define ERR_INPUT_BLINK         27
#define ERR_OUTPUT              28
#define ERR_PERTURB             29
#define ERR_INPUT_ERR           30
#define ERR_OFFSET              31
#define ERR_INIBIZ              32


