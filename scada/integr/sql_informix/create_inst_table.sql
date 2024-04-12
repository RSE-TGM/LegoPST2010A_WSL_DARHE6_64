--
-- modulo %M%
-- tipo %Y%
-- release %I%
-- data %G%
-- reserved %W%
--

-- =========================================================
--
-- Creazione tabelle editing necessarie all'istallatore dei
-- punti funzionante su PC IBM compatibile.
-- 
-- =========================================================

--
-- EDITAA table definition
--
create table ONLINE.EDITAA
	(
  Sigla   			           CHARACTER VARYING(20),
  Descrizione                              CHARACTER VARYING(60),
  Morsetticampo                            CHARACTER VARYING(24),
  cavo                                     CHARACTER VARYING(8),
  Morsettisistema                          CHARACTER VARYING(24),
  TipoPeriferica                           CHARACTER VARYING(4),
  IDperi                                   SMALLINT,
  Nomescheda                               CHARACTER VARYING(10),
  IDscheda                                 SMALLINT,
  IDpunto                                  SMALLINT,
  Unitamisura                              CHARACTER VARYING(10),
  Periodo                                  SMALLINT,
  TipoSegnale                              CHARACTER VARYING(4),
  CSbasso                                  INTEGER,
  CSalto                                   INTEGER,
  IdAttendibile                            SMALLINT,
  CoeffGV                                  SMALLINT,
  TipoConversione                          CHARACTER VARYING(4),
  FSbasso                                  SMALLFLOAT,
  FSalto                                   SMALLFLOAT,
  Coeff0                                   SMALLFLOAT,
  Coeff1                                   SMALLFLOAT,
  Coeff2                                   SMALLFLOAT,
  Coeff3                                   SMALLFLOAT,
  Coeff4                                   SMALLFLOAT,
  GiuntoFreddo                             CHARACTER VARYING(10),
  Coeffiltro                               SMALLFLOAT,
  Limite0                                  SMALLFLOAT,
  Zonaimpianto                             SMALLINT,
  LalBC                                    CHARACTER VARYING(20),
  LalBS                                    CHARACTER VARYING(20),
  LalAC                                    CHARACTER VARYING(20),
  LalAS                                    CHARACTER VARYING(20),
  BandaMorta                               SMALLINT,
  Trattamento                              SMALLINT,
  Severita                                 SMALLINT,
  Note                                     CHARACTER VARYING(32),
  Dainstallare                             SMALLINT,
  SiglaSim                                 CHARACTER VARYING(16),
  Gerarchia                                CHARACTER VARYING(18)
	);
alter table ONLINE.EDITAA add constraint primary key (Sigla) constraint
	PK_EDITAA;

--
-- EDITAC table definition
--
create table ONLINE.EDITAC
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 valoreDB                                SMALLFLOAT,
 Unitamisura                             CHARACTER VARYING(10),
 Zonaimpianto                            SMALLINT,
 LalBC                                   CHARACTER VARYING(20),
 LalBS                                   CHARACTER VARYING(20),
 LalAC                                   CHARACTER VARYING(20),
 LalAS                                   CHARACTER VARYING(20),
 BandaMorta                              SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITAC add constraint primary key (Sigla) constraint
        PK_EDITAC;

--
-- EDITAD table definition
--
create table ONLINE.EDITAD
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 IndDB                                   SMALLINT,
 Unitamisura                             CHARACTER VARYING(10),
 Zonaimpianto                            SMALLINT,
 LalBC                                   CHARACTER VARYING(20),
 LalBS                                   CHARACTER VARYING(20),
 LalAC                                   CHARACTER VARYING(20),
 LalAS                                   CHARACTER VARYING(20),
 BandaMorta                              SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITAD add constraint primary key (Sigla) constraint
        PK_EDITAD;

--
-- EDITAO table definition
--
create table ONLINE.EDITAO
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Morsetticampo                           CHARACTER VARYING(24),
 cavo                                    CHARACTER VARYING(8),
 Morsettisistema                         CHARACTER VARYING(24),
 TipoPeriferica                          CHARACTER VARYING(4),
 IDperi                                  SMALLINT,
 Nomescheda                              CHARACTER VARYING(10),
 IDscheda                                SMALLINT,
 IDpunto                                 SMALLINT,
 Unitamisura                             CHARACTER VARYING(10),
 TipoSegnale                             CHARACTER VARYING(4),
 CSbasso                                 SMALLINT,
 CSalto                                  SMALLINT,
 FSbasso                                 SMALLFLOAT,
 FSalto                                  SMALLFLOAT,
 Coeffiltro                              SMALLFLOAT,
 LimiteFiltro                            SMALLFLOAT,
 Zonaimpianto                            SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 SiglaSim                                CHARACTER VARYING(16),
 InStampa                                SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITAO add constraint primary key (Sigla) constraint
        PK_EDITAO;

--
-- EDITAS table definition
--
create table ONLINE.EDITAS
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Unitamisura                             CHARACTER VARYING(10),
 Periodo                                 SMALLINT,
 TipoCalc                                SMALLINT,
 Contrib1                                CHARACTER VARYING(20),
 Contrib2                                CHARACTER VARYING(20),
 Contrib3                                CHARACTER VARYING(20),
 Contrib4                                CHARACTER VARYING(20),
 Contrib5                                CHARACTER VARYING(20),
 Contrib6                                CHARACTER VARYING(20),
 Contrib7                                CHARACTER VARYING(20),
 Contrib8                                CHARACTER VARYING(20),
 Freq                                    SMALLINT,
 Codice                                  SMALLINT,
 Zonaimpianto                            SMALLINT,
 LalBC                                   CHARACTER VARYING(20),
 LalBS                                   CHARACTER VARYING(20),
 LalAC                                   CHARACTER VARYING(20),
 LalAS                                   CHARACTER VARYING(20),
 BandaMorta                              SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITAS add constraint primary key (Sigla) constraint
        PK_EDITAS;

