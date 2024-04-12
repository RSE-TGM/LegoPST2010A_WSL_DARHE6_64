/**********************************************************************
*
*       C Header:               UxSubproc.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:05:47 1996 %
*
**********************************************************************/
/* @(#)71	1.4  com/include/UxSubproc.h, aic, aic322, 9238322 4/27/92 19:11:36 */
/*
 *  COMPONENT_NAME: AIC     AIXwindows Interface Composer
 *  
 *  ORIGINS: 58
 *  
 *  Licensed Materials - Property of IBM
 *  5756-027 (C) Copyright International Business Machines Corp. 1991, 1992.
 *  All Rights Reserved.
 *  
 *  US Government Users Restricted Rights - Use, duplication or
 *  disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*/
/**********************************************************************/
/*
/* $Date: 91/05/31 14:10:34 $
/* $Revision: 1.3 $
/*
/**********************************************************************/
/***   stitute an acknowledgment that publication has  occurred	 nor  to   ***/
/***   imply  any  waiver  of confidentiality.	The year included in the   ***/
/***   notice is the year of the creation of the work.			   ***/
/***									   ***/
/*****************************************************************************/

#ifndef _UXSUBPROC_H
#define _UXSUBPROC_H

/****************************************************************************
DESCRIPTION:	
============

Include File:		"UxSubproc.h"
=============


Subprocess creation:
====================

Syntax: 	handle UxCreateSubproc(process, defarg, functionptr)

Arguments:	char *process - name of the command line based program
		char *defarg  - default arguments passed to the process
		void (*functionptr) - function to be executed on output
				      from the process

Return Type:	handle  - UIMX key to the subprocess


Description:	Creates a subprocess object and returns a key to it.
		The process is not executed by this function.

See also:	UxExecSubproc, UxRunSubproc, UxSetSubprocClosure, 
		UxSetSubprocFunction

-----

Syntax:		int UxSetSubprocEcho(subproc, echo)

Arguments:	handle		subproc - handle of the subprocess
		int		echo	- flag whether echo is on or off

Return Type:	-1 on error
		0 otherwise

Description:	Set whether command lines are echoed by the subprocess.
		The default for this is off (0). It would typically not
		be set unless the application being built with UIMX acts
		as a terminal emulator in ful duplex mode.
		This function must be called before the subprocess is
		executed with either UxExecSubproc or UxRunSubproc, for
		it to have any effect.

Subprocess execution:
=====================

Syntax: 	int UxRunSubproc(vh, arg)
		int UxExecSubproc(vh, arg)

Arguments:	handle vh    - key returned by UxCreateSubproc
		char *arg     - argument to the subprocess
				if arg is NULL, the default argument set
			    	by UxCreateSubproc is used.

Return Type:	-1 on error
		0 otherwise

Description: 	Both functions execute the child process created with 
		UxCreateSubproc, UxRunSubproc and UxExecSubproc. The
		functions differ only on repeated execution. UxRunSubproc
		returns an error if the subprocess is still running whereas
		UxExecSubproc terminates the running process and executes 
		it again.

See also:	UxCreateSubproc, UxSetSubprocClosure, UxSetSubprocFunction

 

Setting the Subprocess output function:
=======================================

Syntax: 	int UxSetSubprocFunction(vh, fnt)

Arguments:	handle vh    - key returned by UxCreateSubproc
		void (*fnt)() - function ptr that handles the output
				from the subprocess
Return Type:	-1 on error
		0 otherwise

Description: 	Overrides the function pointer passed to UxCreateSubproc.
		This function allows the user to change the output
		handling of the subprocess during execution of the program.
		
See also:	UxCreateSubproc, UxSetSubprocClosure and output function format.


Setting the Subprocess output function:
=======================================

Syntax: 	int UxSetSubprocClosure(vh, data)

Arguments:	handle vh    - key returned by UxCreateSubproc
		char *data    - Data passed to the output function.

Return Type:	-1 on error
		0 otherwise

Description: 	Sets the data passed to the output function of the subprocess.
		
See also:	UxCreateSubproc, UxSetSubprocFunction and output function 
		format.


Sending commands to the Subprocess:
===================================

Syntax: 	int UxSendSubproc(vh, command)

Arguments:	handle vh    - key returned by UxCreateSubproc
		char *command - String send to the subprocess

Return Type:	-1 on error
		0 otherwise

Description: 	Sends the command string to the subprocess. A carriage
		return is automatically appended to the command string.
		

-----

Syntax: 	int UxSendSubprocNoCR(vh, command)

Arguments:	handle vh    - key returned by UxCreateSubproc
		char *command - String send to the subprocess

Return Type:	-1 on error
		0 otherwise

Description: 	Sends the command string to the subprocess. No carriage
		return is appended to the command string.
		

Terminating a running Subprocess:
=================================

Syntax: 	int UxExitSubproc(vh)

Arguments:	handle vh    - key returned by UxCreateSubproc

Return Type:	-1 on error
		0 otherwise

Description: 	Terminates a running subprocess
		
See also:	UxCreateSubproc, UxExecSubproc and UxRunSubproc


Getting the process id of a Subprocess:
=======================================

Syntax: 	int UxGetSubprocPid(vh)

Arguments:	handle vh    - key returned by UxCreateSubproc

Return Type:	Process id of the running process
		0 otherwise

Description: 	Checks if a process is still running and returns the 
		process id of it. If the process was improperly 
		terminated, it performs error checking and closes
		open file descriptors associated with the running 
		process.
		
See also:	UxExitSubproc


Destroying a Subprocess:
========================

Syntax:		int UxDeleteSubproc (vh)


Arguments:	handle vh    - key returned by UxCreateSubproc

Return type:	ERROR/NO_ERROR


Description:	Destroys the subprocess information,
		after calling UxExitSuproc to terminate the process.
		After a call to this function, the handle vh
		no longer identifies a valid subprocess.

See also:	UxCreateSubproc, UxExitSubproc.


Format of the Subprocess output function:
=========================================

Syntax: 	void USER_FUNCTION(fd, data)

Arguments:	int fd 		- file descriptor with output from the 
			  	  subprocess
		char *data	- data set with UxSetSubprocClosure

Description: 	When data is returned from the subprocess, the 
		function set with UxSetSubprocFunction is executed.
		
		
See also:	UxSetSubprocFunction and UxSetSubprocClosure


User utility functions:
=======================

Syntax: 	void UxAppendTo(fd, wid)

Arguments:	int fd 		- file descriptor with output from the 
			  	  subprocess
		Widget wid	- data set with UxSetSubprocClosure

Description: 	When data is returned from the subprocess with the 
		UxAppendTo as output function, it attempts to append
		data to the text widget passed in as data. If wid is
		NULL, the output is printed to stdout.
		
		
See also:	UxCreateSubproc, UxSetSubprocFunction and UxSetSubprocClosure




Syntax: 	char *UxTransferToBuffer(fd, status)

Arguments:	int fd 		- file descriptor with output from the 
			  	  subprocess
		int *status	- Filled in by UxTransferToBuffer.
				  0  if there is no more output data
				  1  if more output data is present

Return Type:	char *		- Null terminated ouput text string.
				  The buffer containing the text string
				  is a static text buffer of 512 bytes.

Description: 	Utility function to read blocks of data from the file
		descriptor into a NULL terminated text buffer. 
		
		
See also:	UxCreateSubproc, UxSetSubprocFunction and UxSetSubprocClosure


	
CREATION:       Jul 20 1988  Visual Edge Software
---------------------------------------------------------------------------*/

typedef int  handle;

extern handle	UxCreateSubproc();
extern int	UxExecSubproc(), UxRunSubproc(), UxGetSubprocPid(),
		UxSendSubproc(), UxSendSubprocNoCR(), UxSetSubprocEcho(),
		UxExitSubproc(), UxSetSubprocClosure(), UxSetSubprocFunction(),
		UxDeleteSubproc(), UxSetSubprocExitCallback();
extern char	*UxTransferToBuffer();
extern void	UxAppendTo();

#ifndef ERROR
#define ERROR -1
#endif
#ifndef NO_ERROR
#define NO_ERROR 0
#endif


#endif

