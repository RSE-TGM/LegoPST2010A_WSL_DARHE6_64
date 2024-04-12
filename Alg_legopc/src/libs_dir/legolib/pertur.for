C******************************************************************************
C modulo pertur.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)pertur.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE PERTUR(NPER,ITPER,IPPER,IVPER,DATPER,UU,NU,
     $                  VARI,MX3,TEMPO,TSTEP,DTINT,IGRAD)
      DIMENSION ITPER(*),IPPER(*),IVPER(*),DATPER(*),UU(*)
      CHARACTER*8 VARI(MX3)
C
C     QUESTA SUBROUTINE,IN BASE AL TEMPO DEFINISCE IL VALORE DEGLI
C     INGRESSI AL SISTEMA CHE POSSONO VARIARE O CON UNA RAMPA O CON
C     UNA LEGGE TABULATA. - INOLTRE SCEGLIE IL PASSO DI INTEGRAZ.
C
      DTINT=TSTEP
C
      IGRAD=0
      IF(NPER.EQ.0)RETURN
C
C     DEFINISCE IL PASSO DI INTEGRAZ. DTINT SCEGLIENDOLO COME IL
C     PIU'PICCOLO FRA QUELLI CONSENTITI NELL'INTORNO DI 'TEMPO'.
C
      DTT=TSTEP/100.
      DO 20 I=1,NPER
      IT=ITPER(I)
      I1=IPPER(I)
      GO TO (1,20,5),IT
    1 KN=DATPER(I1+4)
      T1=DATPER(I1)
      T2=DATPER(I1+1)
      T1M=T1-DTT
      T2M=T2-DTT
      IF(TEMPO.GT.T2M)GO TO 20
      IF(TEMPO.LT.T1M)GO TO 20
      DTIN =TSTEP/KN
      IF(DTIN.LT.DTINT)DTINT=DTIN
      GO TO 20
C
C      PERTURBAZIONE A GRADINO
C
    5 T1=DATPER(I1)
      T1M=T1-DTT
       IF(TEMPO.LT.T1M)GO TO 20
      IGRAD=1
      DATPER(I1)=99999.
      DTINT=0.
      U0=DATPER(I1+1)
      UX=DATPER(I1+2)
      IPV=IVPER(I)
      UU(IPV)=UX*U0
   20 CONTINUE
C
C     SCELTA DEL PASSO DI TEMPO PER IL PASSO SUCCESSIVO
C
      TEMPOD=TEMPO+DTINT
C
      DTT=TSTEP/100.
      DO 102 I=1,NPER
      IT=ITPER(I)
      I1=IPPER(I)
      GO TO (101,102,102),IT
  101 KN=DATPER(I1+4)
      T1=DATPER(I1)
      T2=DATPER(I1+1)
      T1M=T1-DTT
      T2M=T2-DTT
      IF(TEMPOD.GT.T2M)GO TO 102
      IF(TEMPOD.LT.T1M)GO TO 102
      DTIN =TSTEP/KN
  102 CONTINUE
C
      IF(IGRAD.EQ.1)GO TO 105
C
      DO 100 I=1,NPER
      IPV=IVPER(I)
      IT=ITPER(I)
      I1= IPPER(I)
      I2= IPPER(I+1)-1
      GO TO (10,50,100),IT
C
C   PERTURBAZIONE A RAMPA
C
   10 T1=DATPER(I1  )
      T2=DATPER(I1+1)
      CU=DATPER(I1+2)
      UO=DATPER(I1+3)
      T1M=T1-DTT
      T2M=T2-DTT
      IF(TEMPO.GT.T2M)GO TO 100
      IF(TEMPO.LT.T1M)GO TO 100
      UT=UO*DTINT*CU
      UU(IPV)=UU(IPV)+UT
      GO TO 100
C
C     PERTURBAZIONE LEGGE TABULATA
C
  50  UO=DATPER(I1)
      KPUN=(I2-I1)/2
      DO 60 J=1,KPUN
      K1= J*2-1
      K2= K1+1
      T1= DATPER(K1+I1)
      T2= DATPER(K1+I1+2)
      T1M=T1-DTT
      T2M=T2-DTT
      IF(TEMPO.GT.T2M)GO TO 60
      IF(TEMPO.LT.T1M)GO TO 60
      GO TO 70
   60 CONTINUE
      GO TO 100
   70 U1= DATPER(I1+K2)
      U2= DATPER(I1+K2+2)
      CU=(U2-U1)/(T2-T1)
      UT=UO*DTINT*CU
      UU(IPV)=UU(IPV)+UT
  100 CONTINUE
  105 CALL SSWTCH(1,LL)
      IF(LL.NE.1)RETURN
C
C     STAMPE DI CONTROLLO
C
      WRITE(6,1000)
 1000 FORMAT(///10X,'STAMPE OPZIONALI SSWTCH-1 '//)
      TT=TEMPO + DTINT
      WRITE(6,1001)TT,DTINT
 1001 FORMAT(/10X,'VALORI DEGLI INGRESSI AL TEMPO ',F8.3/
     $        10X,'PASSO DI INTEGRAZIONE SCELTO ',F8.5//)
      DO 120 I=1,NU
      WRITE(6,1002) VARI(I),UU(I)
 1002 FORMAT(10X,A8,2X,E15.8)
  120 CONTINUE
      RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_pertur
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)pertur.f	2.1\t7/10/95'/
      END
