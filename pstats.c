#include <pstats.h>
//#include <pdsComp.h>
#include <specInfo.h>

double peakWidth(const char* curdat)
{
	float z[1000];
	int zsize; //unknown at compile time. set after filling
	int i, ii, iii, iiii;
	int regionsum;
	int subregions;
	float offset; //needed for datatype preservation when pulling from bruker parameter 
	double blSWppm=0;
	double regionsizeppm, subregioncenterppm;
	char dummystr[PATH_MAX];
	float intleft, intright;
	int num_regions=80;
	int leftpoint, rightpoint;
	int minsize;
	FILE *fptr;
	FILE *intfile;
	SPI spcInf;

	 
	int indexOf(double peakShift, SPI spi)
	{
		return spi.si*((spi.left - peakShift)/(spi.sw_p/spi.sf));
	}
	double toCS(int indx, SPI spi)
	{
		return spcInf.sw_p - (indx * (spcInf.sw_p/spi.si));
	}	

	if (access(PROCPATH("1r"),F_OK)!=0)
	{
		Proc_err(0,"no processed data.");
		return(-1);
	}
	int origprocno=procno;
	//save copy of initial spectrum in PROCNO 40 
	

	FETCHPARS("SI",&spcInf.si);
	minsize = spcInf.si/500;

	FETCHPARS("OFFSET",&spcInf.offset);
	FETCHPARS("SW_p",&spcInf.sw_p);
	FETCHPARS("SF",&spcInf.sf);
	spcInf.left = spcInf.offset;
	spcInf.right = spcInf.left - (spcInf.sw_p / spcInf.sf);
	// Divide the baseline into 80 roughly equal subregions and use extracted real data
	// save x, y (average), index information in a linked list of type SR
	regionsizeppm = blSWppm/num_regions;
	FILE *datafile;
	long  *pld; 
	long *ldata; // use this pointer to store reals
	int readin;
	int cant_modify_1r=0;
	if ( ( ldata = (long *)malloc(sizeof(long) * spcInf.si ) )==NULL )
	//if ( ( ldata = (long *)malloc(sizeof(long) * si ) )==NULL )
	{
		Proc_err(0,"Could not allocate memory for data?");
		cant_modify_1r=1;
	}
	
	if ( ( datafile = fopen(PROCPATH("1r"), "r+") ) == NULL)
	{
		Proc_err(INFO_OPT, "Could not open data file %s for read/write - ignored", PROCPATH("1r"));
		cant_modify_1r=1;
	}
	else if ( (readin = fread(ldata, sizeof(int), spcInf.si, datafile)) != spcInf.si)
	{
		Proc_err(INFO_OPT, "read only %d of %d points from %s - ignored", readin, spcInf.si, PROCPATH("1r"));
		fclose(datafile);
		cant_modify_1r=1;
	}

	long lowI = indexOf(0.1, spcInf);
	long highI = indexOf(-0.1, spcInf);
	long mx = 0;
	long mxi = 0;
	long delmx = 10000000;
	long lft = 0;
	long lfti = 0;
	long rt = 0;
	long rti = 0;
	i=0;	
	for (i = lowI; i < highI; i++)
	{
		//printf("i: %d  ldata[i]: %d\n", i, ldata[i]);
		if (ldata[i] > mx)
		{
			mx = ldata[i];
			mxi = i;
		}
	}
	//printf("10**2: %f\n", pow(10.0, 2.0));
	i=0;
	for (i = lowI; i < mxi; i++)
	{
		//printf("power term: %f\n", pow((ldata[i] - (mx/2.0)), 2.0));
		//if ((ldata[i] - (mx/2))**2 < delmx)
		if (pow(pow((ldata[i] - (mx/2.0)), 2.0), 0.5) < delmx)
		{
			lft = ldata[i];
			lfti = i;
			//printf("OK\n");
			delmx = pow(pow((ldata[i] - (mx/2.0)), 2.0), 0.5);
		}
	}
	delmx = 10000000;
	i=0;
	for (i = mxi; i < highI; i++)
	{
		//printf("i: %d  ldata[i]: %d\n", i, ldata[i]);
		//if ((ldata[i] - (mx/2))**2 < delmx)
		if (pow(pow(ldata[i] - (mx/2.0), 2.0), 0.5) < delmx)
		{
			rt = ldata[i];
			rti = i;
			//printf("KO");
			delmx = pow(pow((ldata[i] - (mx/2.0)), 2.0), 0.5);
		}
	}	
	//printf("mx: %d\n", mx);
	//printf("mxi: %d\n", mxi);
	//printf("lft: %d\n", lft);
	//printf("lfti: %d\n", lfti);
	//printf("rt: %d\n", rt);
	//printf("rti: %d\n", rti);
    fclose(datafile);
    //printf("pwhh: %f\n", toCS(lfti, spcInf) - toCS(rti, spcInf));
	//printf("tms peakwidth: %f\n", toCS(lfti, spcInf) - toCS(rti, spcInf));
	//cs->linewidth = toCS(lfti, spcInf) - toCS(rti, spcInf);
	return toCS(lfti, spcInf) - toCS(rti, spcInf);
	//return 0;
}

