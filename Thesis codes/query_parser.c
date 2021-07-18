#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "query_var.c"


void getQuery(struct query_structure *queryvar, char *pquery){
 FILE *fp; 
 char *ptemp= NULL;
 char buffr[512];
 char *pword =NULL;
 char tmpvl[25];
 int  first;
 int last;
 int counter=0;
 int sizeofword;
 char a[20];

 //printf("%s, " ,pquery);
 
 fp = fopen(queryvar->file_name,"r");


 if(!fp){
     printf("can't open query file\n");
 }
    fgets(buffr,512,fp);
    pword =strtok(buffr, " ");
 while (pword)
 {
     if(counter ==1){
         strcpy(queryvar->func_name,pword);
         
     }

     if(counter == 3){
         ptemp = strchr(pword,',');
         if(ptemp){
              *ptemp='\0';

         }
        
         strcpy(queryvar->table_name,pword);
         ptemp = NULL;
         
     }
     if(counter == 4){
         strcpy(queryvar->table_name2, pword);
         
     }
     if (counter == 6)
     {
         strcpy(queryvar->cond_col_name,pword);
     }
     if(counter ==7){
         strcpy(queryvar->operation,pword);

     }
     if (counter == 8)
     {
         strcpy(queryvar->cond,pword);
     }
     if (counter == 10){
        strcpy(queryvar->cond_col_name2,pword);

     }
     if (counter == 11){
        strcpy(queryvar->operation2,pword);

     }
     if (counter == 12){
        strcpy(queryvar->cond2,pword);

     }
     if (counter == 14){
        sscanf(pword,"%[a-zA-z1-9].%[a-zA-z1-9]=%[a-zA-z1-9].%[a-zA-z1-9]",queryvar->condtable,queryvar->condtablecol,queryvar->condtable2,queryvar->condtablecol2 );
        


     }
     
     
     counter++;
     pword = strtok(NULL," ");
    
 }
 


}
 



