/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
//	-------------------------------------
//
//	ANSI Escape Sequences 
//	Macro definitions
//
//	-------------------------------------

#define byte    unsigned char
#define word    unsigned short
#define dword   unsigned long

#define Xmax(X)		( X<=24 ? X : 0 )
#define Ymax(Y)		( Y<=80 ? Y : 0 )

//	-------------------------------------
//	---- Display styles
//	-------------------------------------

// cursor UP one line
#define upcur()  	( printf("\033[A") ) 

// cursor DOWN one line
#define dwncur()  	( printf("\033[B") ) 

// cursor RIGHT one character
#define rigcur()  	( printf("\033[C") ) 

// cursor LEFT one character
#define lefcur()  	( printf("\033[D") ) 

// cursor UP # line
#define nupcur(X)  	( printf("\033[%dA",X) ) 

// cursor DOWN # line
#define ndwncur(X)  	( printf("\033[%dB",X) ) 

// cursor RIGHT # line
#define nrigcur(X)  	( printf("\033[%dC",X) ) 

// cursor LEFT # line
#define nlefcur(X)  	( printf("\033[%dD",X) ) 

// move cursor to pos(X,Y) position
#define scrxy(X,Y)  	( printf("\033[%d;%dH",Xmax(X),Ymax(Y)) ) 
#define curxy(X,Y)  	( printf("\033[%d;%dH",Xmax(X),Ymax(Y)) ) 

// save cursor position
#define savcur()  	( printf("\033[s") ) 

// restore cursor position
#define rescur()  	( printf("\033[u") ) 

//	-------------------------------------
//	---- Display styles
//	-------------------------------------

// reset attributi
#define clratt()	( printf("\033[0m") )

// set bold
#define bldatt()	( printf("\033[1m") )

// set underline
#define undatt()	( printf("\033[2M") )

// set blink
#define blkatt()	( printf("\033[3M") )

// set reverse
#define revatt()	( printf("\033[7m") )

//	-------------------------------------
//	----       Screen Color
//	-------------------------------------

//	----- foreground --------------------

// black foreground
#define blkfor()	( printf("\033[30M") )

// red foreground
#define bedfor()	( printf("\033[31M") )

// green foreground
#define grefor()	( printf("\033[32M") )

// yellow foreground
#define yelfor()	( printf("\033[33M") )

// blue foreground
#define blufor()	( printf("\033[34M") )

// magenta foreground
#define magfor()	( printf("\033[35M") )

// cyan foreground
#define cyafor()	( printf("\033[36M") )

// white foreground
#define whifor()	( printf("\033[37M") )

//---------- background

// black background
#define blkbak()	( printf("\033[40M") )

// red background
#define bedbak()	( printf("\033[41M") )

// green background
#define grebak()	( printf("\033[42M") )

// yellow background
#define yelbak()	( printf("\033[43M") )

// blue background
#define blubak()	( printf("\033[44M") )

// magenta background
#define magbak()	( printf("\033[45M") )

// cyan background
#define cyabak()	( printf("\033[46M") )

// white background
#define whibak()	( printf("\033[47M") )


//	-------------------------------------
//	----       Character Deletion
//	-------------------------------------

// erase from cursor to end of line
#define deleol()	( printf("\033[K") )

// erase beg of line to cursor 
#define delbol()	( printf("\033[1K") )

// erase line
#define dellin()	( printf("\033[2K") )
#define erase_line()	( printf("\033[2K") )

// erase from cursor to end of screen
#define deleos()	( printf("\033[J") )

// erase beg of screen to cursor
#define delbos()	( printf("\033[1J") )

// erase screen
#define clrscr()	( printf("\033[2J") )

/*
	bell
*/
#define bell()  (printf("\007"))

