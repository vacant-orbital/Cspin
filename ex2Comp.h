#ifndef EX2COMP_H
#define EX2COMP_H

struct composition {
	double bpa;
	double ald;
	double bpawt;
	double aldwt;
	double linewidth;
};

void printComp(FILE *of, struct composition cs);

#endif
