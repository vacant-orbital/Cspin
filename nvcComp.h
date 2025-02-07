#ifndef NVCCOMP_H
#define NVCCOMP_H

struct composition {
	double pga;
	double gly;
	double pcl;
	double cap;
	double total;
	
	double _CGGC;
	double CGGC;
	double CGC;
	double PCL_ACSL;
	double ACggSL;
};

void printComp(FILE *of, struct composition cs);

#endif