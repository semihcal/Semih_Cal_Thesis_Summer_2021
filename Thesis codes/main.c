#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include "query_parser.c"
#include "readtable.c"
#include "counter.c"
#include "RandNumG.c"
#include "data_sampling.c"
#include "grandtruth.c"
#include "bootstrap1.c"
#include "variance.c"
#include "samplecol.c"

void usage(){
 
 printf("./csv.o -i <input file name> -o <output file name> -s <sample size> ex: ./csv.o -i xx.csv -o y.csv -s .3 ");

}

int main(int argc, char **argv){
  //creating seed to generate random numbers
  srand(time(NULL));
  clock_t second; 
  second = clock();
  // create table struct t to store data of the table
  struct table_structure t;
  
  // get the input parameters for the program input file name, output file name, and sample ratio
  if(argc<3){
    usage();
  }
  int option_index = 0;
  int bootstarpsize = 2000;
  while ((option_index = getopt(argc, argv, "i:o:s:")) != -1) 
  {
    switch (option_index)
    {
    case 'i':
      t.inputfile = optarg;
      break;
    case 'o':
      t.outputfile =optarg;
      break;
    case 's':
      t.samplesize =atof(optarg);


    
    default:
      
      break;
      return 1;
    }
  }
 //create query struct q to store query variables from query.txt file.
 struct query_structure q;
 //create dictionary to compare data types of the attributes in the data file
 Dict data_types;
 data_types = DictCreate();
 t.arsizec = 20;
 long int range;
 double freadtime;
 double randtime;
 double file_rand_time;
 char *stringinput;
 
 
 strcpy(q.file_name,"query.txt");
 //read and parse the query from query.txt file.
 getQuery(&q, t.outputfile);
 //count number of columns in create_table.txt file
 countcolnames(&t.arrsize);
 char colnames[t.arrsize][t.arsizec];
 char samplecolnames[3][t.arsizec];
 // get data types of the columns
  getTableDict(data_types,colnames,t.arrsize);
  
  //count total number of tuples in the original table
  countNumofRecord(t.inputfile, &t.row_size,&freadtime);
  //count total number of fields in the original table
  CounterColumn(t.inputfile,&t.col_size);
  
  //calculate the total number of tuples needed for the sample table
  t.numOfRandNum = t.row_size * t.samplesize;
  //printf("%d",t.numOfRandNum);
  //create an array to store random numbers for selecting tuples from original table.
  long int *rand_numbers =malloc(t.numOfRandNum * sizeof(long int));
  range = t.row_size/t.numOfRandNum;
  // create the random numbers and store into array
  getRandom(&t.numOfRandNum,rand_numbers,&t.row_size, &range, &randtime);
  
  
  
    
    /*for (int i=0; i<t.numOfRandNum;i++)
    {
        printf("%d : %d, " ,i,rand_numbers[i]);
    }*/
  
  //sampleData(&t,&q,rand_numbers,colnames,samplecolnames);
  //getsamplecol(&t,&q,colnames,samplecolnames);
  //printf("%s",samplecolnames[1]);
 
  char tabletype;

   int grandTruth;
   long int *samplearr;
//array of the sample table
samplearr = malloc(t.numOfRandNum * sizeof(long int));
long int grandTruthsample;
   
  //calculateGrandT(&t,&q,data_types ,rand_numbers,colnames,samplecolnames,&tabletype, &grandTruth);
  //printf(" gt of sample is: %d\n", grandTruth);
  //grandTruth = grandTruth/ t.samplesize;
  //grandTruthsample = grandTruth;
  //printf(" gt of sample is: %d\n",  grandTruth);
   tabletype ='o';
   long int tt =0;
   //calculate the grand truth of original table and create sample table
  calculateGrandT(&t,&q,data_types ,rand_numbers,colnames,samplecolnames,&tabletype, &grandTruth,samplearr);
  for (int x =0; x< t.numOfRandNum; x++ ){

    //printf(" arr %d : %d",x, samplearr[x]);
    if(samplearr[x]==1){
        tt +=1;

    }
  }
  //ground truth calculation of sample table 
  grandTruthsample = tt/ t.samplesize;
  printf(" gt of sample is: %d\n",  grandTruthsample);
  
  printf(" gt of original is: %d\n", grandTruth);
  int b_sample_result[bootstarpsize];
  
  

  //bootstrap samples
  getBootstrap(&t,&bootstarpsize,b_sample_result,samplearr, &freadtime, &randtime, &file_rand_time);
    for(int bootstrap_counter = 0; bootstrap_counter< bootstarpsize; bootstrap_counter++){
             b_sample_result[bootstrap_counter] = b_sample_result[bootstrap_counter]/ t.samplesize;
             //printf("bssr result : %d \n", b_sample_result[bootstrap_counter]);
    }
  
  float std;
  float z = 1.960;
  float ci_positive;
  float ci_negative;
  float mean;
  float std_error;
  float ci;
  float sqrt_of_n; 
  //calculate variance and standard error from BS samples
  getVariance(b_sample_result, &bootstarpsize, &std, &mean);
  
  //std = std / t.samplesize  ;
  
  sqrt_of_n = sqrtf(bootstarpsize);
  //printf(" kare %2.2f", sqrt_of_n);
  mean = mean / t.samplesize;
  //printf("bs mean is: %2.2f\n", mean);
  printf("bs std is: %2.2f\n", std);
  //printf("row size is: %d\n", t.row_size);
  //std_error = std/ sqrt_of_n;
  //ci =std*z*t.row_size;
  ci =std*z;
  //printf("upper ci: %2.2f\n",ci);
  //CI lower and upper range calculation
  ci_positive = (float) grandTruthsample + ci;
  ci_negative = (float) grandTruthsample - ci;
  //printf("upper ci: %2.2f\n",ci_positive);
  //printf("lower ci: %2.2f\n",ci_negative);
  printf("CI: [%2.2f, %2.2f]\n", ci_negative, ci_positive);
  if(grandTruth<=ci_positive && grandTruth>=ci_negative){
  printf("%d is hit in CI\n",grandTruth);
  }else{
  printf("%d is not hit in CI\n",grandTruth);
  }
  


  second = clock() -second;
  double time_taken = ((double)second)/CLOCKS_PER_SEC;
  printf("execution time %2.2fs \n", time_taken);
 


 free(rand_numbers);
 free(samplearr);
}