rem =======================================================
rem  
rem   modulo crea_scada_tab.sql
rem   tipo 
rem   release 1.1
rem   data 4/5/96
rem   reserved @(#)crea_scada_tab.sql	1.1
rem  
rem                        **************
rem                        CREA_SCADA_TAB 
rem                        **************
rem 
rem This procedure create all the tables nedeed for SCADA 
rem 
rem First Creation 28 March 1996
rem Author M.De Chirico & E.Locatelli 
rem
rem =========================================================

rem =========================================================
rem
rem Creazione tabelle editing
rem
rem =========================================================

rem
rem EDITAA table definition
rem

create table LEGOSVIL.EDITAA
	(
  Sigla   VARCHAR2(10) CONSTRAINT pk_editaa PRIMARY KEY,
  Descrizione                              VARCHAR2(24),
  Morsetticampo                            VARCHAR2(24),
  cavo                                     VARCHAR2(8),
  Morsettisistema                          VARCHAR2(24),
  TipoPeriferica                           VARCHAR2(4),
  IDperi                                   NUMBER(5),
  Nomescheda                               VARCHAR2(10),
  IDscheda                                 NUMBER(5),
  IDpunto                                  NUMBER(5),
  Unitamisura                              VARCHAR2(10),
  Periodo                                  NUMBER(5),
  TipoSegnale                              VARCHAR2(4),
  CSbasso                                  NUMBER(10),
  CSalto                                   NUMBER(10),
  IdAttendibile                            NUMBER(5),
  CoeffGV                                  NUMBER(5),
  TipoConversione                          VARCHAR2(4),
  FSbasso                                  FLOAT(126),
  FSalto                                   FLOAT(126),
  Coeff0                                   FLOAT(126),
  Coeff1                                   FLOAT(126),
  Coeff2                                   FLOAT(126),
  Coeff3                                   FLOAT(126),
  Coeff4                                   FLOAT(126),
  GiuntoFreddo                             VARCHAR2(10),
  Coeffiltro                               FLOAT(126),
  Limite0                                  FLOAT(126),
  Zonaimpianto                             NUMBER(5),
  LalBC                                    VARCHAR2(10),
  LalBS                                    VARCHAR2(10),
  LalAC                                    VARCHAR2(10),
  LalAS                                    VARCHAR2(10),
  BandaMorta                               NUMBER(5),
  Trattamento                              NUMBER(5),
  Severita                                 NUMBER(5),
  Note                                     VARCHAR2(32),
  Dainstallare                             NUMBER(5),
  SiglaSim                                 VARCHAR2(16),
  Gerarchia                                VARCHAR2(18)
	);

rem
rem EDITAC table definition
rem

create table LEGOSVIL.EDITAC
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editac PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 valoreDB                                FLOAT(126),
 Unitamisura                             VARCHAR2(10),
 Zonaimpianto                            NUMBER(5),
 LalBC                                   VARCHAR2(10),
 LalBS                                   VARCHAR2(10),
 LalAC                                   VARCHAR2(10),
 LalAS                                   VARCHAR2(10),
 BandaMorta                              NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITAD table definition
rem

create table LEGOSVIL.EDITAD
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editad PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 IndDB                                   NUMBER(5),
 Unitamisura                             VARCHAR2(10),
 Zonaimpianto                            NUMBER(5),
 LalBC                                   VARCHAR2(10),
 LalBS                                   VARCHAR2(10),
 LalAC                                   VARCHAR2(10),
 LalAS                                   VARCHAR2(10),
 BandaMorta                              NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITAO table definition
rem

create table LEGOSVIL.EDITAO
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editao PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Morsetticampo                           VARCHAR2(24),
 cavo                                    VARCHAR2(8),
 Morsettisistema                         VARCHAR2(24),
 TipoPeriferica                          VARCHAR2(4),
 IDperi                                  NUMBER(5),
 Nomescheda                              VARCHAR2(10),
 IDscheda                                NUMBER(5),
 IDpunto                                 NUMBER(5),
 Unitamisura                             VARCHAR2(10),
 TipoSegnale                             VARCHAR2(4),
 CSbasso                                 NUMBER(5),
 CSalto                                  NUMBER(5),
 FSbasso                                 FLOAT(126),
 FSalto                                  FLOAT(126),
 Coeffiltro                              FLOAT(126),
 LimiteFiltro                            FLOAT(126),
 Zonaimpianto                            NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 SiglaSim                                VARCHAR2(16),
 InStampa                                NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITAS table definition
rem

create table LEGOSVIL.EDITAS
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editas PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Unitamisura                             VARCHAR2(10),
 Periodo                                 NUMBER(5),
 TipoCalc                                NUMBER(5),
 Contrib1                                VARCHAR2(10),
 Contrib2                                VARCHAR2(10),
 Contrib3                                VARCHAR2(10),
 Contrib4                                VARCHAR2(10),
 Contrib5                                VARCHAR2(10),
 Contrib6                                VARCHAR2(10),
 Contrib7                                VARCHAR2(10),
 Contrib8                                VARCHAR2(10),
 Freq                                    NUMBER(5),
 Codice                                  NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 LalBC                                   VARCHAR2(10),
 LalBS                                   VARCHAR2(10),
 LalAC                                   VARCHAR2(10),
 LalAS                                   VARCHAR2(10),
 BandaMorta                              NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITARC table definition
rem

create table LEGOSVIL.EDITARC
	(
 Indice   NUMBER(5) CONSTRAINT pk_editarc PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Tipo                                    NUMBER(5),
 PeriodoL                                NUMBER(5),
 Durata                                  NUMBER(5),
 NumeroFile                              NUMBER(5),
 TriggerA                                NUMBER(5),
 TriggerD                                NUMBER(5),
 TotPar                                  NUMBER(5),
 DatiVet                                 NUMBER(5),
 Campione01                              VARCHAR2(10),
 Campione02                              VARCHAR2(10),
 Campione03                              VARCHAR2(10),
 Campione04                              VARCHAR2(10),
 Campione05                              VARCHAR2(10),
 Campione06                              VARCHAR2(10),
 Campione07                              VARCHAR2(10),
 Campione08                              VARCHAR2(10),
 Campione09                              VARCHAR2(10),
 Campione10                              VARCHAR2(10),
 Campione11                              VARCHAR2(10),
 Campione12                              VARCHAR2(10),
 Campione13                              VARCHAR2(10),
 Campione14                              VARCHAR2(10),
 Campione15                              VARCHAR2(10),
 Campione16                              VARCHAR2(10),
 Campione17                              VARCHAR2(10),
 Campione18                              VARCHAR2(10),
 Campione19                              VARCHAR2(10),
 Campione20                              VARCHAR2(10),
 Campione21                              VARCHAR2(10),
 Campione22                              VARCHAR2(10),
 Campione23                              VARCHAR2(10),
 Campione24                              VARCHAR2(10),
 Campione25                              VARCHAR2(10),
 Campione26                              VARCHAR2(10),
 Campione27                              VARCHAR2(10),
 Campione28                              VARCHAR2(10),
 Campione29                              VARCHAR2(10),
 Campione30                              VARCHAR2(10),
 Campione31                              VARCHAR2(10),
 Campione32                              VARCHAR2(10),
 Campione33                              VARCHAR2(10),
 Campione34                              VARCHAR2(10),
 Campione35                              VARCHAR2(10),
 Campione36                              VARCHAR2(10),
 Campione37                              VARCHAR2(10),
 Campione38                              VARCHAR2(10),
 Campione39                              VARCHAR2(10),
 Campione40                              VARCHAR2(10),
 Campione41                              VARCHAR2(10),
 Campione42                              VARCHAR2(10),
 Campione43                              VARCHAR2(10),
 Campione44                              VARCHAR2(10),
 Campione45                              VARCHAR2(10),
 Campione46                              VARCHAR2(10),
 Campione47                              VARCHAR2(10),
 Campione48                              VARCHAR2(10),
 Campione49                              VARCHAR2(10),
 Campione50                              VARCHAR2(10),
 Campione51                              VARCHAR2(10),
 Campione52                              VARCHAR2(10),
 Campione53                              VARCHAR2(10),
 Campione54                              VARCHAR2(10),
 Campione55                              VARCHAR2(10),
 Campione56                              VARCHAR2(10),
 Campione57                              VARCHAR2(10),
 Campione58                              VARCHAR2(10),
 Campione59                              VARCHAR2(10),
 Campione60                              VARCHAR2(10),
 Campione61                              VARCHAR2(10),
 Campione62                              VARCHAR2(10),
 Campione63                              VARCHAR2(10),
 Campione64                              VARCHAR2(10),
 Campione65                              VARCHAR2(10),
 Campione66                              VARCHAR2(10),
 Campione67                              VARCHAR2(10),
 Campione68                              VARCHAR2(10),
 Campione69                              VARCHAR2(10),
 Campione70                              VARCHAR2(10),
 Campione71                              VARCHAR2(10),
 Campione72                              VARCHAR2(10),
 Campione73                              VARCHAR2(10),
 Campione74                              VARCHAR2(10),
 Campione75                              VARCHAR2(10),
 Campione76                              VARCHAR2(10),
 Campione77                              VARCHAR2(10),
 Campione78                              VARCHAR2(10),
 Campione79                              VARCHAR2(10),
 Campione80                              VARCHAR2(10),
 Campione81                              VARCHAR2(10),
 Campione82                              VARCHAR2(10),
 Campione83                              VARCHAR2(10)
	);

rem
rem EDITDA table definition
rem

create table LEGOSVIL.EDITDA
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editda PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Morsetticampo                           VARCHAR2(24),
 cavo                                    VARCHAR2(8),
 Morsettisistema                         VARCHAR2(24),
 TipoPeriferica                          VARCHAR2(4),
 IDperi                                  NUMBER(5),
 Nomescheda                              VARCHAR2(10),
 IDscheda                                NUMBER(5),
 IDpunto                                 NUMBER(5),
 Contatto                                NUMBER(5),
 Stato0                                  VARCHAR2(12),
 Stato1                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 TInib                                   NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 TipoSegnale                             VARCHAR2(1),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 SiglaSim                                VARCHAR2(16),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITDC table definition
rem

create table LEGOSVIL.EDITDC
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editdc PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Stato0                                  VARCHAR2(12),
 Stato1                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 TInib                                   NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITDD table definition
rem

create table LEGOSVIL.EDITDD
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editdd PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 IndDB                                   NUMBER(5),
 Stato0                                  VARCHAR2(12),
 Stato1                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 TInib                                   NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITDO table definition
rem

create table LEGOSVIL.EDITDO
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editdo PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Morsetticampo                           VARCHAR2(24),
 cavo                                    VARCHAR2(8),
 Morsettisistema                         VARCHAR2(24),
 TipoPeriferica                          VARCHAR2(4),
 IDperi                                  NUMBER(5),
 Nomescheda                              VARCHAR2(10),
 IDscheda                                NUMBER(5),
 IDpunto                                 NUMBER(5),
 IDscheda2                               NUMBER(5),
 IDpunto2                                NUMBER(5),
 IDscheda3                               NUMBER(5),
 IDpunto3                                NUMBER(5),
 IDscheda4                               NUMBER(5),
 IDpunto4                                NUMBER(5),
 Temporizzazione                         NUMBER(5),
 Tempo                                   NUMBER(5),
 Azione                                  NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 TipoCom                                 NUMBER(5),
 SiglaOrg                                VARCHAR2(10),
 TimeOut                                 NUMBER(5),
 StAttuale1                              VARCHAR2(12),
 StAtteso1                               VARCHAR2(12),
 StAttuale2                              VARCHAR2(12),
 StAtteso2                               VARCHAR2(12),
 StAttuale3                              VARCHAR2(12),
 StAtteso3                               VARCHAR2(12),
 StAttuale4                              VARCHAR2(12),
 StAtteso4                               VARCHAR2(12),
 ComProt                                 NUMBER(5),
 Note                                    VARCHAR2(32),
 InStampa                                NUMBER(5),
 Dainstallare                            NUMBER(5),
 SiglaSim                                VARCHAR2(16),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITDS table definition
rem

create table LEGOSVIL.EDITDS
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editds PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 TipoCalc                                NUMBER(5),
 SiglaDig1                               VARCHAR2(10),
 SiglaDig2                               VARCHAR2(10),
 SiglaDig3                               VARCHAR2(10),
 SiglaDig4                               VARCHAR2(10),
 Stato0                                  VARCHAR2(10),
 Stato1                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 TInib                                   NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITOR table definition
rem

create table LEGOSVIL.EDITOR
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editor PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Zonaimpianto                            NUMBER(5),
 Timeout                                 NUMBER(5),
 Tipo                                    VARCHAR2(12),
 SCont1                                  VARCHAR2(10),
 SCont2                                  VARCHAR2(10),
 SCont3                                  VARCHAR2(10),
 SCont4                                  VARCHAR2(10),
 SCont5                                  VARCHAR2(10),
 STProt                                  VARCHAR2(8),
 Inibente                                NUMBER(5),
 StatoI                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 Tinibiz                                 NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITST table definition
rem

create table LEGOSVIL.EDITST
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_editst PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Valore                                  VARCHAR2(15),
 Zonaimpianto                            NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem EDITTO table definition
rem

create table LEGOSVIL.EDITTO
	(
 TipoO   VARCHAR2(12) CONSTRAINT pk_editto PRIMARY KEY,
 codice                                  NUMBER(5),
 Descrizione                             VARCHAR2(24),
 NumSegC                                 NUMBER(5),
 DescrSeg1                               VARCHAR2(24),
 DescrSeg2                               VARCHAR2(24),
 DescrSeg3                               VARCHAR2(24),
 Descrseg4                               VARCHAR2(24),
 DescrSeg5                               VARCHAR2(24),
 Stato1                                  VARCHAR2(12),
 Stato2                                  VARCHAR2(12),
 Stato3                                  VARCHAR2(12),
 Stato4                                  VARCHAR2(12),
 Stato5                                  VARCHAR2(12),
 Stato6                                  VARCHAR2(12),
 Stato7                                  VARCHAR2(12),
 Stato8                                  VARCHAR2(12),
 Stato9                                  VARCHAR2(12),
 Stato10                                 VARCHAR2(12),
 Stato11                                 VARCHAR2(12),
 Stato12                                 VARCHAR2(12),
 Stato13                                 VARCHAR2(12),
 Stato14                                 VARCHAR2(12),
 Stato15                                 VARCHAR2(12),
 Stato16                                 VARCHAR2(12),
 Stato17                                 VARCHAR2(12),
 Stato18                                 VARCHAR2(12),
 Stato19                                 VARCHAR2(12),
 Stato20                                 VARCHAR2(12),
 Stato21                                 VARCHAR2(12),
 Stato22                                 VARCHAR2(12),
 Stato23                                 VARCHAR2(12),
 Stato24                                 VARCHAR2(12),
 Stato25                                 VARCHAR2(12),
 Stato26                                 VARCHAR2(12),
 Stato27                                 VARCHAR2(12),
 Stato28                                 VARCHAR2(12),
 Stato29                                 VARCHAR2(12),
 Stato30                                 VARCHAR2(12),
 Stato31                                 VARCHAR2(12),
 Stato32                                 VARCHAR2(12)
	);

rem
rem ERRORIPUNTI table definition
rem

create table LEGOSVIL.ERRORIPUNTI
	(
 Sigla   				   VARCHAR2(12),
 Tipo                                    VARCHAR2(2),
 ErrCode                                 NUMBER(5),
 ErrString                               VARCHAR2(255),
 CONSTRAINT pk_erroripunti PRIMARY KEY (Sigla,Tipo,ErrCode)
	);


rem =========================================================
rem
rem Creazione tabelle operative
rem
rem =========================================================

rem
rem TDPUNAA table definition
rem

create table LEGOSVIL.TDPUNAA
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntaa PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Morsetticampo                           VARCHAR2(24),
 cavo                                    VARCHAR2(8),
 Morsettisistema                         VARCHAR2(24),
 TipoPeriferica                          VARCHAR2(4),
 IDperi                                  NUMBER(5),
 Nomescheda                              VARCHAR2(10),
 IDscheda                                NUMBER(5),
 IDpunto                                 NUMBER(5),
 Unitamisura                             VARCHAR2(10),
 Periodo                                 NUMBER(5),
 TipoSegnale                             VARCHAR2(4),
 CSbasso                                 NUMBER(10),
 CSalto                                  NUMBER(10),
 IdAttendibile                           NUMBER(5),
 CoeffGV                                 NUMBER(5),
 TipoConversione                         VARCHAR2(4),
 FSbasso                                 FLOAT(126),
 FSalto                                  FLOAT(126),
 Coeff0                                  FLOAT(126),
 Coeff1                                  FLOAT(126),
 Coeff2                                  FLOAT(126),
 Coeff3                                  FLOAT(126),
 Coeff4                                  FLOAT(126),
 GiuntoFreddo                            VARCHAR2(10),
 Coeffiltro                              FLOAT(126),
 Limite0                                 FLOAT(126),
 Zonaimpianto                            NUMBER(5),
 LalBC                                   VARCHAR2(10),
 LalBS                                   VARCHAR2(10),
 LalAC                                   VARCHAR2(10),
 LalAS                                   VARCHAR2(10),
 BandaMorta                              NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 SiglaSim                                VARCHAR2(16),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNAC table definition
rem

create table LEGOSVIL.TDPUNAC
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntac PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 valoreDB                                FLOAT(126),
 Unitamisura                             VARCHAR2(10),
 Zonaimpianto                            NUMBER(5),
 LalBC                                   VARCHAR2(10),
 LalBS                                   VARCHAR2(10),
 LalAC                                   VARCHAR2(10),
 LalAS                                   VARCHAR2(10),
 BandaMorta                              NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNAD table definition
rem

create table LEGOSVIL.TDPUNAD
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntad PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 IndDB                                   NUMBER(5),
 Unitamisura                             VARCHAR2(10),
 Zonaimpianto                            NUMBER(5),
 LalBC                                   VARCHAR2(10),
 LalBS                                   VARCHAR2(10),
 LalAC                                   VARCHAR2(10),
 LalAS                                   VARCHAR2(10),
 BandaMorta                              NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNAO table definition
rem

create table LEGOSVIL.TDPUNAO
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntao PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Morsetticampo                           VARCHAR2(24),
 cavo                                    VARCHAR2(8),
 Morsettisistema                         VARCHAR2(24),
 TipoPeriferica                          VARCHAR2(4),
 IDperi                                  NUMBER(5),
 Nomescheda                              VARCHAR2(10),
 IDscheda                                NUMBER(5),
 IDpunto                                 NUMBER(5),
 Unitamisura                             VARCHAR2(10),
 TipoSegnale                             VARCHAR2(4),
 CSbasso                                 NUMBER(5),
 CSalto                                  NUMBER(5),
 FSbasso                                 FLOAT(126),
 FSalto                                  FLOAT(126),
 Coeffiltro                              FLOAT(126),
 LimiteFiltro                            FLOAT(126),
 Zonaimpianto                            NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 SiglaSim                                VARCHAR2(16),
 InStampa                                NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNAS table definition
rem

create table LEGOSVIL.TDPUNAS
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntas PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Unitamisura                             VARCHAR2(10),
 Periodo                                 NUMBER(5),
 TipoCalc                                NUMBER(5),
 Contrib1                                VARCHAR2(10),
 Contrib2                                VARCHAR2(10),
 Contrib3                                VARCHAR2(10),
 Contrib4                                VARCHAR2(10),
 Contrib5                                VARCHAR2(10),
 Contrib6                                VARCHAR2(10),
 Contrib7                                VARCHAR2(10),
 Contrib8                                VARCHAR2(10),
 Freq                                    NUMBER(5),
 Codice                                  NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 LalBC                                   VARCHAR2(10),
 LalBS                                   VARCHAR2(10),
 LalAC                                   VARCHAR2(10),
 LalAS                                   VARCHAR2(10),
 BandaMorta                              NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNARC table definition
rem

create table LEGOSVIL.TDPUNARC
	(
 Indice  NUMBER(5) CONSTRAINT pk_puntarc PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Tipo                                    NUMBER(5),
 PeriodoL                                NUMBER(5),
 Durata                                  NUMBER(5),
 NumeroFile                              NUMBER(5),
 TriggerA                                NUMBER(5),
 TriggerD                                NUMBER(5),
 TotPar                                  NUMBER(5),
 DatiVet                                 NUMBER(5),
 Campione01                              VARCHAR2(10),
 Campione02                              VARCHAR2(10),
 Campione03                              VARCHAR2(10),
 Campione04                              VARCHAR2(10),
 Campione05                              VARCHAR2(10),
 Campione06                              VARCHAR2(10),
 Campione07                              VARCHAR2(10),
 Campione08                              VARCHAR2(10),
 Campione09                              VARCHAR2(10),
 Campione10                              VARCHAR2(10),
 Campione11                              VARCHAR2(10),
 Campione12                              VARCHAR2(10),
 Campione13                              VARCHAR2(10),
 Campione14                              VARCHAR2(10),
 Campione15                              VARCHAR2(10),
 Campione16                              VARCHAR2(10),
 Campione17                              VARCHAR2(10),
 Campione18                              VARCHAR2(10),
 Campione19                              VARCHAR2(10),
 Campione20                              VARCHAR2(10),
 Campione21                              VARCHAR2(10),
 Campione22                              VARCHAR2(10),
 Campione23                              VARCHAR2(10),
 Campione24                              VARCHAR2(10),
 Campione25                              VARCHAR2(10),
 Campione26                              VARCHAR2(10),
 Campione27                              VARCHAR2(10),
 Campione28                              VARCHAR2(10),
 Campione29                              VARCHAR2(10),
 Campione30                              VARCHAR2(10),
 Campione31                              VARCHAR2(10),
 Campione32                              VARCHAR2(10),
 Campione33                              VARCHAR2(10),
 Campione34                              VARCHAR2(10),
 Campione35                              VARCHAR2(10),
 Campione36                              VARCHAR2(10),
 Campione37                              VARCHAR2(10),
 Campione38                              VARCHAR2(10),
 Campione39                              VARCHAR2(10),
 Campione40                              VARCHAR2(10),
 Campione41                              VARCHAR2(10),
 Campione42                              VARCHAR2(10),
 Campione43                              VARCHAR2(10),
 Campione44                              VARCHAR2(10),
 Campione45                              VARCHAR2(10),
 Campione46                              VARCHAR2(10),
 Campione47                              VARCHAR2(10),
 Campione48                              VARCHAR2(10),
 Campione49                              VARCHAR2(10),
 Campione50                              VARCHAR2(10),
 Campione51                              VARCHAR2(10),
 Campione52                              VARCHAR2(10),
 Campione53                              VARCHAR2(10),
 Campione54                              VARCHAR2(10),
 Campione55                              VARCHAR2(10),
 Campione56                              VARCHAR2(10),
 Campione57                              VARCHAR2(10),
 Campione58                              VARCHAR2(10),
 Campione59                              VARCHAR2(10),
 Campione60                              VARCHAR2(10),
 Campione61                              VARCHAR2(10),
 Campione62                              VARCHAR2(10),
 Campione63                              VARCHAR2(10),
 Campione64                              VARCHAR2(10),
 Campione65                              VARCHAR2(10),
 Campione66                              VARCHAR2(10),
 Campione67                              VARCHAR2(10),
 Campione68                              VARCHAR2(10),
 Campione69                              VARCHAR2(10),
 Campione70                              VARCHAR2(10),
 Campione71                              VARCHAR2(10),
 Campione72                              VARCHAR2(10),
 Campione73                              VARCHAR2(10),
 Campione74                              VARCHAR2(10),
 Campione75                              VARCHAR2(10),
 Campione76                              VARCHAR2(10),
 Campione77                              VARCHAR2(10),
 Campione78                              VARCHAR2(10),
 Campione79                              VARCHAR2(10),
 Campione80                              VARCHAR2(10),
 Campione81                              VARCHAR2(10),
 Campione82                              VARCHAR2(10),
 Campione83                              VARCHAR2(10)
	);

rem
rem TDPUNDA table definition
rem

create table LEGOSVIL.TDPUNDA
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntda PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Morsetticampo                           VARCHAR2(24),
 cavo                                    VARCHAR2(8),
 Morsettisistema                         VARCHAR2(24),
 TipoPeriferica                          VARCHAR2(4),
 IDperi                                  NUMBER(5),
 Nomescheda                              VARCHAR2(10),
 IDscheda                                NUMBER(5),
 IDpunto                                 NUMBER(5),
 Contatto                                NUMBER(5),
 Stato0                                  VARCHAR2(12),
 Stato1                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 TInib                                   NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 TipoSegnale                             VARCHAR2(1),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 SiglaSim                                VARCHAR2(16),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNDC table definition
rem

create table LEGOSVIL.TDPUNDC
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntdc PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Stato0                                  VARCHAR2(12),
 Stato1                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 TInib                                   NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNDD table definition
rem

create table LEGOSVIL.TDPUNDD
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntdd PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 IndDB                                   NUMBER(5),
 Stato0                                  VARCHAR2(12),
 Stato1                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 TInib                                   NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNDO table definition
rem

create table LEGOSVIL.TDPUNDO
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntdo PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Morsetticampo                           VARCHAR2(24),
 cavo                                    VARCHAR2(8),
 Morsettisistema                         VARCHAR2(24),
 TipoPeriferica                          VARCHAR2(4),
 IDperi                                  NUMBER(5),
 Nomescheda                              VARCHAR2(10),
 IDscheda                                NUMBER(5),
 IDpunto                                 NUMBER(5),
 IDscheda2                               NUMBER(5),
 IDpunto2                                NUMBER(5),
 IDscheda3                               NUMBER(5),
 IDpunto3                                NUMBER(5),
 IDscheda4                               NUMBER(5),
 IDpunto4                                NUMBER(5),
 Temporizzazione                         NUMBER(5),
 Tempo                                   NUMBER(5),
 Azione                                  NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 TipoCom                                 NUMBER(5),
 SiglaOrg                                VARCHAR2(10),
 TimeOut                                 NUMBER(5),
 StAttuale1                              VARCHAR2(12),
 StAtteso1                               VARCHAR2(12),
 StAttuale2                              VARCHAR2(12),
 StAtteso2                               VARCHAR2(12),
 StAttuale3                              VARCHAR2(12),
 StAtteso3                               VARCHAR2(12),
 StAttuale4                              VARCHAR2(12),
 StAtteso4                               VARCHAR2(12),
 ComProt                                 NUMBER(5),
 Note                                    VARCHAR2(32),
 InStampa                                NUMBER(5),
 Dainstallare                            NUMBER(5),
 SiglaSim                                VARCHAR2(16),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNDS table definition
rem

create table LEGOSVIL.TDPUNDS
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntds PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 TipoCalc                                NUMBER(5),
 SiglaDig1                               VARCHAR2(10),
 SiglaDig2                               VARCHAR2(10),
 SiglaDig3                               VARCHAR2(10),
 SiglaDig4                               VARCHAR2(10),
 Stato0                                  VARCHAR2(10),
 Stato1                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 TInib                                   NUMBER(5),
 Zonaimpianto                            NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNOR table definition
rem

create table LEGOSVIL.TDPUNOR
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntor PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Zonaimpianto                            NUMBER(5),
 Timeout                                 NUMBER(5),
 Tipo                                    VARCHAR2(12),
 SCont1                                  VARCHAR2(10),
 SCont2                                  VARCHAR2(10),
 SCont3                                  VARCHAR2(10),
 SCont4                                  VARCHAR2(10),
 SCont5                                  VARCHAR2(10),
 STProt                                  VARCHAR2(8),
 Inibente                                NUMBER(5),
 StatoI                                  VARCHAR2(12),
 TagPP1                                  VARCHAR2(10),
 TagPP2                                  VARCHAR2(10),
 Tinibiz                                 NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNST table definition
rem

create table LEGOSVIL.TDPUNST
	(
 Sigla   VARCHAR2(10) CONSTRAINT pk_puntst PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 Valore                                  VARCHAR2(15),
 Zonaimpianto                            NUMBER(5),
 Trattamento                             NUMBER(5),
 Severita                                NUMBER(5),
 Note                                    VARCHAR2(32),
 Dainstallare                            NUMBER(5),
 Gerarchia                               VARCHAR2(18)
	);

rem
rem TDPUNTO table definition
rem

create table LEGOSVIL.TDPUNTO
	(
 TipoO   				   VARCHAR2(12),
 codice NUMBER(5) CONSTRAINT pk_puntto PRIMARY KEY,
 Descrizione                             VARCHAR2(24),
 NumSegC                                 NUMBER(5),
 DescrSeg1                               VARCHAR2(24),
 DescrSeg2                               VARCHAR2(24),
 DescrSeg3                               VARCHAR2(24),
 Descrseg4                               VARCHAR2(24),
 DescrSeg5                               VARCHAR2(24),
 Stato1                                  VARCHAR2(12),
 Stato2                                  VARCHAR2(12),
 Stato3                                  VARCHAR2(12),
 Stato4                                  VARCHAR2(12),
 Stato5                                  VARCHAR2(12),
 Stato6                                  VARCHAR2(12),
 Stato7                                  VARCHAR2(12),
 Stato8                                  VARCHAR2(12),
 Stato9                                  VARCHAR2(12),
 Stato10                                 VARCHAR2(12),
 Stato11                                 VARCHAR2(12),
 Stato12                                 VARCHAR2(12),
 Stato13                                 VARCHAR2(12),
 Stato14                                 VARCHAR2(12),
 Stato15                                 VARCHAR2(12),
 Stato16                                 VARCHAR2(12),
 Stato17                                 VARCHAR2(12),
 Stato18                                 VARCHAR2(12),
 Stato19                                 VARCHAR2(12),
 Stato20                                 VARCHAR2(12),
 Stato21                                 VARCHAR2(12),
 Stato22                                 VARCHAR2(12),
 Stato23                                 VARCHAR2(12),
 Stato24                                 VARCHAR2(12),
 Stato25                                 VARCHAR2(12),
 Stato26                                 VARCHAR2(12),
 Stato27                                 VARCHAR2(12),
 Stato28                                 VARCHAR2(12),
 Stato29                                 VARCHAR2(12),
 Stato30                                 VARCHAR2(12),
 Stato31                                 VARCHAR2(12),
 Stato32                                 VARCHAR2(12)
	);
rem
rem ALLARDB table definition
rem

create table LEGOSVIL.ALLARDB
	(
 Indice  NUMBER(5) CONSTRAINT pk_allardb PRIMARY KEY,
 NumAll                                  NUMBER(10),
 zona0                                   NUMBER(5),
 zona1                                   NUMBER(5),
 zona2                                   NUMBER(5),
 zona3                                   NUMBER(5),
 zona4                                   NUMBER(5),
 zona5                                   NUMBER(5),
 zona6                                   NUMBER(5),
 zona7                                   NUMBER(5),
 zona8                                   NUMBER(5),
 zona9                                   NUMBER(5),
 zona10                                  NUMBER(5),
 zona11                                  NUMBER(5),
 zona12                                  NUMBER(5),
 zona13                                  NUMBER(5),
 zona14                                  NUMBER(5),
 zona15                                  NUMBER(5)
	);

rem
rem ALLARLINE table definition
rem

create table LEGOSVIL.ALLARLINE
	(
 Indice  NUMBER(5) CONSTRAINT pk_allarline PRIMARY KEY,
 Device                                    VARCHAR2(8),
 baud                                    VARCHAR2(16),
 data                                    VARCHAR2(1),
 stop                                    VARCHAR2(1),
 parita                                  VARCHAR2(1)
	);

rem
rem ALLARLIV table definition
rem

create table LEGOSVIL.ALLARLIV
	(
 Indice  NUMBER(5) CONSTRAINT pk_allarliv PRIMARY KEY,
 ColSev1                                 VARCHAR2(2),
 ColSev2                                 VARCHAR2(2),
 ColSev3                                 VARCHAR2(2),
 Emissione                               VARCHAR2(16),
 Rientro                                 VARCHAR2(16)
	);

rem
rem ALLARSERV table definition
rem

create table LEGOSVIL.ALLARSERV
	(
 TipoCicalino  NUMBER(5) CONSTRAINT pk_allarserv PRIMARY KEY,
 Sev1Cica                                NUMBER(5),
 Sev2Cica                                NUMBER(5),
 Sev3Cica                                NUMBER(5),
 FaMediaT                                NUMBER(5),
 FaFiltro                                NUMBER(5),
 FaScarto                                NUMBER(5),
 FaMediaI                                NUMBER(5),
 FaSomma                                 NUMBER(5),
 FaIntegrale                             NUMBER(5),
 freq_ut                                 NUMBER(5),
 REP_MESS                                NUMBER(5),
 REP_RETRY                               NUMBER(5)
	);

rem
rem ALLARSTRAT table definition
rem

create table LEGOSVIL.ALLARSTRAT
	(
 Indice  NUMBER(5) CONSTRAINT pk_allarstrat PRIMARY KEY,
 linea0                                  NUMBER(5),
 linea1                                  NUMBER(5),
 linea2                                  NUMBER(5),
 linea3                                  NUMBER(5),
 zona0                                   NUMBER(5),
 zona1                                   NUMBER(5),
 zona2                                   NUMBER(5),
 zona3                                   NUMBER(5),
 zona4                                   NUMBER(5),
 zona5                                   NUMBER(5),
 zona6                                   NUMBER(5),
 zona7                                   NUMBER(5),
 zona8                                   NUMBER(5),
 zona9                                   NUMBER(5),
 zona10                                  NUMBER(5),
 zona11                                  NUMBER(5),
 zona12                                  NUMBER(5),
 zona13                                  NUMBER(5),
 zona14                                  NUMBER(5),
 zona15                                  NUMBER(5)
	);

rem
rem CONFIGURAZIONEDB table definition
rem

create table LEGOSVIL.CONFIGURAZIONEDB
	(
 NomeImpianto  VARCHAR2(24) CONSTRAINT pk_configurazionedb PRIMARY KEY,
 Tipo                                    VARCHAR2(12),
 Descrizione                             VARCHAR2(50),
 subuten                                 VARCHAR2(10),
 DimAA                                   NUMBER(10),
 DimAS                                   NUMBER(10),
 DimAC                                   NUMBER(10),
 DimAD                                   NUMBER(10),
 DimAO                                   NUMBER(10),
 DimDA                                   NUMBER(10),
 DimDS                                   NUMBER(10),
 DimDC                                   NUMBER(10),
 DimDD                                   NUMBER(10),
 DimDO                                   NUMBER(10),
 Organi                                  NUMBER(10),
 Stringhe                                NUMBER(10)
	);

rem
rem MISTABK table definition
rem

create table LEGOSVIL.MISTABK
	(
 Indice  NUMBER(5) CONSTRAINT pk_mistabk PRIMARY KEY,
 Coeff                                   FLOAT(126)
	);

rem
rem CPERIF table definition
rem

create table LEGOSVIL.CPERIF
	(
 IndStar                                 NUMBER(5),
 NomeScheda                              VARCHAR2(10),
 Quantita                                NUMBER(5),
  CONSTRAINT pk_cperif PRIMARY KEY (IndStar,NomeScheda)
	);

rem
rem DESCRISCHEDA table definition
rem

create table LEGOSVIL.DESCRISCHEDA
	(
 NomeScheda   VARCHAR2(10) CONSTRAINT pk_descrischeda PRIMARY KEY,
 Codice                                  NUMBER(5),
 Descrizione                             VARCHAR2(30),
 NumeroAA                                NUMBER(5),
 NumeroAO                                NUMBER(5),
 NumeroDA                                NUMBER(5),
 NumeroDO                                NUMBER(5)
	);

rem
rem ELABORAZIONI table definition
rem

create table LEGOSVIL.ELABORAZIONI
	(
 Sigla                                   VARCHAR2(12),
 TipoElabo                               NUMBER(5),
 Elemento                                VARCHAR2(50),
 CONSTRAINT pk_elaborazioni PRIMARY KEY (Sigla,TipoElabo,Elemento)
	);

rem
rem ERRORIPUNTI table definition
rem

rem create table LEGOSVIL.ERRORIPUNTI
rem (
rem Sigla                                   VARCHAR2(12),
rem Tipo                                    VARCHAR2(2),
rem ErrCode                                 NUMBER(5),
rem ErrString                               VARCHAR2(255),
rem CONSTRAINT pk_errorirtf PRIMARY KEY (Sigla,Tipo,ErrCode)
rem );

rem
rem NOMI table definition
rem

create table LEGOSVIL.NOMI
	(
 Sigla  VARCHAR2(12) CONSTRAINT pk_nomi PRIMARY KEY,
 Tipo                                    VARCHAR2(2),
 PointDB                                 NUMBER(10),
 ExtDB                                   NUMBER(5)
	);

rem
rem TABPERI table definition
rem

create table LEGOSVIL.TABPERI
	(
 IndStar  NUMBER(5) CONSTRAINT pk_tabperi PRIMARY KEY,
 TipoP                                   VARCHAR2(10),
 Duale                                   NUMBER(5),
 Abilitato                               NUMBER(5)
	);

rem
rem TDIZST table definition
rem

create table LEGOSVIL.TDIZST
	(
 Stato                                   VARCHAR2(12),
 codice NUMBER(5) CONSTRAINT pk_tdizst PRIMARY KEY
	);

rem
rem TABULATI table definition
rem

create table LEGOSVIL.TABULATI
	(
 Nome  VARCHAR2(8) CONSTRAINT pk_tabulati PRIMARY KEY,
 Periodo                                 NUMBER(5),
 Periodico                               NUMBER(5),
 Cicli                                   NUMBER(5),
 Attesa                                  NUMBER(5),
 Tipo                                    NUMBER(5)
	);
