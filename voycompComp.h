#ifndef VOYCOMPCOMP_H
#define VOYCOMPCOMP_H

struct composition {
	double pga;
	double gly;
	double pla;
	double lac;
	double total;
	double linewidth;
};

void printComp(FILE *of, struct composition cs);

#endif