#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void getsamplecol(struct table_structure *p, struct query_structure *qvar, char colnames[][20], char samplecol[][20]){

    int counter = 0;

for( int i =0; i< p->col_size; i++){

    if(strcmp(colnames[i], qvar->cond_col_name2)==0 ||strcmp(colnames[i],qvar->cond_col_name)==0||
            strcmp(colnames[i], qvar->condtablecol)==0 ||strcmp(colnames[i],qvar->condtablecol2)==0){

                strcpy(samplecol[counter],colnames[i]);

                counter++;

            }
}

}