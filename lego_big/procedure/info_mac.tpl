      PROGRAM INFOMAC
      IMPLICIT NONE
      CHARACTER *4 IOB, SIMBXREG, SIMBXLOW, DESC*80, NOMXBLOC*6
      COMMON /NOMXREG/ SIMBXREG
      REAL DATI (1000)
      INTEGER IPD, IER, I

      IOB = 'ZZ'
      SIMBXREG = '####'
      DO 666 I = 1, 4
          IF (ICHAR (SIMBXREG(I:I)) .GT. 64 .AND. 
     $    ICHAR (SIMBXREG(I:I)) .LE. 90) THEN
                 SIMBXLOW(I:I) = CHAR (ICHAR (SIMBXREG(I:I)) + 32)
          ELSE
                 SIMBXLOW(I:I) = SIMBXREG(I:I)
          ENDIF
  666 CONTINUE
      DESC = 'Generazione informazioni modulo ####'
      OPEN (14, FILE = SIMBXLOW // 'info.dat', STATUS = 'UNKNOWN')
C (per VAX)     $    RECORDTYPE = 'VARIABLE', CARRIAGECONTROL = 'LIST')
      CALL ####I3 (14, IOB, DESC)

      NOMXBLOC = '####' // IOB(1:2)
      IPD = 0
      IER = 0

      CALL ####$I (1, NOMXBLOC, 0, DATI, IPD, IER)
      CLOSE (14)

      STOP 'Fine esecuzione info_mac'
      END
