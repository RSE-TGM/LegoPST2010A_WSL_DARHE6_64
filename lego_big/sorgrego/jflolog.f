C******************************************************************************
C modulo jflolog.f
C tipo 
C release 1.3
C data 8/10/93
C reserver @(#)jflolog.f	1.3
C******************************************************************************
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

C Procedura contenete la variabile per l'identificazione della versione
C
      SUBROUTINE SCCS_jflolog
      CHARACTER*80 SccsID
      END
