#ifndef COATINGSCOMP_H
#define COATINGSCOMP_H

struct composition {
	double pg370;
	double nvc;
	double str;
	double wtPCTpg370;
	double wtPCTnvc;
	double wtPCTstr;
	double tot;
	double wtTot;
};

void printComp(FILE *of, struct composition cs);

#endif