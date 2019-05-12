#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int strrindex(char *s, char t) {
    int i;
    int count = -1;
    for(i=0; i<strlen(s); i++) {
        if(s[i] == t) {
            count = i;
        }
    }
    return count;
}

main() {
    char s[100];
    char t;
    printf("Enter the string : ");
    // scanf("%s", s);
    gets(s);
    printf("Enter the character : ");
    scanf("%c", &t);
    printf("%d\n", strrindex(s, t));
}