/**
  * ECE254 Linux Dynamic Memory Management Lab
  * @file: main_test.c
  * @brief: The main file to write tests of memory allocation algorithms
  */ 

/* includes */
/* system provided header files. You may add more */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* non-system provided header files. 
   Do not include more user-defined header files here
 */
#include "mem.h"
#include "helper.h"
extern 	void print_list ();

// unit tests
int test_basic_allocation(int alg);
int test_basic_deallocation(int alg);
int test_multiple_allocation(int alg);
int test_middle_deallocation(int alg);
int test_front_deallocation(int alg);
int test_back_deallocation(int alg);

int test_coalesce_back(int alg);
int test_coalesce_both(int alg);

int test_full_allocation(int alg);
int test_full_deallocation(int alg);

// integration testing
int test_integration(int alg);

int main(int argc, char *argv[])
{
	int algo = 0; // default algorithm to test is best fit  

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <0/1>. 0 for best fit and 1 for worst fit \n", argv[0]);
		exit (1);
	} else if (!strcmp(argv[1], "1") || !strcmp(argv[1], "0")) {
		algo = atoi(argv[1]);
	} else {
		fprintf(stderr, "Invalid argument, please specify 0 or 1\n");
		exit(1);
	}
	
	if ( algo == 0 ) {
		//initialize memory for test runner
		best_fit_memory_init(1024);
		
		test_basic_allocation(algo);
		test_basic_deallocation(algo);
		test_multiple_allocation(algo);
		test_middle_deallocation(algo);
		test_front_deallocation(algo);
		
		test_back_deallocation(algo);
		test_coalesce_back(algo);
		test_coalesce_both(algo);

		test_full_allocation(algo);
		test_full_deallocation(algo);

		test_integration(algo);

	} else if ( algo == 1 ) {

		worst_fit_memory_init(1024);

		test_basic_allocation(algo);
		test_basic_deallocation(algo);
		test_multiple_allocation(algo);
		test_middle_deallocation(algo);
		test_front_deallocation(algo);
		test_back_deallocation(algo);
		test_coalesce_back(algo);
		test_coalesce_both(algo);

		test_full_allocation(algo);
		test_full_deallocation(algo);

		test_integration(algo);
	} else {
		fprintf(stderr, "Should not reach here!\n");
		exit(1);
	}

	printf("Passed all tests.\n");

	return 0;
}


int test_basic_allocation(int alg) {
	printf("Beginning basic allocation test...\n");

	int before = 0;
	int after = 0;
	void *p;
	if (alg == 0) {
		//arrange
		before = best_fit_count_extfrag(512);

		//act
		p = best_fit_alloc(512);

		//assert
		after = best_fit_count_extfrag(512);
		if (before == 0 && after == 1) {
			//Allocation should introduce frag < 512
			best_fit_dealloc(p);
			printf("Finished basic allocation test.\n");
			return 0;
		}
	} else {
		//arrange
		before = worst_fit_count_extfrag(512);

		//act
		p = worst_fit_alloc(512);

		//assert
		after = worst_fit_count_extfrag(512);
		if (before == 0 && after == 1) {
			//Allocation should introduce frag < 512
			worst_fit_dealloc(p);
			printf("Finished basic allocation test.\n");
			return 0;
		}
	}
	

	printf("Failed basic allocation test.\n");
	return -1;
}

int test_basic_deallocation(int alg) {
	printf("Beginning basic deallocation test...\n");

	int before, after;
	void *p;

	if (alg == 0) {
		//arrange
		p = best_fit_alloc(512);
		before = best_fit_count_extfrag(512);

		//act
		best_fit_dealloc(p);

		//assert
		after = best_fit_count_extfrag(512);
		if (before == 1 && after == 0) {
			//Deallocation should remove frag < 512
			printf("Finished basic deallocation test.\n");
			return 0;
		}
	} else {
		//arrange
		p = worst_fit_alloc(512);
		before = worst_fit_count_extfrag(512);

		//act
		worst_fit_dealloc(p);

		//assert
		after = worst_fit_count_extfrag(512);
		if (before == 1 && after == 0) {
			//Deallocation should remove frag < 512
			printf("Finished basic deallocation test.\n");
			return 0;
		}
	}
	
	printf("Failed basic deallocation test.\n");
	return -1;
}

