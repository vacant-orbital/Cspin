#include <pOut.h>

int makeOut(void (*prComp)(FILE *anOF, struct composition acomp), struct composition acomp, const char* curdat){
	FILE *intfile, *outfile;
	int i, result, total;
	char dummystr[256];

	/* generate output file */
	outfile=fopen(PROCPATH("output.txt"), "w");
	if(outfile==NULL)
	{
		Proc_err(DEF_ERR_OPT, "Can't write output file:\n%s", PROCPATH("output.txt"));
		return(-1);
	}
	fprintf(outfile, "%s\n", "Comments:\n");
	/* copy lines from title file */
	intfile=fopen(PROCPATH("title"), "r");
	if (intfile != NULL)
	{
		while (fgets(dummystr, sizeof(dummystr), intfile))
		{
			fprintf(outfile,"%s", dummystr);
		}
		fclose(intfile);
	}
	fprintf(outfile,"\n\n");
	/* copy lines from integrals.txt file */
	intfile=fopen(PROCPATH("integrals.txt"), "r");
	/*discard first 4 lines */
	for (i = 0; i < 4; i++)
	{
		fgets(dummystr, sizeof(dummystr), intfile);
	}
	
	while (fgets(dummystr, sizeof(dummystr), intfile))
	{
		fprintf(outfile,"%s", dummystr);	
	}
	fclose(intfile);
	(*prComp)(outfile, acomp);
	return 0;
}
	