C*********************************************************************
C       Fortran Source:             jflolog.f
C       Subsystem:              2
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:23:41 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_jflolog_f
      CHARACTER*80  RepoID
      COMMON /CM_jflolog_f / RepoID
      DATA RepoID/'@(#)2,fsrc,jflolog.f,2'/
      END
C**********************************************************************
      LOGICAL FUNCTION JFLOLOG(A)
      REAL A
      IF (MOD(NINT(ABS(A)),2).EQ.0) THEN
         JFLOLOG=.FALSE. 
      ELSE
         JFLOLOG=.TRUE.
      ENDIF
      RETURN
      END
C
C-------------------------------------------
C
      REAL FUNCTION JLOGFLO(J)
      LOGICAL J
      IF (J) THEN 
         JLOGFLO=1.
      ELSE
         JLOGFLO=0.
      END IF
      RETURN
      END
