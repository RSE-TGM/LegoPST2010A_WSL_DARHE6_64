	program UP_SCHEMA_F01
C--------------------------------------------------------------------
C
C       Sostituisce uno schema di regolazione vecchio con uno nuovo
C       Produce un nuovo file F01 : UP_SCHEMA_f01.OUT
C
C       input:  - F01.DAT
C               - "schema_nuovo.dat"
C
C       output: - UP_SCHEMA_f01.OUT
C
C--------------------------------------------------------------------
	parameter (MAXLIN1=10000)
	parameter (MAXLIN2=1000)
	parameter (MAXLIN3=1000)
C
	parameter (MAXLIN4=1000)
C
        COMMON/COM/FILE1,SCHENUO,SCHEVE,L_FILE1,L_SCHENUO,L_SCHEVE,
     &  NOSCHE,INI_SCHE,IFI_SCHE,PUNT1,PUNT2,PUNT3,
     $  IU_SCHENUO,IN_SCHENUO,IU_SCHEVE,IN_SCHEVE,SCHENUO_BUFF
C
        COMMON/AGGIO/AGGIO_CO,AGGIO_IN,L_AGGIO_CO,
     &  L_AGGIO_IN
C
        character*80 AGGIO_CO(MAXLIN4),AGGIO_IN(MAXLIN4)
C
	character*80 F1/'f01.dat'/,F2,F3/'UP_SCHEMA_f01.OUT'/, LINEA
	character*80 FILE1(MAXLIN1), SCHENUO(MAXLIN2), SCHEVE(MAXLIN3)
        character*80 SCHENUO_BUFF(MAXLIN2)
	character*4 STAR/'****'/
	character*4 IMAG/'>>>>'/,NOSCHE
	character*8 NOME_MOD/'QQ'/,NOME_COMPLE
	integer N1/1/, N2/2/,N3/3/,L_FILE1
C
	integer PUNT1/0/, PUNT2/0/, PUNT3/0/
	integer PUNT1_2/0/, PUNT2_2/0/, PUNT3_2/0/
        CHARACTER*2 TIPO
C
C
	PRINT*,'Nome dello schema? (COMPRESO IL PATH)= '
	READ(5,'(A)') F2
C
C--Apro il file F01
	open(UNIT=N1,FILE=F1,FORM='formatted', status='old')
C--Apro il file dello schema
	open(UNIT=N2,FILE=F2,FORM='formatted',status='old')
C
10000	format(A80)
C
C
C-Lettura del SCHENUO -- SCHEMA
	print*,'**************************'
	I=0
200	read(N2,10000,end=210)LINEA
!	print*,linea
	I=I+1
C
	SCHENUO(I)=LINEA
	SCHENUO_BUFF(I)=LINEA
        IF((TIPO(SCHENUO(I))).eq.'US') IU_SCHENUO=I
        IF((TIPO(SCHENUO(I))).eq.'IN') IN_SCHENUO=I
C
	goto 200
210	L_SCHENUO=I
        NOSCHE=SCHENUO(2)(1:4)        
        NOME_COMPLE=SCHENUO(4)(1:8)
        PRINT*,'IU_SCHENUO=',IU_SCHENUO
        PRINT*,'IN_SCHENUO=',IN_SCHENUO
C
C-Lettura del FILE1
	I=0
100	read(N1,10000,end=110)LINEA
!	print*,linea
	I=I+1
C
C--PUNT1= fine zona dichiarazione dei blocchi
C--PUNT2= inizio zona >>>>>INGRESSO DI TUTTI I MODULI
C--PUNT3= inizio zona ingressi connessi
C--INI_SCHE= puntatore inizio schema da sostituire
C--IFI_SCHE= puntatore fine schema da sostituire
C
C
	if(I.ne.1.and.PUNT1.eq.0.and.LINEA(1:4).eq.STAR) PUNT1=I 
C
	if((PUNT2.eq.0).and.
	1(LINEA(11:14).eq.IMAG(1:4))) 	PUNT2=I
C
	if((PUNT1.ne.0).and.
	1(PUNT2.ne.0).and.
	1(PUNT3.eq.0).and.
	1(LINEA(1:4).eq.STAR).and.
	1(I.ne.PUNT2)) PUNT3=I
C
        if(PUNT1.ne.0.and.LINEA(1:8).eq.NOME_COMPLE) INI_SCHE=I
C
        if(INI_SCHE.ne.0.and.IPUN_SCHE.eq.0
     &  .and.LINEA(1:4).eq.STAR) then
           IPUN_SCHE=1
           IFI_SCHE=I
        endif
C
	FILE1(I)=LINEA
	goto 100
