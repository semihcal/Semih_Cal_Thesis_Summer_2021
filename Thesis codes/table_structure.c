#include <stdio.h>
#include <stdlib.h>

struct table_structure
{
    char *inputfile ;   //original data file name
    char *outputfile ;  // sample data file name
    float samplesize ;  // sample ratio
    int arsizec;    // column size of column name arr
    int arrsize;    // row size of column name arr
    int col_size;   // column size of original data
    long int row_size;   // row size of of original data
    long int numOfRandNum; // total number of rand num to generate
    
    
};
