#include <ex2Comp.h>

void printComp(FILE *of, struct composition cs){
	fprintf(of,"\n\nMole Percent Composition");
	fprintf(of,"\n%s    %s", "bisphenol a (bpa)", "3,5-ditertbutylsalicylaldehyde");
	fprintf(of,"\n%5.2f    %5.2f", cs.bpa, cs.ald);
	fprintf(of,"\n\nWeight Percent Composition");
	fprintf(of,"\n%s    %s", "bisphenol a (bpa)", "3,5-ditertbutylsalicylaldehyde");
	fprintf(of,"\n%5.2f    %5.2f", cs.bpawt, cs.aldwt);
	fprintf(of,"\n\nCalculated using AU program example2\n");
	fprintf(of,"\naldehyde linewidth measured at %5.2f Hz", cs.linewidth);
	fclose(of);
}
