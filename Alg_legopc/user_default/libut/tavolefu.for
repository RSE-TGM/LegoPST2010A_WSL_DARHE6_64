C******************************************************************************
C modulo tavolefumi.f
C tipo 
C release 4.2
C data 2/9/95
C reserver @(#)tavolefumi.f	4.2
C******************************************************************************
C*                                                                     *
C*                   VERSIONE MODIFICATA DA S.D.I.                     *
C*                          IL 29/5/1992                               *
C*                                                                     *
C***********************************************************************
C
C*******************************************************************************
C
C           FUNCTIONS PER IL CALCOLO DELLE PROPRIETA` DEI FUMI :
C           
C           CPFU  = CALORE SPECIFICO
C
C           HTFU  = ENTALPIA O TEMPERATURA
C
C           DHTFU = CALCOLA (@H/@UMID) DEI FUMI A TEMPERATURA COSTANTE (tkel)
C
C*******************************************************************************
C
      REAL FUNCTION CPFU(TKELVIN,H2O)                                   !SNGL
C      DOUBLE PRECISION FUNCTION CPFU(TKELVIN,H2O)                       !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C
C     CALCOLA IL CALORE SPECIFICO DEI FUMI IN
C     FUNZIONE DELLA TEMPERATURA E UMIDITA'.
C
      IF (TKELVIN-2072.35681) 1,1,2
  1   CP0 = 924.257+0.2269*TKELVIN
      GO TO 3
  2   CP0 = -2983.379+2.1125*TKELVIN
  3   CPFU = CP0*(1.+H2O/1.05)
      RETURN
      END
C
      REAL FUNCTION HTFU(ENTR,UMID,JHT)                                 !SNGL
C      DOUBLE PRECISION FUNCTION HTFU(ENTR,UMID,JHT)                     !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C
C     CALCOLA L'ENTALPIA DEI FUMI IN FUNZIONE DELLA
C     TEMPERATURA E VICEVERSA.
C
C$$$$$$$$$$$
      ICONT=0      
C$$$$$$$$$$$
      IF(JHT-1) 2,2,1
C
C     PER JHT=1 INGRESSO IN T, USCITA IN H
C     PER JHT=2 INGRESSO IN H, USCITA IN T.
C
  1   H = ENTR/2326.
      T = H*(4.-H/2048.-UMID-UMID)+32.
      GOTO 8
  2   T = (ENTR-273.15)*1.8+32.
  8   X = T/256.-UMID/(UMID+0.146)
C$$$$$$$$
      ICONT= ICONT +1
C$$$$$$$$
      X = X*X+18.539
      Y = (.4272461E-3*UMID+.1425781E-3)*X+(.2387694*UMID+.2635135)
     $    *(1.-2./X)
      HC = Y*(T-32.)
      U  = T-3311.
      IF (U) 4,4,3
  3   HC = HC+U*U/8192.
  4   IF(JHT-1) 7,7,5
  5   DT  = (H-HC)/(Y+HC/8192.)
      T  = T+DT
C$$$$$$$$
      IF(ICONT.GT.100) THEN
      WRITE(6,1000)ENTR,T
 1000 FORMAT(//10X,'SUPERATO IL NUMERO MASSIMO DI ITERAZIONI IN HTFU'
     $/10X, 'ENTALPIA FUMI = ',E12.5, 'TEMPERATURA TROVATA = ',E12.5)
C---- Valore fittizio negativo di HTFU 
      HTFU = -1.E+10
      RETURN
      ENDIF
C$$$$$$$$
      IF (DT-.2) 6,10,8
  6   IF (DT+.2) 8,10,10
  7   HTFU = HC*2326.
      RETURN
 10   HTFU = (T-32.)/1.8+273.15
      RETURN
      END
C
      REAL FUNCTION DHTFU(TKEL,UMID)                                    !SNGL
C      DOUBLE PRECISION FUNCTION DHTFU(TKEL,UMID)                        !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C--- calcola (@h/@umid) dei fumi a temperatura costante (TKEL)
      T = (TKEL-273.15)*1.8+32.
      X1= T/256.-UMID/(UMID+0.146)
      DX1=-.146/(UMID+.146)**2
      X = X1*X1+18.539
      DX=2*X1*DX1
      DY = (.4272461E-3*UMID+.1425781E-3)*DX+X*.4272461E-3
     $     +(.2387694*UMID+.2635135)*2/X**2*DX+(1.-2./X)*.2387694
      DHC = DY*(T-32.)
      DHTFU = DHC*2326.
      RETURN
      END
