/*
 * SmartKey Driver
 * Copyright EUTRON 1993-2002
 */

#ifndef __SMARTKEY_H
#define __SMARTKEY_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/
/* Smartkey mode codes */

#define SCRAMBLING_MODE 's'
#define READING_MODE 'r'
#define WRITING_MODE 'w'
#define FIXING_MODE 'f'
#define LOCATING_MODE 'l'
#define COMPARING_MODE 'c'
#define PROGRAMMING_MODE 'p'
#define MODEL_READING_MODE 'm'
#define ENCRYPTING_MODE 'e'
#define SERIAL_NUMBER_READING_MODE 'n'
#define FIX_READING_MODE 'x'
#define EXT_MODEL_READING_MODE 'h'
#define FAIL_COUNTER_READING_MODE 'a'
#define BLOCK_READING_MODE ('b' | ((unsigned)'r' << 8))
#define BLOCK_WRITING_MODE ('b' | ((unsigned)'w' << 8))
#define AES_SET_MODE 'g'
#define AES_SCRAMBLE_MODE 'o'

/***************************************************************************/
/* Smartkey models */

#define SKEY_NONE '0' /* No Smartkey */
#define SKEY_FX '1' /* Smartkey mod. FX */
#define SKEY_PR '2' /* Smartkey mod. PR */
#define SKEY_EP '3' /* Smartkey mod. EP */
#define SKEY_SP '9' /* Smartkey mod. SP */
#define SKEY_NET 'A' /* Smartkey mod. NET */

/***************************************************************************/
/* Return codes */

#define ST_OK 0 /* No errors */
#define ST_NONE_KEY -1 /* No Smartkey present */
#define ST_SYNT_ERR -2 /* Syntax error */
#define ST_LABEL_FAILED -3 /* Uncorrect label */
#define ST_PW_DATA_FAILED -4 /* Uncorrect password or data */
#define ST_HW_FAILURE -20 /* Smartkey damaged */

/***************************************************************************/
/* Field length */

#define LABEL_LENGTH 16
#define PASSWORD_LENGTH 16
#define DATA_LENGTH 64
#define EXTENDED_DATA_LENGTH 352
#define SCRAMBLE_LENGTH 8

/***************************************************************************/
/* Communication structure definition */

typedef struct smartkey {
	short lpt;
	short command;
	unsigned char label[LABEL_LENGTH];
	unsigned char password[PASSWORD_LENGTH];
	unsigned char data[DATA_LENGTH];
	short fail_counter;
	short status;
	unsigned char ext_data[EXTENDED_DATA_LENGTH];
} SKEY_DATA;

/***************************************************************************/
/* Interface function prototype */

int clink(SKEY_DATA*);

#ifdef __cplusplus
}
#endif

#endif
