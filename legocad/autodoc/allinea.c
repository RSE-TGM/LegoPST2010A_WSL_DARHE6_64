/**********************************************************************
*
*       C Source:               allinea.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:53:20 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: allinea.c,2 %  (%full_filespec: 1,csrc,allinea.c,2 %)";
#endif
allinea_file_info(lista_blocchi, num_blocchi, flag)
ModelBlockStruct *lista_blocchi;
int num_blocchi, flag;
{
   int i, nstr;
   char *nome_file, temp[256], buffer[128], str[64], nome_blocco[9];
   FILE *fp_app, *fp_info;
   char ok=0;

   strcpy(str, "*LG*DATI DEL BLOCCO");
   nstr = strlen(str);

   if (flag == DATI_GEOMETRICI)
      nome_file = FILE_INFO_DATI;
   else
      nome_file = FILE_INFO_VAR;

   tmpnam(temp);
   fp_app = fopen(temp, "w+");
   fp_info = fopen(nome_file, "r+");

   while (fgets(buffer, 128, fp_info) != NULL)
   {
       if (strncmp(buffer, str, nstr) == 0)
       {
          sscanf(buffer+nstr, "%s", nome_blocco);
          printf("nome blocco da esaminare: %s\n", nome_blocco);

          for (i=0, ok=0 ; i<num_blocchi ; i++)
              if (strcmp(nome_blocco, lista_blocchi[i].nome) == 0)
              {
                 ok = 1;
                 break;
              }
       }

       if (ok)
          fputs(buffer, fp_app);
   }

   fclose (fp_app);
   fclose (fp_info);
   copia_file(temp, nome_file);

#ifndef VMS
   unlink(temp);
#else
   remove(temp);
#endif
}