int test_multiple_allocation(int alg) {
	printf("Beginning multiple deallocation test...\n");

	int initial = 0;
	int final = 0;
	void *p, *q, *r;
	if (alg == 0) {
		//arrange
		initial = best_fit_count_extfrag(512);

		//act
		p = best_fit_alloc(512);
		q = best_fit_alloc(256);
		r = best_fit_alloc(64);
		//assert
		final = best_fit_count_extfrag(512);
		if (initial == 0 && final == 1) {
			//single frag at front of list
			best_fit_dealloc(p);
			best_fit_dealloc(q);
			best_fit_dealloc(r);
			printf("Finished multiple allocation test.\n");
			return 0;
		}

	} else {
		//arrange
		initial = worst_fit_count_extfrag(512);

		//act
		p = worst_fit_alloc(512);
		q = worst_fit_alloc(256);
		r = worst_fit_alloc(64);

		//assert
		final = worst_fit_count_extfrag(512);
		if (initial == 0 && final == 1) {
			//single frag at front of list
			worst_fit_dealloc(p);
			worst_fit_dealloc(q);
			worst_fit_dealloc(r);
			printf("Finished multiple allocation test.\n");
			return 0;
		}
	}
	
	printf("Failed multiple allocation test.\n");
	return -1;
}

int test_middle_deallocation(int alg) {
	printf("Beginning middle deallocation test...\n");

	int initial = 0;
	int final = 0;
	void *p, *q, *r;

	if (alg == 0) {
		//arrange
		p = best_fit_alloc(512);
		q = best_fit_alloc(256);
		r = best_fit_alloc(64);
		initial = best_fit_count_extfrag(512);

		//act
		best_fit_dealloc(q);

		//assert
		final = best_fit_count_extfrag(512);
		if (initial == 1 && final == 2) {
			//No coalescing; a new frag is created
			best_fit_dealloc(p);
			best_fit_dealloc(r);

			printf("Finished middle deallocation test.\n");
			return 0;
		}

		
	} else {
		//arrange
		p = worst_fit_alloc(512);
		q = worst_fit_alloc(256);
		r = worst_fit_alloc(64);
		initial = worst_fit_count_extfrag(512);

		//act
		worst_fit_dealloc(q);

		//assert
		final = worst_fit_count_extfrag(512);
		if (initial == 1 && final == 2) {
			//No coalescing; a new frag is created
			worst_fit_dealloc(p);
			worst_fit_dealloc(r);
			printf("Finished middle deallocation test.\n");
			return 0;
		}
	}

	printf("Failed middle deallocation test.\n");
	return -1;
}

int test_front_deallocation(int alg) {
	printf("Beginning front deallocation test...\n");

	int initial = 0;
	int final = 0;
	void *p, *q, *r;

	if (alg == 0) {
		//arrange

		p = best_fit_alloc(512);
		
		q = best_fit_alloc(256);

		r = best_fit_alloc(64);


		initial = best_fit_count_extfrag(512);

		//act
		best_fit_dealloc(r);

		//assert
		final = best_fit_count_extfrag(512);

		if (initial == 1 && final == 1) {
			//intial and final should be the same due to
			//coalescing of free space and p
			best_fit_dealloc(p);
			best_fit_dealloc(q);
			printf("Finished front deallocation test.\n");
			return 0;
		}

	} else {
		//arrange
		p = worst_fit_alloc(512);
		q = worst_fit_alloc(256);
		r = worst_fit_alloc(64);

		initial = worst_fit_count_extfrag(512);

		//act
		worst_fit_dealloc(r);

		//assert
		final = worst_fit_count_extfrag(512);
		if (initial == 1 && final == 1) {
			//intial and final should be the same due to
			//coalescing of free space and p
			worst_fit_dealloc(p);
			worst_fit_dealloc(q);
			printf("Finished front deallocation test.\n");
			return 0;
		}
	}

	printf("Failed front deallocation test.\n");
	return -1;
}

int test_back_deallocation(int alg) {
	printf("Beginning back deallocation test...\n");

	int initial = 0;
	int final = 0;
	void *p, *q, *r;
	if (alg == 0) {
		//arrange
		print_list();
		p = best_fit_alloc(512);
		q = best_fit_alloc(256);
		r = best_fit_alloc(64);
		initial = best_fit_count_extfrag(516);
		print_list();

		//act
		best_fit_dealloc(p);	
		print_list();

		//assert
		final = best_fit_count_extfrag(516);
		if (initial == 1 && final == 2) {
			//A frag is made as the two empties are
			//not adjacent
			
			best_fit_dealloc(q);
			best_fit_dealloc(r);
			printf("Finished back deallocation test.\n");
			return 0;
		}

	} else {
		//arrange
		print_list();
		p = worst_fit_alloc(512);
		q = worst_fit_alloc(256);
		r = worst_fit_alloc(64);
		initial = worst_fit_count_extfrag(512);
		print_list();

		//act
		worst_fit_dealloc(p);
		print_list();

		//assert
		final = worst_fit_count_extfrag(516);
		if (initial == 1 && final == 2) {
			//A frag is made as the two empties are
			//not adjacent
			worst_fit_dealloc(q);
			worst_fit_dealloc(r);
			printf("Finished back deallocation test.\n");
			return 0;
		}
	}

	printf("Failed back deallocation test.\n");
	return -1;
}

