#include <stdio.h>
#include <stdlib.h>
#include "table_structure.c"
#include <stdbool.h>


void sampleData(struct table_structure *p, struct query_structure *qvar, long int *randnumarr, char colnames[][20], char samplecol[][20]){

FILE *fp;
FILE *fp2;
fp =fopen(p->inputfile,"r");
if(!fp){
    printf("Can't open Original file\n");
}

fp2 =fopen(p->outputfile, "w+");
if(!fp2){
    printf("Can't open output file\n");
}
char buf[1024];
char *tmp = NULL;
long int counter_row =0;
long int randnumarrcounter =0;
int counter_column;
int sample_file_counter;
char *ptr;
bool flag =true;








while(fgets(buf, 1024, fp)){
    

    if(counter_row == randnumarr[randnumarrcounter]){

        //printf("-%d- : %d ",counter_row, randnumarr[randnumarrcounter]);

        tmp = strtok(buf, ",");
        counter_column=0;
        sample_file_counter =0;
    

        while (tmp)
        {
            if((ptr = strchr(tmp,'\r'))!=NULL || (ptr = strchr(tmp,'\n'))!=NULL){
                        *ptr = '\0';}
            if(strcmp(colnames[counter_column], qvar->cond_col_name2)==0 ||strcmp(colnames[counter_column],qvar->cond_col_name)==0||
            strcmp(colnames[counter_column], qvar->condtablecol)==0 ||strcmp(colnames[counter_column],qvar->condtablecol2)==0){
                if(flag){
                    strcpy(samplecol[sample_file_counter],colnames[counter_column]);
                }
                

                fprintf(fp2, "%s%s",tmp,(sample_file_counter<1 ? "," :"\n"));
                sample_file_counter++;
            }
            
            tmp = strtok(NULL,",");
            counter_column++;
        }
        randnumarrcounter++;
        flag = false;
    }
    
    counter_row++;
 
}


fclose(fp);
fclose(fp2);

}