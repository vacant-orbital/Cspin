#include <pdsformateComp.h>

void printComp(FILE *of, struct composition cs){
	fprintf(of,"\n\nMole Percent Composition");
	fprintf(of,"\n%s    %s", "PDS", "pdo");
	fprintf(of,"\n%5.2f    %5.2f", cs.PDS, cs.pdo);
	fprintf(of,"\n\nCalculated using AU program pds_formate\n");
	fprintf(of,"\nTMS linewidth measured at %5.2f Hz", cs.linewidth);
	fclose(of);
}