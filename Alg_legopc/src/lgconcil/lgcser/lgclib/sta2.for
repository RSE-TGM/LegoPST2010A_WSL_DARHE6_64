C******************************************************************************
C modulo sta2.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)sta2.f	2.1
C******************************************************************************
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
C     Modifica MAURO RECINE 05.12.1991 (variabile FORMA)
      CHARACTER * 56 FORMA
C
C     SUBROUTINE STAMPA CARATTERISTICHE DEL SISTEMA
C
      DATA BLK/' '/,IBLK/' '/,IX/'X'/,ICAR/'I'/
      DATA  IFORM /'(14X', ', A8' , ',1X,' , 'G12.' ,
     $             '5,9X' , ',A8,' , '1X,' , 'G12.' ,
     $             '5,9X' , ',A8,' , '1X,' , 'G12.' ,
     $             '5,9X' , ')' /
      DATA IFA/'A4'/,IFX/',17X'/
C
C      IFORM(4),IFORM(5)
C      IFORM(8),IFORM(9)
C      IFORM(12),IFORM(13)
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
      WRITE(90,1001)NOMBLC(I,1),NOMBLC(I,2),NOMSUB(I)
 1001 FORMAT(///10X,'BLOCCO ',2A4,2X,'(SUB. ',A4,')'//)
      MM=NU+NS
      WRITE(90,1002)NI,MM,NS,NU
 1002 FORMAT(10X,I3,' INGRESSI',40X,I3,' USCITE'/40X,I3,
     $       ' VAR.STATO',16X,I3,' VAR.ALG.'//)
      MX=NI
      IF(MX.LT.NS)MX=NS
      IF(MX.LT.NU)MX=NU
   65 DO 70 K=1,MX
      DO 66 KK=1,14
      NFORM(KK)=IFORM(KK)
   66 CONTINUE
      IF(VARBL(K,1).NE.' ')GO TO 67
      XBL(K,1)=BLK
      NFORM(4)=IFA
      NFORM(5)=IFX
   67 IF(VARBL(K,2).NE.' ')GO TO 68
      XBL(K,2)=BLK
      NFORM(8)=IFA
      NFORM(9)=IFX
   68 IF(VARBL(K,3).NE.' ')GO TO 69
      XBL(K,3)=BLK
      NFORM(12)=IFA
      NFORM(13)=IFX
   69 WRITE (FORMA,'(14A4)') NFORM
      WRITE(90,FORMA) (VARBL(K,IK),XBL(K,IK),IK=1,3)
   70 CONTINUE
  100 CONTINUE
      RETURN
      END
