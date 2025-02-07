#ifndef BASELINEDEF_H
#define BASELINEDEF_H

typedef struct baselineDef{
	float startppm;
	float endppm;
	int startpoint;
	int endpoint;
	struct baselineDef *next;
} BL;

// insert func used to return null
void insertatendofBL(BL **hd, float stppm, float ndppm, int stpt, int ndpt);
void printBLs(BL *hd);
int blCount(BL *hd);
float baselineSW(BL *hd);
int calcSubregions(BL *bl, BL *hed);

#endif