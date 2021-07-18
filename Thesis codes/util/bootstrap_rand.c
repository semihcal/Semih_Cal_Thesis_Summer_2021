#include <stdio.h>
#include <stdlib.h>





int getRandomNumber( long int *n, long int *pr){
long int *tmp = NULL;
tmp = pr;
//srand(time(NULL));
for (long int i = 0; i< *n; i++){
   *pr= rand()% (*n) ;
   pr++;
}
pr = tmp;

qsort(pr,*n, sizeof(long int), cmpfunc);


}


