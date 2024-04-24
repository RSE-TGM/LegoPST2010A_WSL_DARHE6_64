C*********************************************************************
C       Fortran Source:             main_edi14.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:14:40 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_main_edi14_f
      CHARACTER*80  RepoID
      COMMON /CM_main_edi14_f / RepoID
      DATA RepoID/'@(#)1,fsrc,main_edi14.f,2'/
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

      PROGRAM EDI14
C
       include 'lg_parameter.fh'
C
C parameter di EDI14
C
C      KN001 = N. VARIABILI SU FILE 14
C      KN002 = N. BLOCCHI
C      KN003 = N. LINEE FILE 14
C
      PARAMETER (KN001=N005, KN002=N002, KN003=KN001+N007)
C
      DIMENSION LINE(33),IA(KN003,2),IX(KN003,3),ICD(KN001),
     $          NMBL1(KN002),NMBL2(KN002),IPDT(KN002)
      CHARACTER*15 IAV(KN003)
      CHARACTER*88 IBV(KN003)
C
      CHARACTER*100 INPFIL,OLDFIL,OUTFIL
      DATA IEOF/'EOF'/
  101 FORMAT(A)
  102 FORMAT(//)
      INPFIL='proc/f14.dat'
      OLDFIL='f14.dat'
      OUTFIL='f14.out'
C
    2 OPEN(UNIT=1,FILE=INPFIL,STATUS='OLD')
      OPEN(UNIT=3,FILE=OLDFIL,STATUS='OLD')
      OPEN(UNIT=2,FILE=OUTFIL,STATUS='UNKNOWN')
C
      MX1=KN003
      REWIND 1
      REWIND 2
      IPOSF1=0
      IRCF1I=0
C
   10 CALL PFILE5(IA,IX,ICD,MX1,NMBL1,NMBL2,IPDT,NBL,NVAR,LINE,
     $            IAV,IBV)
      CALL PFILE6(LINE,NVAR,IA,IX,MX1,ICD,NBL,NMBL1,NMBL2,IPDT,
     $            IAV,IBV)
      CALL LGSTOP
      STOP
      END
C
C
C
      SUBROUTINE PFILE3(NF,NREC,IGO,LINE,IPOSF1)
      DIMENSION LINE(*)
      DATA IEOF/'EOF'/,ILG/'*LG*'/,IAS/'*'/,IFIS/' FIS'/,IBLO/' BLO'/
C
C      IGO =1  COMMENTO
C          =2  VARIABILI
C          =3  BLOCCO
C          =4  DATI
C          =5  EOF
C
      IGO=0
      READ(NF,1000)(LINE(I),I=1,33)
 1000 FORMAT(33A4)
      NREC=NREC+1
      IF(LINE(2).NE.IEOF)GO TO 10
      KEOF=1
      IGO=5
      GO TO 100
C
   10 IF(LINE(1).EQ.IAS)GO TO 30
      IF(LINE(1).EQ.ILG)GO TO 40
      GO TO (15,20),IPOSF1
   15 IGO=2
      GO TO 100
   20 IGO=4
      GO TO 100
   30 IGO=1
      GO TO 100
   40 IGO=1
      IF(IPOSF1.NE.0)GO TO 45
      IPOSF1=1
      GO TO 100
   45 IF(LINE(3).EQ.IFIS)GO TO 50
      IF(LINE(4).EQ.IBLO)IGO=3
      GO TO 100
   50 IPOSF1=2
  100 RETURN
      END
C
C
C
      SUBROUTINE PFILE5(IA,IX,ICD,MX1,NMBL1,NMBL2,IPDT,NBL,NVAR,LINE,
     $                  IAV,IBV)
C
C      SUBROUTINE PER LA LETTURA DEI SIMBOLI DEI DATI E DEI VALORI
C      DAL FILE CONSIDERATO VECCHIO (3)
C
      DIMENSION LINE(*),IB(3,2),IP(3,3),IA(MX1,2),IX(MX1,3),ICD(*),
     $   NMBL1(*),NMBL2(*),IPDT(*)
      CHARACTER*(*) IAV(*)
      CHARACTER*(*) IBV(*)
      CHARACTER LIN*132
      DATA ILG/'*LG*'/,IDT/'DATI'/,IEOFR/' '/,IEOF/'EOF'/,
     $     IAS/'*'/
      REWIND 3
      DO 1 I=1,4
      READ(3,1000)
    1 CONTINUE
      N=0
C
C      LETTURA VARIABILI
C
    2 N=N+1
      READ(3,1000)IKO,IA(N,1),IA(N,2),IX(N,1),IX(N,2),IX(N,3),
     $            IAV(N)(1:15),ICD(N),IBV(N)(1:88)
 1000 FORMAT(3A4,2X,2A4,A2,A,A4,1X,A)
      IF(IKO.NE.ILG)GO TO 2
      N=N-1
      IF(IA(N+1,1).NE.IDT)GO TO 2
C
C      LETTURA DATI DEI BLOCCHI
C
      KBL=0
      IPDT(1)=N
      NVAR=N
   20 READ(3,1001)(LINE(I),I=1,33)
 1001 FORMAT(33A4)
      IF(LINE(2).EQ.IEOF)GO TO 50
      IF(LINE(1).EQ.IAS)GO TO 20
C
      IF(LINE(1).NE.ILG)GO TO 30
C------BLOCCO
      KBL=KBL+1
      IPDT(KBL+1)=IPDT(KBL)
      IPDT(KBL)=IPDT(KBL)+1
      NMBL1(KBL)=LINE(6)
      NMBL2(KBL)=LINE(7)
      GO TO 20
C------DATI DI UN BLOCCO
   30 WRITE(LIN,1001)(LINE(I),I=1,33)
      READ(LIN,1002)(IB(I,1),IB(I,2),IP(I,1),IP(I,2),IP(I,3),I=1,3)
 1002 FORMAT(3(4X,2A4,2X,2A4,A2,1X))
      M=1
      IF(IB(2,1).NE.IEOFR)M=2
      IF(IB(3,1).NE.IEOFR)M=3
      IPDT(KBL+1)=IPDT(KBL+1)+M
      DO 40 I=1,M
      N=N+1
      IA(N,1)=IB(I,1)
      IA(N,2)=IB(I,2)
      IX(N,1)=IP(I,1)
      IX(N,2)=IP(I,2)
      IX(N,3)=IP(I,3)
   40 CONTINUE
      GO TO 20
   50 NBL=KBL
      NSY=N
      IPDT(KBL+1)=NSY+1
      RETURN
      END
C
C
C
      SUBROUTINE PFILE6(LINE,NVAR,IA,IX,MX1,ICD,NBL,NMBL1,NMBL2,IPDT,
     $                 IAV,IBV)
      DIMENSION LINE(*),IA(MX1,2),IX(MX1,3),ICD(*),NMBL1(*),NMBL2(*),
     $          IPDT(*),INDT(3,2),IVDT(3,3)
      CHARACTER*(*) IAV(1)
      CHARACTER*(*) IBV(1)
      CHARACTER*132 PLIN,LIN
      DATA IEOFR/' '/,IBL/' '/,IEOFR1/' '/
C
      REWIND 3
C
      READ (1,1000)(LINE(I),I=1,33)
      READ(3,1000)
      WRITE(2,1000)(LINE(I),I=1,33)
C
      READ (1,1000)
      READ (3,1000)(LINE(I),I=1,33)
      WRITE(2,1000)(LINE(I),I=1,33)
C
      READ (1,1000)
      READ (3,1000)(LINE(I),I=1,33)
      WRITE(2,1000)(LINE(I),I=1,33)
C
      READ (1,1000)
      READ (3,1000)(LINE(I),I=1,33)
      WRITE(2,1000)(LINE(I),I=1,33)
C
      IPOSF1=0
      IPRIM=0
      IPRIM1=0
    1 CALL PFILE3(1,NREC,IGO,LINE,IPOSF1)
      WRITE(PLIN,1000)(LINE(KK),KK=1,33)
      GO TO (10,20,40,60,10),IGO
C
   10 WRITE(2,1000)(LINE(I),I=1,33)
 1000 FORMAT(33A4)
      IF(IGO.NE.5)GO TO 1
      GO TO 80
C-----VARIABILI
   20 DO 25 I=1,NVAR
      IF(LINE(2).NE.IA(I,1))GO TO 25
      IF(LINE(3).EQ.IA(I,2))GO TO 30
   25 CONTINUE
C
      IF(IPRIM.EQ.1)GO TO 26
      WRITE(6,*)' '
      WRITE(6,*)'**** VARIABILI DEL MODELLO ATTUALE'
      WRITE(6,*)'     NON RITROVATE NEL MODELLO DA COPIARE'
      WRITE(6,*)' '
      WRITE(6,*)' '
      IPRIM=1
   26 CONTINUE
      WRITE(6,1000)(LINE(I),I=1,33)
      WRITE(2,1000)(LINE(I),I=1,33)
      GO TO 1
   30 K=I
      WRITE(2,1001)PLIN(1:12),(IX(K,J),J=1,3),
     $              PLIN(25:39),ICD(K),PLIN(45:132)
 1001 FORMAT(A,' =',2A4,A2,A,A4,'*',A)
      GO TO 1
C
C-----BLOCCO
C
   40 DO 45 I=1,NBL
      IF(LINE(6).NE.NMBL1(I))GO TO 45
      IF(LINE(7).EQ.NMBL2(I))GO TO 50
   45 CONTINUE
C
      IF(IPRIM1.EQ.1)GO TO 46
      WRITE(6,*)' '
      WRITE(6,*)'**** BLOCCHI DEL MODELLO ATTUALE'
      WRITE(6,*)'     NON RITROVATI NEL MODELLO DA COPIARE'
      WRITE(6,*)' '
      WRITE(6,*)' '
      IPRIM1=1
   46 CONTINUE
      WRITE(6,1000)(LINE(I),I=1,33)
      KPTB=0
      GO TO 55
   50 KPTB=I
   55 WRITE(2,1000)(LINE(I),I=1,33)
      GO TO 1
C
C----DATI DI UN BLOCCO
C
   60 IF(KPTB.EQ.0)GO TO 55
      WRITE(LIN,1000)(LINE(I),I=1,33)
      READ(LIN,1002)((INDT(I,J),J=1,2),I=1,3)
 1002 FORMAT(3(4X,2A4,13X))
      M=1
      IF(INDT(2,1).EQ.IEOFR1)GO TO 63
      M=2
      IF(INDT(3,1).EQ.IEOFR)GO TO 63
      M=3
   63 CONTINUE
      I1=IPDT(KPTB)
      I2=IPDT(KPTB+1)-1
      DO 70 I=1,M
      DO 65 J=I1,I2
      IF(INDT(I,1).NE.IA(J,1))GO TO 65
      IF(INDT(I,2).EQ.IA(J,2))GO TO 67
   65 CONTINUE
      WRITE(6,3003)INDT(I,1),INDT(I,2),NMBL1(KPTB),NMBL2(KPTB)
 3003 FORMAT(/5X,'***DATO',2A4,' BL.',2A4,' NON TROVATO'/)
      IVDT(I,1)=IBL
      IVDT(I,2)=IBL
      IVDT(I,3)=IBL
      GO TO 70
   67 IVDT(I,1)=IX(J,1)
      IVDT(I,2)=IX(J,2)
      IVDT(I,3)=IX(J,3)
   70 CONTINUE
      WRITE(2,1004)((INDT(I,J),J=1,2),(IVDT(I,J),J=1,3),I=1,M)
 1004 FORMAT(3(4X,2A4,' =',2A4,A2,'*'))
      GO TO 1
C
   80 WRITE(6,3005)
 3005 FORMAT(//5X,'ESECUZIONE TERMINATA')
      RETURN
      END
C            
