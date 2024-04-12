      PROGRAM TRADF22
C
C     18.02.99
C
      PARAMETER (MAXNPAS=1000,MAXVAR=1000)
      CHARACTER*20 TITOLO
      CHARACTER*8 VAR(4), SYOUT(MAXVAR)
      CHARACTER*4 MODE
      INTEGER IND(4)
      REAL VAR_T0(4)
      REAL T(MAXNPAS),V(4,MAXNPAS)
      REAL XYOUT(MAXVAR)
      OPEN(UNIT=22,FILE='proc/f22.dat',
     $     STATUS='OLD',FORM='UNFORMATTED')
      OPEN(UNIT=1,FILE='f22.asc',
     $     STATUS='UNKNOWN',FORM='FORMATTED')
      OPEN(UNIT=2,FILE='tradf22.inp',
     $     STATUS='UNKNOWN',FORM='FORMATTED')
      NVAR=0
	READ(2,'(A4)') MODE
      DO I=1,4
         READ(2,'(A8)') VAR(I)
         IF (VAR(I)(1:3).NE.'EOF') THEN
            NVAR=NVAR+1
         ELSE
            GOTO 10
         ENDIF
      ENDDO
10    CONTINUE
      READ(22)
      READ(22) NN,(SYOUT(I), I=1,NN)
      DO I=1,NVAR
         DO J=1,NN
            IF(SYOUT(J).EQ.VAR(I)) THEN
               IND(I)=J
               GOTO 20
            ENDIF
         ENDDO
         WRITE(6,*) 'VARIABILE ',VAR(I),' NON TROVATA'
         STOP
20       CONTINUE
      ENDDO
      DO I=1,MAXNPAS
         READ(22,END=30) T(I),(XYOUT(J),J=1,NN)
         NPAS=I
         IF (MODE.EQ.'dim.') THEN    
            DO J=1,NVAR
               V(J,NPAS)=XYOUT(IND(J))
            ENDDO
         ELSE IF (MODE.EQ.'p.u.') THEN       
            DO J=1,NVAR
               IF (NPAS.EQ.1) THEN
                  VAR_T0(J)=XYOUT(IND(J))
                  IF (VAR_T0(J).EQ.0.) VAR_T0(J)=1.
               ENDIF
               V(J,NPAS)=XYOUT(IND(J))/VAR_T0(J)
            ENDDO
         ELSE
            WRITE(6,*) 'CONFIGURAZIONE NON PERMESSA'
         ENDIF
      ENDDO
30    CONTINUE
      IF (MODE.EQ.'p.u.') THEN
         WRITE(1,40) (VAR_T0(I),I=1,NVAR)
      ENDIF
40    FORMAT('##',8X,4(1X,G10.4))      
      IF (NVAR.EQ.1) THEN
         DO I=1,NPAS
            WRITE(1,61) T(I),V(1,I)
61          FORMAT(F10.2,1X,G10.4)
         ENDDO
      ELSE IF (NVAR.EQ.2) THEN
         DO I=1,NPAS
            WRITE(1,62) T(I),(V(J,I), J=1,NVAR)
62          FORMAT(F10.2,2(1X,G10.4))
         ENDDO
      ELSE IF (NVAR.EQ.3) THEN
         DO I=1,NPAS
            WRITE(1,63) T(I),(V(J,I), J=1,NVAR)
63          FORMAT(F10.2,3(1X,G10.4))
         ENDDO
      ELSE 
         DO I=1,NPAS
            WRITE(1,64) T(I),(V(J,I), J=1,NVAR)
64          FORMAT(F10.2,4(1X,G10.4))
         ENDDO
      ENDIF
C
      CLOSE(UNIT=1)
      CLOSE(UNIT=2)
      CLOSE(UNIT=22)
C
      END
