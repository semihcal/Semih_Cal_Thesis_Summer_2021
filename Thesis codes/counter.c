#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define MAX_FILE_NAME 100 
#define SIZE 2048

void  countNumofRecord(char* pname, long int* xx, double *ptime){
  clock_t second2; 
  second2 = clock();
 FILE *fp; 
    int count = 0;  
    //char filename[MAX_FILE_NAME]; 
    char c;  
    fp = fopen(pname, "r"); 
  
    if (fp == NULL) 
    { 
        printf("Could not open file %s", pname); 
        
    } 
    char buffer[SIZE + 1], lastchar = '\n';
    size_t bytes;
    long int lines = 0;

   

    while ((bytes = fread(buffer, 1, sizeof(buffer) - 1, fp))) {
        lastchar = buffer[bytes - 1];
        for (char *c = buffer; (c = memchr(c, '\n', bytes - (c - buffer))); c++) {
            lines++;
        }
    }
    if (lastchar != '\n') {
        lines++;  /* Count the last line even if it lacks a newline */
    }
    
  
   

    

    
    fclose(fp); 
    *xx = lines;
    
    
    second2 = clock() -second2;
  *ptime = ((double)second2)/CLOCKS_PER_SEC;

  //printf("r time %2.2fs \n", time_taken2);
    
  
    

}

void CounterColumn(char* pname, int* xx ){
      
    FILE *fp; 
 int countcol =0;
char c;  

fp = fopen(pname, "r"); 

for (c = getc(fp); c != '\n'; c = getc(fp)) {

        if(c == ','){
          countcol = countcol+1;
        }

    }

    fclose(fp); 
    countcol = countcol+1;
   *xx = countcol;
   

}


