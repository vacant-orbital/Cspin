#ifndef SUBREGION_H
#define SUBREGION_H

#include <specInfo.c>

typedef struct subregion {
	float srleftppm;
	float srrightppm;
	long center;
	int regionsum;
	long average;
	struct subregion *next;
} SR;

typedef struct srStruct{
		int subregions;
		double subregionsize;
		int subregionsizept;
} SRS;


void insertatendofSR(SR **hd, int indx, double stpp, SRS asrs, struct specInfo s, long ar[]);
int srCount(SR *hd);
void printSRs(SR *hd);
void fprintSRs(SR *hd, SPI s);
int indexOf(double peakShift, SPI spi);

#endif