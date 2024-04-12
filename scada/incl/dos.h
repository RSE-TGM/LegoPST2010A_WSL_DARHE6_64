/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
	-> dos.h

	File di include: contiene le definizioni di alcune strutture e
	funzioni del DOS.
*/
struct dosdate_t{
	unsigned char day;
	unsigned char month;
	unsigned char year;
	unsigned char dayofweek;
	};

struct dostime_t{
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char hsecond;
	};

struct find_t{
	char reserved[21];
	char attrib;
	unsigned short wr_time;
	unsigned short wr_date;
	unsigned long size;
	char name[256];
	};

#define O_BINARY 0x0000

#define _A_NORMAL 0x00

unsigned _dos_findfirst(const char *filename,unsigned attrib,struct find_t *fileinfo);
unsigned _dos_findnext(struct find_t *fileinfo);
