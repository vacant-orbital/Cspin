#include <pBC.h>
//"C:\\Bruker\\nmrsuite-client\\topspin\\exp\\stan\\nmr\\au\\src\\user\\pBC.h"
int makeBC(double ar[], int arSize){
	FILE *intfile;
	int i = 0, j = 1;
	intfile=fopen(PROCPATH("intrng"), "w");
	if(intfile==NULL)
	{
		Proc_err(DEF_ERR_OPT, "Can't write integrals:\n%s", PROCPATH("intrng"));
		return(-1);
	}
	fprintf(intfile, "A 1.0 #regions in PPM\n");
	fprintf(intfile, "# low field   high field  bias        slope\n");
	while (i < arSize - 1)
	{
		j = i + 1;
		fprintf(intfile, "%lf %lf  0  0\n", ar[i], ar[j]);
		i+=2;
	}
	fclose(intfile);
	return 0;
}