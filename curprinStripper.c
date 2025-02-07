#include <curprinStripper.h>
#define BUFFER_SIZE 1000

void linuxToWindowsPath(char* pth)
{
	int index = 0;
	while(pth[index]){
		if(pth[index] == '/'){
			pth[index] = '\\';
			index++;
		}
		else
		{
			index++;
		}
	}
}

int defineCurprin(char* anOutd, char* aCurprin)
{
	FILE *rdFile;
    FILE *fTemp; 
	int letter;
	char newLine[BUFFER_SIZE]; 
	strcpy(newLine, "##$CURPRIN= \<");	
	strcat(newLine, aCurprin);
	strcat(newLine, "\>\n");	
    char buffer[BUFFER_SIZE];
	char shortBuff[BUFFER_SIZE];
    int line, lineNumber;
	int readLn = 0;	
	char pattern[] = "##$CURPRIN= <";
	rdFile = fopen(anOutd, "r");
	if(rdFile==NULL)
	{
		Proc_err(DEF_ERR_OPT, "No file present:\n%s", anOutd);
		return(-1);
	}
	while(fgets(buffer, sizeof(buffer), rdFile)) 
	{
		strncpy(shortBuff, buffer, 13);
		shortBuff[13]='\0';
		if (!(strcmp(shortBuff, pattern)))
		{
			lineNumber = readLn + 1;
		}
		readLn++;
	}
	fclose(rdFile);
    rdFile  = fopen(anOutd, "r");
    fTemp = fopen("replace.tmp", "w"); 
    if (rdFile == NULL || fTemp == NULL)
    {
        // Unable to open file hence exit //
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }

    int count = 0;
    while ((fgets(buffer, BUFFER_SIZE, rdFile)) != NULL)
    {
        count++;

        // If current line is line to replace //
        if (count == lineNumber)
            fputs(newLine, fTemp);
        else
            fputs(buffer, fTemp);
    }

    fclose(rdFile);
    fclose(fTemp);
    // Delete original source file //
    remove(anOutd);
    // Rename temporary file as original file //
    rename("replace.tmp", anOutd);
    return 0;
}