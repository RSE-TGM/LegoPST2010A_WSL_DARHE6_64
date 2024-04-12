CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LEGREG(NOTO,NNOTO,IGO,NEQSIS,NBL,ISLB,NUSTA,NUSCI,
     $     IPDATI,DATI,IP,TN,CDT,XYU,RN,ICONV,SIVAR,MX1,IPVRS,TOLL,
     $     RNO,XYO,JACYES,NITERJ,NJACMX,IPS,IPVRT,

     $     XY,UU,NU,IPI,IPVRI,FJ,RIGA, NEQAL,TEMPO,AJAC,MX5,NOBLC,
     $     MX3,RNI,IRJ,ICJ,IKMA28,IWMA28,WMA28,NZMAX,MXCOL,
     $     MXROW,NOSUB,NUMS,PCEN,stampa1,stampa2)

      CHARACTER*8 SIVAR(MX1)
      DIMENSION ISLB(*),NUSTA(*),NUSCI(*),IPDATI(*),DATI(*),IP(*),
     $     TN(*),XYU(*),RN(*),ICONV(*),IPVRS(*),TOLL(*),
     $     RNO(*),XYO(*),IPS(*),IPVRT(*),XY(*),UU(*),IPI(*),IPVRI(*),

     $     FJ(*),RIGA(*), AJAC(MX5,MX5),NOBLC(MX3,2),
     $     RNI(*),IRJ(*),ICJ(*),IKMA28(NNOTO,*),IWMA28(*),WMA28(*)
      DIMENSION NOSUB(*)   !tavole
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
C       - VETTORI DI COMODO  -  RIGA,ICONV,AJAC(MX5,MX5)
C       - VETTORI MA28       -  IKMA28,IWMA28,WMA28
C      

C
      real*4 etime,tmp(2),tt,ttot,tres,tjac,tma,tmb                 
C     external etime
      
      if((stampa1.eq.1).or.(stampa2.eq.1))then   
      open(unit=55,file='stampe',status='unknown',form='formatted') 
      write(55,*)' metodo ma28 '                                     
      write(55,*)
      endif                  
      if(stampa1.eq.1)then                                  
      write(55,*)' dimensione ',neqsis,nnoto,noto                   
      write(55,*)
      endif                                                  

      MMX1=MX1
      MMX3=MX3
      MMX5=MX5
      UPIV=.1
      MTMA28=1
      CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)
      CALL LEGBL1(NOTO,IPI,IPVRI,UU,XYU)
      IGO=1
C

C
      BETA=.5
      IBETA=0
      ZZ=0.
      ITERT=0
      ITER=0     
      VAR=0.
      VARR=0.
      JAC=0
      JACYES=1
      
      tres=0.         
      tjac=0.          
      tma=0.           
      tmb=0.           
      nres=0            
      njac=0           
      nma=0             
      nmb=0             
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
          ELSEIF(VAR.GT.VARR)THEN  !difficoltà di convergenza    
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
ccc           CALL LEGBL1(NOTO ,IPI,IPVRI,UU,XYU)   !**
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
     $              MMX5,NOBLC,MMX3,RNI,NOSUB,NNOTO,IWMA28)  
C         tt=etime(tmp)-tt                      
          tjac=tjac+tt                           
          njac=njac+1                            
          nnzt=nnzt+nzter                       
          if(stampa1.eq.1)write(55,*)'tempo jacobiano',tt,nzter  

C         fattorizzazione
C         tt=etime(tmp)                         
          CALL MA28A(NNOTO,NZTER,FJ,MXCOL,IRJ,MXROW,ICJ,UPIV,
     $               IKMA28,IWMA28,WMA28,IFLAG)
