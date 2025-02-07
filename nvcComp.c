#include <nvcComp.h>

void printComp(FILE *of, struct composition cs){
	fprintf(of,"\n\nMol Percent Composition");
	fprintf(of,"\n%s\t%s\t%s\t%s", "PGA", "gly", "PCL", "cap");
	fprintf(of,"\n%5.2f\t%5.2f\t%5.2f\t%5.2f", cs.pga, cs.gly, cs.pcl, cs.cap);
	
	fprintf(of, "\nSEQUENCE DISTRIBUTION: AS % OF G PRESENT (This section has not been validated)");
	fprintf(of,"\n%s\t%s\t%s\t%s\t%s", "CGC", "CGGC", ">CGGC", "PCL ACSL", "ACggSL");
	fprintf(of,"\n%5.2f\t%5.2f\t%5.2f\t%5.2f\t\t%5.2f", cs.CGC,  cs.CGGC, cs._CGGC, cs.PCL_ACSL, cs.ACggSL);
	fprintf(of,"\n\nCalculated using AU program nvc (last revision 24Oct2023)\n");
	fclose(of);
}

//rgp 23Oct2023