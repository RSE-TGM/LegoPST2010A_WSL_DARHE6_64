C******************************************************************************
C modulo legpri.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)legpri.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LEGPRI(IVAI,NSTSTP,TSTEP,TFIN,ITITOL,IGRAD,NVSTP,
     $                  ISTMP,SIVAR,MX1,VARI,MX3,NEQSIS,NU,XY,UU,
     $                  CNXY,CNUU,XYOUT,SYOUT,MX2,TEMPO,KSTP)
      DIMENSION ITITOL(*),ISTMP(*),XY(*),
     $           UU(*),CNXY(*),CNUU(*),XYOUT(*)
      CHARACTER*8 SIVAR(MX1),VARI(MX3),SYOUT(MX2)
C
      MMX1=MX1
      MMX2=MX2
      MMX3=MX3
      GO TO (1,10),IVAI
C
C     STAMPA INTESTAZIONE
C
    1 WRITE(6,1000)(ITITOL(I),I=1,20),TSTEP,TFIN
 1000 FORMAT(1H1///50X,'PROGRAMMA  L E G O '
     $      ///20X,'CALCOLO DEL TRANSITORIO '
     $      //10X,'***',20A4,'***'
     $      //10X,'PASSO DI INTEGRAZIONE ',F10.4,' (SEC)'
     $      //10X,'DURATA DEL TRANSITORIO ',F10.2,' (SEC) '///)
      RETURN
C
   10 CALL PASSOT(NSTSTP,TSTEP,TEMPO,IGRAD,KOUT)
C
      KSTP=KOUT
      IF(KOUT.EQ.0)RETURN
C
      NN=0
      CALL PLPROT(NVSTP,ISTMP,SIVAR,MMX1,VARI,MMX3,NEQSIS,NU,
     $            XY,UU,CNXY,CNUU,NN,XYOUT,SYOUT,MMX2)
C
      IF(NN.EQ.0)RETURN
      WRITE(6,1001)TEMPO,(SYOUT(I),XYOUT(I),I=1,NN)
 1001 FORMAT(//10X,'TEMPO= ',F10.4,' (SEC)'/(5(1X,A8,'= ',E12.5,1X)))
      RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_legpri
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)legpri.f	2.1\t7/10/95'/
      END
