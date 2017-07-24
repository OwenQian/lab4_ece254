/**
  * ECE254 Linux Dynamic Memory Management Lab
  * @file: main_test.c
  * @brief: The main file to write tests of memory allocation algorithms
  */ 

/* includes */
/* system provided header files. You may add more */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* non-system provided header files. 
   Do not include more user-defined header files here
 */
#include "mem.h"

int main(int argc, char *argv[])
{

	int num = 0;
	void *a, *b, *c, *d;
	int res = -2;
//------------------------BEST FIT TEST CASES--------------------------------------//	
	
	best_fit_memory_init(1023);	// initizae 1KB, best fit
//-------------TEST CASE 1----------------------//	
	a = best_fit_alloc(12);
	b = best_fit_alloc(24);
	c = best_fit_alloc(22);
	d = best_fit_alloc(8);

	best_fit_dealloc(c);

//------------TEST CASE 2----------------------//

	best_fit_dealloc(d);
//------------TEST CASE 3----------------------//

	c = best_fit_alloc(22);
	d = best_fit_alloc(8);	
	
	best_fit_dealloc(b);
	best_fit_dealloc(c);
	
//------------TEST CASE 4----------------------//
	b = best_fit_alloc(24);
	best_fit_dealloc(b);
	
//------------TEST CASE 5----------------------//
	b = best_fit_alloc(24);
	c = best_fit_alloc(22);
	best_fit_dealloc(a);
//------------TEST CASE 6----------------------//
	a = best_fit_alloc(12);
	best_fit_dealloc(c);
	c = best_fit_alloc(22);

//------------TEST CASE 7----------------------//
	res = best_fit_memory_init(20);
	if(res != -1) {
		printf("Test 7 failed\n");
    return -1;
	}
//------------TEST CASE 8----------------------//
	d = best_fit_alloc(824);
	if(d) {
		printf("Test 8 failed\n");
    return -1;
	}

//------------TEST CASE 9----------------------//
	num = best_fit_count_extfrag(824);
	printf("Num of external fragments (824): %d\n", num);
  if (num != 2) {
		printf("Best fit Test 9 failed\n");
    return -1;
  }

		printf("###############################\n");
		printf("#### Best fit tests passed ####\n");
		printf("###############################\n");
	
//--------------------------WORST FIT TEST CASES---------------------------//


	worst_fit_memory_init(1023);	// initizae 1KB, worst fit
//-------------TEST CASE 1----------------------//	
	a = worst_fit_alloc(12);
	b = worst_fit_alloc(24);
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);	
	printf("WORST FIT TEST CASE 1\n ______________________________\n");

	worst_fit_dealloc(c);
	worst_fit_dealloc(a);
	worst_fit_dealloc(b);
	worst_fit_dealloc(d);


//------------TEST CASE 2----------------------//
	printf("WORST FIT TEST CASE 2\n ______________________________\n");
	a = worst_fit_alloc(12);
	b = worst_fit_alloc(24);
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);	
	
	worst_fit_dealloc(d);
	worst_fit_dealloc(a);
	worst_fit_dealloc(b);
	worst_fit_dealloc(c);
//------------TEST CASE 3----------------------//
	printf("WORST FIT TEST CASE 3\n ______________________________\n");
	a = worst_fit_alloc(12);
	b = worst_fit_alloc(24);
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);
	
	worst_fit_dealloc(b);
	worst_fit_dealloc(c);
	worst_fit_dealloc(a);
	worst_fit_dealloc(d);

	
//------------TEST CASE 4----------------------//
	printf("WORST FIT TEST CASE 4\n ______________________________\n");
	a = worst_fit_alloc(12);
	b = worst_fit_alloc(24);
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);
	
	worst_fit_dealloc(d);
	worst_fit_dealloc(a);
	worst_fit_dealloc(b);
	worst_fit_dealloc(c);
	
//------------TEST CASE 5----------------------//
	printf("WORST FIT TEST CASE 5\n ______________________________\n");
	a = worst_fit_alloc(12);
	b = worst_fit_alloc(24);
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);
	
	worst_fit_dealloc(a);
//------------TEST CASE 6----------------------//
	printf("WORST FIT TEST CASE 6\n ______________________________\n");
	a = best_fit_alloc(12);
	worst_fit_dealloc(d);

//------------TEST CASE 7----------------------//
	printf("WORST FIT TEST CASE 7\n ______________________________\n");
	
	res = worst_fit_memory_init(20);
	if(res != -1) {
		printf("Worst fit Test 7 failed\n");
    return -1;
	}
//------------TEST CASE 8----------------------//
	printf("WORST FIT TEST CASE 8\n ______________________________\n");
	d = worst_fit_alloc(824);
	if (d) {
		printf("Worst fit Test 8 failed\n");
    return -1;
	}

//------------TEST CASE 9----------------------//
	printf("WORST FIT TEST CASE 9\n ______________________________\n");	
	num = best_fit_count_extfrag(824);
	printf("Num of external fragments (824): %d\n", num);

//---------------------------------------------------------------------//

//------------ Fragmentation test -------------//
  size_t cnt = 0;
  int iterations = 15;
  int allocsPerIt = 5;
  int deallocsPerIt = 3;
  void* allocationPtr[iterations*allocsPerIt];
  int poolSize = 8196;
  time_t t;
  int bestAvg = 0;
  int worstAvg = 0;
  int numRepeats = 50;

  srand((unsigned) time(&t));
  best_fit_memory_init(poolSize);
  for (int repeat = 0; repeat < numRepeats; ++repeat) {
    cnt = 0;
    for (int i = 0; i < iterations; i++) {
      for (int j = 0; j < allocsPerIt; j++) {
        int size = rand()%poolSize;
        allocationPtr[cnt++] = best_fit_alloc(size);
      }
      for (int j = 0; j < deallocsPerIt; j++) {
        best_fit_dealloc(allocationPtr[rand()%cnt]);
      }
    }
    printf("Best fit 10%% size: %d\n", best_fit_count_extfrag(poolSize/20));
    bestAvg += best_fit_count_extfrag(poolSize/10);
  }
  printf("Best fit AVERAGE 10%% size: %f\n", (double) bestAvg/(double)numRepeats);
  worst_fit_memory_init(poolSize);
  for (int repeat = 0; repeat < numRepeats; ++repeat) {
    cnt = 0;
    for (int i = 0; i < iterations; i++) {
      for (int j = 0; j < allocsPerIt; j++) {
        int size = rand()%poolSize;
        allocationPtr[cnt++] = worst_fit_alloc(size);
      }
      for (int j = 0; j < deallocsPerIt; j++) {
        worst_fit_dealloc(allocationPtr[rand()%cnt]);
      }
    }
    printf("Worst fit 10%% size: %d\n", worst_fit_count_extfrag(poolSize/10));
    worstAvg += worst_fit_count_extfrag(poolSize/10);
  }
  printf("Worst fit average 10%% size: %f\n", (double) worstAvg/(double)numRepeats);
	return 0;
}