110	L_FILE1=I
        PRINT*,'PUNT1',PUNT1
        PRINT*,'PUNT2',PUNT2
        PRINT*,'PUNT3',PUNT3
        PRINT*,'L_FILE1=',L_FILE1
        PRINT*,'INI_SCHE',INI_SCHE
        PRINT*,'IFI_SCHE',IfI_SCHE
	NOME_MOD=FILE1(PUNT1+1)(1:8)

	close (N1)
	close (N2)
C
C-----carico lo schema SCHEVE (vecchio schema)
        do I=INI_SCHE,IFI_SCHE
        J=J+1
        SCHEVE(J)=FILE1(I)           
        IF((TIPO(SCHEVE(J))).eq.'US') IU_SCHEVE=J
        IF((TIPO(SCHEVE(J))).eq.'IN') IN_SCHEVE=J
        enddo        
        L_SCHEVE=J
	print*,'IU_SCHEVE=',IU_SCHEVE
        print*,'IN_SCHEVE=',IN_SCHEVE
C
        call CONTR_USC

        call CONTR_ING

C
C--Apro il file del merge UP_SCHEMA_F01
	open(unit=N3,file=F3,form='formatted',status='new',
	1    carriagecontrol='list')		
        IKK=0
        IK=0
        DO I=1,L_FILE1
        IF(FILE1(I).ne.' ') then
          if(I.ge.INI_SCHE.and.IK.eq.0) then
            IK=1
            do J=4,L_SCHENUO-1
             call STAMPA(N3,SCHENUO_BUFF(J))
            enddo
          endif
          if(I.gt.(PUNT3-1).and.IKK.eq.0) then
            ikk=1
            do J=1,L_AGGIO_IN
              call STAMPA(N3,AGGIO_IN(J))
            enddo
          endif
          if(I.lt.INI_SCHE.or.I.ge.IFI_SCHE) then
           call STAMPA(N3,FILE1(I))               
          endif
        ENDIF
        ENDDO
        do J=1,L_AGGIO_CO
           call STAMPA(N3,AGGIO_CO(J))
        enddo

        close (N3)
        stop
        end        
C
        CHARACTER*2 FUNCTION TIPO(LINEA)
        character*(*) LINEA
        character*2 US/'US'/,IN/'IN'/
C
        integer*4 ADDR
        integer*2 LUN
C
C	call STR$ANALYZE_SDESC(LINEA,LUN,ADDR)
C
        LUN=LUNGHEZZA_P(LINEA)
        if(LUN.lt.14) then
          TIPO='**'
          return
        endif
C
        if(LINEA(13:14).eq.'UA'.or.LINEA(13:14).eq.'US') then
              TIPO=US
        else if (LINEA(13:14).eq.'IN') then
              TIPO=IN
        else
              TIPO='**'
C
        endif
        RETURN
        END
C
        SUBROUTINE CONTR_USC
C
C Subroutine di controllo delle uscite dello schema nuovo
C
C Stati:
C      U1 : uscita non piu` esistente e connessa
C      U2 : uscita non piu` esistente non connessa
C      U3 : uscita nuova
C      U5 e U4 : uscita esistente nel vecchio e nel nuovo schema
C
	parameter (MAXLIN1=10000)
	parameter (MAXLIN2=1000)
	parameter (MAXLIN3=1000)
C
        COMMON/COM/FILE1,SCHENUO,SCHEVE,L_FILE1,L_SCHENUO,L_SCHEVE,
     &  NOSCHE,INI_SCHE,IFI_SCHE,PUNT1,PUNT2,PUNT3,
     &  IU_SCHENUO,IN_SCHENUO,IU_SCHEVE,IN_SCHEVE,SCHENUO_BUFF
C
	character*80 FILE1(MAXLIN1), SCHENUO(MAXLIN2), SCHEVE(MAXLIN3)
        character*80 SCHENUO_BUFF(MAXLIN2)
        character*4 NOSCHE
        CHARACTER*2 US/'US'/,IN/'IN'/,TIPO
C
        INTEGER PUNT1,PUNT2,PUNT3
        character*80 LINEA,TOGLI_CO_IN
C
        DO K=2,IU_SCHEVE
          DO I=5,IU_SCHENUO
           if(SCHEVE(K)(1:8).eq.SCHENUO(I)(1:8)) then
C---caso U5 e U4
             stat=U5
             print*,'-----------------------------------------------'
             print*,'-caso U5 o U4-',SCHEVE(K)(1:8),
     &              ' uscita gia` esistente'
             goto 10
           endif
          ENDDO
          IES=0
          DO J=PUNT1,PUNT2
            IF(J.lt.INI_SCHE.or.J.gt.IFI_SCHE) then
               IF(FILE1(J)(1:8).eq.SCHEVE(K)(1:8)) then
