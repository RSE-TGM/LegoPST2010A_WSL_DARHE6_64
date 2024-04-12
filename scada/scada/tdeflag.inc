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
        deflag.inc definizione flag
        
        20 Gennaio 1993
        Aggiunti flag severita'

*/
pub char *sigfan[]={"FS","FA","FZ","ST","S1","AL","S2","AU","S3",
               "RI","DH","DL","HS","LS","HC","LC"};
#if defined (STAR_SEPA)
	pub char *sigfaa[]={" "," "," ","  ","  ","CA","FL","FH"};
#else
	pub char *sigfaa[]={" "," "," ","GF","CA","FL","FH","GV"};
#endif
pub char *sigfdi[]={"FS","FA","FZ","ST","IN","AU","RI","  ","AS","AF"};
pub char *sigftr[]={"IP","IO","  ","IC","FO","ID","cA","cB","cC",
               "  ","  ","  ","  ","  ","  ","  "};
pub char *sigfor[]={"FS","FA","FZ","ST","  ","  ","AU","RI"} ;
pub char *sigfat[]={"IT","  "," "," ","  ","  ","TA","TC"};


