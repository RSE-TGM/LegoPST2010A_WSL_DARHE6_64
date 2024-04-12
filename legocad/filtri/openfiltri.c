/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif

int openedf()
{
   strcpy(filedf,UxGetTextString(fileSelectionBox1));
 
    if(fpedf != NULL)
      closedf();

   if( ( fpedf=fopen(filedf,"r+") ) == NULL)
   {
      printf("\n Apro file nuovo\n");
      if( ( fpedf=fopen(filedf,"w") ) == NULL)
         return(ERROPEN);
   }
   return(OK);
}
