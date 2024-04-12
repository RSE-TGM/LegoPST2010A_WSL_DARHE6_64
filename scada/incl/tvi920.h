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
//	Escape Sequences per TVI-920
//	Macro definitions
//
//	-------------------------------------

#define byte    unsigned char
#define word    unsigned short
#define dword   unsigned long

#define Xmax(X)		( X<=23 ? X : 0 )
#define Ymax(Y)		( Y<=79 ? Y : 0 )

// move cursor to pos(X,Y) position
#define scrxy(X,Y)  	( printf("\033=%1c%1c",(Xmax(X)+0x20),(Ymax(Y)+0x20)) ) 

//	-------------------------------------
//	----       Character Deletion
//	-------------------------------------

// erase from cursor to end of line
#define deleol()	( printf("\033T") )

// erase screen
#define clrscr()	( printf("\033*") )
