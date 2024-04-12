CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE WGSREG(NOTO,NNOTO,IGO,NEQSIS,NBL,ISLB,NUSTA,NUSCI,
     $     IPDATI,DATI,IP,TN,CDT,XYU,RN,ICONV,SIVAR,MX1,IPVRS,TOLL,
     $     RNO,XYO,JACYES,NITERJ,NJACMX,IPS,IPVRT,
     $     XY,UU,NU,IPI,IPVRI,FJ,RIGA, NEQAL,TEMPO,AJAC,MX5,NOBLC,
     $     MX3,RNI,IRJ,ICJ,NZMAX,MXCOL,MXROW,NOSUB,PESI,SENSINDX,
     $     NZPMX,NZGMX,IPN,IPNA,IPNB,IPNP,IPNG,IPNR,INDP,INDG,IEQ,   
     $     FJD,PD,GD,D1,D2,D3,WD,NUMS,PCEN,stampa1,stampa2)

      CHARACTER*8 SIVAR(MX1)
      DIMENSION ISLB(*),NUSTA(*),NUSCI(*),IPDATI(*),DATI(*),IP(*),
     $     TN(*),XYU(*),RN(*),ICONV(*),IPVRS(*),TOLL(*),PESI(*),
     $     RNO(*),XYO(*),IPS(*),IPVRT(*),XY(*),UU(*),IPI(*),IPVRI(*),
     $     FJ(*),RIGA(*), AJAC(MX5,MX5),NOBLC(MX3,2),
     $     RNI(*),IRJ(*),ICJ(*)
      DIMENSION NOSUB(*)  !tavole      
      INTEGER IPN(*),IPNA(*),IPNB(*),IPNP(*),IPNG(*),IPNR(*)
      INTEGER INDP(*),INDG(*),IEQ(*),SENSINDX(*)
      REAL*8 FJD(*),PD(*),GD(*),D1(*),D2(*),D3(*),WD(*),EPS,ZD
      PARAMETER(ZD=0.D+0,IWR1=90,IWR2=0)
C
C      RISOLVE IL SISTEMA ALGEBRICO COL METODO DI NEWTON-RAPHSON SMORZ.
C
C      IGO=1   SISTEMA RISOLTO
C      IGO=-1  SISTEMA NON RISOLTO
C
C     DESCRIZIONE  DEI VETTORI
C       - MATRICE JACOBIANA -   FJ,IRJ,ICJ
C       - RESIDUI-SOLUZIONI - TN,   RN ,RNO, XY ,XYO
C       - INGRESSI  -          UU
C       - TOLLERANZE -           TOLL
C       - MATRICE COLLEG. DIRETTA -  IPVRS
C       - MATRICI COLLEG. INVERSE -  IPS,IPVRT , IPI,IPVRI
C       - VETTORI IN INGRESSO TIPICI- ISLB,NUSTA,NUSCI,IP,XYU,
C                                      IPDATI,DATI,SIVAR
C       - VETTORI DI COMODO  -  RIGA,ICONV,AJAC(MX5,MX5),
C       - VETTORI GRAM-SCHMIDT - IPN,IPNA,IPNB,IPNP,IPNG,IPNR,INDP,INDG, 
C                                IEQ,FJD,PD,GD,D1,D2,D3,WD 
C       - PARAMETRI GRAM-SCHMIDT - EPS,ZD
C       - PARAMETRI GRAM-SCHMIDT STAMPE - IWR1,IWR2   
C

C
      CHARACTER*6 STAMPE
      INTEGER SMOR
      REAL TOLLER, PESO0, TOLGS
C      
      COMMON/SETTINGS/TOLLER,SMOR,PESO0,TOLGS,STAMPE
C      
      IF(PESO0.LE.0.)PESO0=0.01E+0
      EPS=TOLGS
      IF(EPS.LE.0.)EPS=1.D-5
C
      MMX1=MX1
      MMX3=MX3
      MMX5=MX5
      CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)
      CALL LEGBL1(NOTO,IPI,IPVRI,UU,XYU)
      IGO=1
C

