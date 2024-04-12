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
     $     MX3,RNI,IRJ,ICJ,NZMAX,MXCOL,MXROW,NOSUB,PESI,
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
      INTEGER INDP(*),INDG(*),IEQ(*)  
      REAL*8 FJD(*),PD(*),GD(*),D1(*),D2(*),D3(*),WD(*),EPS,ZD
      PARAMETER(ZD=0.D+0,IWR1=6,IWR2=0)  
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
      real*4 etime,tmp(2),tt,ttot,tres,tjac,twa,twb                  
C     external etime 
      
      if((stampa1.eq.1).or.(stampa2.eq.1))then   
      open(unit=55,file='stampe',status='unknown',form='formatted')
      write(55,*)' metodo wgsa wgsb '                                
      write(55,*)
      endif                  
      if(stampa1.eq.1)then                                    
      write(55,*)' dimensione ',neqsis,nnoto,noto                
      write(55,*)
      endif                                                    

      WRITE(6,200)
  200 FORMAT(//10X, 'VALORE DEL PESO ZERO',
     $            ' (DEFAULT PESO ZERO = 0.01)') 
      READ(5,*) PESO0
      IF(PESO0.LE.0.)PESO0=0.01E+0
      WRITE(6,201)
  201 FORMAT(//10X, 'TOLLERANZA PER IL METODO GRAM SCHMIDT'/
     $         10X '(DEFAULT TOLLERANZA = 1.D-5)') 
      READ(5,*) EPS
      IF(EPS.LE.0.)EPS=1.D-5
      WRITE(6,202)PESO0,EPS
  202 FORMAT(//10X,'PESO ZERO = ',E12.5
     $        /10X,'TOLLERANZA PER IL METODO GRAM SCHMIDT = ',D12.5//)          

      MMX1=MX1
      MMX3=MX3
      MMX5=MX5
      CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)
      CALL LEGBL1(NOTO,IPI,IPVRI,UU,XYU)
      IGO=1
C

C 
      CALL PESIWD(NNOTO,PESI,PESO0,WD)  ! pesi inversi      
      BETA=.5
      IBETA=0
      ITERT=0
      ITER=0     
      VAR=0.
      VARR=0.
      JAC=0
      JACYES=1
      
      tres=0.           
      tjac=0.           
      twa=0.           
      twb=0.           
      nres=0           
      njac=0           
      nwa=0             
      nwb=0            
      nnzt=0           
C     ttot=etime(tmp)   

      ICONVE=0
      DO WHILE(ICONVE.EQ.0)

      ICONVE=1        ! calcolo residui
C     tt=etime(tmp)                     
      CALL RESREG(NBL,ISLB,NUSTA,NUSCI,IPDATI,DATI,IP,TN,CDT,XYU,RN,
     $  ICONV,SIVAR,MMX1,NEQSIS,IPVRS,TOLL,ICONVE,NOBLC,MMX3,RNI,NOSUB)  
C     tt=etime(tmp)-tt                  
      tres=tres+tt                      
      nres=nres+1                       
      if(stampa1.eq.1)write(55,*)'tempo residui  ',tt   
      VAR=SNRM2(NEQSIS,RN,1)/NEQSIS  ! calcolo della norma residui
      if(stampa1.eq.1)
     *write(55,*)'itert iter var kbeta',itert,iter,var,kbeta    	 

      IF(ICONVE.EQ.0)THEN
      
        IF(JACYES.EQ.0)THEN
          IF((VAR.LE.VARR).AND.(ITER.GE.NITERJ))THEN
            JACYES=1 !superato numero max iterazioni, calcolare lo jacobiano
          ELSEIF(VAR.GT.VARR)THEN !difficoltà di convergenza     
            CALL SSWTCH(2,LL)
            IF(LL.EQ.1)THEN

            WRITE(6,1000)VAR,VARR

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
ccc           CALL LEGBL1(NOTO ,IPI,IPVRI,UU,XYU)  !**
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
C         tt=etime(tmp)                         
          CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)      ! calcolo jacobiano
ccc       CALL LEGBL1(NOTO ,IPI,IPVRI,UU,XYU)    !**
          CALL JACREG(NBL,ISLB,IPDATI,IP,XYU,DATI,IPVRS,NUSCI,NUSTA,
     $              NZMAX,NZTER,IRJ,ICJ, FJ,NEQSIS, RIGA,AJAC,
     $              MMX5,NOBLC,MMX3,RNI,NOSUB,NNOTO,IPNP) 
C         tt=etime(tmp)-tt                       
          tjac=tjac+tt                           
          njac=njac+1                           
          nnzt=nnzt+nzter                       
          if(stampa1.eq.1)write(55,*)'tempo jacobiano',tt,nzter 

C         fattorizzazione gram-schmidt pesato
C         tt=etime(tmp)                     
          CALL PUNT(NEQSIS,NZTER,IRJ,IPN)  ! creazione puntatore di fj
          CALL SNDB(NZTER,FJ,FJD)          ! copia fj in fjd doppia precisione
          CALL WGSA(NEQSIS,NNOTO,FJD,ICJ,IPN,IPNA,IPNB,WD,ZD,EPS,PD,
     $      INDP,IPNP,NZPMX,GD,INDG,IPNG,IPNR,NZGMX,D1,D2,D3,IRK,IEQ,
     $      IWR1,IER)      
