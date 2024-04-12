      LOGICAL FUNCTION JFLOLOG(A)
      REAL A
      IF (A.GT.-0.1 .AND. A.LT.0.1) THEN
         JFLOLOG=.FALSE. 
      ELSE IF (A.GT.0.9 .AND. A.LT.1.1) THEN
         JFLOLOG=.TRUE. 
      ELSE IF (A.GT.-1.1 .AND. A.LT.-0.9) THEN
         JFLOLOG=.TRUE. 
      ELSE IF (A.GT.-2.1 .AND. A.LT.-1.9) THEN
         JFLOLOG=.FALSE. 
      ELSE IF (A.GT.1.9 .AND. A.LT.2.1) THEN
         JFLOLOG=.FALSE. 
      ENDIF
      RETURN
      END
C
C-------------------------------------------
C
      REAL FUNCTION JLOGFLO(J)
      LOGICAL J
      IF (J.EQ.2) THEN 
         JLOGFLO=2.
      ELSE IF (J) THEN 
         JLOGFLO=1.
      ELSE
         JLOGFLO=0.
      END IF
      RETURN
      END
