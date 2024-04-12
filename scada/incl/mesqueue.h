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
mesqueue.h

Defizione interfaccia per funzioni di scambio messaggi

*/

#define MSG_NOWAIT	0x0000		/* flag per evitare attesa per coda vuota/piena */
#define MSG_QCYCL		0x0002		/* flag coda ciclica */
#define MSG_CHDYN		0x0004		/* flag canale dinamico */
#define MSG_WAIT		0x0001		/* attesa */
#define MSG_SHRD		0x0010		/* coda  shared */

typedef struct send_packet
	{
	unsigned	short dch,		/* coda di destinazione messaggio */
				      flg,		/* send flag */
				      lmsg;		/* lunghezza messaggio */
	char 	         *amsg;	/* indirizzo messaggio */
	unsigned	short wto,		/* time-out per attesa per coda piena */
				      mbrem,	/* indice mail box per send remote */					
				      que;		/* indice coda di detinazione per canali dinamici */
	unsigned	short spare[24];
	} SEND_PACKET;

typedef struct rec_packet
	{
	unsigned	short que,		/* coda di ricezione messaggio */
				      flg,		/* receive flag */
				      lmsg;		/* lunghezza buffer di ricezione */
	char           *amsg;	/* indirizzo buffer */
	unsigned	short wto;		/* time-out per attesa per coda vuota */
	unsigned	short spare[26];
	} REC_PACKET;

typedef struct queue_packet
	{
	unsigned short que,		/* indice coda di ricezione messaggio */
				      flg,		/* receive flag */
				      lmsg;		/* lunghezza buffer di ricezione */
	char           *amsg;	/* indirizzo buffer */
	unsigned short wto;		/* time-out per attesa per coda vuota */
	} QUEUE_PACKET;
                  
typedef struct extsend_pk
	{
	unsigned	short dch,		/* canale logico di destinazione */
				      flg,		/* send flag */
				      lmsg;		/* lunghezza messaggio */
	char           *amsg;	/* indirizzo messaggio */
	unsigned	short wto,		/* time-out per attesa per coda piena */
				      mbrem,	/* indice mail box per send remote */					
				      que;		/* indice coda di detinazione per canali dinamici */
	unsigned	short spare[24];
	} EXTSEND_PK;

typedef struct extrec_pk
	{
	unsigned	short dch,		/* indice coda di ricezione messaggio */
				      flg,		/* receive flag */
				      lmsg;		/* lunghezza buffer di ricezione */
	char           *amsg;	/* indirizzo buffer */
	unsigned	short wto;		/* time-out per attesa per coda vuota */
	unsigned	short spare[26];
	} EXTREC_PK;

/* codici di errore */
#define	_MSG_BASE_ERR	50
#define	ERSV_QTO			_MSG_BASE_ERR  		/* time out generico */
#define	ERSV_QTO_CPU1	_MSG_BASE_ERR+1		/* time out fra CPU #1 */
#define	ERSV_QTO_CPU2	_MSG_BASE_ERR+2		/* time out fra CPU #2 */
#define	ERSV_QTO_CPU3	_MSG_BASE_ERR+3		/* time out fra CPU #3 */
#define	ERSV_QTO_CPU4	_MSG_BASE_ERR+3		/* time out fra CPU #4 */
#define	ERSV_QTO_CPU5	_MSG_BASE_ERR+5		/* time out fra CPU #5 */
#define	ERSV_QTO_CPU6	_MSG_BASE_ERR+6		/* time out fra CPU #6 */
#define	ERSV_QTO_CPU7	_MSG_BASE_ERR+7		/* time out fra CPU #7 */
#define	ERSV_QTO_CPU8	_MSG_BASE_ERR+8		/* time out fra CPU #8 */
#define	ERSV_SYSTO		_MSG_BASE_ERR+9		/* time out fra sistemi */
#define	ERSV_ENQUE		_MSG_BASE_ERR+10		/* errore in accodamento */
#define	ERSV_FQUE		_MSG_BASE_ERR+11		/* errore in accodamento, coda piena */
#define	ERSV_TOQUE		_MSG_BASE_ERR+12		/* errore in accodamento, time-out attesa */
#define	ERSV_EQUE		_MSG_BASE_ERR+13		/* errore in accodamento, coda vuota */
#define	ERSV_DEQUE		_MSG_BASE_ERR+14		/* errore in scodamento */
#define	ERSV_OUT			_MSG_BASE_ERR+15		/* errore su device in output messaggio */
#define	ERSV_IN			_MSG_BASE_ERR+16		/* errore su device in input messaggio */
#define	_MSG_END_ERR	_MSG_BASE_ERR+16

short  msend(SEND_PACKET *sep);
short  mrec(REC_PACKET *rep);
short  enqueue(QUEUE_PACKET *sep);
short  dequeue(QUEUE_PACKET *rep);


