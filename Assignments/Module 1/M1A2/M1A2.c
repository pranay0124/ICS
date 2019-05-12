#include<stdio.h>
#include<string.h>

void reverse(char str[]);
char str[50];

void main(){
	gets(str);
	reverse(str);
	//puts(strrev);
}

void reverse(char str[]){
	char strrev[50];
	int i, j = 0;
	for(i = strlen(str) - 1; i >= 0; i--){
		strrev[j++] = str[i];
	}
	puts(strrev);
}