--
-- EDITARC table definition
--
create table ONLINE.EDITARC
	(
 Indice   				 SMALLINT,
 Descrizione                             CHARACTER VARYING(60),
 Tipo                                    SMALLINT,
 PeriodoL                                SMALLINT,
 Durata                                  SMALLINT,
 NumeroFile                              SMALLINT,
 TriggerA                                SMALLINT,
 TriggerD                                SMALLINT,
 TotPar                                  SMALLINT,
 DatiVet                                 SMALLINT,
 Campione01                              CHARACTER VARYING(20),
 Campione02                              CHARACTER VARYING(20),
 Campione03                              CHARACTER VARYING(20),
 Campione04                              CHARACTER VARYING(20),
 Campione05                              CHARACTER VARYING(20),
 Campione06                              CHARACTER VARYING(20),
 Campione07                              CHARACTER VARYING(20),
 Campione08                              CHARACTER VARYING(20),
 Campione09                              CHARACTER VARYING(20),
 Campione10                              CHARACTER VARYING(20),
 Campione11                              CHARACTER VARYING(20),
 Campione12                              CHARACTER VARYING(20),
 Campione13                              CHARACTER VARYING(20),
 Campione14                              CHARACTER VARYING(20),
 Campione15                              CHARACTER VARYING(20),
 Campione16                              CHARACTER VARYING(20),
 Campione17                              CHARACTER VARYING(20),
 Campione18                              CHARACTER VARYING(20),
 Campione19                              CHARACTER VARYING(20),
 Campione20                              CHARACTER VARYING(20),
 Campione21                              CHARACTER VARYING(20),
 Campione22                              CHARACTER VARYING(20),
 Campione23                              CHARACTER VARYING(20),
 Campione24                              CHARACTER VARYING(20),
 Campione25                              CHARACTER VARYING(20),
 Campione26                              CHARACTER VARYING(20),
 Campione27                              CHARACTER VARYING(20),
 Campione28                              CHARACTER VARYING(20),
 Campione29                              CHARACTER VARYING(20),
 Campione30                              CHARACTER VARYING(20),
 Campione31                              CHARACTER VARYING(20),
 Campione32                              CHARACTER VARYING(20),
 Campione33                              CHARACTER VARYING(20),
 Campione34                              CHARACTER VARYING(20),
 Campione35                              CHARACTER VARYING(20),
 Campione36                              CHARACTER VARYING(20),
 Campione37                              CHARACTER VARYING(20),
 Campione38                              CHARACTER VARYING(20),
 Campione39                              CHARACTER VARYING(20),
 Campione40                              CHARACTER VARYING(20),
 Campione41                              CHARACTER VARYING(20),
 Campione42                              CHARACTER VARYING(20),
 Campione43                              CHARACTER VARYING(20),
 Campione44                              CHARACTER VARYING(20),
 Campione45                              CHARACTER VARYING(20),
 Campione46                              CHARACTER VARYING(20),
 Campione47                              CHARACTER VARYING(20),
 Campione48                              CHARACTER VARYING(20),
 Campione49                              CHARACTER VARYING(20),
 Campione50                              CHARACTER VARYING(20),
 Campione51                              CHARACTER VARYING(20),
 Campione52                              CHARACTER VARYING(20),
 Campione53                              CHARACTER VARYING(20),
 Campione54                              CHARACTER VARYING(20),
 Campione55                              CHARACTER VARYING(20),
 Campione56                              CHARACTER VARYING(20),
 Campione57                              CHARACTER VARYING(20),
 Campione58                              CHARACTER VARYING(20),
 Campione59                              CHARACTER VARYING(20),
 Campione60                              CHARACTER VARYING(20),
 Campione61                              CHARACTER VARYING(20),
 Campione62                              CHARACTER VARYING(20),
 Campione63                              CHARACTER VARYING(20),
 Campione64                              CHARACTER VARYING(20),
 Campione65                              CHARACTER VARYING(20),
 Campione66                              CHARACTER VARYING(20),
 Campione67                              CHARACTER VARYING(20),
 Campione68                              CHARACTER VARYING(20),
 Campione69                              CHARACTER VARYING(20),
 Campione70                              CHARACTER VARYING(20),
 Campione71                              CHARACTER VARYING(20),
 Campione72                              CHARACTER VARYING(20),
 Campione73                              CHARACTER VARYING(20),
 Campione74                              CHARACTER VARYING(20),
 Campione75                              CHARACTER VARYING(20),
 Campione76                              CHARACTER VARYING(20),
 Campione77                              CHARACTER VARYING(20),
 Campione78                              CHARACTER VARYING(20),
 Campione79                              CHARACTER VARYING(20),
 Campione80                              CHARACTER VARYING(20),
 Campione81                              CHARACTER VARYING(20),
 Campione82                              CHARACTER VARYING(20),
 Campione83                              CHARACTER VARYING(20)
	);
alter table ONLINE.EDITARC add constraint primary key (Indice) constraint
        PK_EDITARC;

