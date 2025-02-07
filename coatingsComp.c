#include <coatingsComp.h>

void printComp(FILE *of, struct composition cs){
	fprintf(of,"\n\nWeight Percent Composition");
	fprintf(of,"\n%s\t%s\t%s", "NVC", "PG370", "Stearate");
	fprintf(of,"\n%5.2f\t%5.2f\t%5.2f", cs.wtPCTnvc, cs.wtPCTpg370, cs.wtPCTstr);
	fprintf(of,"\n\nCalculated using AU program nvcPG370 (last revision 23Oct2023)\n");
	fclose(of);
}

//rgp 23Oct2023