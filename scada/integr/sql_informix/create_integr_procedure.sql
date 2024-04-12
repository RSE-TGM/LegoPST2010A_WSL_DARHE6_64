
--
-- modulo create_integr_procedure.sql
-- tipo 
-- release 1.2
-- data 6/3/96
-- reserved @(#)create_integr_procedure.sql	1.2
--

--------------------------------------
--  CREATE PROCEDURE check_historic
--------------------------------------
drop procedure check_historic;
create procedure check_historic (_hdr_code INT,_hdr_pos INT)

-- CODICE ARCHIVIO -1 NESSUN CONTROLLO
if(_hdr_code = -1) then
	return ;
end if


-- CONTROLLA CHE LA COPPIA ARCHIVIO POSIZIONE 
-- NON SIA GIA' USATA DA UN'ALTRA MISURA
if (select count(*) from tag where
	(HDR_CODE = _hdr_code) and (TAG_HDR_POS = _hdr_pos))>1 then
	raise exception -746, 0 , 'Couple HDR_CODE - TAG_HDR_POS duplicated' ;
end if

end procedure;


---------------------------------------------
--  CREATE PROCEDURE limit_historic_num
---------------------------------------------
drop procedure limit_historic_num;
create procedure limit_historic_num(_hdr_code INT)

-- CONTROLLA CHE GLI ARCHIVI SIANO
-- AL MASSIMO 8
if (_hdr_code<-1 or _hdr_code>8 or _hdr_code=0) then
	raise exception -746, 0 , 'HDR_CODE must be a number between 1 and 8';
end if
end procedure;


----------------------------------------
--  CREATE PROCEDURE limit_log_num
----------------------------------------
drop procedure limit_log_num;
create procedure limit_log_num(_hdr_code INT)

-- CONTROLLA CHE I TABULATI SIANO
-- AL MASSIMO 32
if (select count(*) from LOG )>32 then
	raise exception -746, 0 , 'Logs number exceeds 32' ;
end if
end procedure;


--------------------------------------------
--  CREATE PROCEDURE limit_scdconf_num
--------------------------------------------
drop procedure limit_scdconf_num;
create procedure limit_scdconf_num()

-- CONTROLLA CHE LA SCHEDA SCDCONF
-- ABBIA AL MASSIMO UN RECORD
if (select count(*) from SCDCONF )>1 then
	raise exception -746, 0 , 'SCDCONF can have just one record';
end if
end procedure;


-------------------------------------------
--  CREATE PROCEDURE limit_scddba_num
-------------------------------------------
drop procedure limit_scddba_num;
create procedure limit_scddba_num(_scddba_id INT)

-- CONTROLLA CHE LA SCHEDA SCDDBA
-- ABBIA AL MASSIMO 6 RECORD
if (_scddba_id>6 or _scddba_id<1) then
	raise exception -746, 0 , 'SCDDBA_ID must be a number between 1 and 6';
end if
end procedure;


-------------------------------------------
--  CREATE PROCEDURE limit_scdlbg_num
-------------------------------------------
drop procedure limit_scdlbg_num;
create procedure limit_scdlbg_num(_scdlbg_id INT)

-- CONTROLLA CHE LA SCHEDA SCDLBG
-- ABBIA AL MASSIMO 8 RECORD
if (_scdlbg_id>8 or _scdlbg_id<1) then
	raise exception -746, 0 , 'SCDLBG_ID must be a number between 1 and 8';
end if
end procedure;

-------------------------------------------
--  CREATE PROCEDURE limit_scdtab_num
-------------------------------------------
drop procedure limit_scdtab_num;
create procedure limit_scdtab_num(_scdtab_id INT)

-- CONTROLLA CHE LA SCHEDA SCDTAB
-- ABBIA AL MASSIMO 4 RECORD
if (_scdtab_id>4 or _scdtab_id<1) then
	raise exception -746, 0 , 'SCDTAB_ID must be a number between 1 and 4';
end if
end procedure;
