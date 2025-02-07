#include <subregion.h>
#include <specInfo.c>

void insertatendofSR(SR **hd, int indx, double stpp, SRS asrs, struct specInfo s, long ar[]){
   //create a link
   SR *srlk = (struct subregion*) malloc(sizeof(SR));
    
   double subregioncenterppm=stpp-(asrs.subregionsize/2)-(indx*asrs.subregionsize);
   srlk->srleftppm = stpp-(indx*asrs.subregionsize);
   srlk->srrightppm = stpp-((indx + 1)*asrs.subregionsize);
   long centerpoint = s.si*(s.left-subregioncenterppm)/(s.sw_p/s.sf);
   long regionsum = 0;
   /* calculate average value for region and set this at center of region */
   int iii;
   for (iii=centerpoint-asrs.subregionsizept/2; iii<centerpoint+asrs.subregionsizept/2; iii++)
   {
      regionsum+=ar[iii];
   }
   srlk->center = centerpoint;
   srlk->average = regionsum/asrs.subregionsizept;
   srlk->next = NULL;
   
   if (*hd == NULL){
	   *hd = srlk;
   }
   else{
	   SR *tail = *hd;
	   // point it to old last node
	   while(tail->next != NULL){
		   tail = tail->next;
	   }
	   //point first to new first node
	   tail->next = srlk;
   }   

}

void printSRs(SR *hd){
	SR *temporary = hd;
	while (temporary->next != NULL){
		printf("(%d, %lf)", temporary->center, temporary->average);
		temporary = temporary->next;
	}
	printf("\n");
}

void fprintSRs(SR *hd, SPI s){
	FILE *srFile = fopen(PROCPATH("basline.txt"), "a+");
	SR *temporary = hd;
	fprintf(srFile, "\n\n");
	fprintf(srFile, "ppm ranges for the subregions\n");
	while (temporary != NULL){
		fprintf(srFile, "%lf, %lf\n", temporary->srleftppm, temporary->srrightppm);
		temporary = temporary->next;
	}
	fprintf(srFile, "\n\n");
	temporary = hd;
	fprintf(srFile, "center points and left/right boundaries, and averages for the subregions\n");
	while (temporary != NULL){
		fprintf(srFile, "%d, %d, %d, %d\n", temporary->center, indexOf(temporary->srleftppm, s), indexOf(temporary->srrightppm, s), temporary->average);
		temporary = temporary->next;
	}
	fclose(srFile);
}

int srCount(SR *hd){
	int count = 0;
	SR *temp = hd;
	while (temp != NULL){
		count += 1;
		temp = temp->next;
	}
	return count;
}

int indexOf(double peakShift, SPI spi)
{
	return spi.si*((spi.left - peakShift)/(spi.sw_p/spi.sf));
}
