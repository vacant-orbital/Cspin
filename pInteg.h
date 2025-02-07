#ifndef PINTEG_H
#define PINTEG_H

typedef struct integralStruct{
	double *intValues;
	int intValuesSize;
	double **regionsAr;  //how to get size of this at runtime????--its the dblpointer for allrows
	int regionsArSize;  //just used as a loop counter to loop through each row, i think
	double total;
	char *curdat;
	char *outd;
	char *crprn;
} pInts;



int makeInteg(double ar[], int arSize, double iv[], int ivSize, double *total, char* curdat, char* anotherOut, char* anotherCurprin);
int makeCuts(double ar[], int arSize);
int makeCuts2D(double** ar, int arSize);
int calcIntegralsOld(pInts pnt);
int calcIntegrals(pInts *pnt);
void getIntegrals(double *curInts);
void getIntegrals2D(double** curInts);
int getNumIntPoints();
void regionsInitAr(double** ir, int is, double* tr);
void regionsInit(pInts *pnt, int is, double* tr);
#endif