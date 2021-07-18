#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "util/bootstrap_rand.c"

void getBootstrap(struct table_structure *p, int *bootstrapsize, int *b_sample_result, long int *slc_attr,double *ptime, double *ptms, double *totaltm){
const int size = *bootstrapsize;
int randomnumber;

int col_counter;
double total_time;
long int *bootrand;
bootrand = (long int*) malloc(p->numOfRandNum * sizeof(long int));
int bootstrap_counter;



clock_t FA_time; 
FA_time = clock();
// loop for the amount of bootstrap sample we need
for(  bootstrap_counter =0; bootstrap_counter < *bootstrapsize; ){

    clock_t second; 
    second = clock();
    getRandomNumber(&p->numOfRandNum, bootrand);
    second = clock() -second;
    double time_taken = ((double)second)/CLOCKS_PER_SEC;
    total_time += time_taken;
    b_sample_result[bootstrap_counter]=0;
    long int bsample_count = 0;
    for (long int row_counter =0; row_counter< p->numOfRandNum; row_counter++){
        if(slc_attr[bootrand[row_counter]] == 1){
            
            b_sample_result[bootstrap_counter] += 1;

        }
        bsample_count++;
    }
    bsample_count = 0;
    bootstrap_counter ++;


}

FA_time = clock() -FA_time;
double filetime_taken = ((double)FA_time)/CLOCKS_PER_SEC;
*totaltm = filetime_taken + *ptime - total_time;

printf("FA Time: %2.2fs \n", filetime_taken);
printf("Rand Num Gen Time: %2.2fs \n", total_time);
*totaltm = total_time + filetime_taken;
free(bootrand);

}