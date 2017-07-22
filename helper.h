#ifndef __HELPER_H
#define __HELPER_H

#include <stdbool.h>

typedef struct memNode{
	bool isAllocated;
	size_t memAllocatedSize;
	struct memNode* next;
	struct memNode* previous;
}memNode;

void* mem_alloc(size_t, int);
void mem_dealloc(void*);

void printLinkedList();

#endif  // __HELPER_H