--
-- EDITDA table definition
--
create table ONLINE.EDITDA
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Morsetticampo                           CHARACTER VARYING(24),
 cavo                                    CHARACTER VARYING(8),
 Morsettisistema                         CHARACTER VARYING(24),
 TipoPeriferica                          CHARACTER VARYING(4),
 IDperi                                  SMALLINT,
 Nomescheda                              CHARACTER VARYING(10),
 IDscheda                                SMALLINT,
 IDpunto                                 SMALLINT,
 Contatto                                SMALLINT,
 Stato0                                  CHARACTER VARYING(12),
 Stato1                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 TInib                                   SMALLINT,
 Zonaimpianto                            SMALLINT,
 TipoSegnale                             CHARACTER VARYING(1),
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 SiglaSim                                CHARACTER VARYING(16),
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITDA add constraint primary key (Sigla) constraint
        PK_EDITDA;

--
-- EDITDC table definition
--
create table ONLINE.EDITDC
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Stato0                                  CHARACTER VARYING(12),
 Stato1                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 TInib                                   SMALLINT,
 Zonaimpianto                            SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITDC add constraint primary key (Sigla) constraint
        PK_EDITDC;

--
-- EDITDD table definition
--
create table ONLINE.EDITDD
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 IndDB                                   SMALLINT,
 Stato0                                  CHARACTER VARYING(12),
 Stato1                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 TInib                                   SMALLINT,
 Zonaimpianto                            SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITDD add constraint primary key (Sigla) constraint
        PK_EDITDD;

--
-- EDITDO table definition
--
create table ONLINE.EDITDO
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Morsetticampo                           CHARACTER VARYING(24),
 cavo                                    CHARACTER VARYING(8),
 Morsettisistema                         CHARACTER VARYING(24),
 TipoPeriferica                          CHARACTER VARYING(4),
 IDperi                                  SMALLINT,
 Nomescheda                              CHARACTER VARYING(10),
 IDscheda                                SMALLINT,
 IDpunto                                 SMALLINT,
 IDscheda2                               SMALLINT,
 IDpunto2                                SMALLINT,
 IDscheda3                               SMALLINT,
 IDpunto3                                SMALLINT,
 IDscheda4                               SMALLINT,
 IDpunto4                                SMALLINT,
 Temporizzazione                         SMALLINT,
 Tempo                                   SMALLINT,
 Azione                                  SMALLINT,
 Zonaimpianto                            SMALLINT,
 TipoCom                                 SMALLINT,
 SiglaOrg                                CHARACTER VARYING(20),
 TimeOut                                 SMALLINT,
 StAttuale1                              CHARACTER VARYING(12),
 StAtteso1                               CHARACTER VARYING(12),
 StAttuale2                              CHARACTER VARYING(12),
 StAtteso2                               CHARACTER VARYING(12),
 StAttuale3                              CHARACTER VARYING(12),
 StAtteso3                               CHARACTER VARYING(12),
 StAttuale4                              CHARACTER VARYING(12),
 StAtteso4                               CHARACTER VARYING(12),
 ComProt                                 SMALLINT,
 Note                                    CHARACTER VARYING(32),
 InStampa                                SMALLINT,
 Dainstallare                            SMALLINT,
 SiglaSim                                CHARACTER VARYING(16),
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITDO add constraint primary key (Sigla) constraint
        PK_EDITDO;

--
-- EDITDS table definition
--
create table ONLINE.EDITDS
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 TipoCalc                                SMALLINT,
 SiglaDig1                               CHARACTER VARYING(20),
 SiglaDig2                               CHARACTER VARYING(20),
 SiglaDig3                               CHARACTER VARYING(20),
 SiglaDig4                               CHARACTER VARYING(20),
 Stato0                                  CHARACTER VARYING(10),
 Stato1                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 TInib                                   SMALLINT,
 Zonaimpianto                            SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITDS add constraint primary key (Sigla) constraint
        PK_EDITDS;

--
-- EDITOR table definition
--
create table ONLINE.EDITOR
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Zonaimpianto                            SMALLINT,
 Timeout                                 SMALLINT,
 Tipo                                    CHARACTER VARYING(12),
 SCont1                                  CHARACTER VARYING(20),
 SCont2                                  CHARACTER VARYING(20),
 SCont3                                  CHARACTER VARYING(20),
 SCont4                                  CHARACTER VARYING(20),
 SCont5                                  CHARACTER VARYING(20),
 STProt                                  CHARACTER VARYING(8),
 Inibente                                SMALLINT,
 StatoI                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 Tinibiz                                 SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITOR add constraint primary key (Sigla) constraint
        PK_EDITOR;

--
-- EDITST table definition
--
create table ONLINE.EDITST
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Valore                                  CHARACTER VARYING(15),
 Zonaimpianto                            SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.EDITST add constraint primary key (Sigla) constraint
        PK_EDITST;

