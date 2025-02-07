#include <pInteg.h>
#include <curprinStripper.c>


int calcIntegrals(pInts *pnt)
{
	FILE *intfile;
	int i = 0, j = 1, iii, ii;
	char dummystr[256];
	double d1;
	char prinStr[256];
	
	intfile=fopen(PROCPATH("intrng"), "w");
	char* curdat = pnt->curdat;
	char outd[1000];
	char crprn[1000];
	
	if(intfile==NULL)
	{
		Proc_err(DEF_ERR_OPT, "Can't write integrals:\n%s", PROCPATH("intrng"));
		return(-1);
	}
	fprintf(intfile, "A 1.0 #regions in PPM\n");
	fprintf(intfile, "# low field   high field  bias        slope\n");	
		
	for (i = 0; i < pnt->regionsArSize; i++)
	{
		fprintf(intfile, "%lf %lf  0  0\n", pnt->regionsAr[i][0], pnt->regionsAr[i][1]);
	}
	fclose(intfile);
	
	// read integral values //
	defineCurprin(pnt->outd, pnt->crprn);	
	FETCHPARS("CURPRIN", &prinStr);
	STOREPARS("INTSCL",1.0);
	Show_meta(SM_ALL);
	LI;
    
	intfile=fopen(PROCPATH("integrals.txt"), "r");
	if(intfile==NULL)
	{
		Proc_err(DEF_ERR_OPT, "No integral result file :\n%s", PROCPATH("integrals.txt"));
		return(-1);
	}
	//discard first 5 lines //
	for (iii = 0; iii < 5; iii++)
	{
		fgets(dummystr, sizeof(dummystr), intfile);
	}
	for (iii = 0; iii < pnt->intValuesSize; iii++)
	{
		(void) fgets(dummystr, sizeof(dummystr), intfile);
		(void) sscanf(dummystr,"%*d %*f %*f %lf",&pnt->intValues[iii]);
		if (pnt->intValues[iii] < 0){
			pnt->intValues[iii]=0;  //if integral is negative, set to zero 
		}
		if (pnt->intValues[iii] > 0){
			pnt->total += pnt->intValues[iii];
		}
	}	
	fclose(intfile);
	
	// normalize sum to 100 //
	FETCHPARS("INTSCL", &d1);
	STOREPARS("INTSCL", 100.0 * (d1 / pnt->total));
	Show_meta(SM_ALL);
	LI;
	//refresh display//
	XCMD("sendgui browse_update_tree");
	VIEWDATA_SAMEWIN;
	XCMD("sendgui spec");	
	for (ii = 0; ii < pnt->intValuesSize; ii++)
	{
		pnt->intValues[ii] = 100.0 * (d1 / pnt->total) * pnt->intValues[ii];
	}
	return 0;
}


void regionsInitAr(double** ir, int is, double* tr)
{ 
	int i, j;
	ir = (double**)malloc(is * sizeof(double *));
	for (i = 0; i < is; i++)
	{
		ir[i] = (double*)malloc(2 * sizeof(double));		
	}
	j = 0;
	for (i = 0; i < is; i++)  // append values passed as command line args 
	{
		//printf("loop number: %d\n", i);
		//printf("tr[%d]: %lf\n", j, tr[j]);
		ir[i][0] = tr[j];
		j = j + 1;
		//printf("tr[%d]: %lf\n", j, tr[j]);
		ir[i][1] = tr[j];
		j = j + 1;
	}
    return 0;	
}

void regionsInit(pInts *pnt, int is, double* tr)
{ 
	int i, j;
	pnt->regionsAr = (double**)malloc(is * sizeof(double *));
	for (i = 0; i < is; i++)
	{
		pnt->regionsAr[i] = (double*)malloc(2 * sizeof(double));		
	}
	j = 0;
	for (i = 0; i < is; i++)  // append values passed as command line args 
	{
		//printf("loop number: %d\n", i);
		//printf("tr[%d]: %lf\n", j, tr[j]);
		pnt->regionsAr[i][0] = tr[j];
		j = j + 1;
		//printf("tr[%d]: %lf\n", j, tr[j]);
		pnt->regionsAr[i][1] = tr[j];
		j = j + 1;
	}
    return 0;	
}

void getIntegrals(double *curInts)
{
	FILE *intfile;
	intfile=fopen(PROCPATH("intrng"), "r");
	char dummystr[256];
	int iii;
	int i = 0;
	int j = 1;
	//double r, t, y, u; 
	if(intfile==NULL)
	{
		Proc_err(DEF_ERR_OPT, "Can't write integrals:\n%s", PROCPATH("intrng"));
		return(-1);
	}
	for (iii = 0; iii < 2; iii++)
	{
		fgets(dummystr, sizeof(dummystr), intfile);
		printf("dummystr: %s", dummystr);
	}

	while (fgets(dummystr, sizeof(dummystr), intfile) != NULL)
	{
		(void) sscanf(dummystr,"%lf %lf %*lf %*lf %*s %*s %*s %*d", &curInts[i], &curInts[j]);
		i = i + 2;
		j = j + 2;
	}
	//printf("i: %d", i);
	//(*arrsize) = i;
	fclose(intfile);
}

void getIntegrals2D(double** curInts)
{
	FILE *intfile;
	intfile=fopen(PROCPATH("intrng"), "r");
	char dummystr[256];
	int iii;
	int i = 0;
	int j = 0;
	int k = 1;
	//double r, t, y, u; 
	if(intfile==NULL)
	{
		Proc_err(DEF_ERR_OPT, "Can't write integrals:\n%s", PROCPATH("intrng"));
		return(-1);
	}
	for (iii = 0; iii < 2; iii++)
	{
		fgets(dummystr, sizeof(dummystr), intfile);
		//printf("dummystr: %s", dummystr);
	}

	while (fgets(dummystr, sizeof(dummystr), intfile) != NULL)
	{
		(void) sscanf(dummystr,"%lf %lf %*lf %*lf %*s %*s %*s %*d", &curInts[i][0], &curInts[i][1]);
		i = i + 1;
	}
	//printf("i: %d", i);
	//(*arrsize) = i;
	fclose(intfile);
}

int getNumIntPoints(){
	/* 
	this counts the number of lines in the "intrng" file, subtracts two for the header lines, and multiplies the result
	by two for the start, stop entries.  The resulting count is returned as an int
	*/
	FILE *fp;
	fp = fopen(PROCPATH("intrng"), "r");
	char c;
	int cnt = 0;
	if(fp==NULL)
	{
		Proc_err(DEF_ERR_OPT, "Can't write integrals:\n%s", PROCPATH("intrng"));
		return(-1);
	}
	//for (c = getc(intfile); c!= EOF; c = getc(intfile))
	while((c = fgetc(fp)) != EOF)
	{
		//printf("c: %c\n", c);
		if (c == '\n')
		{
			cnt = cnt + 1;
		}
	}
	cnt = (cnt - 2) * 2;
	fclose(fp);
	return cnt;
}

int makeCuts(double ar[], int arSize){
	FILE *intfile;
	int i = 0, j = 1, iii, ii;
	char dummystr[256];
	double d1;
	char prinStr[256];
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

int makeCuts2D(double** ar, int arSize){
	FILE *intfile;
	int i = 0, j, iii, ii;
	char dummystr[256];
	double d1;
	char prinStr[256];
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
		fprintf(intfile, "%lf %lf  0  0\n", ar[i][0], ar[i][1]);
		i+=1;
	}
	fclose(intfile);
	return 0;
}

