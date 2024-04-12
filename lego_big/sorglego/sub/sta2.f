C*********************************************************************
C       Fortran Source:             sta2.f
C       Subsystem:              1
C       Description:
C       %created_by:    lopez %
C       %date_created:  Mon Oct 28 10:59:09 2002 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_sta2_f
      CHARACTER*80  RepoID
      COMMON /CM_sta2_f / RepoID
      DATA RepoID/'@(#)1,fsrc,sta2.f,2'/
      END
C**********************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE STA2(NBL,NOMBLC,NOMSUB,NSTA,NUSC,NIGR,IPV,VARS,
     $                NX2,NX5,XYU,NX6,VARBL,XBL)
      DIMENSION NOMBLC(NX2,2),NOMSUB(*),NSTA(*),NUSC(*),NIGR(*),IPV(*),
     $          XBL(NX6,3),XYU(*)
      DIMENSION NFORM(14),IFORM(14)
      CHARACTER*8 VARS(NX5),VARBL(NX6,3)
C
C
      NA=0
      NB=0
      DO 100 I=1,NBL
      I1=IPV(I)
      I2=IPV(I+1)-1
      NS=NSTA(I)
      NU=NUSC(I)
      NI=NIGR(I)
      DO 11 J=1,NX6
      DO 11 K=1,3
      VARBL(J,K)=' '
      XBL(J,K)=0.
   11 CONTINUE
      K=0
      IF(NS.EQ.0)GO TO 21
      DO 20 J=1,NS
      K=K+1
      M=I1+K-1
      VARBL(J,2)=VARS(M)
      XBL(J,2)=XYU(M)
   20 CONTINUE
   21 IF(NU.EQ.0)GO TO 31
      DO 30 J=1,NU
      K=K+1
      M=I1+K-1
      VARBL(J,3)=VARS(M)
      XBL(J,3)=XYU(M)
   30 CONTINUE
   31 IF(NI.EQ.0)GOTO 41
      DO 40 J=1,NI
      K=K+1
      M=I1+K-1
      VARBL(J,1)=VARS(M)
      XBL(J,1)=XYU(M)
   40 CONTINUE
   41 CONTINUE
C
C     STAMPA CARATT. DI UN BLOCCO
C
      WRITE(6,1001)NOMBLC(I,1),NOMBLC(I,2),NOMSUB(I)
 1001 FORMAT(///10X,'BLOCCO ',2A4,2X,'(SUB. ',A4,')'//)
      MM=NU+NS
      WRITE(6,1002)NI,MM,NS,NU
 1002 FORMAT(10X,I3,' INGRESSI',40X,I3,' USCITE'/40X,I3,
     $       ' VAR.STATO',16X,I3,' VAR.ALG.'//)
      MX=NI
      IF(MX.LT.NS)MX=NS
      IF(MX.LT.NU)MX=NU
      DO 70 K=1,MX
        IF((VARBL(K,1).NE.' ').AND.(VARBL(K,2).NE.' ')
     &  .AND.(VARBL(K,3).NE.' ')) THEN
   	       write(6,1010) (VARBL(K,IK),XBL(K,IK),IK=1,3)
   	       GOTO 70
   	ELSE IF ((VARBL(K,1).NE.' ').AND.(VARBL(K,2).NE.' ')) THEN
	   write(6,1020) (VARBL(K,IK),XBL(K,IK),IK=1,2)
   	GOTO 70
   	ELSE IF ((VARBL(K,1).NE.' ').AND.(VARBL(K,3).NE.' ')) THEN	
	   write(6,1030) VARBL(K,1),XBL(K,1),VARBL(K,3),XBL(K,3)
   	GOTO 70
   	ELSE IF ((VARBL(K,2).NE.' ').AND.(VARBL(K,3).NE.' ')) THEN	      
   	   write(6,1040) VARBL(K,2),XBL(K,2),VARBL(K,3),XBL(K,3)
   	GOTO 70
   	ELSE IF (VARBL(K,1).NE.' ') THEN		  
   	   write(6,1050) VARBL(K,1),XBL(K,1)
   	GOTO 70
   	ELSE IF (VARBL(K,2).NE.' ') THEN			
   	   write(6,1060) VARBL(K,2),XBL(K,2)
   	GOTO 70
   	ELSE IF (VARBL(K,3).NE.' ') THEN		  
   	   write(6,1070) VARBL(K,3),XBL(K,3)
   	ENDIF
            
   70 CONTINUE
  100 CONTINUE
      RETURN
      
1010   FORMAT(14X,    A8,1X,G12.5,9X, A8,1X,G12.5,9X,A8,1X,G12.5)       
1020   FORMAT(14X,    A8,1X,G12.5,9X, A8,1X,G12.5               )       
1030   FORMAT(14X,    A8,1X,G12.5,9X, 21X        ,9X,A8,1X,G12.5)       
1040   FORMAT(14X,    21X        ,9X, A8,1X,G12.5,9X,A8,1X,G12.5)       
1050   FORMAT(14X,    A8,1X,G12.5)       
1060   FORMAT(14X,    21X        ,9X, A8,1X,G12.5)       
1070   FORMAT(14X,    21X        ,9X, 21X        ,9X,A8,1X,G12.5)       

      END
            
