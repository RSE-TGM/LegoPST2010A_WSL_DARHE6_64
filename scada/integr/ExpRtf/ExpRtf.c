/*
   modulo %M%
   tipo %Y%
   release %I%
   data %G%
   reserved %W%
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc,char *argv[])
{
	char command_line[1024];
	char source_path[FILENAME_MAX+1];
	char destination_path[FILENAME_MAX+1];
	int noinformix;

	if(argc<3)
	{
		fprintf(stderr,
			"Usage: %s  <source> <destination> [-noinformix]\n",
			argv[0]);
		exit(1);
	}
	
	strcpy(source_path,argv[1]);
	strcpy(destination_path,argv[2]);

	if(argc>3)
		noinformix=!strcmp(argv[3],"-noinformix");

	if(access(source_path,F_OK) || access(destination_path,F_OK))
	{
		perror("");
		exit(1);
	}

	/* Copy log source files */
	sprintf(command_line,"cp %s/*.tcr %s",
		source_path,destination_path);
        system(command_line);

#ifdef USE_INFORMIX 
	if(!noinformix)
	{
		if(!DbConnect("online","Online"))
			exit(1);

		if(!SQLCopyTableToTable("editaa","tdpunaa"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editac","tdpunac"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editas","tdpunas"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editad","tdpunad"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editao","tdpunao"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editda","tdpunda"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editdc","tdpundc"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editds","tdpunds"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editdd","tdpundd"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editdo","tdpundo"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editst","tdpunst"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editor","tdpunor"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editarc","tdpunarc"))
		{
			DbDisconnect();
			exit(1);
		}

		if(!SQLCopyTableToTable("editto","tdpunto"))
		{
			DbDisconnect();
			exit(1);
		}

		DbDisconnect();
	}
#endif
	sprintf(command_line,"cp %s/editConfDB.txt %s/ConfDB.txt",
		source_path,destination_path);
	system(command_line);

	sprintf(command_line,"cp %s/editAllarDB.txt %s/AllarDB.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editAllarLin.txt %s/AllarLin.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editAllarServ.txt %s/AllarServ.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editAllarLiv.txt %s/AllarLiv.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editAllarStr.txt %s/AllarStr.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editaa.txt %s/PuntAA.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editac.txt %s/PuntAC.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editad.txt %s/PuntAD.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editao.txt %s/PuntAO.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editas.txt %s/PuntAS.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editda.txt %s/PuntDA.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editdc.txt %s/PuntDC.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editdd.txt %s/PuntDD.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editdo.txt %s/PuntDO.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editds.txt %s/PuntDS.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editor.txt %s/PuntOR.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editst.txt %s/PuntST.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editarc.txt %s/PuntARC.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editto.txt %s/PuntTO.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editTabPeri.txt %s/TabPeri.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editCPerif.txt %s/CPerif.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editDescriSc.txt %s/DescriSc.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editMisTabK.txt %s/MisTabK.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editTDIZST.txt %s/TDIZST.txt",
		source_path,destination_path);
        system(command_line);

	sprintf(command_line,"cp %s/editlog.txt %s/Tabulati.txt",
		source_path,destination_path);
        system(command_line);

	exit(0);
}

