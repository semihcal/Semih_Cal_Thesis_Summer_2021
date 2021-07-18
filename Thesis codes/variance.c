#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void getVariance(int *arr, int *bootssize, float *distmean, float *pmean){

float mean = 0.0;
const int s = *bootssize;
float sqdistance[s];
float distance[s];
float sqsumdist = 0.0;
*distmean= 0.0;

for( int counter= 0; counter < s; counter++){

    mean += arr[counter];
    
    //printf(" sqmean %d: %d", counter, sqmean[counter]);
    
    
}


mean = mean/ *bootssize;


for( int i= 0; i< s; i++){
    distance[i] =0.0;
    distance[i] = (float) arr[i] - mean; 
    sqdistance[i] = 0.0;
    sqdistance[i]= distance[i] * distance[i];
    sqsumdist += sqdistance[i]; 
}
sqsumdist = sqsumdist /(s-1)   ;
*distmean = sqrtf(sqsumdist);
*pmean = mean;
 /*printf(" variance : %2.2f\n",  sqsumdist);
 printf(" std : %2.2f\n",  *distmean);
 printf(" mean : %d\n", (int) mean);
 printf(" mean : %2.2f\n",  mean / 0.001);*/
}