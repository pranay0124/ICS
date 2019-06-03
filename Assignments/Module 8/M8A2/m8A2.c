#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct dict{
   char word[20];
   int freq;
};

int main()
{
   char ch, data_file[25] = "data.txt";
   struct dict d[500];
   int exits = 0;
   FILE *fp_data;

   fp_data = fopen(data_file, "r"); // reading input data

   if (fp_data == NULL)
   {
      perror("Error while opening the files.\n");
      exit(EXIT_FAILURE);
   }


   // An array of input data words-------------
   char datawords[1000][20];

   int idata = 0, idictinsert = 0;

   //Reading each word from input file
   while((fscanf(fp_data, "%s", datawords[idata])) != EOF) {
      // d[idata].word = datawords[idata];
      int idict = 0;

      //iterating over the dict structure to add frequency, if exists----------------------
      while(idict < idictinsert) {
         // printf("%s  -  %s\n", d[idict].word, datawords[idata] );
         if (strcmp(d[idict].word,datawords[idata]) == 0)
         {
            exits = 1;
            ++d[idict].freq;
            break;
         }
         ++idict;
      }

      //if not in the dict struct, adding it now with freq 1
      if(exits == 0){
         strcpy(d[idictinsert].word, datawords[idata]);
         d[idictinsert].freq = 1;
         ++idictinsert;
      }
   	++idata;
      exits = 0;
   }

   //sorting now
   for(int isortouter = 1; isortouter < idictinsert; isortouter++){
      for(int isort = 0; isort < idictinsert - isortouter; isort++) {

         struct dict temp;
         if(d[isort].freq < d[isort + 1].freq) {
            // printf("checking-----------\n");
            temp = d[isort];
            d[isort] = d[isort + 1];
            d[isort + 1] = temp;
         }
      }
   }


   printf("Frequency        Word in Doc \n");
   printf("-----------------------------\n");
   for(int j = 0; j < idictinsert; j++){
         printf("\t%d \t %s\n", d[j].freq, d[j].word);
   }
   // --------------------------------------------------------------------

}