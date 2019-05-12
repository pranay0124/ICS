#include <stdio.h>
#include <string.h>
#include <stdlib.h>
long exponent(int base, int expo) {
	long ans = 1;
	if (expo == 0)
	{
		return 1;
	}
	for(int i = 1; i<=expo; i++) {
		ans = ans * base;
	}
	return ans;
}
unsigned int convert(char * s) {
	unsigned int decimal = 0;
	unsigned int value = 0;
	int length = strlen(s);
	int power = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		if (s[i] == 'X' || s[i] == 'x' || s[i] == '0') 
		{
			continue;
		}
		else if (s[i] >= '1' && s[i] <= '9')
		{
			value = s[i] - 48;
		}
		else if (s[i] >= 'A' && s[i] <= 'F')
		{
			value = s[i] - 65 + 10;
		}
		else if (s[i] >= 'a' && s[i] <= 'f')
		{
			value = s[i] - 97 + 10;
		}

		decimal = decimal + (value * exponent(16,power));
		power++;
	}
	return decimal;
}

int main(int argc, char const *argv[])
{
	char s[100];
	printf("Enter the hexadecimal number\n");
	scanf("%s", s);
	printf("Integer value is: %d\n", convert(s));
	return 0;
}