int test_coalesce_back(int alg) {
	printf("Beginning coalesce back test...\n");

	int initial = 0;
	int single_frag = 0;
	int final = 0;
	void *p, *q, *r;

	if (alg == 0) {
		//arange
		p = best_fit_alloc(512);
		q = best_fit_alloc(256);
		r = best_fit_alloc(64);
		best_fit_dealloc(p);

		initial = best_fit_count_extfrag(516);

		//act
		best_fit_dealloc(q);

		//assert
		single_frag = best_fit_count_extfrag(516);
		final = best_fit_count_extfrag(1024);
		if (initial == 2 && single_frag == 1 && final == 2) {
			//Two frags at the beginning < 512 then coalescing
			//should make a node > 512
			best_fit_dealloc(r);
			printf("Finished coalesce back test.\n");
			return 0;
		}

	} else {
		//arange
		p = worst_fit_alloc(512);
		q = worst_fit_alloc(256);
		r = worst_fit_alloc(64);
		worst_fit_dealloc(p);
		initial = worst_fit_count_extfrag(516);

		//act
		worst_fit_dealloc(q);

		//assert
		single_frag = worst_fit_count_extfrag(516);
		final = worst_fit_count_extfrag(1024);
		if (initial == 2 && single_frag == 1 && final == 2) {
			//Two frags at the beginning < 512 then coalescing
			//should make a node > 512
			worst_fit_dealloc(r);
			printf("Finished coalesce back test.\n");
			return 0;
		}
	}

	printf("Failed coalesce back test.\n");
	return -1;
}

int test_coalesce_both(int alg) {
	printf("Beginning coalesce both test...\n");

	int initial = 0;
	int final = 0;
	void *p, *q, *r;

	if (alg == 0) {
		//arange
		p = best_fit_alloc(512);
		q = best_fit_alloc(256);
		r = best_fit_alloc(64);
		best_fit_dealloc(p);
		best_fit_dealloc(r);
		initial = best_fit_count_extfrag(1024);

		//act
		best_fit_dealloc(q);

		//assert
		final = best_fit_count_extfrag(512);
		if (initial == 2 && final == 0) {
			//Two free blocks should be coalesced
			//into a single node when mutual node
			//is deallocated
			printf("Finished coalesce both test.\n");
			return 0;
		}
	} else {
		//arange
		p = worst_fit_alloc(512);
		q = worst_fit_alloc(256);
		r = worst_fit_alloc(64);
		worst_fit_dealloc(p);
		worst_fit_dealloc(r);
		initial = worst_fit_count_extfrag(1024);

		//act
		worst_fit_dealloc(q);

		//assert
		final = worst_fit_count_extfrag(512);
		if (initial == 2 && final == 0) {
			//Two free blocks should be coalesced
			//into a single node when mutual node
			//is deallocated
			printf("Finished coalesce both test.\n");
			return 0;
		}
	}

	printf("Failed coalesce both test.\n");
	return -1;
}

int test_full_allocation(int alg) {
	printf("Beginning full allocation test...\n");

	int initial = 0;
	int final = 0;
	void *p;

	if (alg == 0) {
		//arange
		initial = best_fit_count_extfrag(1024);

		//act
		p = best_fit_alloc(944);

		//assert
		final = best_fit_count_extfrag(1024);
		if (initial == 1 && final == 0) {
			//Initial fragment should become used
			best_fit_dealloc(p);
			printf("Finished full allocation test.\n");
			return 0;
		}
	} else {
		//arange
		initial = worst_fit_count_extfrag(1024);

		//act
		p = worst_fit_alloc(944);

		//assert
		final = worst_fit_count_extfrag(1024);
		if (initial == 1 && final == 0) {
			//Initial fragment should become used
			worst_fit_dealloc(p);
			printf("Finished full allocation test.\n");
			return 0;
		}
	}

	printf("Failed full allocation test.\n");
	return -1;
}