C---caso U1 
                stat=U1
                print*,'-----------------------------------------------'
                print*,'-caso U1-',SCHEVE(K)(1:8),' non piu` esistente'
                print*,'                connessa con ',FILE1(J)(19:26)
                print*,'!!!!! sconnetto l`uscita ',SCHEVE(K)(1:8),
     &                'dall`ingresso ',FILE1(J)(19:26)
                IES=1
                LINEA=TOGLI_CO_IN(1,FILE1(J)(19:26))
                LINEA(13:14)='IN'
                FILE1(J)=LINEA
                call AGG_CO_IN(2,LINEA)

               ENDIF
            ENDIF                 
          ENDDO
          IF(IES.eq.0) then
C---caso U2
          stat=U2
          print*,'-----------------------------------------------'
          print*,'-caso U2-',SCHEVE(K)(1:8),' non piu` esistente'
          print*,'!!!!! tolgo l`uscita ',SCHEVE(K)(1:8)
          ENDIF
10     continue
       ENDDO
C
        DO I=5,IU_SCHENUO
          DO K=2,IU_SCHEVE
             if(SCHEVE(K)(1:8).eq.SCHENUO(I)(1:8)) then
               goto 20
             endif
          ENDDO
C---caso U3
          stat=U3
          print*,'-----------------------------------------------'
          print*,'-caso U3-',SCHENUO(I)(1:8),' nuova'
          print*,'!!!!! aggiungo l`uscita ',SCHENUO(I)(1:8)
20      continue
        ENDDO
        RETURN
	END
C
        SUBROUTINE CONTR_ING
C
C Subroutine di controllo degli dello schema nuovo
C
C Stati:
C      I1 : ingresso non piu` esistente e connesso
C      I2 : ingresso nuovo
C      I3 : ingresso gia` esistente connesso
C      I4 : ingresso non piu` esistente non connesso
C      I5 : ingresso gia` esistente non connesso
C
	parameter (MAXLIN1=10000)
	parameter (MAXLIN2=1000)
	parameter (MAXLIN3=1000)
C
        COMMON/COM/FILE1,SCHENUO,SCHEVE,L_FILE1,L_SCHENUO,L_SCHEVE,
     &  NOSCHE,INI_SCHE,IFI_SCHE,PUNT1,PUNT2,PUNT3,
     &  IU_SCHENUO,IN_SCHENUO,IU_SCHEVE,IN_SCHEVE,SCHENUO_BUFF
C
	character*80 FILE1(MAXLIN1), SCHENUO(MAXLIN2), SCHEVE(MAXLIN3)
        character*80 SCHENUO_BUFF(MAXLIN2)
        character*4 NOSCHE
        CHARACTER*2 US/'US'/,IN/'IN'/,TIPO
C
        INTEGER PUNT1,PUNT2,PUNT3
C
        character*80 LINEA,TOGLI_CO_IN
C
        DO I=IU_SCHENUO+1,IN_SCHENUO
             DO K=IU_SCHEVE+1,IN_SCHEVE
                if(SCHENUO(I)(1:8).eq.SCHEVE(K)(1:8)) then 
C--caso I5
                    stat=I5
             print*,'-----------------------------------------------'
                    print*,'-caso I5-',SCHENUO(I)(1:8),
     &                     ' ingresso non connesso gia` esistente'
                    goto 10
                else if((scheve(K)(18:18).eq.'#').and.
     &                   (SCHENUO(I)(1:8).eq.SCHEVE(K)(19:26))) then
C--caso I3
                    stat=I3
                    print*,'-caso I3-',SCHENUO(I)(1:8),
     &                     ' ingresso connesso gia` esistente'

                    SCHENUO_BUFF(I)=SCHEVE(K)

                    goto 10
                endif
             ENDDO
C--caso I2
             stat=I2
             print*,'-----------------------------------------------'
             print*,'-caso I2-',SCHENUO(I)(1:8),' ingresso nuovo'
             print*,'!!!!! aggiungo l`ingresso ',SCHENUO(I)(1:8)
           call AGG_CO_IN(2,SCHENUO(I))

10      continue
        ENDDO
C
        DO K=IU_SCHEVE+1,IN_SCHEVE
           DO I=IU_SCHENUO+1,IN_SCHENUO
                if(SCHEVE(K)(1:8).eq.SCHENUO(I)(1:8)) then
                  goto 20
                else if((scheve(K)(18:18).eq.'#').and.
     &                   (SCHENUO(I)(1:8).eq.SCHEVE(K)(19:26))) then
                  goto 20
                endif 
           ENDDO
        if(scheve(K)(18:18).eq.'#') then
C--caso  I1
          stat=I1
          print*,'-----------------------------------------------'
          print*,'-caso I1-',SCHEVE(K)(19:26),
     &           ' ingresso scomparso e collegato'
          print*,'!!!!! tolgo l`ingresso ',SCHEVE(K)(19:26)
        LINEA=TOGLI_CO_IN(1,SCHEVE(K)(19:26))

        else