--
-- EDITTO table definition
--
create table ONLINE.EDITTO
	(
 TipoO   				 CHARACTER VARYING(12),
 codice                                  SMALLINT,
 Descrizione                             CHARACTER VARYING(60),
 NumSegC                                 SMALLINT,
 DescrSeg1                               CHARACTER VARYING(24),
 DescrSeg2                               CHARACTER VARYING(24),
 DescrSeg3                               CHARACTER VARYING(24),
 Descrseg4                               CHARACTER VARYING(24),
 DescrSeg5                               CHARACTER VARYING(24),
 Stato1                                  CHARACTER VARYING(12),
 Stato2                                  CHARACTER VARYING(12),
 Stato3                                  CHARACTER VARYING(12),
 Stato4                                  CHARACTER VARYING(12),
 Stato5                                  CHARACTER VARYING(12),
 Stato6                                  CHARACTER VARYING(12),
 Stato7                                  CHARACTER VARYING(12),
 Stato8                                  CHARACTER VARYING(12),
 Stato9                                  CHARACTER VARYING(12),
 Stato10                                 CHARACTER VARYING(12),
 Stato11                                 CHARACTER VARYING(12),
 Stato12                                 CHARACTER VARYING(12),
 Stato13                                 CHARACTER VARYING(12),
 Stato14                                 CHARACTER VARYING(12),
 Stato15                                 CHARACTER VARYING(12),
 Stato16                                 CHARACTER VARYING(12),
 Stato17                                 CHARACTER VARYING(12),
 Stato18                                 CHARACTER VARYING(12),
 Stato19                                 CHARACTER VARYING(12),
 Stato20                                 CHARACTER VARYING(12),
 Stato21                                 CHARACTER VARYING(12),
 Stato22                                 CHARACTER VARYING(12),
 Stato23                                 CHARACTER VARYING(12),
 Stato24                                 CHARACTER VARYING(12),
 Stato25                                 CHARACTER VARYING(12),
 Stato26                                 CHARACTER VARYING(12),
 Stato27                                 CHARACTER VARYING(12),
 Stato28                                 CHARACTER VARYING(12),
 Stato29                                 CHARACTER VARYING(12),
 Stato30                                 CHARACTER VARYING(12),
 Stato31                                 CHARACTER VARYING(12),
 Stato32                                 CHARACTER VARYING(12)
	);
alter table ONLINE.EDITTO add constraint primary key (codice) constraint
        PK_EDITTO;

--
-- ERRORIPUNTI table definition
--
create table ONLINE.ERRORIPUNTI
	(
 Sigla   				 CHARACTER VARYING(20),
 Tipo                                    CHARACTER VARYING(2),
 ErrCode                                 SMALLINT,
 ErrString                               CHARACTER VARYING(255)
	);
alter table ONLINE.ERRORIPUNTI add constraint primary key (Sigla,Tipo,ErrCode) 
	constraint PK_ERRORIPUNTI;

--
-- ERRORIRTF table definition
--
create table ONLINE.ERRORIRTF
	(
 Sigla   				 CHARACTER VARYING(20),
 Tipo                                    CHARACTER VARYING(2),
 ErrCode                                 SMALLINT,
 ErrString                               CHARACTER VARYING(255)
	);
alter table ONLINE.ERRORIRTF add constraint primary key (Sigla,Tipo,ErrCode) 
	constraint PK_ERRORIRTF;

-- =========================================================
--
-- Creazione tabelle operative per l'istallatore dei
-- punti funzionante su PC IBM compatibile.
--
-- =========================================================

--
-- TDPUNAA table definition
--
create table ONLINE.TDPUNAA
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Morsetticampo                           CHARACTER VARYING(24),
 cavo                                    CHARACTER VARYING(8),
 Morsettisistema                         CHARACTER VARYING(24),
 TipoPeriferica                          CHARACTER VARYING(4),
 IDperi                                  SMALLINT,
 Nomescheda                              CHARACTER VARYING(10),
 IDscheda                                SMALLINT,
 IDpunto                                 SMALLINT,
 Unitamisura                             CHARACTER VARYING(10),
 Periodo                                 SMALLINT,
 TipoSegnale                             CHARACTER VARYING(4),
 CSbasso                                 INTEGER,
 CSalto                                  INTEGER,
 IdAttendibile                           SMALLINT,
 CoeffGV                                 SMALLINT,
 TipoConversione                         CHARACTER VARYING(4),
 FSbasso                                 SMALLFLOAT,
 FSalto                                  SMALLFLOAT,
 Coeff0                                  SMALLFLOAT,
 Coeff1                                  SMALLFLOAT,
 Coeff2                                  SMALLFLOAT,
 Coeff3                                  SMALLFLOAT,
 Coeff4                                  SMALLFLOAT,
 GiuntoFreddo                            CHARACTER VARYING(10),
 Coeffiltro                              SMALLFLOAT,
 Limite0                                 SMALLFLOAT,
 Zonaimpianto                            SMALLINT,
 LalBC                                   CHARACTER VARYING(20),
 LalBS                                   CHARACTER VARYING(20),
 LalAC                                   CHARACTER VARYING(20),
 LalAS                                   CHARACTER VARYING(20),
 BandaMorta                              SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 SiglaSim                                CHARACTER VARYING(16),
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNAA add constraint primary key (Sigla) constraint
        PK_TDPUNAA;

--
-- TDPUNAC table definition
--
create table ONLINE.TDPUNAC
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 valoreDB                                SMALLFLOAT,
 Unitamisura                             CHARACTER VARYING(10),
 Zonaimpianto                            SMALLINT,
 LalBC                                   CHARACTER VARYING(20),
 LalBS                                   CHARACTER VARYING(20),
 LalAC                                   CHARACTER VARYING(20),
 LalAS                                   CHARACTER VARYING(20),
 BandaMorta                              SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNAC add constraint primary key (Sigla) constraint
        PK_TDPUNAC;

--
-- TDPUNAD table definition
--
create table ONLINE.TDPUNAD
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 IndDB                                   SMALLINT,
 Unitamisura                             CHARACTER VARYING(10),
 Zonaimpianto                            SMALLINT,
 LalBC                                   CHARACTER VARYING(20),
 LalBS                                   CHARACTER VARYING(20),
 LalAC                                   CHARACTER VARYING(20),
 LalAS                                   CHARACTER VARYING(20),
 BandaMorta                              SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNAD add constraint primary key (Sigla) constraint
        PK_TDPUNAD;

