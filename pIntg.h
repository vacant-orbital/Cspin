#ifndef PINTEG_H
#define PINTEG_H

typedef struct integrals{
	float startppm;
	float endppm;
	int startpoint;
	int endpoint;
	struct integrals *next;
} ITGS;

//int makeInteg(double ar[], int arSize, double iv[], int ivSize, double *total, char* curdat);
int getIntRegions(ITGS* anints);

#endif