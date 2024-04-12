       PROGRAM CREATAV
       CHARACTER*110 LINE
       REAL VALDA(130000)
       OPEN (UNIT=1,FILE='LECT.DAT',STATUS='OLD',
     $       FORM='FORMATTED')
       READ(1,'(A)') LINE
       ICORR=1
       DO WHILE (LINE(6:8).NE.'END')
              IF (LINE(6:10).NE.'FLOAT') THEN
                   READ(1,'(A)') LINE
              ELSE
                   DO WHILE (LINE(6:10).EQ.'FLOAT')
                     READ(LINE,'(10X,6(1X,E15.8))') 
     $                          (VALDA(I),I=ICORR,ICORR+5) 
                     ICORR=ICORR+6
                     READ(1,'(A)') LINE
                   ENDDO
              ENDIF
       ENDDO
       NVALDA=ICORR-1
       OPEN(UNIT=2,FILE='TAVOLE.DAT',STATUS='UNKNOWN',
     $      FORM='UNFORMATTED')
       WRITE(2) (VALDA(I),I=1,NVALDA)
       END
