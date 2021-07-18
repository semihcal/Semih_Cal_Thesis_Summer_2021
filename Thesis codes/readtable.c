#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "dict.c"

typedef struct tabelColumns tabelColumns;
void removeChar(char *s, int c){ 
  
    int j,n = strlen(s); 
    for (int i =j=0; i<n; i++) 
       if (s[i] != c) 
          s[j++] = s[i]; 
      
    s[j] = '\0'; 
} 

void countcolnames(int *p){
  FILE *fp;
  fp = fopen("create_table.txt","r");
   int i =0;
   char buffr[512];
  while( fgets(buffr, 512,fp))
  {
     
     
     
     i++;
  }

  *p= i-1;
  


}
Dict getTableDict(Dict d ,char arr[][20], int sz) {
     

     FILE *fp;
     fp = fopen("create_table.txt","r");
     char tn[100];
     char dt[100];
     int i =0;
     char k[30];
     char v[30];
     char stop[5];
     int row_counter =0;
     int word_counter = 0;
     char buf[201];
     char buffr[512];
     char *pword =NULL;
     char *ptemp= NULL;
     char tmpvl[100];
     int  first;
     char dtype[10];
     
     
     
     

    if(!fp)
    {
        printf("Error opening file\n");
        exit(1);
    }
    
    
    while (fgets(buffr, 1024,fp)){

      pword =strtok(buffr, " ");
      word_counter = 0;

      while (pword)
      {
        if (row_counter == 0 )
        {
          if( word_counter == 2){
            DictInsert(d, "table_name", pword);
          }
          
        }
        else{
          if (word_counter == 0){
            strcpy(arr[i],pword);
            i++;
            strcpy(k,pword);
          }
          
          if (word_counter == 1){
            strcpy(tmpvl,pword);
            ptemp = strchr(tmpvl,'(');
            if(ptemp){
            first = (int)(ptemp - tmpvl);
            memcpy(dtype, &tmpvl[0],first);
            dtype[first]='\0';
            DictInsert(d, k, dtype);
            strcpy(dtype," ");
            }
            else{
              DictInsert(d, k, pword);

          }
          }
          
          
        }
        pword = strtok(NULL, " ");
        word_counter++;
      }
      row_counter++;
      
    }
    
    
    
  
      
     

    
    fclose(fp);

 }








