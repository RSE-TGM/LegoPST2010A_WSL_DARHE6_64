/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo util.h
   tipo 
   release 1.4
   data 1/19/96
   reserved @(#)util.h	1.4
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

#define BACKGROUND	"#000000005757"
#define FOREGROUND	"cyan"


#define FATTORE_SCALA	7
