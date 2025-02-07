#include <voycompComp.h>

void printComp(FILE *of, struct composition cs){
	fprintf(of,"\n\nMole Percent Composition");
	fprintf(of,"\n%s    %s    %s    %s", "pga", "gly", "pla", "lac");
	fprintf(of,"\n%5.2f    %5.2f    %5.2f    %5.2f", cs.pga, cs.gly, cs.pla, cs.lac);
	fprintf(of,"\n\nCalculated using AU program voycomp\n");
	fprintf(of,"\nTMS linewidth measured at %5.2f Hz", cs.linewidth);
	fclose(of);
}