#include<stdio.h>
#include<string.h>

main(){
	char str[50], out[50];
	gets(str);
	int i, j = 0;
	for(i=0; i<strlen(str); i++) {
		if(str[i] == ' ' && str[i+1] != ' '){
			out[j++] = str[i];
		} else if(str[i]!= ' '){
			out[j++] = str[i];
		}
	}
	puts(out);
}
