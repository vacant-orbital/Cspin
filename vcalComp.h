#ifndef VCALCOMP_H
#define VCALCOMP_H

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