--
-- TDPUNAO table definition
--
create table ONLINE.TDPUNAO
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Morsetticampo                           CHARACTER VARYING(24),
 cavo                                    CHARACTER VARYING(8),
 Morsettisistema                         CHARACTER VARYING(24),
 TipoPeriferica                          CHARACTER VARYING(4),
 IDperi                                  SMALLINT,
 Nomescheda                              CHARACTER VARYING(10),
 IDscheda                                SMALLINT,
 IDpunto                                 SMALLINT,
 Unitamisura                             CHARACTER VARYING(10),
 TipoSegnale                             CHARACTER VARYING(4),
 CSbasso                                 SMALLINT,
 CSalto                                  SMALLINT,
 FSbasso                                 SMALLFLOAT,
 FSalto                                  SMALLFLOAT,
 Coeffiltro                              SMALLFLOAT,
 LimiteFiltro                            SMALLFLOAT,
 Zonaimpianto                            SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 SiglaSim                                CHARACTER VARYING(16),
 InStampa                                SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNAO add constraint primary key (Sigla) constraint
        PK_TDPUNAO;

--
-- TDPUNAS table definition
--
create table ONLINE.TDPUNAS
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Unitamisura                             CHARACTER VARYING(10),
 Periodo                                 SMALLINT,
 TipoCalc                                SMALLINT,
 Contrib1                                CHARACTER VARYING(20),
 Contrib2                                CHARACTER VARYING(20),
 Contrib3                                CHARACTER VARYING(20),
 Contrib4                                CHARACTER VARYING(20),
 Contrib5                                CHARACTER VARYING(20),
 Contrib6                                CHARACTER VARYING(20),
 Contrib7                                CHARACTER VARYING(20),
 Contrib8                                CHARACTER VARYING(20),
 Freq                                    SMALLINT,
 Codice                                  SMALLINT,
 Zonaimpianto                            SMALLINT,
 LalBC                                   CHARACTER VARYING(20),
 LalBS                                   CHARACTER VARYING(20),
 LalAC                                   CHARACTER VARYING(20),
 LalAS                                   CHARACTER VARYING(20),
 BandaMorta                              SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNAS add constraint primary key (Sigla) constraint
        PK_TDPUNAS;

--
-- TDPUNARC table definition
--
create table ONLINE.TDPUNARC
	(
 Indice  				 SMALLINT,
 Descrizione                             CHARACTER VARYING(60),
 Tipo                                    SMALLINT,
 PeriodoL                                SMALLINT,
 Durata                                  SMALLINT,
 NumeroFile                              SMALLINT,
 TriggerA                                SMALLINT,
 TriggerD                                SMALLINT,
 TotPar                                  SMALLINT,
 DatiVet                                 SMALLINT,
 Campione01                              CHARACTER VARYING(20),
 Campione02                              CHARACTER VARYING(20),
 Campione03                              CHARACTER VARYING(20),
 Campione04                              CHARACTER VARYING(20),
 Campione05                              CHARACTER VARYING(20),
 Campione06                              CHARACTER VARYING(20),
 Campione07                              CHARACTER VARYING(20),
 Campione08                              CHARACTER VARYING(20),
 Campione09                              CHARACTER VARYING(20),
 Campione10                              CHARACTER VARYING(20),
 Campione11                              CHARACTER VARYING(20),
 Campione12                              CHARACTER VARYING(20),
 Campione13                              CHARACTER VARYING(20),
 Campione14                              CHARACTER VARYING(20),
 Campione15                              CHARACTER VARYING(20),
 Campione16                              CHARACTER VARYING(20),
 Campione17                              CHARACTER VARYING(20),
 Campione18                              CHARACTER VARYING(20),
 Campione19                              CHARACTER VARYING(20),
 Campione20                              CHARACTER VARYING(20),
 Campione21                              CHARACTER VARYING(20),
 Campione22                              CHARACTER VARYING(20),
 Campione23                              CHARACTER VARYING(20),
 Campione24                              CHARACTER VARYING(20),
 Campione25                              CHARACTER VARYING(20),
 Campione26                              CHARACTER VARYING(20),
 Campione27                              CHARACTER VARYING(20),
 Campione28                              CHARACTER VARYING(20),
 Campione29                              CHARACTER VARYING(20),
 Campione30                              CHARACTER VARYING(20),
 Campione31                              CHARACTER VARYING(20),
 Campione32                              CHARACTER VARYING(20),
 Campione33                              CHARACTER VARYING(20),
 Campione34                              CHARACTER VARYING(20),
 Campione35                              CHARACTER VARYING(20),
 Campione36                              CHARACTER VARYING(20),
 Campione37                              CHARACTER VARYING(20),
 Campione38                              CHARACTER VARYING(20),
 Campione39                              CHARACTER VARYING(20),
 Campione40                              CHARACTER VARYING(20),
 Campione41                              CHARACTER VARYING(20),
 Campione42                              CHARACTER VARYING(20),
 Campione43                              CHARACTER VARYING(20),
 Campione44                              CHARACTER VARYING(20),
 Campione45                              CHARACTER VARYING(20),
 Campione46                              CHARACTER VARYING(20),
 Campione47                              CHARACTER VARYING(20),
 Campione48                              CHARACTER VARYING(20),
 Campione49                              CHARACTER VARYING(20),
 Campione50                              CHARACTER VARYING(20),
 Campione51                              CHARACTER VARYING(20),
 Campione52                              CHARACTER VARYING(20),
 Campione53                              CHARACTER VARYING(20),
 Campione54                              CHARACTER VARYING(20),
 Campione55                              CHARACTER VARYING(20),
 Campione56                              CHARACTER VARYING(20),
 Campione57                              CHARACTER VARYING(20),
 Campione58                              CHARACTER VARYING(20),
 Campione59                              CHARACTER VARYING(20),
 Campione60                              CHARACTER VARYING(20),
 Campione61                              CHARACTER VARYING(20),
 Campione62                              CHARACTER VARYING(20),
 Campione63                              CHARACTER VARYING(20),
 Campione64                              CHARACTER VARYING(20),
 Campione65                              CHARACTER VARYING(20),
 Campione66                              CHARACTER VARYING(20),
 Campione67                              CHARACTER VARYING(20),
 Campione68                              CHARACTER VARYING(20),
 Campione69                              CHARACTER VARYING(20),
 Campione70                              CHARACTER VARYING(20),
 Campione71                              CHARACTER VARYING(20),
 Campione72                              CHARACTER VARYING(20),
 Campione73                              CHARACTER VARYING(20),
 Campione74                              CHARACTER VARYING(20),
 Campione75                              CHARACTER VARYING(20),
 Campione76                              CHARACTER VARYING(20),
 Campione77                              CHARACTER VARYING(20),
 Campione78                              CHARACTER VARYING(20),
 Campione79                              CHARACTER VARYING(20),
 Campione80                              CHARACTER VARYING(20),
 Campione81                              CHARACTER VARYING(20),
 Campione82                              CHARACTER VARYING(20),
 Campione83                              CHARACTER VARYING(20)
	);
