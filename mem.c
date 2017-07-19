/**
 * @file memory.c
 * @brief: ECE254 Lab: memory allocation algorithm comparison template file
 * @author: 
 * @date: 2015-11-20
 */

/* includes */
#include <stdio.h> 
#include <stdlib.h> 
#include "mem.h"
#include <stdbool.h>


/* defines */

/*typedef struct memNode{
	
	bool isAllocated;
	size_t memAllocatedSize;
	struct memNode* next;
	struct memNode* previous;

}memNode;*/

struct memNode *memoryBlock;

/* global varaiables */
size_t totalFreeMemory;
struct memNode *allocNode;
struct memNode *iterator;
size_t difference;
int extfrag;
char * startOfMem;

/* Functions */
int coalescence(memNode* deallocNode){
	if (!deallocNode->next && !deallocNode->previous) {
		totalFreeMemory += deallocNode->memAllocatedSize;
		return 0;
	}
	
	if (!deallocNode->previous && deallocNode->next){
		printf("right there\n");

		if(!deallocNode->next->isAllocated){
			printf("this\n");
			deallocNode->memAllocatedSize += deallocNode->next->memAllocatedSize + sizeof(memNode); 
			deallocNode->next = deallocNode->next->next;


			totalFreeMemory += deallocNode->memAllocatedSize + sizeof(memNode);
		}
		
		return 0;
	} else if(deallocNode->previous && !deallocNode->next) {
		

		if (!deallocNode-> previous->isAllocated){

			iterator = deallocNode->previous;
			iterator->next = deallocNode->next;
			iterator->memAllocatedSize += deallocNode->memAllocatedSize + sizeof(memNode); 
		
			totalFreeMemory += deallocNode->memAllocatedSize + sizeof(memNode);
		}
		return 0;
	}
	
	
	if (deallocNode-> previous->isAllocated == deallocNode->next->isAllocated){
		if (!deallocNode->previous->isAllocated) {
			
			iterator = deallocNode->previous;
			iterator->next = deallocNode->next->next;
			iterator->memAllocatedSize += deallocNode->memAllocatedSize + deallocNode->next->memAllocatedSize + 2*sizeof(memNode); 
			
			totalFreeMemory += deallocNode->memAllocatedSize + deallocNode->next->memAllocatedSize + 2*sizeof(memNode);
		}
	}else if (!deallocNode-> previous->isAllocated){

		iterator = deallocNode->previous;
		iterator->next = deallocNode->next;
		iterator->memAllocatedSize += deallocNode->memAllocatedSize + sizeof(memNode); 
		
		totalFreeMemory += deallocNode->memAllocatedSize + sizeof(memNode);
		
	}else if(!deallocNode->next->isAllocated){
		deallocNode->memAllocatedSize += deallocNode->next->memAllocatedSize + sizeof(memNode); 
		deallocNode->next = deallocNode->next->next;
		
		totalFreeMemory += deallocNode->memAllocatedSize + sizeof(memNode);

	} else{
		totalFreeMemory += deallocNode->memAllocatedSize;
	}
	
}

int memInit(size_t size){
	if (size < (sizeof(memNode)+ sizeof(totalFreeMemory) + sizeof(iterator) + sizeof (difference) + sizeof(extfrag)+ sizeof(startOfMem))){
		return -1;
	}
	
	size = size + size%4;

	startOfMem = malloc(size); 
	startOfMem += sizeof(memNode)+ sizeof(totalFreeMemory) + sizeof(iterator) + sizeof (difference) + sizeof(extfrag)+ sizeof(startOfMem);
	size_t temp = sizeof(memNode)+ sizeof(totalFreeMemory) + sizeof(iterator) + sizeof (difference) + sizeof(extfrag)+ sizeof(startOfMem);
		
	memoryBlock = (memNode*)startOfMem;
	memoryBlock->isAllocated = false;
	memoryBlock->memAllocatedSize = size - sizeof(memNode) - sizeof(totalFreeMemory) - sizeof(iterator) - sizeof (difference) - sizeof(extfrag)-sizeof(startOfMem);
	memoryBlock->next = NULL;
	memoryBlock->previous = NULL;

	totalFreeMemory = size - sizeof(memNode) - sizeof(totalFreeMemory) - sizeof(iterator) - sizeof (difference) - sizeof(extfrag)- sizeof(startOfMem);
	extfrag = 0;
	return 0;
}