double solventWidth(double chemShift, const char* curdat)
{
	float z[1000];
	int zsize; //unknown at compile time. set after filling
	int i, ii, iii, iiii;
	float offset; //needed for datatype preservation when pulling from bruker parameter 
	char dummystr[PATH_MAX];
	float intleft, intright;
	int leftpoint, rightpoint;
	int minsize;
	FILE *fptr;
	FILE *intfile;
	SPI spcInf;

	 
	int indexOf(double peakShift, SPI spi)
	{
		return spi.si*((spi.left - peakShift)/(spi.sw_p/spi.sf));
	}
	
	
	
	double toHz(long indx, SPI spi, double lft)// should be named toHz()
	{
		return lft - (indx * (spi.sw_p/spi.si));
	}
	
	
	
	double toPPM(long indx, SPI spi)
	{
		return 	(spi.left - (indx * ((spi.left - spi.right)/spi.si)));
	}

	
	
	//double toCS(int indx, SPI spi)
	//{
	//	return spcInf.sw_p - (indx * (spcInf.sw_p/spi.si));
	//}	

	if (access(PROCPATH("1r"),F_OK)!=0)
	{
		Proc_err(0,"no processed data.");
		return(-1);
	}
	int origprocno=procno;
	

	FETCHPARS("SI",&spcInf.si);
	minsize = spcInf.si/500;
	FETCHPARS("OFFSET",&spcInf.offset);
	FETCHPARS("SW_p",&spcInf.sw_p);
	FETCHPARS("SF",&spcInf.sf);
	spcInf.left = spcInf.offset;
	spcInf.right = spcInf.left - (spcInf.sw_p / spcInf.sf);

	double lefthz = spcInf.left * spcInf.sf;
	double righthz = spcInf.right * spcInf.sf;	
	
	FILE *datafile;
	long  *pld; 
	long *ldata; // use this pointer to store reals
	int readin;
	int cant_modify_1r=0;
	if ( ( ldata = (long *)malloc(sizeof(long) * spcInf.si ) )==NULL )
	//if ( ( ldata = (long *)malloc(sizeof(long) * si ) )==NULL )
	{
		Proc_err(0,"Could not allocate memory for data?");
		cant_modify_1r=1;
	}
	
	if ( ( datafile = fopen(PROCPATH("1r"), "r+") ) == NULL)
	{
		Proc_err(INFO_OPT, "Could not open data file %s for read/write - ignored", PROCPATH("1r"));
		cant_modify_1r=1;
	}
	else if ( (readin = fread(ldata, sizeof(int), spcInf.si, datafile)) != spcInf.si)
	{
		Proc_err(INFO_OPT, "read only %d of %d points from %s - ignored", readin, spcInf.si, PROCPATH("1r"));
		fclose(datafile);
		cant_modify_1r=1;
	}

	long lowI = indexOf(chemShift + 0.1, spcInf);
	long highI = indexOf(chemShift - 0.1, spcInf);
	long mx = 0;
	long mxi = 0;
	long delmx = 1000000000; //just a big number to force first evaluation, can replace with do while
	long lft = 0;
	long lfti = 0;
	long rt = 0;
	long rti = 0;
	i=0;	
	for (i = lowI; i < highI; i++)
	{
		//printf("i: %d  ldata[i]: %d\n", i, ldata[i]);
		if (ldata[i] > mx)
		{
			mx = ldata[i];
			mxi = i;
		}
	}
	//printf("10**2: %f\n", pow(10.0, 2.0));
	i=0;
	for (i = lowI; i < mxi; i++)
	{
		if (abs(ldata[i] - (mx/2.0)) < delmx)
		{
			lft = ldata[i];
			lfti = i;
			//printf("OK\n");
			//delmx = (ldata[i] - (mx/2.0));
			//delmx = pow(pow((ldata[i] - (mx/2.0)), 2.0), 0.5);
			delmx = abs(ldata[i] - (mx/2.0));
			//printf("i: %d, ldata[1]: %d, halfMax: %d, delta: %d, chemical shift: %g\n", i, ldata[i], mx/2, delmx, toPPM(i, spcInf));
		}
	
		
		
	}
	delmx = 1000000000;  //just a big number to force first evaluation, can replace with do while
	i=0;
	for (i = mxi; i < highI; i++)
	{
		if (abs(ldata[i] - (mx/2.0)) < delmx)
		{
			rt = ldata[i];
			rti = i;
			//printf("KO");
			//delmx = pow(pow((ldata[i] - (mx/2.0)), 2.0), 0.5);
			//delmx = ldata[i] - (mx/2.0);
			delmx = abs(ldata[i] - (mx/2.0));
			//printf("i: %d, ldata[1]: %d, halfMax: %d, delta: %d, chemical shift: %g\n", i, ldata[i], mx/2, delmx, toPPM(i, spcInf));
		}

		
		
	}	
	//printf("chemShift: %lf\n", chemShift);
	//printf("second delmx: %ld\n", delmx);
	//printf("Here are the low: %ld, (%d) and high: %ld, (%d) indices for iteration\n", lowI, ldata[lowI], highI, ldata[highI]);
	//printf("Here are the low: %ld,  and high: %ld, Hz values for iteration\n", toHz(lowI, spcInf, lefthz),  toHz(highI, spcInf, lefthz));
	//printf("mx: %ld\n", mx);
	//printf("mxi: %ld\n", mxi);
	//printf("lft: %ld at %g ppm\n", lft, toPPM(lfti, spcInf));
	//printf("lfti: %ld at %g ppm\n", lfti, toPPM(lfti, spcInf));
	//printf("rt: %ld at %g ppm\n", rti, toPPM(rti, spcInf));
	//printf("rti: %ld at %g ppm\n", rti, toPPM(rti, spcInf));	
	
	
	
	
	//printf("mx: %d\n", mx);
	//printf("mxi: %d\n", mxi);
	//printf("lft: %d\n", lft);
	//printf("lfti: %d\n", lfti);
	//printf("rt: %d\n", rt);
	//printf("rti: %d\n", rti);
    fclose(datafile);
    //printf("pwhh: %f\n", toCS(lfti, spcInf) - toCS(rti, spcInf));
	//printf("tms peakwidth: %f\n", toCS(lfti, spcInf) - toCS(rti, spcInf));
	//cs->linewidth = toCS(lfti, spcInf) - toCS(rti, spcInf);
	return (toHz(lfti, spcInf, lefthz) - toHz(rti, spcInf, lefthz));
	//return 0;
}