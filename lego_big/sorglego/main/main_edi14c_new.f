
C*********************************************************************
C       Fortran Source:             main_edi14c.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Wed May 12 12:46:50 2004 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_main_edi14c_f
      CHARACTER*80  RepoID
      COMMON /CM_main_edi14c_f / RepoID
      DATA RepoID/'@(#)1,fsrc,main_edi14c.f,3'/
      END
C******************************************************************************
                    PROGRAM EDI14
C
       include 'lg_parameter.fh'
C
C parameter di EDI14
C
C      KN001 = N. VARIABILI SU FILE 14
C      KN002 = N. BLOCCHI
C      KN003 = N. LINEE FILE 14
C
      PARAMETER (KN001=N005, KN002=N002, KN003=KN001+N007)
C
      DIMENSION LINE(33)
      DIMENSION IA(KN003,2),IX(KN003,3),ICD(KN001),
     &          NMBL1(KN002),NMBL2(KN002),IPDT(KN002)
      CHARACTER*15 IA_V(KN003)
      CHARACTER*88 IB_V(KN003)
C
      CHARACTER*100 INPUT_FILE,OLD_FILE,OUT_FILE
      DATA IEOF/'EOF'/
100      FORMAT(5X,$,A)
101      FORMAT(A)
102      FORMAT(//)
C
C    Il programma EDI14 puo` essere usato da LEGOCAD o
C    dall'utente direttamente.
C    EDI14 ha quindi due diverse modalita` di lavoro.
C    EDI14 riconosce di essere chiamato da LEGOCAD 
C    se ,leggendo il file 4 ,trova un dato.
C   
C
C      READ(4,*,ERR=99)IO
C
C_______ modalita` di LEGOCAD
C
C      INPUT_FILE='[.PROC]F14.DAT'
C      OLD_FILE='F14.DAT'
C      OUT_FILE='F14.DAT'
C
C      IF(IO.EQ.1)GO TO 2
C
C      INPUT_FILE='F14.DAT'
C      OLD_FILE='F14.DAT'
C      OUT_FILE='[.PROC]F14.DAT'
C________ LETTURA DEL NOME DEL FILE "VECCHIO" DA CUI COPIARE I DATI
C      READ(4,101) OLD_FILE
C      GO TO 2
C
C
C_______ modalita` diretta 
C
C
  99  CONTINUE
      PRINT *,'           PROGRAMMA EDI14'
      PRINT *,'           ==============='
      PRINT *,' '
      PRINT *,'           TRASFERISCE I DATI FISICI E GEOMETRICI'
      PRINT *,' '
      PRINT *,'           DAL FILE F14 O F24 DI UN DATO MODELLO '
      PRINT *,' '
      PRINT *,'           AL MODELLO ATTUALE'
      PRINT *,' '
      PRINT *,'   F14.DAT + FILE_CHE_MI_DICI ====> EDI14.OUT'
      PRINT *,' '
      PRINT *,'  NOME DEL FILE DEL MODELLO DA CUI COPIARE I DATI ?   '
C________ LETTURA DEL NOME DEL FILE "VECCHIO" DA CUI COPIARE I DATI
      READ(5,101) OLD_FILE
      INPUT_FILE='f14.dat'
      OUT_FILE='edi14.out'
C
   2  OPEN(UNIT=1,FILE=INPUT_FILE,STATUS='OLD')
      OPEN(UNIT=3,FILE=OLD_FILE,STATUS='OLD')
      OPEN(UNIT=2,FILE=OUT_FILE,STATUS='UNKNOWN')
C
      MX1=KN003
      REWIND 1
      REWIND 2
      IPOSF1=0
      IRCF1I=0
C
 10   CALL PFILE5(IA,IX,ICD,MX1,NMBL1,NMBL2,IPDT,NBL,NVAR,LINE,
     &            IA_V,IB_V)
      CALL PFILE6(LINE,NVAR,IA,IX,MX1,ICD,NBL,NMBL1,NMBL2,IPDT,
     &            IA_V,IB_V)
      STOP ' '
      END
      SUBROUTINE PFILE3(NF,NREC,IGO,LINE,IPOSF1)
      DATA IEOF/'EOF'/,ILG/'*LG*'/,IAS/'*'/,IFIS/' FIS'/,IBLO/' BLO'/
      DIMENSION LINE(*)
C
C      IGO =1  COMMENTO
C          =2  VARIABILI
C          =3  BLOCCO
C          =4  DATI
C          =5  EOF
C
      IGO=0
      READ(NF,1000)(LINE(I),I=1,33)
 1000 FORMAT(33A4)
      NREC=NREC+1
      IF(LINE(2).NE.IEOF)GO TO 10
      KEOF=1
      IGO=5
      GO TO 100
C
   10 IF(LINE(1).EQ.IAS)GO TO 30
      IF(LINE(1).EQ.ILG)GO TO 40
      GO TO (15,20),IPOSF1
   15 IGO=2
      GO TO 100
   20 IGO=4
      GO TO 100
   30 IGO=1
      GO TO 100
   40 IGO=1
      IF(IPOSF1.NE.0)GO TO 45
      IPOSF1=1
      GO TO 100
   45 IF(LINE(3).EQ.IFIS)GO TO 50
      IF(LINE(4).EQ.IBLO)IGO=3
      GO TO 100
   50 IPOSF1=2
  100 RETURN
      END
      SUBROUTINE PFILE5(IA,IX,ICD,MX1,NMBL1,NMBL2,IPDT,NBL,NVAR,LINE,
     &                  IA_V,IB_V)
C
C      SUBROUTINE PER LA LETTURA DEI SIMBOLI DEI DATI E DEI VALORI
C      DAL FILE CONSIDERATO VECCHIO (3)
C
      DATA ILG/'*LG*'/,IDT/'DATI'/,IEOFR/' '/,IEOF/'EOF'/,
     &     IAS/'*'/
      DIMENSION LINE(*),IB(3,2),IP(3,3),IA(MX1,2),IX(MX1,3),ICD(*),
     &   NMBL1(*),NMBL2(*),IPDT(*)
      CHARACTER*(*) IA_V(*)
      CHARACTER*(*) IB_V(*)
      CHARACTER LIN*132
      REWIND 3
      DO 1 I=1,4
      READ(3,1000)
    1 CONTINUE
      N=0
C
C      LETTURA VARIABILI
C
    2 N=N+1
      READ(3,1000)IKO,IA(N,1),IA(N,2),IX(N,1),IX(N,2),IX(N,3),
     &            IA_V(N)(1:15),ICD(N),IB_V(N)(1:88)
 1000 FORMAT(3A4,2X,2A4,A2,A,A4,1X,A)
      IF(IKO.NE.ILG)GO TO 2
      N=N-1
      IF(IA(N+1,1).NE.IDT)GO TO 2
C
C      LETTURA DATI DEI BLOCCHI
C
      KBL=0
      IPDT(1)=N
      NVAR=N
   20 READ(3,1001)(LINE(I),I=1,33)
 1001 FORMAT(33A4)
      IF(LINE(2).EQ.IEOF)GO TO 50
      IF(LINE(1).EQ.IAS)GO TO 20
C
      IF(LINE(1).NE.ILG)GO TO 30
C------BLOCCO
      KBL=KBL+1
      IPDT(KBL+1)=IPDT(KBL)
      IPDT(KBL)=IPDT(KBL)+1
      NMBL1(KBL)=LINE(6)
      NMBL2(KBL)=LINE(7)
      GO TO 20
C------DATI DI UN BLOCCO
   30 WRITE(LIN,1001)(LINE(I),I=1,33)
      READ(LIN,1002)(IB(I,1),IB(I,2),IP(I,1),IP(I,2),IP(I,3),I=1,3)
 1002 FORMAT(3(4X,2A4,2X,2A4,A2,1X))
      M=1
      IF(IB(2,1).NE.IEOFR)M=2
      IF(IB(3,1).NE.IEOFR)M=3
      IPDT(KBL+1)=IPDT(KBL+1)+M
      DO 40 I=1,M
      N=N+1
      IA(N,1)=IB(I,1)
      IA(N,2)=IB(I,2)
      IX(N,1)=IP(I,1)
      IX(N,2)=IP(I,2)
      IX(N,3)=IP(I,3)
   40 CONTINUE
      GO TO 20
   50 NBL=KBL
      NSY=N
      IPDT(KBL+1)=NSY+1
      RETURN
      END
      SUBROUTINE PFILE6(LINE,NVAR,IA,IX,MX1,ICD,NBL,NMBL1,NMBL2,IPDT,
     &                 IA_V,IB_V)
      DIMENSION LINE(*),IA(MX1,2),IX(MX1,3),ICD(*),NMBL1(*),NMBL2(*),
     &           IPDT(*)
      DIMENSION INDT(3,2),IVDT(3,3)
      DATA IEOFR/' '/,IBL/' '/,IEOFR1/' '/
      CHARACTER*(*) IA_V(*)
      CHARACTER*(*) IB_V(*)
      CHARACTER LIN*132
      CHARACTER*132 PLIN
      DATA IEOFR/' '/,IBL/' '/,IEOFR1/' '/
C
      REWIND 3
C
      READ (1,1000)(LINE(I),I=1,33)
      READ(3,1000)
      WRITE(2,1000)(LINE(I),I=1,33)
C
      READ (1,1000)
      READ (3,1000)(LINE(I),I=1,33)
      WRITE(2,1000)(LINE(I),I=1,33)
C
      READ (1,1000)
      READ (3,1000)(LINE(I),I=1,33)
      WRITE(2,1000)(LINE(I),I=1,33)
C
      READ (1,1000)
      READ (3,1000)(LINE(I),I=1,33)
      WRITE(2,1000)(LINE(I),I=1,33)
C
      IPOSF1=0
C
      IPRIM=0
      IPRIM1=0
    1 CALL PFILE3(1,NREC,IGO,LINE,IPOSF1)
      WRITE(PLIN,'(33A4)')(LINE(KK),KK=1,33)
      GO TO (10,20,40,60,10),IGO
C
   10 WRITE(2,1000)(LINE(I),I=1,33)
 1000 FORMAT(33A4)
      IF(IGO.NE.5)GO TO 1
      GO TO 80
C-----VARIABILI
   20 DO 25 I=1,NVAR
      IF(LINE(2).NE.IA(I,1))GO TO 25
      IF((LINE(3).EQ.IA(I,2)).OR.
     &   (IVERECC(LINE(3),IA(I,2)).EQ.1))GOTO 30
   25 CONTINUE
C
      IF(IPRIM.EQ.1)GO TO 26
      WRITE(6,*)' '
      WRITE(6,*)'**** VARIABILI DEL MODELLO ATTUALE'
      WRITE(6,*)'     NON RITROVATE NEL MODELLO DA COPIARE'
      WRITE(6,*)' '
      WRITE(6,*)' '
      IPRIM=1
  26  CONTINUE
      WRITE(6,3321)(LINE(I),I=1,33)
 3321 FORMAT(33A4)
      WRITE(2,1000)(LINE(I),I=1,33)
      GO TO 1
   30 K=I
C      WRITE(2,1001)(LINE(J),J=1,3),(IX(K,J),J=1,3),
C     &              IA_V(K),ICD(K),IB_V(K)
C 1001 FORMAT(3A4,' =',2A4,A2,A,A4,'*',A)
      WRITE(2,1001)PLIN(1:12),(IX(K,J),J=1,3),
     &              PLIN(25:39),ICD(K),PLIN(45:132)
 1001 FORMAT(A,' =',2A4,A2,A,A4,'*',A)
      GO TO 1
C
C-----BLOCCO
C
   40 DO 45 I=1,NBL
      IF(LINE(6).NE.NMBL1(I))GO TO 45
      IF((LINE(7).EQ.NMBL2(I)).OR.(IVERECC(LINE(7),NMBL2(I)).EQ.1))
     & GO TO 50
   45 CONTINUE
C
      IF(IPRIM1.EQ.1)GO TO 46
      WRITE(6,*)' '
      WRITE(6,*)'**** BLOCCHI DEL MODELLO ATTUALE'
      WRITE(6,*)'     NON RITROVATI NEL MODELLO DA COPIARE'
      WRITE(6,*)' '
      WRITE(6,*)' '
      IPRIM1=1
  46  CONTINUE
      WRITE(6,3321)(LINE(I),I=1,33)
      KPTB=0
      GO TO 55
   50 KPTB=I
   55 WRITE(2,1000)(LINE(I),I=1,33)
      GO TO 1
C
C----DATI DI UN BLOCCO
C
   60 IF(KPTB.EQ.0)GO TO 55
      WRITE(LIN,1000)(LINE(I),I=1,33)
      READ(LIN,1002)((INDT(I,J),J=1,2),I=1,3)
 1002 FORMAT(3(4X,2A4,13X))
      M=1
      IF(INDT(2,1).EQ.IEOFR1)GO TO 63
      M=2
      IF(INDT(3,1).EQ.IEOFR)GO TO 63
      M=3
   63 CONTINUE
      I1=IPDT(KPTB)
      I2=IPDT(KPTB+1)-1
      DO 70 I=1,M
      DO 65 J=I1,I2
      IF(INDT(I,1).NE.IA(J,1))GO TO 65
      IF(INDT(I,2).EQ.IA(J,2))GO TO 67
   65 CONTINUE
      WRITE(6,3003)INDT(I,1),INDT(I,2),NMBL1(KPTB),NMBL2(KPTB)
 3003 FORMAT(/5X,'***DATO',2A4,' BL.',2A4,' NON TROVATO'/)
      IVDT(I,1)=IBL
      IVDT(I,2)=IBL
      IVDT(I,3)=IBL
      GO TO 70
   67 IVDT(I,1)=IX(J,1)
      IVDT(I,2)=IX(J,2)
      IVDT(I,3)=IX(J,3)
   70 CONTINUE
      WRITE(2,1004)((INDT(I,J),J=1,2),(IVDT(I,J),J=1,3),I=1,M)
 1004 FORMAT(3(4X,2A4,' =',2A4,A2,'*'))
      GO TO 1
C
   80 WRITE(6,3005)
 3005 FORMAT(//5X,'ESECUZIONE TERMINATA')
      RETURN
      END



      INTEGER FUNCTION IVERECC(IBLDEST,IBLSORG)

      parameter(NSORG=100,NDEST=100)
      integer*4 IECC(NSORG,NDEST),NECC(NSORG)
      integer*4 IPRIMAVOLTA,ICEFILE,NUMECC
      COMMON/EDI14ECC/IECC(NSORG,NDEST),NECC(NSORG),NUMECC,
     &                  IPRIMAVOLTA,ICEFILE 
        
        character*132 LINEA, FINP

C     DIMENSION IECC(2,3)
C      DATA IECC(1,1)/'T410'/,IECC(1,2)/'T010'/,IECC(1,3)/'T422'/
C      DATA IECC(2,1)/'BBB2'/,IECC(2,2)/'CCC2'/,IECC(2,3)/'DDD2'/
C      NECCI=2
C      NECCJ=3
C GUAG 17 maggio 2012
C la function testa se è ammissibile la copia delle informazioni del blocc0o IBLSORG del f14.old in IBLDEST del f14.new 
C corrispondente ad una nuova topologia del modello.
C Struttura di IECC. Ha dimensioni IECC(NSORG,NDEST) dove NSORG sono i nomi dei blocchi sorgenti di informazione
C che quindi sono presenti nel f14.old, base per la copia di informazioni nel f14.new, di solito vuoto.
C NDEST sono il numero di blocchi nuovi, ma identici (come dati) a quelli contati da NSORG. 
C Ad esempio se nel file f14.old avevo un blocco AAAA e nel nuovo ho modificato la topologia del modello 
C eseguendo due copy/paste di AAAA con il nome BBBB e CCCC allora in IECC avrò una riga [AAAA BBBB CCCC], ed il 
C programma copierà le informazioni di AAAA in BBBB e CCCC
!      print*,'IPRIMAVOLTA ',IPRIMAVOLTA,' ICEFILE', ICEFILE

      IF(IPRIMAVOLTA.EQ.0) then
        ICEFILE=0
C        call leggi_inp(IECC,NECC,NUMECC,ICEFILE)
        call leggi_inp()
        IPRIMAVOLTA=1
      print*,'Debug: IPRIMAVOLTA ',IPRIMAVOLTA,' ICEFILE', ICEFILE
      ENDIF
      if (ICEFILE.EQ.0) then
      IVERECC=0
      print*,'NO File'
      RETURN
      endif
 
!        DO JJ=1,NUMECC
!        DO J=1,NECC(JJ)
!        print*,'IVERECC - int  IECC(',JJ,',',J,')=',IECC(JJ,J)
!        ENDDO
!        ENDDO
  
      DO 100 I=1,NUMECC
      IF(IBLSORG.EQ.IECC(I,1)) GO TO 10
  100 CONTINUE
      GO TO 300
      
   10 DO 200 J=1,NECC(I)
      IF(IBLDEST.EQ.IECC(I,J)) THEN
       IVERECC=1
       PRINT*,'Debug: IVERECC=',IVERECC, 'IBLDEST=',IBLDEST,
     &        ') NECC(',I,')=',NECC(I),' IBLSORG=',IBLSORG
       RETURN
      ENDIF      
  200 CONTINUE

  
  300 IVERECC=0
      RETURN 
      END
      
      SUBROUTINE leggi_inp()
      parameter(NSORG=100,NDEST=100)
      integer*4 IECC(NSORG,NDEST),NECC(NSORG)
      integer*4 IPRIMAVOLTA,ICEFILE,NUMECC
      COMMON/EDI14ECC/IECC(NSORG,NDEST),NECC(NSORG),NUMECC,
     &                  IPRIMAVOLTA,ICEFILE 

      character*132 LINEA, FINP, FOUT
      character*4,SECC
      integer*4 IBL,ISORG
C        integer*4 IECC(1,1),NECC(1)
        
        
        NUMECC=0

        FINP='edi14_eccezioni.inp'
        FOUT='edi14_eccezioni_letto.out'
        OPEN(UNIT=27,FILE=FINP,STATUS='OLD', ERR=2000)
        OPEN(UNIT=28,FILE=FOUT,STATUS='UNKNOWN', ERR=50)
        rewind(28)
   50   READ(27,'(A)', END=1000) LINEA        

        lunlin=LEN(LINEA)
        iposblank=INDEX(LINEA,' ')
        print*, lunlin,'Debug: iposblank=',iposblank,'=',LINEA
               
        I=1
        K=0
        NUMECC=NUMECC+1
        if (NUMECC.GT.NSORG) THEN 
          Print*,'edi14: ERRORE. Numero massimo di blocchi:',NUMECC
          STOP
        ENDIF
  100   read(LINEA(I:I+3),'(A4)') IBL
        
        
C        print*,'I=',I,' ', 
C     &   LINEA(I:I+3),' int  IECC(',NUMECC,',',K,')=',IECC(NUMECC,K)

C   Cerco eventuali catene di sorgenti e destinazioni
C   ad esempio la  AAAA,BBBB   diventa  AAAA,BBBB,DDDD
C                  BBBB,DDDD
C        
        do II=1,NUMECC
          do KK=1,NECC(II)
           if(IBL.EQ.IECC(II,KK)) then
C             NECC(II)=KK+1
              NECC(II)=NECC(II)+1
             if (LINEA(I+4:I+4).NE.',') Print*,'edi14: ERRORE'
             read(LINEA(I+5:I+5+3),'(A4)') IECC(II,NECC(II))
             NUMECC=NUMECC-1
             GO TO 50
           endif
          enddo
         enddo
            
        K=K+1
        IF(K.GT.NDEST) THEN 
          Print*,'edi14: ERRORE. Numero massimo di blocchi:',K
          STOP
        ENDIF
        IECC(NUMECC,K)=IBL       
        NECC(NUMECC)=K
        if (LINEA(I+4:I+4).NE.',') then
          GO TO 50
        endif
        I=I+5
        GO TO 100
                
 1000   continue
        CLOSE(27)
        
        print*,'Debug: NUMECC',NUMECC
        DO JJ=1,NUMECC
        DO J=1,NECC(JJ)
        write(SECC,'(A4)') IECC(JJ,J)
        print*,'Debug: int  IECC(',JJ,',',J,')=',IECC(JJ,J),' ',SECC
        ENDDO
        ENDDO
        
        DO JJ=1,NUMECC
        write(28,1002)(IECC(JJ,J),J=1,NECC(JJ))
 1002   FORMAT(A4,10(',',A4))
        ENDDO

        CLOSE(28)
        
        ICEFILE=1
        RETURN        
 2000   ICEFILE=0
        RETURN
        end
        
      

