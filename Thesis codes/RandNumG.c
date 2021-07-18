#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(long int*)a - *( long int*)b );
}



void changeNum( long int *arr2, long int *m) 
{ 
    long int g, key, j; 
    for (g = 1; g < *m; g++) { 
        key = arr2[g]; 
        j = g - 1; 
  
        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && arr2[j] == key) { 
            arr2[j + 1] = key+1; 
            j = j - 1; 
        } 

        arr2[j + 1] = key;
        
    } 
} 

void getRandom(long int *k, long int *r, long int *numofrec, long int *range, double *ptime) {
    clock_t second2; 
  second2 = clock();
   long int a = *k;
   
   long int b = *numofrec;
   long int *tmp = NULL;
   tmp = r;
   int hasDuplicate;
   long int lower = 0;


   /* seed */
   srand(time( NULL ) );
   
  
   for (long int i = 0; i < a; i++) {
      r[i] = rand()% ((*range+(i* (*range)))- lower) + lower + 1;
      lower += *range; 
     
      
   }
   r = tmp;
    
   
   //changeNum(r,&a);
    second2 = clock() -second2;
  *ptime = ((double)second2)/CLOCKS_PER_SEC;
   


}

/*int main(){

    int a= 10;
    int b =100;
    long int c[a];

    getRandom(&a,c,&b);
for (int i=0; i<a;i++)
    {
        printf("%d : %d, " ,i,c[i]);
    }

}*/