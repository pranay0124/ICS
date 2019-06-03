#include <stdio.h>
int main()

{
    char Arp[10][100];

    printf("%s\n", "\nEnter some lines of input\n");
    for (int i = 0; i < 10; i++)
    {
        scanf("%100s",Arp[i]);
    }
        
    printf("%s\n","\nEnter a number to print the last elements\n\n" );
    int ne;
    scanf("%d",&ne);

    for (int j = 10; j >= ne; j--)
    {
        
        printf("%s\n", Arp[j]);
    }
        return 0;
}