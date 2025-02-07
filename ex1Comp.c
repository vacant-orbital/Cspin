#include <pdsComp.h>

void printComp(FILE *of, struct composition cs){
	fprintf(of,"\n\nMole Percent Composition");
	fprintf(of,"\n%s    %s", "3-methyl-furoic acid", "acetic acid");
	fprintf(of,"\n%5.2f    %5.2f", cs.mfa, cs.aa);
	fprintf(of,"\n\nWeight Percent Composition");
	fprintf(of,"\n%s    %s", "3-methyl-furoic acid", "acetic acid");
	fprintf(of,"\n%5.2f    %5.2f", cs.mfawt, cs.aawt);
	fprintf(of,"\n\nCalculated using AU program example1\n");
	fprintf(of,"\nD2O linewidth measured at %5.2f Hz", cs.linewidth);
	fclose(of);
}