alter table ONLINE.TDPUNARC add constraint primary key (Indice) constraint
        PK_TDPUNARC;

--
-- TDPUNDA table definition
--
create table ONLINE.TDPUNDA
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Morsetticampo                           CHARACTER VARYING(24),
 cavo                                    CHARACTER VARYING(8),
 Morsettisistema                         CHARACTER VARYING(24),
 TipoPeriferica                          CHARACTER VARYING(4),
 IDperi                                  SMALLINT,
 Nomescheda                              CHARACTER VARYING(10),
 IDscheda                                SMALLINT,
 IDpunto                                 SMALLINT,
 Contatto                                SMALLINT,
 Stato0                                  CHARACTER VARYING(12),
 Stato1                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 TInib                                   SMALLINT,
 Zonaimpianto                            SMALLINT,
 TipoSegnale                             CHARACTER VARYING(1),
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 SiglaSim                                CHARACTER VARYING(16),
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNDA add constraint primary key (Sigla) constraint
        PK_TDPUNDA;

--
-- TDPUNDC table definition
--
create table ONLINE.TDPUNDC
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Stato0                                  CHARACTER VARYING(12),
 Stato1                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 TInib                                   SMALLINT,
 Zonaimpianto                            SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNDC add constraint primary key (Sigla) constraint
        PK_TDPUNDC;

--
-- TDPUNDD table definition
--
create table ONLINE.TDPUNDD
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 IndDB                                   SMALLINT,
 Stato0                                  CHARACTER VARYING(12),
 Stato1                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 TInib                                   SMALLINT,
 Zonaimpianto                            SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNDD add constraint primary key (Sigla) constraint
        PK_TDPUNDD;

--
-- TDPUNDO table definition
--
create table ONLINE.TDPUNDO
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Morsetticampo                           CHARACTER VARYING(24),
 cavo                                    CHARACTER VARYING(8),
 Morsettisistema                         CHARACTER VARYING(24),
 TipoPeriferica                          CHARACTER VARYING(4),
 IDperi                                  SMALLINT,
 Nomescheda                              CHARACTER VARYING(10),
 IDscheda                                SMALLINT,
 IDpunto                                 SMALLINT,
 IDscheda2                               SMALLINT,
 IDpunto2                                SMALLINT,
 IDscheda3                               SMALLINT,
 IDpunto3                                SMALLINT,
 IDscheda4                               SMALLINT,
 IDpunto4                                SMALLINT,
 Temporizzazione                         SMALLINT,
 Tempo                                   SMALLINT,
 Azione                                  SMALLINT,
 Zonaimpianto                            SMALLINT,
 TipoCom                                 SMALLINT,
 SiglaOrg                                CHARACTER VARYING(20),
 TimeOut                                 SMALLINT,
 StAttuale1                              CHARACTER VARYING(12),
 StAtteso1                               CHARACTER VARYING(12),
 StAttuale2                              CHARACTER VARYING(12),
 StAtteso2                               CHARACTER VARYING(12),
 StAttuale3                              CHARACTER VARYING(12),
 StAtteso3                               CHARACTER VARYING(12),
 StAttuale4                              CHARACTER VARYING(12),
 StAtteso4                               CHARACTER VARYING(12),
 ComProt                                 SMALLINT,
 Note                                    CHARACTER VARYING(32),
 InStampa                                SMALLINT,
 Dainstallare                            SMALLINT,
 SiglaSim                                CHARACTER VARYING(16),
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNDO add constraint primary key (Sigla) constraint
        PK_TDPUNDO;

--
-- TDPUNDS table definition
--
create table ONLINE.TDPUNDS
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 TipoCalc                                SMALLINT,
 SiglaDig1                               CHARACTER VARYING(20),
 SiglaDig2                               CHARACTER VARYING(20),
 SiglaDig3                               CHARACTER VARYING(20),
 SiglaDig4                               CHARACTER VARYING(20),
 Stato0                                  CHARACTER VARYING(10),
 Stato1                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 TInib                                   SMALLINT,
 Zonaimpianto                            SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNDS add constraint primary key (Sigla) constraint
        PK_TDPUNDS;

