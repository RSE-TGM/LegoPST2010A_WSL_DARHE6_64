$!******************************************************************************
$! modulo gen_stazionario.com
$! tipo 
$! release 5.1
$! data 96/03/22
$! reserver @(#)gen_stazionario.com	5.1
$!******************************************************************************
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$!!
$!!	COMPILA IL FILE schema.for
$!!	INSERISCE schema.obj NELLA LIBRERIA SCHEMI_REG.OLB
$!!	COMPILA IL FILE LG3_REG.DAT
$!!	CREA IL FILE LG3REG.EXE
$!!     LANCIA LG3REG CREANDO I FILES schema_04.dat,schema_14.dat
$!!	AGGIORNA O CREA IL FILE LISTA_SCHEMI.DAT
$!!
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$!
$! RICAVO I NOMI DEI FILE DI USCITA
$!
$    schema     = P1
$    IF SCHEMA .EQS. "" 
$    THEN 
$      WRITE SYS$OUTPUT "LANCIARE <GEN_STAZIONARIO> <NOME SCHEMA> <WORK_DIR>"
$      EXIT 2
$    ENDIF
$    schema_f14 = P1 + "_14.dat"
$    schema_f04 = P1 + "_04.dat"
$
$!
$! GENERAZIONE DEL FILE F14.DAT CON I VALORI DI INIZIALIZZAZIONE
$!
$    DEFINE LG_TAVOLE lg_lego:LG_TAVOLE.EXE
$    DEFINE LG_OPTAVOLE lg_lego:LG_TAVOLE
$
$
$!
$! RICAVO IL PATH A LIBUT_REG DELL' UTENTE LEGOCAD E MI POSIZIONO
$!
$    PATH  = F$TRNLNM("LEGOCAD_USER","LNM$PROCESS_TABLE")
$    SHIFT = F$LOCATE("]",PATH)
$    PATH  = F$EXTRACT(0,SHIFT,PATH)
$
$
$!
$! RICAVO IL PATH A LEGOMMI_WORK, PATH DI LAVORO 
$!
$    WORK  = F$TRNLNM("LEGOMMI_WORK","LNM$PROCESS_TABLE")
$    IF WORK .EQS. ""
$    THEN
$      WORK = P3
$    ENDIF
$
$
$!
$! RICAVO I PATH NECESSARI PER LE LIBRERIE 
$!
$!   libschemi  =  PATH + ".LIBUT_REG]SCHEMI_REG/LIB"
$!   libreg     =  "LG_LEGO:MODULI_REG"
$!   libmacro   =  PATH + ".TK$MACR]MACRO_REG/LIB"
$    libpath    =  PATH + ".LEGOCAD.LIBUT_REG]"
$    libreg     =  PATH + ".LEGOCAD.LIBUT_REG.LIBREG]MODULI_REG"
$    libschemi  =  WORK + "SCHEMI_REG"
$
$ 
$!    WRITE SYS$OUTPUT " P1=''P1' "
$!    WRITE SYS$OUTPUT " P2=''P2' "
$!    WRITE SYS$OUTPUT " P3=''P3' "
$!    WRITE SYS$OUTPUT " P4=''P4' "
$!    WRITE SYS$OUTPUT " P5=''P5' "
$!    WRITE SYS$OUTPUT " WORK=''WORK'"
$!    WRITE SYS$OUTPUT " libpath   =''libpath'  "
$!    WRITE SYS$OUTPUT " libschemi =''libschemi'  "
$!    WRITE SYS$OUTPUT " libreg    =''libreg'     "
$!    WRITE SYS$OUTPUT " schema_f14=''schema_f14' "
$!    WRITE SYS$OUTPUT " schema_f04=''schema_f04' "
$
$
$!
$! COMPILO IL FILE shema.f E LO INSERISCO IN LIBRERIA
$! 
$!
$
$!    WRITE SYS$OUTPUT ""
$!    WRITE SYS$OUTPUT "         COMPILAZIONE ''schema'.FOR"
$    FOR/WARN=(NOUNUSED)/OBJ='WORK''schema'.OBJ   'WORK''schema'.FOR
$
$    DIREC = F$SEARCH("''libschemi'.OLB")
$!    WRITE SYS$OUTPUT ""
$    IF DIREC .EQS. "" 
$    THEN 
$!       WRITE SYS$OUTPUT "         LIB/CREATE ''libschemi' ''P1'"
$       LIBRARY/CREATE 'libschemi' 'WORK''P1'
$    ELSE
$!       WRITE SYS$OUTPUT "         LIB/REPLACE ''libschemi' ''P1'"
$       LIBRARY/REPLACE 'libschemi' 'WORK''P1'
$    ENDIF
$
$
$!
$! CREO LG3REG.EXE, DA LG3REG.FOR CREATO DA GENF14
$! 
$
$!    WRITE SYS$OUTPUT ""
$!    WRITE SYS$OUTPUT "         COMPILAZIONE LG3REG.FOR"
$    FOR/OBJ='WORK'LG3REG.OBJ   'libpath'LG3REG.FOR
$
$!    WRITE SYS$OUTPUT ""
$!    WRITE SYS$OUTPUT "         GENERAZIONE LG3REG.EXE"
$    LINK/EXE='WORK'LG3REG.EXE  'WORK'LG3REG,-
                                 'libschemi'/LIB,-
                                 lg_lego:VAPO_DIAGN,-
                                 'libreg'/LIB,-
                                 LG_OPTAVOLE/opt
$
$
$!
$! SPOSTO LG3REG.EXE nel direttorio di lavoro
$! 
$!    ren 'libpath'LG3REG.EXE 'WORK'LG3REG.EXE
$
$
$!
$! OTTENGO LO STAZIONARIO DELLO SCHEMA (schema_14.DAT)
$! 
$!    WRITE SYS$OUTPUT ""
$!    WRITE SYS$OUTPUT "         RUN LG3REG"
$    DIRETTORIO = F$ENVIRONMENT("DEFAULT")
$    SET DEF 'WORK'
$    RUN 'WORK'LG3REG
$
$
$!
$! AGGIORNO IL FILE LISTA_SCHEMI.DAT
$! 
$    DIREC = F$SEARCH("LISTA_SCHEMI.DAT")
$    IF DIREC .EQS. "" THEN GOTO CREALISTA
$
$    OPEN/READ  LISTA_INPUT  LISTA_SCHEMI.DAT
$LEGGI_FILE_R:
$       READ/END_OF_FILE=FINE_LETTURA_R LISTA_INPUT LINEA
$       NOME_SCH  = F$EXTRACT(0,4,LINEA)
$       IF NOME_SCH .EQS. P1 THEN GOTO MODULO_PRESENTE
$       GOTO LEGGI_FILE_R
$
$MODULO_PRESENTE:
$    CLOSE LISTA_INPUT
$    GOTO FINE_AGGIORNAMENTO
$
$CREALISTA:
$!    WRITE SYS$OUTPUT "         CREO LISTA_SCHEMI.DAT INSERENDO ''P1'"
$!    WRITE SYS$OUTPUT ""
$    OPEN/WRITE  LISTA_OUTPUT  LISTA_SCHEMI.DAT
$    WRITE LISTA_OUTPUT P1
$    CLOSE LISTA_OUTPUT
$    GOTO FINE_AGGIORNAMENTO
$
$FINE_LETTURA_R:
$    CLOSE LISTA_INPUT
$    OPEN/READ  LISTA_INPUT  LISTA_SCHEMI.DAT
$    OPEN/WRITE LISTA_OUTPUT LISTA_SCHEMI.DAT
$!    WRITE SYS$OUTPUT "         INSERISCO LO SCHEMA ''P1' IN LISTA_SCHEMI.DAT"
$!    WRITE SYS$OUTPUT ""
$    WRITE LISTA_OUTPUT P1
$    LEGGI_FILE_W:
$       READ/END_OF_FILE=FINE_LETTURA_W LISTA_INPUT LINEA
$       WRITE LISTA_OUTPUT LINEA
$       GOTO LEGGI_FILE_W
$
$FINE_LETTURA_W:
$    CLOSE LISTA_INPUT
$    CLOSE LISTA_OUTPUT
$    PURGE/NOLOG  LISTA_SCHEMI.DAT
$    GOTO FINE_AGGIORNAMENTO
$
$FINE_AGGIORNAMENTO:
$!
$! PURGE VARI
$! 
$    DEL/NOCONF/NOLOG LG3REG.EXE;*
$    DEL/NOCONF/NOLOG LG3REG.OBJ;*
$    DEL/NOCONF/NOLOG 'libpath'LG3REG.FOR;*
$    DEL/NOCONF/NOLOG F14.DAT;*
$    PURGE/NOCONF/NOLOG *.*
$    PURGE/NOCONF/NOLOG 'P4'_ERR
$    ERRTSK = P4
$    SHIFT  = F$LOCATE("]",ERRTSK)
$    ERRTSK = F$EXTRACT(0,SHIFT,ERRTSK)
$    ERRTSK = ERRTSK + "]"
$    PURGE/NOCONF/NOLOG 'ERRTSK'*.REG_ERR
$
$!
$! RITORNO AL DIRETTORIO DI PARTENZA
$! 
$    SET DEF 'DIRETTORIO'
$
$
$EXIT 1
