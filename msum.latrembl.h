#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4
#define NUM_ELEMENTS 64000
double A[NUM_ELEMENTS] ;

typedef struct {
    int firstIndex;
    int lastIndex;
    double theSum ;
} SumInfo ;

void *doSum(void *data);