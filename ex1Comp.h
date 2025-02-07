#ifndef ex1COMP_H
#define ex1COMP_H

struct composition {
	double mfa;
	double aa;
	double mfawt;
	double aawt;
	double linewidth;
};

void printComp(FILE *of, struct composition cs);

#endif
