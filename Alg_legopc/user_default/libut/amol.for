C**********************************************************************
C modulo amol.f
C tipo 
C release 5.3
C data 11/19/97
C reserver @(#)amol.f	5.3
C**********************************************************************
C
      SUBROUTINE AMOLI3(IFO,IOB,DEBL)
C*****************************************************************************
C
C
C        BLOCCO MOLTIPLICATORE DI PIU` SEGNALI
C
C
C*****************************************************************************
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/AMOL01/IBLOC
      COMMON/AMOL02/NCEL,NPAR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'AMOL'/
C
      CALL AMOLI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 1
      NINGRE = NCEL
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3001)IOB
 3001 FORMAT('UMOL',A4,2X,
     & '--UA-- OUTPUT ANALOG SIGNAL FROM MULTIPLIER')
      DO I=1,NCEL
C
      WRITE(IFO,3003)I,IOB,I
 3003 FORMAT('I',I1,'MO',A4,2X,
     & '--IN-- INPUT SIGNAL', I2, ' TO MULTIPLIER')
C
      ENDDO
C
      RETURN
      END
      SUBROUTINE AMOLI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/AMOL01/IBLOC
      COMMON/AMOL02/NCEL,NPAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
   1  WRITE(6,*)'   HOW MANY INPUT SIGNALS ? (MAX 9)'
      READ(5,*)NCEL
      IF(NCEL.LT.0.OR.NCEL.GT.9) GO TO 1
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
      RETURN
      END
      SUBROUTINE AMOLI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     &  IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
C*******************************************
C
C____ AMOL - BLOCCO MOLTIPLICATORE CON USCITA LIMITATA
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      NIN=IV2-IV1
C
      GO TO(100,200), IFUN
 100  CONTINUE
C
C____ CHIAMATE AL MODULO AMOL PER SCRIVERE I DATI
C
      IDP=ID1
      CALL AMOLSI(IFUN,DATI,IDP,NIN)
C
      RETURN
C
C____ LETTURA DA FILE14 DEL NOME DEL BLOCCO
C
  200 READ(14,1000)
 1000 FORMAT(A)
C
C____ CHIAMATE AL MODULO AMOL PER LEGGERE I DATI
C
      IDP=ID1
      CALL AMOLSI(IFUN,DATI,IDP,NIN)
C
      ID2=IDP
C
C____ COSTANTI DI NORMALIZZAZIONE
C
      DO I=1,NIN+1
      CNXYU(IV1+I-1 )=1.
      ENDDO
C
C____ TOLLERANZA
C
      TOL(1)=1.E-3
      RETURN
      END
      SUBROUTINE AMOLSI(IFUN,DATI,ID,NIN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION DATI(*)
C
      GO TO (100,200),IFUN
C
C____ SCRITTURA SUL FILE 14 DEI DATI DI AMOL
C
  100 CONTINUE
      WRITE(14,500)
  500 FORMAT('    U MAX    =          *    U MIN    =          *')
      RETURN
C
C____ LETTURA DA FILE 14 DEI DATI DI PROP
C
  200 CONTINUE
      READ(14,502)UMAX,UMIN
  502 FORMAT(3(14X,F10.0,1X))
C
       IF(CNORM.EQ.0.)CNORM=1.
      DATI(ID   )=NIN
      DATI(ID+1 )=UMAX
      DATI(ID+2 )=UMIN
C
      ID=ID+2
      RETURN
      END
      SUBROUTINE AMOLC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      LOGICAL KREGIM
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT
C*******************************************
C
C____ AMOL - BLOCCO MOLTIPLICATORE CON USCITA LIMITATA
C
C*********** INIZIO ISTRUZIONI DICHIARATIVE
      REAL II (9)                                                       !SNGL
C      DOUBLE PRECISION II (9)                                           !DBLE
      LOGICAL SAT
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      NIN  =DATI(IPD   )
      UMAX =DATI(IPD+1 )
      UMIN =DATI(IPD+2 )
C
      UU   = XYU(IXYU)
      DO I=1,NIN
        II(I)= XYU(IXYU +I)
      ENDDO
C
      GO TO (1,100,2),IFUN
C
C____ TOPOLOGIA JACOBIANO
C
 1    DO I=1,NIN+1
      AJAC(1,I)=1.
      ENDDO
      RETURN
C
C____ COEFFICIENTI JACOBIANO
C
 2    CONTINUE
C
      IDD=IPD
      CALL AMOLSR(UUC,II,IDD,DATI,SAT,NIN,UMAX,UMIN)
C
      IF(.NOT.SAT) THEN
	 AJAC(1,1)=-1.
	 DO I=1,NIN
	   AMO=1.
	   DO J=1,NIN
	     IF(I.NE.J) THEN
		AMO=AMO*II(J)
	     ENDIF
	   ENDDO
	   AJAC(1,I+1)=AMO
	 ENDDO
      ELSE
	 AJAC(1,1)=-1.
      ENDIF
      RETURN
C
C____ CALCOLO DELLA RISPOSTA DEI REGOLATORI
C
 100  CONTINUE
C
      IDD=IPD
      CALL AMOLSR(UUC,II,IDD,DATI,SAT,NIN,UMAX,UMIN)
C
C____ RESIDUI
C
      RNI(  1) = UU-UUC
      RETURN
      END
      SUBROUTINE AMOLSR(UU,II,ID,DATI,SAT,NIN,UMAX,UMIN)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION DATI(*)
      REAL      II(*)                                                  !SNGL
C       DOUBLE PRECISION      II(*)                                      !DBLE
      LOGICAL SAT
C
      UU=1.
      DO I=1,NIN
      UU = UU*II(I)
      ENDDO
C
      SAT=.FALSE.
       IF(UU.LT.UMIN) THEN
	  UU=UMIN
	  SAT=.TRUE.
       ENDIF
       IF(UU.GT.UMAX) THEN
	  UU=UMAX
	  SAT=.TRUE.
       ENDIF
C
      RETURN
      END
CC
      SUBROUTINE AMOLD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $      IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
