/*
   modulo %M%
   tipo %Y%
   release %I%
   data %G%
   reserved %W%
*/

#define WARNNOTIFY        1
#define NOWARNNOTIFY      0
#define BUFFSZ 		256
#define LCASE(c) (isupper(c) ? tolower(c) : c)

#define DB_NAME		255
#define DB_USER_NAME	255
#define DB_USER_PWD	255

#define DB_COLUMN_SIZE	255
#define DB_TABLE_NAME	18
#define DB_COLUMN_NAME	18

#define OPERATION 	10
#define LOAD		0
#define DUMP		1

#define FIX_PAR_NUM	3

int getdesc_len(int fd);
int ParseCommandLine(char *db_msg,int argc,char **argv);
int GetTableName(char *table_name,int argc,char **argv);
int GetBlobColumn(char *blob_column,char **argv);

