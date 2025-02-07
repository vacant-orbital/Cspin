#include <pTools.h>

void pStrip(char *str, char c)
{
	int i, j;
	int len = strlen(str);
	for (i = j = 0; i < len; i++)
	{
		if (str[i] != c)
		{
			str[j++] = str[i];
		}
	}
	str[j] = '\0';
}