--
-- TDPUNOR table definition
--
create table ONLINE.TDPUNOR
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Zonaimpianto                            SMALLINT,
 Timeout                                 SMALLINT,
 Tipo                                    CHARACTER VARYING(12),
 SCont1                                  CHARACTER VARYING(20),
 SCont2                                  CHARACTER VARYING(20),
 SCont3                                  CHARACTER VARYING(20),
 SCont4                                  CHARACTER VARYING(20),
 SCont5                                  CHARACTER VARYING(20),
 STProt                                  CHARACTER VARYING(8),
 Inibente                                SMALLINT,
 StatoI                                  CHARACTER VARYING(12),
 TagPP1                                  CHARACTER VARYING(20),
 TagPP2                                  CHARACTER VARYING(20),
 Tinibiz                                 SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNOR add constraint primary key (Sigla) constraint
        PK_TDPUNOR;

--
-- TDPUNST table definition
--
create table ONLINE.TDPUNST
	(
 Sigla   				 CHARACTER VARYING(20),
 Descrizione                             CHARACTER VARYING(60),
 Valore                                  CHARACTER VARYING(15),
 Zonaimpianto                            SMALLINT,
 Trattamento                             SMALLINT,
 Severita                                SMALLINT,
 Note                                    CHARACTER VARYING(32),
 Dainstallare                            SMALLINT,
 Gerarchia                               CHARACTER VARYING(18)
	);
alter table ONLINE.TDPUNST add constraint primary key (Sigla) constraint
        PK_TDPUNST;

--
-- TDPUNTO table definition
--
create table ONLINE.TDPUNTO
	(
 TipoO  			   	 CHARACTER VARYING(12),
 codice 				 SMALLINT,
 Descrizione                             CHARACTER VARYING(60),
 NumSegC                                 SMALLINT,
 DescrSeg1                               CHARACTER VARYING(24),
 DescrSeg2                               CHARACTER VARYING(24),
 DescrSeg3                               CHARACTER VARYING(24),
 Descrseg4                               CHARACTER VARYING(24),
 DescrSeg5                               CHARACTER VARYING(24),
 Stato1                                  CHARACTER VARYING(12),
 Stato2                                  CHARACTER VARYING(12),
 Stato3                                  CHARACTER VARYING(12),
 Stato4                                  CHARACTER VARYING(12),
 Stato5                                  CHARACTER VARYING(12),
 Stato6                                  CHARACTER VARYING(12),
 Stato7                                  CHARACTER VARYING(12),
 Stato8                                  CHARACTER VARYING(12),
 Stato9                                  CHARACTER VARYING(12),
 Stato10                                 CHARACTER VARYING(12),
 Stato11                                 CHARACTER VARYING(12),
 Stato12                                 CHARACTER VARYING(12),
 Stato13                                 CHARACTER VARYING(12),
 Stato14                                 CHARACTER VARYING(12),
 Stato15                                 CHARACTER VARYING(12),
 Stato16                                 CHARACTER VARYING(12),
 Stato17                                 CHARACTER VARYING(12),
 Stato18                                 CHARACTER VARYING(12),
 Stato19                                 CHARACTER VARYING(12),
 Stato20                                 CHARACTER VARYING(12),
 Stato21                                 CHARACTER VARYING(12),
 Stato22                                 CHARACTER VARYING(12),
 Stato23                                 CHARACTER VARYING(12),
 Stato24                                 CHARACTER VARYING(12),
 Stato25                                 CHARACTER VARYING(12),
 Stato26                                 CHARACTER VARYING(12),
 Stato27                                 CHARACTER VARYING(12),
 Stato28                                 CHARACTER VARYING(12),
 Stato29                                 CHARACTER VARYING(12),
 Stato30                                 CHARACTER VARYING(12),
 Stato31                                 CHARACTER VARYING(12),
 Stato32                                 CHARACTER VARYING(12)
	);
alter table ONLINE.TDPUNTO add constraint primary key (codice) constraint
        PK_TDPUNTO;

--
-- ALLARDB table definition
--
create table ONLINE.ALLARDB
	(
 Indice  				 SMALLINT,
 NumAll                                  INTEGER,
 zona0                                   SMALLINT,
 zona1                                   SMALLINT,
 zona2                                   SMALLINT,
 zona3                                   SMALLINT,
 zona4                                   SMALLINT,
 zona5                                   SMALLINT,
 zona6                                   SMALLINT,
 zona7                                   SMALLINT,
 zona8                                   SMALLINT,
 zona9                                   SMALLINT,
 zona10                                  SMALLINT,
 zona11                                  SMALLINT,
 zona12                                  SMALLINT,
 zona13                                  SMALLINT,
 zona14                                  SMALLINT,
 zona15                                  SMALLINT
	);
alter table ONLINE.ALLARDB add constraint primary key (Indice) constraint
        PK_ALLARDB;

--
-- ALLARLINE table definition
--
create table ONLINE.ALLARLINE
	(
 Indice  				 SMALLINT,
 Device                                  CHARACTER VARYING(8),
 baud                                    CHARACTER VARYING(16),
 data                                    CHARACTER VARYING(1),
 stop                                    CHARACTER VARYING(1),
 parita                                  CHARACTER VARYING(1)
	);
alter table ONLINE.ALLARLINE add constraint primary key (Indice) constraint
        PK_ALLARLINE;

--
-- ALLARLIV table definition
--
create table ONLINE.ALLARLIV
	(
 Indice  				 SMALLINT,
 ColSev1                                 CHARACTER VARYING(2),
 ColSev2                                 CHARACTER VARYING(2),
 ColSev3                                 CHARACTER VARYING(2),
 Emissione                               CHARACTER VARYING(16),
 Rientro                                 CHARACTER VARYING(16)
	);
alter table ONLINE.ALLARLIV add constraint primary key (Indice) constraint
        PK_ALLARLIV;
