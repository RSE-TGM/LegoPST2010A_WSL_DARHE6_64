-- ======================================================================
-- ===   Sql Script for Database : ALGRT_DB
-- ===
-- === Build : 79
-- ======================================================================

CREATE TABLE PARAMETRI
  (
    sigla      varchar(32)   unique not null,
    contenuto  varchar(32),

    primary key(sigla)
  );

CREATE INDEX PARAMETRIIDX1 ON PARAMETRI(sigla);

-- ======================================================================

CREATE TABLE TIPIMODELLO
  (
    sigla_tipimodello  varchar(32)    unique not null,
    descrizione        varchar(256)   not null,

    primary key(sigla_tipimodello)
  );

-- ======================================================================

CREATE TABLE GRANDEZZE_FISICHE
  (
    nome_grand_fisica  varchar(32)    unique not null,
    descrizione        varchar(256)   not null,

    primary key(nome_grand_fisica)
  );

-- ======================================================================

CREATE TABLE TIPIVAR
  (
    progr_tipivar  int4           unique not null,
    descrizione    varchar(256)   not null,

    primary key(progr_tipivar)
  );

-- ======================================================================

CREATE TABLE PORTE_CONNESSE
  (
    ingresso_connesso  varchar(32),
    uscita_utilizzata  varchar(32),

    primary key(ingresso_connesso)
  );

-- ======================================================================

CREATE TABLE MODELLI
  (
    progr_modello      int4           unique not null,
    sigla              varchar(32)    unique not null,
    descrizione        varchar(256),
    dt                 float8         not null,
    path_locale        varchar(256)   not null,
    path_globale       varchar(256)   not null,
    sistema_operativo  varchar(32)    not null default OS,
    host               varchar(32)    not null default host,
    utente             varchar(32)    not null default guest,
    sigla_tipimodello  varchar(32)    not null,

    primary key(progr_modello),

    foreign key(sigla_tipimodello) references TIPIMODELLO(sigla_tipimodello) on update CASCADE on delete CASCADE
  );

CREATE INDEX MODELLIIDX1 ON MODELLI(progr_modello,sigla);

-- ======================================================================

CREATE TABLE BLOCCHI
  (
    progr_blocco   int4           not null,
    progr_modello  int4           not null,
    sigla          varchar(32)    not null,
    descrizione    varchar(256),

    primary key(progr_blocco,progr_modello),

    foreign key(progr_modello) references MODELLI(progr_modello) on update CASCADE on delete CASCADE
  );

CREATE INDEX BLOCCHIIDX1 ON BLOCCHI(progr_blocco,sigla);

-- ======================================================================

CREATE TABLE UNITA_MISURA
  (
    nome_unita_misura  varchar(32)    unique not null,
    descrizione        varchar(256),
    nome_grand_fisica  varchar(32)    not null,
    coefficiente       float8         not null,

    primary key(nome_unita_misura),

    foreign key(nome_grand_fisica) references GRANDEZZE_FISICHE(nome_grand_fisica) on update CASCADE on delete CASCADE
  );

CREATE INDEX UNITA_MISURAIDX1 ON UNITA_MISURA(nome_unita_misura);

-- ======================================================================

CREATE TABLE VARIABILI
  (
    progr_variabile        int4           unique not null,
    sigla                  varchar(32)    not null,
    descrizione            varchar(256),
    tag_kks                varchar(32)    default NULL,
    dimensione             int8           not null default 1,
    struttura              varchar(32),
    nome_unita_misura      varchar(32)    not null,
    progr_tipivar          int4           not null,
    progr_varout_connessa  int4,
    sigla_blocchetto       varchar(32)    default NULL,
    tipo_blocchetto        varchar(32)    default NULL,

    primary key(progr_variabile),

    foreign key(nome_unita_misura) references UNITA_MISURA(nome_unita_misura) on update CASCADE on delete CASCADE,
    foreign key(progr_tipivar) references TIPIVAR(progr_tipivar) on update CASCADE on delete CASCADE,
    foreign key(progr_varout_connessa) references VARIABILI(progr_variabile) on update CASCADE on delete SET NULL
  );

CREATE INDEX VARIABILIIDX1 ON VARIABILI(sigla);

-- ======================================================================

CREATE TABLE BLOC_VAR
  (
    progressivo      int4   not null,
    progr_blocco     int4   not null,
    progr_modello    int4   not null,
    progr_variabile  int4   not null,

    primary key(progressivo,progr_blocco,progr_modello),

    foreign key(progr_blocco) references BLOCCHI(progr_blocco) on update CASCADE on delete CASCADE,
    foreign key(progr_modello) references MODELLI(progr_modello) on update CASCADE on delete CASCADE,
    foreign key(progr_variabile) references VARIABILI(progr_variabile) on update CASCADE on delete CASCADE
  );

-- ======================================================================

CREATE VIEW connessioni_tra_tag AS
   select varin.progr_variabile,varin.sigla,varout.progr_variabile,varout.sigla 
   from variabili as varin , variabili as varout  
   where (varin.tag_kks is not NULL) 
     and (varout.progr_tipivar=0) 
     and (varin.progr_tipivar=1 or varin.progr_tipivar=2) 
     and (varin.tag_kks=varout.tag_kks);

-- ======================================================================