/* memory initializer */
int best_fit_memory_init(size_t size)
{
	return memInit(size);
}

int worst_fit_memory_init(size_t size)
{
	return memInit(size);
}

/* memory allocators */

void printLinkedList() {
	printf("NEW CALL TO PRINT\n");
	if (!memoryBlock){
		printf ("address of node is NULL\n");
		return;
	}
	iterator = memoryBlock;
	while (iterator) {
		printf ("Start address: %p\nisAllocated: %d\nsize: %d\n------------------\n",iterator, iterator->isAllocated, iterator->memAllocatedSize);
		iterator = iterator->next;
	}
	return;
}

// TODO there's a bug with worst_fit_alloc ending up with a null allocNode
void* mem_alloc(size_t size, int flag) {
  printf("totalFreeMemory: %d\n", totalFreeMemory);
	if (size > totalFreeMemory){
		return NULL;
	}
	size += size%4;
	
	iterator = memoryBlock;
	allocNode = NULL;
	difference = (iterator->isAllocated || (iterator->memAllocatedSize < size)) ?
    totalFreeMemory : (iterator->memAllocatedSize - size);
  while (iterator) {
    if (iterator->isAllocated) {
      iterator = iterator->next;
      continue;
    }
    // Note: hijacking extfrag as a boolean flag
    if (flag == 0) { // best fit
      extfrag = ((iterator->memAllocatedSize > size) && (iterator->memAllocatedSize - size) <= difference);
    } else {         // worst fit
      extfrag = ((iterator->memAllocatedSize > size) && (iterator->memAllocatedSize - size) >= difference);
    }
    if (extfrag) {
				difference = iterator->memAllocatedSize - size;
				allocNode = iterator;
    }
		iterator = iterator->next;
  }
	if (!allocNode) {
    if (flag == 1) {
      allocNode = memoryBlock;
    } else {
      return NULL;
    }
	}
		startOfMem = (char*)allocNode;
		
		allocNode->isAllocated = true;
		
		size_t tempSize = allocNode->memAllocatedSize;

		if (difference > sizeof(memNode)) {
			allocNode->memAllocatedSize = size;
						
			startOfMem += sizeof(memNode) + allocNode->memAllocatedSize;
			
			iterator = (memNode*)startOfMem;
		
			iterator->memAllocatedSize = tempSize - sizeof(memNode) - size;

			iterator->isAllocated = false;
			
			iterator->next =allocNode->next;
			iterator->previous = allocNode;
			allocNode->next = iterator;
			
			totalFreeMemory -= sizeof(memNode) - size;
		} else {
			totalFreeMemory -= allocNode->memAllocatedSize;
		}

	return allocNode;
}

void* best_fit_alloc(size_t size) {
  return mem_alloc(size, 0);
}

void* worst_fit_alloc(size_t size) {
  return mem_alloc(size, 1);
}

void mem_dealloc(void* ptr) {
	iterator = (memNode*) ptr;
  if (!iterator) {
    return;
  }
	iterator->isAllocated = false;
	
	coalescence(iterator);
}

/* memory de-allocator */
void best_fit_dealloc(void *ptr) {
  mem_dealloc(ptr);
}

void worst_fit_dealloc(void *ptr) {
  mem_dealloc(ptr);
}

/* memory algorithm metric utility function(s) */

/* count how many free blocks are less than the input size */ 
int best_fit_count_extfrag(size_t size)
{
	extfrag = 0;
	iterator = memoryBlock;
	while (iterator) {
		if (!iterator->isAllocated && iterator->memAllocatedSize < size){
      ++extfrag;
		}
		iterator = iterator->next;
	}
	return extfrag;
}

int worst_fit_count_extfrag(size_t size)
{
	extfrag = 0;
	iterator = memoryBlock;
	while(iterator != NULL){
		if (!iterator->isAllocated && iterator->memAllocatedSize < size){
			extfrag += 1;
		}
		iterator = iterator->next;	
	}
	// To be completed by students
	return extfrag;
}
