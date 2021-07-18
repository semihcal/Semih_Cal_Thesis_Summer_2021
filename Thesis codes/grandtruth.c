#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



void calculateGrandT(struct table_structure *p, 
struct query_structure *qvar, struct dict *d, long int *randnumarr, char colnames[][20], 
char samplecol[][20], char *filet, int *result, long int *slc_attr){
FILE *fp;


//original table or sample table
if(*filet == 's'){
 fp =fopen(p->outputfile,"r");
}
else if(*filet=='o'){
    fp =fopen(p->inputfile,"r");
}
else{
    printf("can't recognize the file sample or original");
}


if(!fp){
    printf("Can't open sample data file\n");
}
char buf[1024];
char *tmp = NULL;
int counter_row =0;
int randnumarrcounter =0;
int counter_column;
char *ptr;
bool flag =true;
char cmpfl[8] = "DECIMAL";
char cmpin[4] = "INT";
*result =0;
float col_val;
float cond_val;
char values[p->arsizec][20];


while(fgets(buf, 1024, fp)){
    tmp = strtok(buf, ",");
    counter_column=0;
    while (tmp){
        strcpy(values[counter_column],tmp);
        if(*filet == 's'){
            if(counter_column == 1){
                //printf(" dict result: %s",DictSearch(d,samplecol[counter_column]));
                if(strcmp(DictSearch(d,samplecol[counter_column]),cmpfl) == 0){
                    if(strcmp(qvar->operation, ">")==0){
                         
                        if( atof(tmp) > atof(qvar->cond) &&atof(tmp) < atof(qvar->cond2)){
                            

                            *result +=1;
                        }

                    }
                    if(strcmp(qvar->operation, "<")==0){
                         
                        if( atof(tmp) < atof(qvar->cond) &&atof(tmp) > atof(qvar->cond2)){
                            

                            *result +=1;
                        }

                    }
                    

                }
                else if(strcmp(DictSearch(d,samplecol[counter_column]),cmpin)==0){
                    if(strcmp(qvar->operation, ">")==0){
                         
                        if( atoi(tmp) > atoi(qvar->cond) &&atoi(tmp) < atoi(qvar->cond2)){
                            
                            *result +=1;
                        }

                    }
                    if(strcmp(qvar->operation, "<")==0){
                         
                        if( atof(tmp) < atoi(qvar->cond) &&atoi(tmp) > atoi(qvar->cond2)){
                            

                            *result +=1;
                        }

                    }
                }
            }
 
        }
        if(*filet == 'o'){
            if(strcmp(colnames[counter_column], qvar->cond_col_name2)==0 ||strcmp(colnames[counter_column],qvar->cond_col_name)==0){
                if(strcmp(DictSearch(d,colnames[counter_column]),cmpfl) == 0){
                    if(strcmp(qvar->operation, ">")==0){
                         
                        if( atof(tmp) > atof(qvar->cond) &&atof(tmp) < atof(qvar->cond2)){
                            

                            *result +=1;
                            if(counter_row == randnumarr[randnumarrcounter]){
                                slc_attr[randnumarrcounter] = 1;
                                randnumarrcounter++;
                            }
                            
                            
                            
                        }else if(counter_row == randnumarr[randnumarrcounter]){
                                slc_attr[randnumarrcounter] = 0;
                                randnumarrcounter++;
                            }
                       
                        

                    }
                    if(strcmp(qvar->operation, "<")==0){
                         
                        if( atof(tmp) < atof(qvar->cond) &&atof(tmp) > atof(qvar->cond2)){
                            
                            *result +=1;
                            if(counter_row == randnumarr[randnumarrcounter]){
                                slc_attr[randnumarrcounter] = 1;
                                randnumarrcounter++;
                            }
                            
                        }else if(counter_row == randnumarr[randnumarrcounter]){
                                slc_attr[randnumarrcounter] = 0;
                                randnumarrcounter++;
                            }

                    }

                }
                if(strcmp(DictSearch(d,colnames[counter_column]),cmpin) == 0){
                    if(strcmp(qvar->operation, ">")==0){
                         
                        if( atoi(tmp) > atoi(qvar->cond) &&atoi(tmp) < atoi(qvar->cond2)){
                            
                            *result +=1;
                            if(counter_row == randnumarr[randnumarrcounter]){
                                slc_attr[randnumarrcounter] = 1;
                                randnumarrcounter++;
                            }
                            
                        }else if(counter_row == randnumarr[randnumarrcounter]){
                                slc_attr[randnumarrcounter] = 0;
                                randnumarrcounter++;
                            }
                        

                    }
                    if(strcmp(qvar->operation, "<")==0){
                         
                        if( atoi(tmp) < atoi(qvar->cond) &&atoi(tmp) > atoi(qvar->cond2)){
                            
                            
                            *result +=1;
                            if(counter_row == randnumarr[randnumarrcounter]){
                                slc_attr[randnumarrcounter] = 1;
                                randnumarrcounter++;
                            }
                            
                        }else if(counter_row == randnumarr[randnumarrcounter]){
                                slc_attr[randnumarrcounter] = 0;
                                randnumarrcounter++;
                            }

                    }

                }

                counter_row++;

            }

        }

        tmp = strtok(NULL,",");
            counter_column++;

    }

}

fclose(fp);
  
}