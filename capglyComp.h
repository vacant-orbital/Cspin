#ifndef CAPGLYCOMP_H
#define CAPGLYCOMP_H

struct composition {
	double cg1;
	double cg2;
	double cg3;
	double PGA;
	double GLY;
	double PCL;
	double CAP;
	double acsl;
	double ACggSL;
	double total;
	double linewidth;
};

void printComp(FILE *of, struct composition cs);

#endif