#include "msum.latrembl.h"

void *doSum(void *data) {
	
	     // define first and last indicies
		 int first = ((SumInfo*)data)->firstIndex;
		 int last = ((SumInfo*)data)->lastIndex;
		 printf("\nFirst index: %i \n", first);
		 printf("Last index: %i \n", last);
		 
		 double sum = 0;	
		 
		 // increment sum value beginning at index[first] and ending with index[last]
		 for (int i =first; i<=last; i++) {
			 //printf("i: %i \n", i);
			 sum += A[i];
			 //printf("Sum: %f \n", sum);
		 }
		 
		 // store the sum in the data struct 
		 ((SumInfo*)data)->theSum = sum;
		 printf("Sum: %f \n", sum);
}

int main() {
	
	// truly random number using time as seed
	srand48((unsigned int)time(NULL));
	
	// length of array
	int length = sizeof(A)/sizeof(A[0]);	
	//printf("Size of array: %i \n", length);
	
	// filling array A with 64000 random numbers ranging from 0-1
	for (int i=0; i<length;i++){
		double rand= drand48();
		A[i] = rand;
		//printf("Array[%i] %f \n", i, A[i]);
	}

	// malloc of data structs
	SumInfo *data1 = (SumInfo*) malloc(sizeof(SumInfo*));
	SumInfo *data2 = (SumInfo*) malloc(sizeof(SumInfo*));
	SumInfo *data3 = (SumInfo*) malloc(sizeof(SumInfo*));
	SumInfo *data4 = (SumInfo*) malloc(sizeof(SumInfo*));	
	
	// dividing arra
	int chunkSize = NUM_ELEMENTS/NUM_THREADS;	
	data1->firstIndex = 0;
	data1->lastIndex = data1->firstIndex + (chunkSize -1);	
	data2->firstIndex = data1->lastIndex + 1;
	data2->lastIndex = data2->firstIndex + (chunkSize -1);	
	data3->firstIndex = data2->lastIndex + 1;
	data3->lastIndex = data3->firstIndex + (chunkSize -1);	
	data4->firstIndex = data3->lastIndex + 1;
	data4->lastIndex = data4->firstIndex + chunkSize;
	
    // thread creation
	pthread_t threads[NUM_THREADS];
	pthread_create(&threads[0], NULL, doSum, (void *)data1);
	pthread_create(&threads[1], NULL, doSum, (void *)data2);
	pthread_create(&threads[2], NULL, doSum, (void *)data3);
	pthread_create(&threads[3], NULL, doSum, (void *)data4);
	
	// joining threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); 
	}
	
	//calculating sum
	double sum = data1->theSum + data2->theSum + data3->theSum + data4->theSum;
	printf("Final Sum: %f \n", sum);
	
	//checking sum by adding all values in array A with a simple for loop 
	/*
	double sum2 = 0;
	for (int i=0;i<NUM_ELEMENTS;i++) {
		sum2 += A[i];		
	}
	printf("Final Sum2: %f \n", sum2);
	*/
	
	// free memory
	free(data1);
	free(data2);
	free(data3);
	free(data4);
	
	return 0;
}



	