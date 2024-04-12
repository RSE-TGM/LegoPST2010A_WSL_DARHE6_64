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
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	programma test Crc Sepa

	1.	1,2,3,4	-> 4001
	2. da 1 a 10 -> 50731
	3.	100, 110... 190 -> 49824
	4. 0-255				-> 40750
*/
#define WORD unsigned short
#define BYTE unsigned char

tcrc1[16]={	0x0000, 	0xC0C1, 	0xC181, 	0x0140,
				0xC301,	0x03C0,	0x0280,	0xC241,
				0xC601,	0x06C0,	0x0780,	0xC741,
				0x0500,	0xC5C1,	0xC481,	0x0440};

tcrc2[16]={	0x0000, 	0xCC01, 	0xD801, 	0x1400,
				0xF001,	0x3C00,	0x2800,	0xE401,
				0xA001,	0x6C00,	0x7800,	0xB401,
				0x5000,	0x9C01,	0x8801,	0x4400};

WORD calc_crc16 (BYTE *, WORD );
main()
{
	char buffer1[5]={1,2,3,4};
	char buffer2[11]={1,2,3,4,5,6,7,8,9,10};
	char buffer3[11]={100,110,120,130,140,150,160,170,180,190};
	char buffer4[257];
	short i;

	for(i=0;i<257;i++) buffer4[i]=i;

	printf("\n 4001 %u ",crc16(buffer1,4));
	printf("\n 50731 %u ",crc16(buffer2,10));
	printf("\n 49824 %u ",crc16(buffer3,10));
	printf("\n 40750 %u ",crc16(buffer4,256));
	buffer4[0]=0x61;
	buffer4[1]=0x0;
	printf("\n %x",crc16(buffer4,2));
}

WORD calc_crc16 (BYTE *pt_ini, WORD num_byte)
{
	BYTE *ptin;
	WORD acc, i1, i2, x, y;

	acc=0;
	for(ptin=pt_ini; ptin<(pt_ini+num_byte);ptin++)
		{
			i1=((acc & 0xFF) ^ *ptin) & 0xF;
			i2=(((acc & 0xFF) ^ *ptin) & 0xF0) >> 4;

			x=(tcrc2[i2] & 0xFF) ^ (tcrc1[i1] & 0xFF);
			y=(tcrc2[i2] & 0xFF00) ^ (tcrc1[i1] & 0xFF00);

			acc=((acc>>8) ^ x)  | y;

		}
	return(acc);
}