C         tt=etime(tmp)-tt                  
          twa=twa+tt                         
          nwa=nwa+1                          
          if(stampa1.eq.1)write(55,*)'tempo wgsa     ',tt   

          IF(IER.NE.0)THEN
            CALL WGSERR(IER)
            CALL LGABRT
          ENDIF
        ELSE    !superamento num.max.jacob.   

          WRITE(6,1005)TEMPO
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
C         tt=etime(tmp)                   
          CALL SNDB(NEQSIS,RN,D3)   ! copia rn in d3 doppia precisione
          CALL WGSB(NEQSIS,NNOTO,FJD,ICJ,IPN,D3,PD,INDP,IPNP, !risoluzione
     $              GD,INDG,IPNG,D1,D2,IRK,IEQ,IWR2)
          CALL DBSN(NNOTO,D3,TN)    ! copia d3 in tn semplice precisione
C         tt=etime(tmp)-tt                
          twb=twb+tt                      
          nwb=nwb+1                       
          if(stampa1.eq.1)write(55,*)'tempo wgsb     ',tt    

          CALL SSWTCH(5,LL)
          IF(LL.EQ.1)THEN

            WRITE(6,4501)  !soluzioni del sistema lineare
            WRITE(6,4500)(TN(I),I=1,NNOTO)
            WRITE(6,3901)   !soluzioni nulle del sistema lineare

            DO I=1,NNOTO
              DEX=ABS(TN(I))
              IF(DEX.LE.0.)THEN

                WRITE(6,3900)I

              ENDIF
            ENDDO
          ENDIF                                          !eventuale
          IF(NUMS.GT.0)CALL SMORZ(NUMS,PCEN,NNOTO,XY,TN) !smorzamento in tn
          CALL SAXPY(NNOTO,1.,TN,1,XY,1)  !xy=xy+tn  aggiornamento soluzione   
          CALL SSWTCH(5,LL)
          IF(LL.EQ.1)THEN

            WRITE(6,4502)
            WRITE(6,4500)(XY(I),I=1,NNOTO)

          ENDIF
          CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)
ccc       CALL LEGBL1(NOTO,IPI,IPVRI,UU,XYU)     !**
        ENDIF
      ENDIF           
      ENDIF
      ENDDO

      IF(IGO.EQ.-1)THEN   !soluzione non trovata

        WRITE(6,1003)
        WRITE(6,7656)VAR

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

        WRITE(6,1028)RN(IRX),IRX,TOLL(IRX)
        WRITE(6,1030)ICEF  !numero equazioni non verificate
        WRITE(6,1029)

      ENDIF

C     IL SISTEMA EST RISOLTO
  
      CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)
ccc   CALL LEGBL1(NOTO,IPI,IPVRI,UU,XYU)      !**

      WRITE(6,3152)TEMPO,ITERT,JAC

C     ttot=etime(tmp)-ttot 
      if((stampa1.eq.1).or.(stampa2.eq.1))then 
      write(55,*)                                                   
      write(55,*)'tempo  residui   ',tres,tres/nres,nres            
      write(55,*)'tempo  jacobiano ',tjac,tjac/njac,njac,nnzt/njac   
      write(55,*)'tempo  wgsa      ',twa,twa/nwa,nwa                
      write(55,*)'tempo  wgsb      ',twb,twb/nwb,nwb                 
      write(55,*)'tempo totale     ',ttot                           
      close(55)
      endif  
      RETURN            
 1000 FORMAT(///10X,'DIFFICOLTA DI CONVERGENZA N(I)= ',E15.8,1X,
     $   '  N(I-1) =',E15.8)      
 1410 FORMAT(1X,'Convergence problem N(I)= ',E15.8,1X,
     $   '  N(I-1) =',E15.8,'\0')      
 1400 FORMAT(1X,'Jacobian matrix computed at iteration # ',I4,'\0')
 1005 FORMAT(///10X,'SUPERATO IL NUMERO MASSIMO DI JACOBIANI DURANTE ',
     $   'LA SOLUZIONE '/10X,'DEL SISTEMA ALG-DIFF AL TEMPO ', F8.3 //)
 4501 FORMAT(//10X,'SOLUZIONI DEL SISTEMA LINEARE')
 4500 FORMAT(10(1X,E12.5))       
 3901 FORMAT(//10X,'SOLUZIONI NULLE DEL SISTEMA LINEARE')
 3900 FORMAT(10X,I6)     
 4502 FORMAT(//10X,'SOLUZIONI DEL SISTEMA NON-LINEARE')
 1003 FORMAT(//10X,'NON RIESCO A RISOLVERE IL SISTEMA DI REGIME ')
 7656 FORMAT(10X,'NORMA RESIDUI= ',E15.8//)
 1028 FORMAT(//10X,'RESIDUO MASSIMO ',E12.5,' NELL EQUAZIONE',I4/
     $       10X,'TOLLERANZA ',E12.5//)
 1030 FORMAT(/10X,I4,' EQUAZIONI NON SONO VERIFICATE '//)
 1029 FORMAT(//10X,'PER CAPIRE L ANDAMENTO ITERATIVO DELLA SOLUZIONE'
     $   /10X,'RIPETERE L ESECUZIONE ASSEGNANDO I SSWTCH'
     $   /10X,' 1  -STAMPA DELLA TOPOLOGIA '
     $   /10X,' 2  -STAMPA DEI RESIDUI '/10X,' 3  -STAMPA JACOBIANI'
     $   /10X,' 5  -SOLUZIONI DEL SISTEMA'//)
 1401 FORMAT(1X,'Number of iterations ',I4,' with ',I4,
     $       ' jacobian matrix computed.\0')
 3152 FORMAT(//10X,'SOL.SIS.ALG.-DIFF. AL TEMPO  ',F8.2
     $      /10X,'ITER.SOL.-RES.  ',I6/10X,'JACOBIANI',I6//)     
      END