C--caso  I4
          stat=I4
          print*,'-----------------------------------------------'
          print*,'-caso I4-',SCHEVE(K)(1:8),' ingresso scomparso'
          print*,'!!!!! tolgo l`ingresso ',SCHEVE(K)(1:8)
        LINEA=TOGLI_CO_IN(2,SCHEVE(K))

        endif
20      continue
        ENDDO
C
        RETURN
	END

C
        character*80 function TOGLI_CO_IN(IGO,NOME)
C
C  IGO=1 aggirono  CO
C  IGO=2 aggirono  IN
C
C ritorna  la linea cancellata
C
	parameter (MAXLIN1=10000)
	parameter (MAXLIN2=1000)
	parameter (MAXLIN3=1000)
C
        COMMON/COM/FILE1,SCHENUO,SCHEVE,L_FILE1,L_SCHENUO,L_SCHEVE,
     &  NOSCHE,INI_SCHE,IFI_SCHE,PUNT1,PUNT2,PUNT3,
     &  IU_SCHENUO,IN_SCHENUO,IU_SCHEVE,IN_SCHEVE,SCHENUO_BUFF
C
	character*80 FILE1(MAXLIN1), SCHENUO(MAXLIN2), SCHEVE(MAXLIN3)
        character*80 SCHENUO_BUFF(MAXLIN2)
        character*4 NOSCHE
        CHARACTER*2 US/'US'/,IN/'IN'/,TIPO
C
        INTEGER PUNT1,PUNT2,PUNT3
C        
        character*8 NOME
C
C
        IF (IGO.eq.1) then
         DO J=PUNT3,L_FILE1
           if(NOME(1:8).eq.FILE1(J)(1:8)) then
             TOGLI_CO_IN=FILE1(J)
             FILE1(J)=' '
             goto 10
           endif
         ENDDO
        ELSE
        DO J=PUNT2,PUNT3
           if(NOME(1:8).eq.FILE1(J)(1:8)) then
             TOGLI_CO_IN=FILE1(J)
             FILE1(J)=' '
             goto 10
           endif
        ENDDO
        ENDIF   
C
10      continue
        return
        end        

        subroutine AGG_CO_IN(IGO,LINEA)
C
C  IGO=1 aggirono  CO
C  IGO=2 aggirono  IN
C
C
	parameter (MAXLIN1=10000)
	parameter (MAXLIN2=1000)
	parameter (MAXLIN3=1000)
C
        parameter (MAXLIN4=1000)
C
        COMMON/COM/FILE1,SCHENUO,SCHEVE,L_FILE1,L_SCHENUO,L_SCHEVE,
     &  NOSCHE,INI_SCHE,IFI_SCHE,PUNT1,PUNT2,PUNT3,
     &  IU_SCHENUO,IN_SCHENUO,IU_SCHEVE,IN_SCHEVE,SCHENUO_BUFF
C
        COMMON/AGGIO/AGGIO_CO,AGGIO_IN,L_AGGIO_CO,
     &  L_AGGIO_IN
C
        character*80 AGGIO_CO(MAXLIN4),AGGIO_IN(MAXLIN4)
	character*80 FILE1(MAXLIN1), SCHENUO(MAXLIN2), SCHEVE(MAXLIN3)
        character*80 SCHENUO_BUFF(MAXLIN2)
        character*4 NOSCHE
        CHARACTER*2 US/'US'/,IN/'IN'/,TIPO
C
        INTEGER PUNT1,PUNT2,PUNT3
C        
        character*80 LINEA
C
C
        IF (IGO.eq.1) THEN
           L_AGGIO_CO=L_AGGIO_CO+1
           AGGIO_CO(L_AGGIO_CO)=LINEA
        ELSE
           L_AGGIO_IN=L_AGGIO_IN+1
           AGGIO_IN(L_AGGIO_IN)=LINEA
        ENDIF
C
10      continue
        return
        end        

        subroutine STAMPA(IUN,LINEA)
        character*(*) LINEA
        
!        do I=80,1,-1
!           if(LINEA(I:I).ne.' ') goto 10
!        enddo
!        return
!10      write(IUN,1000) LINEA(1:LUN)
        write(IUN,1000) LINEA
1000    format(A)
        return
        end        
C
C
C   FUNZIONE PER CALCOLARE LA LUNGHEZZA DI UNA STRINGA
C
        INTEGER*4 FUNCTION LUNGHEZZA_P(STRINGA)
        CHARACTER*80 STRINGA
        INTEGER*4 I

        DO 667,I=80,1,-1
C          WRITE(6,889) STRINGA(I:I)
C889       FORMAT(A1)
           IF( STRINGA(I:I).NE.' ' )  GOTO 999
667     CONTINUE
999     LUNGHEZZA_P = I
        RETURN
        END

