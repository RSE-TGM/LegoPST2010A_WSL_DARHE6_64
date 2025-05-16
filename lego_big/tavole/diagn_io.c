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

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>


int diagn_io_()
   {
     return( chdir( getenv("WORK_DIR") ) );
   }

