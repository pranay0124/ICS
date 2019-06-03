#include <stdio.h>
#include <string.h>

void cpy(char* s, char* t, int n) {
	char string[1000];
	for (int i = 0; i < strlen(s); ++i)
	{
		string[i] = s[i];
	}
	for (int i = 0; i < strlen(string); ++i)
	{
		if (i != n)
		{
			string[i] = t[i];
		}

		if (n == i)
		{
			break;
		}
	}

	printf("copy = %s\n", string);
}

void cnt(char* s, char* t, int n)  {
	char string[1000];
	for (int i = 0; i < strlen(s); ++i)
	{
		string[i] = s[i];
	}

	int len = strlen(s);

	for (int i = 0; i < n; ++i)
	{
		string[len++] = t[i];
	}

	printf("append = %s\n", string);
}


void cmp(char* s, char* t, int n) {
	char string[1000];

	for (int i = 0; i < strlen(s); ++i)
	{
		string[i] = s[i];
	}

	int check = 0;

	for (int i = 0; i < n; ++i)
	{
		if (s[i] == t[i])
		{
			check++;
		}
	}

	if (check == 0)
	{
		printf("compare = 1\n");
	} else {
		printf("compare = 0\n");
	}
}


int main(int argc, char const *argv[])
{
	char str[1000],str1[1000];
	int n;
	printf("Enter two strings\n");
	scanf("%s", str);
	scanf("%s", str1);
	scanf("%d", &n);
	cpy(str,str1,n);
	cnt(str,str1,n);
	cmp(str,str1,n);
	return 0;
}