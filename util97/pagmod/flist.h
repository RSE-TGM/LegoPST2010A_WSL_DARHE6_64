#ifndef		PAGMOD_FLIST_H
#define         PAGMOD_FLIST_H


/*
 * Date:
 *
 * 1997-04-21
 */


struct FileList
{
  char * Path ;
  struct FileList * Next ;
} ;


extern	char *	ListFileName;
extern  struct FileList FileListHandle ;
extern  struct FileList * FLH , * FLT ;


extern int ReadListFile ( void ) ;
extern void AppendToFileList ( char * ) ;
extern void FreeFileList ( void ) ;


#endif        /*PAGMOD_FLIST_H*/
