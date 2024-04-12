--
-- modulo delete_integr_table.sql
-- tipo 
-- release 1.2
-- data 6/14/96
-- reserved @(#)delete_integr_table.sql	1.2
--

--
-- Delete all rows from SCADA integration tables
--

delete from ONLINE.ALARM;
delete from ONLINE.MEASURE;
delete from ONLINE.TAG;
delete from ONLINE.HDR;
delete from ONLINE.LOG;
delete from ONLINE.ALARMTYPE;
delete from ONLINE.SCDCONF;
delete from ONLINE.SCDDBA;
delete from ONLINE.SCDLBG;
delete from ONLINE.SCDTAB;
delete from ONLINE.POINTINSTERR;