int test_full_deallocation(int alg) {
	printf("Beginning full deallocation test...\n");

	int initial = 0;
	int final = 0;
	void *p;
	if (alg == 0) {
		//arange
		p = best_fit_alloc(944);	
		initial = best_fit_count_extfrag(1024);

		//act
		best_fit_dealloc(p);

		//assert
		final = best_fit_count_extfrag(1024);
		if (initial == 0 && final == 1) {
			//Used fragment should become free
			printf("Finished full deallocation test.\n");
			return 0;
		}
	} else {
		//arange
		p = worst_fit_alloc(944);	
		initial = worst_fit_count_extfrag(1024);

		//act
		worst_fit_dealloc(p);

		//assert
		final = worst_fit_count_extfrag(1024);
		if (initial == 0 && final == 1) {
			//Used fragment should become free
			printf("Finished full deallocation test.\n");
			return 0;
		}
	}

	printf("Failed full deallocation test.\n");
	return -1;
}

int test_integration(int alg) {
	int i = 0;
    int frag_count = 0;

	int alloc_size[120];    	//alloc size
	int *alloc_addr[120];   	//alloc address

	int realloc_size[100];    	//realloc size
	int *realloc_addr[100];   	//realloc address

	if (alg == 0) {
		//best fit
		for (i = 0; i < 120; i++){ 
			alloc_size[i] = rand() % 95 + 20;
		}
		for (i = 0; i < 100; i++) { 
			realloc_size[i] = rand() % 65 + 20;
		}
		
		best_fit_memory_init(16384);			//initialize 16k

		//allocate 120 blocks
		for(i = 0; i < 120; i++){
			alloc_addr[i] = best_fit_alloc(alloc_size[i]);
		}
		
		printf("Allocated 120 blocks.\n");
		frag_count = best_fit_count_extfrag(135);		
		printf("Best fit external fragment count ( < 135 ) = %d\n",frag_count);

		//deallocate 60 blocks
		for(i = 0; i < 60; i++){
			void *de_addr = alloc_addr[alloc_size[i]];
			best_fit_dealloc(de_addr);
		}

		printf("Deallocated 60 blocks.\n");
		frag_count = best_fit_count_extfrag(135);		
		printf("Best fit external fragment count ( < 135 ) = %d\n",frag_count);

		//reallocate 50 blocks
		for(i = 0; i < 50; i++){
			realloc_addr[i] = best_fit_alloc(alloc_size[i]);
		}

		printf("Reallocated 50 blocks.\n");		
		frag_count = best_fit_count_extfrag(16384);		
		printf("Best fit external fragment count (all) = %d\n",frag_count);
		
		//reallocate 50 blocks
		for (i = 50; i < 100; i++) {
			realloc_addr[i] = best_fit_alloc(realloc_size[i]);
		}

		printf("Reallocated 100 blocks.\n");		
		frag_count = best_fit_count_extfrag(16384);
		printf("Best fit external fragment count (all) = %d\n",frag_count);

	} else {
		//worst fit		
		for (i = 0; i < 120; i++){ 
			alloc_size[i] = rand() % 95 + 20;
		}
		for (i = 0; i < 100; i++) { 
			realloc_size[i] = rand() % 65 + 20;
		}

		worst_fit_memory_init(16384);						//initialize 16k
		
		//allocate 120 blocks
		for(i = 0; i < 120; i++){
			alloc_addr[i] = worst_fit_alloc(alloc_size[i]);
		}

		printf("Allocated 120 blocks.\n");
		frag_count = worst_fit_count_extfrag(135);		
		printf("Worst fit external fragment count ( < 135 ) = %d\n",frag_count);
		
		//deallocate 60 blocks
		for(i = 0; i < 60; i++){
			void *de_addr = alloc_addr[alloc_size[i]];
			worst_fit_dealloc(de_addr);
		}

		printf("Deallocated 60 blocks.\n");
		frag_count = worst_fit_count_extfrag(135);
		printf("Worst fit external fragment count ( < 135 ) = %d\n",frag_count);

		//reallocate 50 blocks
		for(i = 0; i < 50; i++){
			realloc_addr[i] = worst_fit_alloc(realloc_size[i]);
		}

		printf("Reallocated 50 blocks.\n");		
		frag_count = worst_fit_count_extfrag(16384);
		printf("Worst fit external fragment count (all) = %d\n",frag_count);
		
		//reallocate 50 blocks
		for (i = 50; i < 100; i++) {
			realloc_addr[i] = worst_fit_alloc(realloc_size[i]);
		}
		printf("Reallocated 100 blocks.\n");		
		frag_count = worst_fit_count_extfrag(16384);
		printf("Worst fit external fragment count (all) = %d\n",frag_count);
	}
	return 0;
}