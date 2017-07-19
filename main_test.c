/**
  * ECE254 Linux Dynamic Memory Management Lab
  * @file: main_test.c
  * @brief: The main file to write tests of memory allocation algorithms
  */ 

/* includes */
/* system provided header files. You may add more */
#include <stdio.h>

/* non-system provided header files. 
   Do not include more user-defined header files here
 */
#include "mem.h"


int main(int argc, char *argv[])
{

	int num = 0;
	void *p, *q, *a, *b, *c, *d, *e, *f;
	int res = -2;
//------------------------BEST FIT TEST CASES--------------------------------------//	
	
	best_fit_memory_init(1023);	// initizae 1KB, best fit
//-------------TEST CASE 1----------------------//	
  printLinkedList();
	a = best_fit_alloc(12);
	b = best_fit_alloc(24);
	c = best_fit_alloc(22);
	d = best_fit_alloc(8);	

	printLinkedList();
	best_fit_dealloc(c);
	printLinkedList();	

//------------TEST CASE 2----------------------//

	best_fit_dealloc(d);
	printLinkedList();	
//------------TEST CASE 3----------------------//

	c = best_fit_alloc(22);
	d = best_fit_alloc(8);	
	
	printLinkedList();
	best_fit_dealloc(b);
	best_fit_dealloc(c);
	printLinkedList();
	
//------------TEST CASE 4----------------------//
	b = best_fit_alloc(24);
	printLinkedList();
	best_fit_dealloc(b);
	printLinkedList();
	
//------------TEST CASE 5----------------------//
	b = best_fit_alloc(24);
	c = best_fit_alloc(22);
	printLinkedList();
	best_fit_dealloc(a);
	printLinkedList();
//------------TEST CASE 6----------------------//
	a = best_fit_alloc(12);
	printLinkedList();
	best_fit_dealloc(c);
	printLinkedList();
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
  if (num != 3) {
		printf("Test 9 failed\n");
    return -1;
  }

		printf("###############################\n");
		printf("#### Best fit tests passed ####\n");
		printf("###############################\n");
	
//--------------------------WORST FIT TEST CASES---------------------------//


	worst_fit_memory_init(1023);	// initizae 1KB, worst fit
//-------------TEST CASE 1----------------------//	
	a = worst_fit_alloc(12);
	printLinkedList();
  // TODO: problem with this worst_fit_alloc
	b = worst_fit_alloc(24);
	printLinkedList();
  return 0;
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);	
	printf("WORST FIT TEST CASE 1\n ______________________________\n");

	printLinkedList();
	worst_fit_dealloc(c);
	printLinkedList();
	worst_fit_dealloc(a);
	worst_fit_dealloc(b);
	worst_fit_dealloc(d);
	printLinkedList();


//------------TEST CASE 2----------------------//
	printf("WORST FIT TEST CASE 2\n ______________________________\n");
	a = worst_fit_alloc(12);
	b = worst_fit_alloc(24);
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);	
	
	worst_fit_dealloc(d);
	printLinkedList();	
	worst_fit_dealloc(a);
	worst_fit_dealloc(b);
	worst_fit_dealloc(c);
	printLinkedList();
//------------TEST CASE 3----------------------//
	printf("WORST FIT TEST CASE 3\n ______________________________\n");
	a = worst_fit_alloc(12);
	b = worst_fit_alloc(24);
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);		
	
	printLinkedList();
	worst_fit_dealloc(b);
	worst_fit_dealloc(c);
	printLinkedList();
	worst_fit_dealloc(a);
	worst_fit_dealloc(d);
	printLinkedList();

	
//------------TEST CASE 4----------------------//
	printf("WORST FIT TEST CASE 4\n ______________________________\n");
	a = worst_fit_alloc(12);
	b = worst_fit_alloc(24);
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);
	
	printLinkedList();
	worst_fit_dealloc(d);
	printLinkedList();
	worst_fit_dealloc(a);
	worst_fit_dealloc(b);
	worst_fit_dealloc(c);
	printLinkedList();
	
//------------TEST CASE 5----------------------//
	printf("WORST FIT TEST CASE 5\n ______________________________\n");
	a = worst_fit_alloc(12);
	b = worst_fit_alloc(24);
	c = worst_fit_alloc(22);
	d = worst_fit_alloc(8);
	
	printLinkedList();
	worst_fit_dealloc(a);
	printLinkedList();
//------------TEST CASE 6----------------------//
	printf("WORST FIT TEST CASE 6\n ______________________________\n");
	a = best_fit_alloc(12);
	printLinkedList();
	worst_fit_dealloc(d);
	printLinkedList();

//------------TEST CASE 7----------------------//
	printf("WORST FIT TEST CASE 7\n ______________________________\n");
	
	res = worst_fit_memory_init(20);
	if(res == -1) {
		printf("Test 7 passed\n");
	}
//------------TEST CASE 8----------------------//
	printf("WORST FIT TEST CASE 8\n ______________________________\n");
	d = worst_fit_alloc(824);
	if(!d) {
		printf("Test 8 passed\n");
	}

//------------TEST CASE 9----------------------//
	printf("WORST FIT TEST CASE 9\n ______________________________\n");	
	num = best_fit_count_extfrag(824);
	printf("Num of external fragments (824): %d", num);

//---------------------------------------------------------------------//

	return 0;
}