--
-- ALLARSERV table definition
--
create table ONLINE.ALLARSERV
	(
 TipoCicalino  				 SMALLINT,
 Sev1Cica                                SMALLINT,
 Sev2Cica                                SMALLINT,
 Sev3Cica                                SMALLINT,
 FaMediaT                                SMALLINT,
 FaFiltro                                SMALLINT,
 FaScarto                                SMALLINT,
 FaMediaI                                SMALLINT,
 FaSomma                                 SMALLINT,
 FaIntegrale                             SMALLINT,
 freq_ut                                 SMALLINT,
 REP_MESS                                SMALLINT,
 REP_RETRY                               SMALLINT
	);
alter table ONLINE.ALLARSERV add constraint primary key (TipoCicalino) 
	constraint PK_ALLARSERV;

--
-- ALLARSTRAT table definition
--
create table ONLINE.ALLARSTRAT
	(
 Indice  				 SMALLINT,
 linea0                                  SMALLINT,
 linea1                                  SMALLINT,
 linea2                                  SMALLINT,
 linea3                                  SMALLINT,
 zona0                                   SMALLINT,
 zona1                                   SMALLINT,
 zona2                                   SMALLINT,
 zona3                                   SMALLINT,
 zona4                                   SMALLINT,
 zona5                                   SMALLINT,
 zona6                                   SMALLINT,
 zona7                                   SMALLINT,
 zona8                                   SMALLINT,
 zona9                                   SMALLINT,
 zona10                                  SMALLINT,
 zona11                                  SMALLINT,
 zona12                                  SMALLINT,
 zona13                                  SMALLINT,
 zona14                                  SMALLINT,
 zona15                                  SMALLINT
	);
alter table ONLINE.ALLARSTRAT add constraint primary key (Indice) constraint
        PK_ALLARSTRAT;

--
-- CONFIGURAZIONEDB table definition
--
create table ONLINE.CONFIGURAZIONEDB
	(
 NomeImpianto  				 CHARACTER VARYING(24),
 Tipo                                    CHARACTER VARYING(12),
 Descrizione                             CHARACTER VARYING(50),
 subuten                                 CHARACTER VARYING(10),
 DimAA                                   INTEGER,
 DimAS                                   INTEGER,
 DimAC                                   INTEGER,
 DimAD                                   INTEGER,
 DimAO                                   INTEGER,
 DimDA                                   INTEGER,
 DimDS                                   INTEGER,
 DimDC                                   INTEGER,
 DimDD                                   INTEGER,
 DimDO                                   INTEGER,
 Organi                                  INTEGER,
 Stringhe                                INTEGER
	);
alter table ONLINE.CONFIGURAZIONEDB add constraint primary key (NomeImpianto) 
	constraint PK_CONFIGDB;

--
-- MISTABK table definition
--
create table ONLINE.MISTABK
	(
 Indice  				 SMALLINT,
 Coeff                                   SMALLFLOAT
	);
alter table ONLINE.MISTABK add constraint primary key (Indice)
        constraint PK_MISTABK;

--
-- CPERIF table definition
--
create table ONLINE.CPERIF
	(
 IndStar                                 SMALLINT,
 NomeScheda                              CHARACTER VARYING(10),
 Quantita                                SMALLINT
	);
alter table ONLINE.CPERIF add constraint primary key (IndStar,NomeScheda) 
	constraint PK_CPERIF;

--
-- DESCRISCHEDA table definition
--
create table ONLINE.DESCRISCHEDA
	(
 NomeScheda   				 CHARACTER VARYING(10),
 Codice                                  SMALLINT,
 Descrizione                             CHARACTER VARYING(30),
 NumeroAA                                SMALLINT,
 NumeroAO                                SMALLINT,
 NumeroDA                                SMALLINT,
 NumeroDO                                SMALLINT
	);
alter table ONLINE.DESCRISCHEDA add constraint primary key (NomeScheda)
        constraint PK_DESCRISCHEDA;

--
-- ELABORAZIONI table definition
--
create table ONLINE.ELABORAZIONI
	(
 Sigla                                   CHARACTER VARYING(20),
 TipoElabo                               SMALLINT,
 Elemento                                CHARACTER VARYING(50)
	);
alter table ONLINE.ELABORAZIONI add constraint primary key (Sigla,TipoElabo,Elemento)
        constraint PK_ELABORAZIONI;

--
-- NOMI table definition
--
create table ONLINE.NOMI
	(
 Sigla  				 CHARACTER VARYING(20),
 Tipo                                    CHARACTER VARYING(2),
 PointDB                                 INTEGER,
 ExtDB                                   SMALLINT
	);
alter table ONLINE.NOMI add constraint primary key (Sigla) constraint
        PK_NOMI;

--
-- TABPERI table definition
--
create table ONLINE.TABPERI
	(
 IndStar  				 SMALLINT,
 TipoP                                   CHARACTER VARYING(10),
 Duale                                   SMALLINT,
 Abilitato                               SMALLINT
	);
alter table ONLINE.TABPERI add constraint primary key (IndStar) constraint
        PK_TABPERI;

--
-- TDIZST table definition
--
create table ONLINE.TDIZST
	(
 Stato                                   CHARACTER VARYING(12),
 codice 				 SMALLINT
	);
alter table ONLINE.TDIZST add constraint primary key (codice) constraint
        PK_TDIZST;

--
-- TABULATI table definition
--
create table ONLINE.TABULATI
	(
 Nome  					 CHARACTER VARYING(8),
 Periodo                                 SMALLINT,
 Periodico                               SMALLINT,
 Cicli                                   SMALLINT,
 Attesa                                  SMALLINT,
 Tipo                                    SMALLINT
	);
alter table ONLINE.TABULATI add constraint primary key (Nome) constraint
        PK_TABULATI;