C 
      CALL PESIWD(NNOTO,PESI,PESO0,WD,SENSINDX) ! pesi inversi      
      BETA=.5
      IBETA=0
      ITERT=0
      ITER=0     
      VAR=0.
      VARR=0.
      JAC=0
      JACYES=1
      
      ICONVE=0
      DO WHILE(ICONVE.EQ.0)

      ICONVE=1        ! calcolo residui
                   
      CALL RESREG(NBL,ISLB,NUSTA,NUSCI,IPDATI,DATI,IP,TN,CDT,XYU,RN,
     $  ICONV,SIVAR,MMX1,NEQSIS,IPVRS,TOLL,ICONVE,NOBLC,MMX3,RNI,NOSUB)  

      VAR=SNRM2(NEQSIS,RN,1)/NEQSIS  ! calcolo della norma residui

      IF(ICONVE.EQ.0)THEN
      
        IF(JACYES.EQ.0)THEN
          IF((VAR.LE.VARR).AND.(ITER.GE.NITERJ))THEN
            JACYES=1 !superato numero max iterazioni, calcolare lo jacobiano
          ELSEIF(VAR.GT.VARR)THEN !difficoltà di convergenza     
            CALL SSWTCH(2,LL)
            IF(LL.EQ.1)THEN

            WRITE(90,1000)VAR,VARR

            ENDIF      
            IF(JOK.EQ.0)THEN    ! calcolare lo jacobiano
              CALL SCOPY(NEQSIS,RNO,1,RN,1)  ! copia rno in rn
              CALL SCOPY(NNOTO,XYO,1,XY,1)   ! copia xyo in xy
              VAR=VARR
              JACYES=1      
            ELSEIF(KBETA.LT.5)THEN  !(jok=1)      
              KBETA=KBETA+1  !correzioni delle soluzioni con beta  
              CALL SAXPY(NNOTO,1.,XYO,1,XY,1)  !  xy=xy+xyo
              CALL SSCAL(NNOTO,0.5,XY,1)       !  xy=(1/2)xy 

              CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)
            ELSE  ! (kbeta=5)  ripristino soluzione migliore               
              CALL SCOPY(NEQSIS,RNO,1,RN,1)  ! copia rno in rn
              CALL SCOPY(NNOTO,XYO,1,XY,1)   ! copia xyo in xy
              VAR=VARR
              ICONVE=-1 
              IGO=-1  ! soluzione non trovata  
            ENDIF          
          ENDIF
        ENDIF  

      IF(JACYES.EQ.1)THEN      
        IF(JAC.LT.NJACMX)THEN
          ITER=0
          JACYES=0
          JAC=JAC+1
          JOK=1
              
          CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)      ! calcolo jacobiano
          CALL JACREG(NBL,ISLB,IPDATI,IP,XYU,DATI,IPVRS,NUSCI,NUSTA,
     $              NZMAX,NZTER,IRJ,ICJ, FJ,NEQSIS, RIGA,AJAC,
     $              MMX5,NOBLC,MMX3,RNI,NOSUB,NNOTO,IPNP) 

C               
          CALL PUNT(NEQSIS,NZTER,IRJ,IPN)  ! creazione puntatore di fj
          CALL SNDB(NZTER,FJ,FJD)          ! copia fj in fjd doppia precisione
          CALL WGSA(NEQSIS,NNOTO,FJD,ICJ,IPN,IPNA,IPNB,WD,ZD,EPS,PD,
     $      INDP,IPNP,NZPMX,GD,INDG,IPNG,IPNR,NZGMX,D1,D2,D3,IRK,IEQ,
     $      IWR1,IER)      
C
          IF(IER.NE.0)THEN
            CALL WGSERR(IER)
            CALL LGABRT
          ENDIF
        ELSE    !superamento num.max.jacob.   
C
          IGO=-1

          ICONVE=-1
        ENDIF
      ENDIF
      
      IF(ICONVE.NE.-1)THEN     !calcolare la soluzione
        IF((ITER.EQ.0).OR.((VAR.LE.VARR).AND.(ITER.LT.NITERJ)))THEN
          IF((ITERT.EQ.0).OR.(VAR.LE.VARR))THEN
            CALL SCOPY(NNOTO,XY,1,XYO,1)   ! copia xy in xyo
            CALL SCOPY(NEQSIS,RN,1,RNO,1)  ! copia rn in rno         
            VARR=VAR 
            KBETA=0                               
          ENDIF
          IF(ITER.EQ.1)JOK=0
          ITER=ITER+1
          ITERT=ITERT+1          
          CALL SNDB(NEQSIS,RN,D3)   ! copia rn in d3 doppia precisione
          CALL WGSB(NEQSIS,NNOTO,FJD,ICJ,IPN,D3,PD,INDP,IPNP, !risoluzione
     $              GD,INDG,IPNG,D1,D2,IRK,IEQ,IWR2)
          CALL DBSN(NNOTO,D3,TN)    ! copia d3 in tn semplice precisione
