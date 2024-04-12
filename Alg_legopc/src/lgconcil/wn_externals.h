#define MAXSENS 200 // Defines & variabili classless

typedef struct {
	int     control;
	float	tempo;
	float	chiprob;
	int		SensNum;
	int		AlarmNum;
	char	SenVarName[MAXSENS][8];
	char	SensDesc[MAXSENS][100];
	float	SensValue[MAXSENS];
	int		SensorsON[MAXSENS];
	int		AlarmInd[MAXSENS];
	float	AlarmVal[MAXSENS];
} MEMORIASHARED; // Shared struct

extern MEMORIASHARED  *pShrMem1;
extern float SensBand[];
extern float SensOffset[];
