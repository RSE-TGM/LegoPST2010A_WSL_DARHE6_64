C*********************************************************************
C       Fortran Source:             leout.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:27:08 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_leout_f
      CHARACTER*80  RepoID
      COMMON /CM_leout_f / RepoID
      DATA RepoID/'@(#)1,fsrc,leout.f,2'/
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

      SUBROUTINE LEOUT(NEQSIS,SIVAR,MMX1,NU,VARI,MMX3,NVPLT,NSTPLT,
     $           IPLOT,NVSTP,NSTSTP,ISTMP)
      DIMENSION IPLOT(*),ISTMP(*)
      CHARACTER*8 SIVAR(MMX1),VARI(MMX3)
C
C      LETTURA DATI DI PLOTTAGGIO E STAMPA
C
      MX1=MMX1
      NSTSTP=99999
      MX3=MMX3
      WRITE(6,1000)
 1000 FORMAT(10X,'QUALI VARIABILI VUOI REGISTRARE PER L''USCITA ',
     $   'GRAFICA? (*=TUTTE)')
      CALL LEOU(NEQSIS,SIVAR,MX1,NU,VARI,MX3,NVPLT,IPLOT)
      IF(NVPLT.EQ.0) THEN
      NSTPLT=99999
      ELSE
      NSTPLT=1
      WRITE(6,1001)
 1001 FORMAT(/10X,'PASSO DI REGISTRAZIONE? (INTERO CHE MOLTIPLICA IL',
     $   ' PASSO DI INTEGRAZIONE)')
      READ(5,*)NSTP
      IF(NSTP.GT.0)NSTPLT=NSTP
      ENDIF
      WRITE(6,1002)
 1002 FORMAT(10X,'QUALI VARIABILI VUOI STAMPARE DURANTE IL CALCOLO? '
     $   /10X,'(*=TUTTE)')
      CALL LEOU(NEQSIS,SIVAR,MX1,NU,VARI,MX3,NVSTP,ISTMP)
      IF(NVSTP.EQ.0) THEN
      NSTSTP=99999
      ELSE
      NSTSTP=1
      WRITE(6,1003)
 1003 FORMAT(/10X,'PASSO DI STAMPA? (INTERO CHE MOLTIPLICA IL PASSO',
     $   ' DI INTEGRAZIONE)')
      READ(5,*)NSTP
      IF(NSTP.GT.0)NSTSTP=NSTP
      ENDIF
   10 RETURN
      END
C            
