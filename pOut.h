#ifndef POUT_H
#define POUT_H
int makeOut(void (*prComp)(FILE *anof, struct composition acomp), struct composition acomp, const char* curdat);
#endif