-- =======================================================
--
-- modulo %M%
-- tipo %Y%
-- release %I%
-- data %G%
-- reserved %W%
--
--                        ******************
--                        DELETE_SCADA_TABLE 
--                        ******************
-- 
-- This procedure delete all the tables nedeed for SCADA 
-- 
-- First Creation 28 March 1996
-- Author M.De Chirico & E.Locatelli 
--
-- =========================================================

-- =========================================================
--
-- Eliminazione tabelle editing
--
-- =========================================================

--
-- EDITAA table delete
--

delete table ONLINE.EDITAA;

--
-- EDITAC table delete
--

delete table ONLINE.EDITAC;

--
-- EDITAD table delete
--

delete table ONLINE.EDITAD;

--
-- EDITAO table delete
--

delete table ONLINE.EDITAO;

--
-- EDITAS table delete
--

delete table ONLINE.EDITAS;

--
-- EDITARC table delete
--

delete table ONLINE.EDITARC;

--
-- EDITDA table delete
--

delete table ONLINE.EDITDA;

--
-- EDITDC table delete
--

delete table ONLINE.EDITDC;

--
-- EDITDD table delete
--

delete table ONLINE.EDITDD;

--
-- EDITDO table delete
--

delete table ONLINE.EDITDO;

--
-- EDITDS table delete
--

delete table ONLINE.EDITDS;

--
-- EDITOR table delete
--

delete table ONLINE.EDITOR;

--
-- EDITST table delete
--

delete table ONLINE.EDITST;

--
-- EDITTO table delete
--

delete table ONLINE.EDITTO;

--
-- ERRORIPUNTI table delete
--

delete table ONLINE.ERRORIPUNTI;

--
-- ERRORIRTF table delete
--

delete table ONLINE.ERRORIRTF;

-- =========================================================
--
-- Eliminazione tabelle operative
--
-- =========================================================

--
-- TDPUNAA table delete
--

delete table ONLINE.TDPUNAA;

--
-- TDPUNAC table delete
--

delete table ONLINE.TDPUNAC;

--
-- TDPUNAD table delete
--

delete table ONLINE.TDPUNAD;

--
-- TDPUNAO table delete
--

delete table ONLINE.TDPUNAO;

--
-- TDPUNAS table delete
--

delete table ONLINE.TDPUNAS;

--
-- TDPUNARC table delete
--

delete table ONLINE.TDPUNARC;

--
-- TDPUNDA table delete
--

delete table ONLINE.TDPUNDA;

--
-- TDPUNDC table delete
--

delete table ONLINE.TDPUNDC;

--
-- TDPUNDD table delete
--

delete table ONLINE.TDPUNDD;

--
-- TDPUNDO table delete
--

delete table ONLINE.TDPUNDO;

--
-- TDPUNDS table delete
--

delete table ONLINE.TDPUNDS;

--
-- TDPUNOR table delete
--

delete table ONLINE.TDPUNOR;

--
-- TDPUNST table delete
--

delete table ONLINE.TDPUNST;

--
-- TDPUNTO table delete
--

delete table ONLINE.TDPUNTO;

--
-- ALLARDB table delete
--

delete table ONLINE.ALLARDB;

--
-- ALLARLINE table delete
--

delete table ONLINE.ALLARLINE;

--
-- ALLARLIV table delete
--

delete table ONLINE.ALLARLIV;

--
-- ALLARSERV table delete
--

delete table ONLINE.ALLARSERV;

--
-- ALLARSTRAT table delete
--

delete table ONLINE.ALLARSTRAT;

--
-- CONFIGURAZIONEDB table delete
--

delete table ONLINE.CONFIGURAZIONEDB;

--
-- MISTABK table delete
--

delete table ONLINE.MISTABK;

--
-- CPERIF table delete
--

delete table ONLINE.CPERIF;

--
-- DESCRISCHEDA table delete
--

delete table ONLINE.DESCRISCHEDA;

--
-- ELABORAZIONI table delete
--

delete table ONLINE.ELABORAZIONI;


--
-- ERRORIRTF table delete
--

-- delete table ONLINE.ERRORIRTF;

--
-- NOMI table delete
--

delete table ONLINE.NOMI;
                                           
--
-- TABPERI table delete
--

delete table ONLINE.TABPERI;
                                           
--
-- TDIZST table delete
--

delete table ONLINE.TDIZST;
                                           
--
-- TABULATI table delete
--

delete ONLINE.TABULATI;
