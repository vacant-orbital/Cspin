#include <capglyComp.h>

void printComp(FILE *of, struct composition cs){
	fprintf(of,"\n\nMole Percent Composition");
	fprintf(of,"\n%s\t%s\t%s\t%s", "PGA", "GLY", "PCL", "CAP");
	fprintf(of,"\n%5.2f\t%5.2f\t%5.2f\t%5.2f", cs.PGA, cs.GLY, cs.PCL, cs.CAP);
	fprintf(of,"\nSequence Distribution: as %% of G Present (This section is not validated)");
	fprintf(of,"\n%s\t%s\t%s", "CGC", "CGGC", ">CGGC");
	fprintf(of,"\n%5.2f\t%5.2f\t%5.2f", cs.cg3, cs.cg2, cs.cg1);
	fprintf(of,"\n%s\t%5.3f%s", "PCL ACSL", cs.acsl, " (This section is not validated)");
	fprintf(of,"\n%s\t%5.3f%s", "PGA ACggSL", cs.ACggSL, " (This section is not validated)");
	fprintf(of,"\n\nCalculated using AU program capgly_linspl (last revision 12Sep2023)\n");
	fprintf(of,"\nTMS linewidth measured at %5.2f Hz", cs.linewidth);
	fclose(of);
}

//rgp 12Sep2023
//rgp added tms linewidth