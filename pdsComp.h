#ifndef PDSCOMP_H
#define PDSCOMP_H

struct composition {
	double nPDS;
	double npdo;
	double PDS;
	double pdo;
	double total;
	double linewidth;
};

void printComp(FILE *of, struct composition cs);

#endif