C
          CALL SSWTCH(5,LL)
          IF(LL.EQ.1)THEN
            WRITE(90,4501)  !soluzioni del sistema lineare
            WRITE(90,4500)(TN(I),I=1,NNOTO)
            WRITE(90,3901)   !soluzioni nulle del sistema lineare
            DO I=1,NNOTO
              DEX=ABS(TN(I))
              IF(DEX.LE.0.)THEN
                WRITE(90,3900)I
              ENDIF
            ENDDO
          ENDIF                                          !eventuale
          IF(SMOR.GT.0)CALL SMORZ(NUMS,PCEN,NNOTO,XY,TN) !smorzamento in tn
          CALL SAXPY(NNOTO,1.,TN,1,XY,1)  !xy=xy+tn  aggiornamento soluzione   
          CALL SSWTCH(5,LL)
          IF(LL.EQ.1)THEN
            WRITE(90,4502)
            WRITE(90,4500)(XY(I),I=1,NNOTO)
          ENDIF
          CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)
        ENDIF
      ENDIF           
      ENDIF
      ENDDO

      IF (IGO.EQ.-1) THEN   !soluzione non trovata
C
        WRITE(90,9801)TEMPO,VAR
 9801   FORMAT('T = ',F8.2,' NON-SOLVED, Res.Norm = ',E15.8)
C
        OPEN(UNIT=98,FILE='TEMP.DAT',STATUS='UNKNOWN',FORM='FORMATTED')
        WRITE(98,9800)TEMPO,VAR
 9800   FORMAT('T = ',F8.2,' NON-SOLVED Res. =',1P,E7.1,'$')
        CLOSE(98)
C
        ICEF=ICONV(1)
        IRX=1
        RMAX=ABS(RN(1))
        DO I=2,NEQSIS
          ICEF=ICEF+ICONV(I)
          RA=ABS(RN(I))
          IF(RMAX.LT.RA)THEN
            IRX=I      !residuo massimo nella equaz. irx
            RMAX=RA
          ENDIF
        ENDDO
C
        WRITE(90,1028)RN(IRX),IRX,TOLL(IRX)
        WRITE(90,1030)ICEF  !numero equazioni non verificate
C
      ELSE
C
C     IL SISTEMA EST RISOLTO
C
        WRITE(90,9901)TEMPO,ITERT,JAC
 9901   FORMAT('T = ',F8.2,' N.ITER. = ',I2,' N.JAC. = ',I2)
C
        OPEN(UNIT=98,FILE='TEMP.DAT',STATUS='UNKNOWN',FORM='FORMATTED')
        WRITE(98,9900)TEMPO,ITERT,JAC
 9900   FORMAT('T = ',F8.2,' N.ITER. = ',I2,' N.JAC. = ',I2,'$')
        CLOSE(98)
      ENDIF
C
      CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)
C
      RETURN            
 1000 FORMAT(///10X,'DIFFICOLTA DI CONVERGENZA N(I)= ',E15.8,1X,
     $   '  N(I-1) =',E15.8)        
 4501 FORMAT(//10X,'SOLUZIONI DEL SISTEMA LINEARE')
 4500 FORMAT(10(1X,E12.5))       
 3901 FORMAT(//10X,'SOLUZIONI NULLE DEL SISTEMA LINEARE')
 3900 FORMAT(10X,I6)     
 4502 FORMAT(//10X,'SOLUZIONI DEL SISTEMA NON-LINEARE')
 1028 FORMAT(//10X,'RESIDUO MASSIMO ',E12.5,' NELL EQUAZIONE',I4/
     $       10X,'TOLLERANZA ',E12.5//)
 1030 FORMAT(/10X,I4,' EQUAZIONI NON SONO VERIFICATE '//)
      END
