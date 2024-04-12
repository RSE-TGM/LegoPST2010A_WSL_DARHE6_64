/**********************************************************************
*
*       C Header:               pf_macro.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Fri Apr 12 16:17:11 1996 %
*
**********************************************************************/
#if defined UNIX
#define scrivi(punt,size,item,fp)   fwrite(punt,size,item,fp)
#define fluscia(fp)	fflush(fp)
#define sposta(fp,off)	fseek(fp, off, SEEK_SET)
#define sposta_rel(fp,off,rel)	fseek(fp, off, rel)
#else
#define scrivi(punt,size,item,fp) write(fp,punt,size*item)
#define fluscia(fp)	flush(fp)
#define sposta(fp,off)	lseek(fp, off, SEEK_SET)
#define sposta_rel(fp,off,rel)	lseek(fpda, off, rel)
#endif
