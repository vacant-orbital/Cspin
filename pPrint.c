/* potter 03Apr2023 */
/* Build and trigger a cmd prompt call to Notepad to print the results stored in output.txt */
/* As of 06Jul2023 this has not yet failed, but could be cleaned up */
/*--------------------------*/

#include <pPrint.h>

int pPrinter(const char* curdat){
	char notepadCall1[] = "NOTEPAD /P ";
	char notepadCall2[100];
	char tmpNotepadCall2[100];
	strcpy(tmpNotepadCall2, PROCPATH("output.txt"));
	int k = 0;
	int l = 0;
	while (tmpNotepadCall2[k] != '\0')
	{
		if (tmpNotepadCall2[k] == '/')
		{
			notepadCall2[l] = '\\';
			l++;
			k++;
		}
		else
		{
			notepadCall2[l] = tmpNotepadCall2[k];
			l++;
			k++;
		}
	}
	notepadCall2[l] = '\0';
	char notepadCall[400];
	int i = 0;
	int j = 0;
	while(notepadCall1[i] != '\0')
	{
		notepadCall[j] = notepadCall1[i];
		i++;
		j++;
	}
	i = 0;
	while (notepadCall2[i] != '\0')
	{
		notepadCall[j] = notepadCall2[i];
		i++;
		j++;
	}
	notepadCall[j] = '\0';
	system(notepadCall);  //to print the text file.  this works fine, but making a pdf now instead
	return 0;
}