C         tt=etime(tmp)-tt                      
          tma=tma+tt                            
          nma=nma+1                             
          if(stampa1.eq.1)write(55,*)'tempo ma28a    ',tt         

          IF(IFLAG.NE.0)THEN
            CALL ER28A(IFLAG)
            IF(IFLAG.LE.2)THEN
              DO I=1,NNOTO       !stampa singolarità          
                IF(IKMA28(I,3).LT.0)THEN
                  WRITE(6,6666)IABS(IKMA28(I,2))
                  if(stampa1.eq.1)write(55,6666)iabs(ikma28(I,2))
                ENDIF  
              ENDDO
            ELSE

              WRITE(6,3528)  !esecuzione interrotta

              CALL LGABRT
            ENDIF
          ENDIF
        ELSE  !superamento num.max.jacob.     

          WRITE(6,1005)TEMPO
          IGO=-1

          ICONVE=-1
        ENDIF
      ENDIF

      IF(ICONVE.NE.-1)THEN    !calcolare la soluzione
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
          CALL SCOPY(NEQSIS,RN,1,TN,1)   ! copia rn in tn 
          CALL SCOPY(NNOTO-NEQSIS,ZZ,0,TN(NEQSIS+1),1)
          CALL MA28C(NNOTO,FJ,MXCOL,ICJ,IKMA28,TN,WMA28,MTMA28) !risoluzione
C         tt=etime(tmp)-tt                
          tmb=tmb+tt                       
          nmb=nmb+1                      
          if(stampa1.eq.1)write(55,*)'tempo ma28b    ',tt         

          CALL SSWTCH(5,LL)
          IF(LL.EQ.1)THEN

            WRITE(6,4501)  !soluzioni del sistema lineare
            WRITE(6,4500)(TN(I),I=1,NNOTO)
            WRITE(6,3901)  !soluzioni nulle del sistema lineare

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

            WRITE(6,4502)  !soluzioni del sistema non lineare
            WRITE(6,4500)(XY(I),I=1,NNOTO)

          ENDIF
          CALL LEGBL1(NNOTO,IPS,IPVRT,XY,XYU)
ccc       CALL LEGBL1(NOTO,IPI,IPVRI,UU,XYU)    !**
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
ccc   CALL LEGBL1(NOTO,IPI,IPVRI,UU,XYU)    !**

      WRITE(6,3152)TEMPO,ITERT,JAC

C     ttot=etime(tmp)-ttot 
      if((stampa1.eq.1).or.(stampa2.eq.1))then
      write(55,*)                
      write(55,*)'tempo  residui   ',tres,tres/nres,nres            
      write(55,*)'tempo  jacobiano ',tjac,tjac/njac,njac,nnzt/njac  
      write(55,*)'tempo  ma28a     ',tma,tma/nma,nma                
      write(55,*)'tempo  ma28c     ',tmb,tmb/nmb,nmb               
      write(55,*)'tempo totale     ',ttot                           
      close(55)
      endif  
      RETURN       
 1000 FORMAT(///10X,'DIFFICOLTA DI CONVERGENZA N(I)= ',E15.8,1X,
     $   '  N(I-1) =',E15.8)      
 1410 FORMAT(1X,'Convergence problem N(I)= ',E15.8,1X,
     $   '  N(I-1) =',E15.8,'\0')      
 1400 FORMAT(1X,'Jacobian matrix computed at iteration # ',I4,'\0')
 3528 FORMAT(10X,'ESECUZIONE INTERROTTA'/10X,'SI CONSIGLIA DI ',
     $   'CONTROLLARE LA SCELTA DELLE VARIABILI NOTE E DI QUELLE ',
     $   'INCOGNITE'/10X,'TENENDO CONTO DELLE EQUAZIONE DEL MODELLO'/
     $   10X,'RIESEGUIRE,TUTTAVIA,L''ATTIVITA ASSEGNANDO ',
     $   'TUTTI I SSWTCH'//)
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
 6666 FORMAT(1x,'singolarità nella riga',i4,8x)                    
*      IF(IKMA28(I,3).LT.0)WRITE(6,6667)IABS(IKMA28(I,2)),-IKMA28(I,3) 
* 6667 FORMAT(1x,'singolarità nella riga',i4,8x,
*     $       'colonna',i4,2x,'eliminata')            
      END

 
