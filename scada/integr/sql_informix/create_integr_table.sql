
--
-- modulo create_integr_table.sql
-- tipo 
-- release 1.4
-- data 8/6/96
-- reserved @(#)create_integr_table.sql	1.4
--

--
--  create table ONLINE.ALARMTYPE
--
   
create table ONLINE.ALARMTYPE (
	ALTYPE_ID INTEGER CHECK (ALTYPE_ID>=0),
	ALTYPE_COLOR_SEV1 CHARACTER VARYING(2) check (
			ALTYPE_COLOR_SEV1 = 'BI' or ALTYPE_COLOR_SEV1 = 'GI' or
			ALTYPE_COLOR_SEV1 = 'MA' or ALTYPE_COLOR_SEV1 = 'NU' or
			ALTYPE_COLOR_SEV1 = 'RO' or ALTYPE_COLOR_SEV1 = 'VE'),
	ALTYPE_COLOR_SEV2 CHARACTER VARYING(2) check (
			ALTYPE_COLOR_SEV2 = 'BI' or ALTYPE_COLOR_SEV2 = 'GI' or
			ALTYPE_COLOR_SEV2 = 'MA' or ALTYPE_COLOR_SEV2 = 'NU' or
			ALTYPE_COLOR_SEV2 = 'RO' or ALTYPE_COLOR_SEV2 = 'VE'),
	ALTYPE_COLOR_SEV3 CHARACTER VARYING(2) check (
			ALTYPE_COLOR_SEV3 = 'BI' or ALTYPE_COLOR_SEV3 = 'GI' or
			ALTYPE_COLOR_SEV3 = 'MA' or ALTYPE_COLOR_SEV3 = 'NU' or
			ALTYPE_COLOR_SEV3 = 'RO' or ALTYPE_COLOR_SEV3 = 'VE'),
	ALTYPE_SIGNAL CHARACTER VARYING(1) NOT NULL,
	ALTYPE_NORM_STATE CHARACTER VARYING(8) NOT NULL
	);

alter table ONLINE.ALARMTYPE add constraint primary key (ALTYPE_ID) constraint PK_ALTYPE_ID;

--
--  create table ONLINE.HDR
--
   
create table ONLINE.HDR (
	HDR_CODE integer check(HDR_CODE >=-1 and HDR_CODE <=8 and HDR_CODE <>0),
	HDR_DESCR character varying(24),
	HDR_TYPE integer,
	HDR_PERIOD integer,
	HDR_LENGTH integer,
	HDR_NUM_FILE integer check(HDR_NUM_FILE>0 and HDR_NUM_FILE<33),
	HDR_PARTIAL integer,
	HDR_TRIGGER integer);

alter table ONLINE.HDR add constraint primary key (HDR_CODE) constraint PK_HDR_CODE;

create trigger trig_ins_hdr insert on ONLINE.HDR
        referencing NEW as new for each row (execute procedure
        limit_hdr_num(new.HDR_CODE));

create trigger trig_upd_hdr update on ONLINE.HDR
        referencing NEW as new for each row (execute procedure
        limit_hdr_num(new.HDR_CODE));

--
--  create table ONLINE.TAG
--
   
create table ONLINE.TAG (
	TAG_ID SERIAL,
	TAG_NAME CHARACTER VARYING(20) NOT NULL,
	TAG_DESCR CHARACTER VARYING(60) ,
	TAG_SCADA_USE INTEGER DEFAULT 0 CHECK (TAG_SCADA_USE = 0 or TAG_SCADA_USE = 1),
	HDR_CODE INTEGER default -1 check (HDR_CODE>=-1 and HDR_CODE<=8 and HDR_CODE<>0),
	TAG_HDR_POS INTEGER default -1,
	check (TAG_HDR_POS >=0 and TAG_HDR_POS <=82 or HDR_CODE=-1)
	);

alter table ONLINE.TAG add constraint primary key (TAG_ID) constraint PK_TAG_ID;

alter table ONLINE.TAG add constraint foreign key (HDR_CODE)
        references ONLINE.HDR(HDR_CODE) constraint FK_HDR_CODE;

alter table ONLINE.TAG add constraint unique  (TAG_ID) constraint UNQ_TAG_NAME;

create trigger trig_ins_tag insert on ONLINE.TAG
        referencing NEW as new for each row (execute procedure
        check_historic(new.HDR_CODE,new.TAG_HDR_POS));

create trigger trig_upd_tag update on ONLINE.TAG
        referencing NEW as new for each row (execute procedure
        check_historic(new.HDR_CODE,new.TAG_HDR_POS));

--
--  create table ONLINE.MEASURE
--

create table ONLINE.MEASURE (
	MEAS_ID serial,
	TAG_ID integer,
	MEAS_DESCR character varying(60),
	MEAS_ANDIG integer default 0 check (MEAS_ANDIG=0 or MEAS_ANDIG=1),
	MEAS_ZONE integer default 0 check (MEAS_ZONE>=0 and MEAS_ZONE<=15),
	MEAS_HH float default 0.0,
	MEAS_H float default 0.0,
	MEAS_L float default 0.0,
	MEAS_LL float default 0.0,
	MEAS_STATE_0 character varying(8),
	MEAS_STATE_1 character varying(8),
	MEAS_ALARM_STATE integer default 0 check (MEAS_ALARM_STATE=0 or MEAS_ALARM_STATE=1),
	MEAS_DEADZONE integer default 0 check (MEAS_DEADZONE>=0  and MEAS_DEADZONE<=1000),
	MEAS_TREATMENT integer default 0 check (MEAS_TREATMENT>=0  and MEAS_TREATMENT<=8),
	MEAS_SEVERITY integer default 0 check (MEAS_SEVERITY>=0  and MEAS_SEVERITY<=2),
	MEAS_HIER0 integer default -1 check (MEAS_HIER0>=-1  and MEAS_HIER0<=127),
	MEAS_HIER1 integer default -1 check (MEAS_HIER1>=-1  and MEAS_HIER1<=127),
	MEAS_HIER2 integer default -1 check (MEAS_HIER2>=-1  and MEAS_HIER2<=127),
	MEAS_HIER3 integer default -1 check (MEAS_HIER3>=-1  and MEAS_HIER3<=127),
	MEAS_HIER4 integer default -1 check (MEAS_HIER4>=-1  and MEAS_HIER4<=127),
	MEAS_HIER5 integer default -1 check (MEAS_HIER5>=-1  and MEAS_HIER5<=127)
);


alter table ONLINE.MEASURE add constraint primary key (MEAS_ID) constraint PK_MEAS_ID;
alter table ONLINE.MEASURE add constraint foreign key (TAG_ID) 
	references ONLINE.TAG(TAG_ID) constraint FK_TAGMEAS_ID;

--
--  create table ONLINE.ALARM
--

create table ONLINE.ALARM (
	AL_ID SERIAL,
	TAG_ID INTEGER,
	AREA_ID CHARACTER VARYING(2),
	ALTYPE_ID INTEGER,
	AL_DESIGNATION CHARACTER VARYING(40),
	AL_SIGN_DESCR CHARACTER VARYING(20),
	AL_STATE INTEGER DEFAULT 0 check (AL_STATE=0 or AL_STATE=1),
	AL_ZONE INTEGER DEFAULT 0 check (AL_ZONE>=0 and AL_ZONE<=15),
	AL_TREATMENT INTEGER DEFAULT 2 check (AL_TREATMENT>=0 and AL_TREATMENT<=8),
	AL_SEVERITY INTEGER DEFAULT 0 check (AL_SEVERITY>=0 and AL_SEVERITY<=8),
	AL_HIER0 INTEGER DEFAULT -1 check (AL_HIER0>=-1 and AL_HIER0<=127),
	AL_HIER1 INTEGER DEFAULT -1 check (AL_HIER1>=-1 and AL_HIER1<=127),
	AL_HIER2 INTEGER DEFAULT -1 check (AL_HIER2>=-1 and AL_HIER2<=127),
	AL_HIER3 INTEGER DEFAULT -1 check (AL_HIER3>=-1 and AL_HIER3<=127),
	AL_HIER4 INTEGER DEFAULT -1 check (AL_HIER4>=-1 and AL_HIER4<=127),
	AL_HIER5 INTEGER DEFAULT -1 check (AL_HIER5>=-1 and AL_HIER5<=127)
	);


alter table ONLINE.ALARM add constraint primary key (AL_ID) constraint PK_AL_ID;
alter table ONLINE.ALARM add constraint foreign key (TAG_ID)
	references ONLINE.TAG(TAG_ID) constraint FK_TAGAL_ID;
alter table ONLINE.ALARM add constraint foreign key (ALTYPE_ID)
	references ONLINE.ALARMTYPE(ALTYPE_ID) constraint FK_ALTYPE_ID;

--
--  create table ONLINE.LOG
--

create table ONLINE.LOG (
	LOG_NAME character varying(8),
	LOG_PERIODIC integer default 0 check (LOG_PERIODIC=0 or LOG_PERIODIC=1),
	LOG_PERIOD integer default 0 check (LOG_PERIOD>=0 and LOG_PERIOD<=10),
	LOG_CYCLES integer default 1 check (LOG_CYCLES>=1 and LOG_CYCLES<=10),
	LOG_WAIT integer default 1 check (LOG_WAIT>=1 and LOG_WAIT<=10),
	LOG_TYPE integer default 0 check (LOG_TYPE=0 or LOG_TYPE=1),
	LOG_PROGRAM text in blobspace1
);

alter table ONLINE.LOG add constraint primary key (LOG_NAME) constraint PK_LOG_NAME;

create trigger trig_ins_log insert on ONLINE.LOG
        referencing NEW as new for each row (execute procedure
        limit_log_num());

--
--  create table ONLINE.SCDCONF
--
   
create table ONLINE.SCDCONF (
	SCD_ID integer default 1 check (SCD_ID =1),
	SCD_PRN_0 CHARACTER VARYING(50) default '',
	SCD_PRN_1 CHARACTER VARYING(50) default '',
	SCD_PRN_2 CHARACTER VARYING(50) default '',
	SCD_PRN_3 CHARACTER VARYING(50) default '',
	SCD_PRN_4 CHARACTER VARYING(50) default '',
	SCD_PRN_5 CHARACTER VARYING(50) default '',
	SCD_PRN_6 CHARACTER VARYING(50) default '',
	SCD_PRN_7 CHARACTER VARYING(50) default '',
	SCD_SEVCIC1 INTEGER default 0  check(SCD_SEVCIC1=0 or SCD_SEVCIC1=1) ,
	SCD_SEVCIC2 INTEGER default 0  check(SCD_SEVCIC2=0 or SCD_SEVCIC2=1) ,
	SCD_SEVCIC3 INTEGER default 0  check(SCD_SEVCIC3=0 or SCD_SEVCIC3=1) ,
	SCD_TABDEF  INTEGER default 1  check(SCD_TABDEF>0 and SCD_TABDEF<5)
	);

alter table ONLINE.SCDCONF add constraint primary key (SCD_ID) constraint PK_SCD_ID;

create trigger trig_ins_scdconf insert on ONLINE.SCDCONF
        for each row (execute procedure
        limit_scdconf_num());

--
--  create table ONLINE.SCDDBA
--
   
create table ONLINE.SCDDBA (
	SCDDBA_ID integer check(SCDDBA_ID >0 and SCDDBA_ID <7),
	SCDDBA_NUMALL integer  default 0 check (SCDDBA_NUMALL>=0),
	SCDDBA_ZONE_0 integer  default 0 check (SCDDBA_ZONE_0=0 or SCDDBA_ZONE_0=1),
	SCDDBA_ZONE_1 integer  default 0 check (SCDDBA_ZONE_1=0 or SCDDBA_ZONE_1=1),
	SCDDBA_ZONE_2 integer  default 0 check (SCDDBA_ZONE_2=0 or SCDDBA_ZONE_2=1),
	SCDDBA_ZONE_3 integer  default 0 check (SCDDBA_ZONE_3=0 or SCDDBA_ZONE_3=1),
	SCDDBA_ZONE_4 integer  default 0 check (SCDDBA_ZONE_4=0 or SCDDBA_ZONE_4=1),
	SCDDBA_ZONE_5 integer  default 0 check (SCDDBA_ZONE_5=0 or SCDDBA_ZONE_5=1),
	SCDDBA_ZONE_6 integer  default 0 check (SCDDBA_ZONE_6=0 or SCDDBA_ZONE_6=1),
	SCDDBA_ZONE_7 integer  default 0 check (SCDDBA_ZONE_7=0 or SCDDBA_ZONE_7=1),
	SCDDBA_ZONE_8 integer  default 0 check (SCDDBA_ZONE_8=0 or SCDDBA_ZONE_8=1),
	SCDDBA_ZONE_9 integer  default 0 check (SCDDBA_ZONE_9=0 or SCDDBA_ZONE_9=1),
	SCDDBA_ZONE_10 integer  default 0 check (SCDDBA_ZONE_10=0 or SCDDBA_ZONE_10=1),
	SCDDBA_ZONE_11 integer  default 0 check (SCDDBA_ZONE_11=0 or SCDDBA_ZONE_11=1),
	SCDDBA_ZONE_12 integer  default 0 check (SCDDBA_ZONE_12=0 or SCDDBA_ZONE_12=1),
	SCDDBA_ZONE_13 integer  default 0 check (SCDDBA_ZONE_13=0 or SCDDBA_ZONE_13=1),
	SCDDBA_ZONE_14 integer  default 0 check (SCDDBA_ZONE_14=0 or SCDDBA_ZONE_14=1),
	SCDDBA_ZONE_15 integer  default 0 check (SCDDBA_ZONE_15=0 or SCDDBA_ZONE_15=1)
);

alter table ONLINE.SCDDBA add constraint primary key (SCDDBA_ID) constraint PK_SCDDBA_CODE;

create trigger trig_ins_scddba insert on ONLINE.SCDDBA
        referencing NEW as new for each row (execute procedure
        limit_scddba_num(new.SCDDBA_ID));

create trigger trig_upd_scddba update on ONLINE.SCDDBA
        referencing NEW as new for each row (execute procedure
        limit_scddba_num(new.SCDDBA_ID));

--
--  create table ONLINE.SCDLBG
--
   
create table ONLINE.SCDLBG (
	SCDLBG_ID integer check(SCDLBG_ID >0 and SCDLBG_ID <=8),
	SCDLBG_LINE_0 integer  default -1 check (SCDLBG_LINE_0>=-1 and SCDLBG_LINE_0<=8),
	SCDLBG_LINE_1 integer  default -1 check (SCDLBG_LINE_1>=-1 and SCDLBG_LINE_1<=8),
	SCDLBG_LINE_2 integer  default -1 check (SCDLBG_LINE_2>=-1 and SCDLBG_LINE_2<=8),
	SCDLBG_LINE_3 integer  default -1 check (SCDLBG_LINE_3>=-1 and SCDLBG_LINE_3<=8),
	SCDLBG_ZONE_0 integer  default 0 check (SCDLBG_ZONE_0=0 or SCDLBG_ZONE_0=1),
	SCDLBG_ZONE_1 integer  default 0 check (SCDLBG_ZONE_1=0 or SCDLBG_ZONE_1=1),
	SCDLBG_ZONE_2 integer  default 0 check (SCDLBG_ZONE_2=0 or SCDLBG_ZONE_2=1),
	SCDLBG_ZONE_3 integer  default 0 check (SCDLBG_ZONE_3=0 or SCDLBG_ZONE_3=1),
	SCDLBG_ZONE_4 integer  default 0 check (SCDLBG_ZONE_4=0 or SCDLBG_ZONE_4=1),
	SCDLBG_ZONE_5 integer  default 0 check (SCDLBG_ZONE_5=0 or SCDLBG_ZONE_5=1),
	SCDLBG_ZONE_6 integer  default 0 check (SCDLBG_ZONE_6=0 or SCDLBG_ZONE_6=1),
	SCDLBG_ZONE_7 integer  default 0 check (SCDLBG_ZONE_7=0 or SCDLBG_ZONE_7=1),
	SCDLBG_ZONE_8 integer  default 0 check (SCDLBG_ZONE_8=0 or SCDLBG_ZONE_8=1),
	SCDLBG_ZONE_9 integer  default 0 check (SCDLBG_ZONE_9=0 or SCDLBG_ZONE_9=1),
	SCDLBG_ZONE_10 integer  default 0 check (SCDLBG_ZONE_10=0 or SCDLBG_ZONE_10=1),
	SCDLBG_ZONE_11 integer  default 0 check (SCDLBG_ZONE_11=0 or SCDLBG_ZONE_11=1),
	SCDLBG_ZONE_12 integer  default 0 check (SCDLBG_ZONE_12=0 or SCDLBG_ZONE_12=1),
	SCDLBG_ZONE_13 integer  default 0 check (SCDLBG_ZONE_13=0 or SCDLBG_ZONE_13=1),
	SCDLBG_ZONE_14 integer  default 0 check (SCDLBG_ZONE_14=0 or SCDLBG_ZONE_14=1),
	SCDLBG_ZONE_15 integer  default 0 check (SCDLBG_ZONE_15=0 or SCDLBG_ZONE_15=1)
);

alter table ONLINE.SCDLBG add constraint primary key (SCDLBG_ID) constraint PK_SCDLBG_CODE;

create trigger trig_ins_scdlbg insert on ONLINE.SCDLBG
        referencing NEW as new for each row (execute procedure
        limit_scdlbg_num(new.SCDLBG_ID));

create trigger trig_upd_scdlbg update on ONLINE.SCDLBG
        referencing NEW as new for each row (execute procedure
        limit_scdlbg_num(new.SCDLBG_ID));

--
--  create table ONLINE.SCDTAB
--
   
create table ONLINE.SCDTAB (
	SCDTAB_ID INTEGER default 1 check (SCDTAB_ID >0 and SCDTAB_ID<=4),
	SCDTAB_LINE_0 INTEGER default -1 check (SCDTAB_LINE_0 >= -1 and SCDTAB_LINE_0<= 8),
	SCDTAB_LINE_1 INTEGER default -1 check (SCDTAB_LINE_1 >= -1 and SCDTAB_LINE_1<= 8),
	SCDTAB_LINE_2 INTEGER default -1 check (SCDTAB_LINE_2 >= -1 and SCDTAB_LINE_2<= 8),
	SCDTAB_LINE_3 INTEGER default -1 check (SCDTAB_LINE_3 >= -1 and SCDTAB_LINE_3<= 8)
	);

alter table ONLINE.SCDTAB add constraint primary key (SCDTAB_ID) constraint PK_SCDTAB_ID;

create trigger trig_ins_scdtab insert on ONLINE.SCDTAB
        referencing NEW as new for each row (execute procedure
        limit_scdlbg_num(new.SCDTAB_ID));

create trigger trig_upd_scdtab update on ONLINE.SCDTAB
        referencing NEW as new for each row (execute procedure
        limit_scdlbg_num(new.SCDTAB_ID));

--
--  create table ONLINE.POINTINSTERR
--
   
create table ONLINE.POINTINSTERR (
	ERR_ID serial,
	ERR_CODE INTEGER,
	ERR_TAG CHARACTER VARYING(20),
	ERR_DESCRIPTION CHARACTER VARYING(100)
	);

alter table ONLINE.POINTINSTERR add constraint primary key (ERR_ID) constraint PK_POINTINSTERR;
