#include <baselineDef.h>

void insertatendofBL(BL **hd, float stppm, float ndppm, int stpt, int ndpt){

   //create a link
   BL *bllk = (struct baselineDef*)malloc(sizeof(BL));
   bllk->startppm = stppm;
   bllk->endppm = ndppm;
   bllk->startpoint = stpt;
   bllk->endpoint = ndpt;
   bllk->next = NULL;
   
   if (*hd == NULL){
	   *hd = bllk;
   }
   else{
	   BL *tail = *hd;
	   // point it to old last node
	   while(tail->next != NULL){
		   tail = tail->next;
	   }
	   //point first to new first node
	   tail->next = bllk;
   }
}
void printBLs(BL *hd){
	BL *temporary = hd;
	while (temporary->next != NULL){
		printf("(%d, %d)", temporary->startpoint, temporary->endpoint);
		temporary = temporary->next;
	}
	printf("\n");
}
void fprintBLs(BL *hd){
	FILE *blFile = fopen(PROCPATH("basline.txt"), "w");
	BL *temporary = hd;
	while (temporary != NULL){
		fprintf(blFile, "(%d, %d)", temporary->startpoint, temporary->endpoint);
		temporary = temporary->next;
		
	}
	fprintf(blFile, "\n");
	temporary = hd;
	while (temporary != NULL){
		fprintf(blFile, "(%lf, %lf)", temporary->startppm, temporary->endppm);
		temporary = temporary->next;		
	}
	fprintf(blFile, "\n");
	fclose(blFile);
}
float baselineSW(BL *hd){
	float tot = 0.0;
	BL *temp = hd;
	while (temp != NULL){
		tot += temp->startppm - temp->endppm;
		temp = temp->next;
	}
	return tot;
}
	
int blCount(BL *hd){
	int count = 0;
	BL *temp = hd;
	while (temp->next != NULL){
		count += 1;
		temp = temp->next;
	}
	return count;
}
int calcSubregions(BL *bl, BL *hed){
	int srs = (bl->startppm - bl->endppm)/baselineSW(hed);
	if (srs ==0)
		srs=1;
	return srs;
}
//void calcIndices(){
	