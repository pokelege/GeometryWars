#ifndef CUSTOMMEMORYMANAGER
#define CUSTOMMEMORYMANAGER
#include <cstdlib>
#include <iostream>
#include "MemoryBlockInfo.h"

#define MAXMEMORYSIZE 32
class CustomMemoryManager
{
	static size_t currentMaxSize;
	static size_t currentMinSize;
	static MemoryBlockInfo* currentBlock;
	static void* startingAddress;

	static void newedCurrentBlock(MemoryBlockInfo* victim, size_t sizeOfObj);
	static void addSlot(MemoryBlockInfo* overwrittenSlot, size_t sizeOfObj);

	static void deletedCurrentBlock(MemoryBlockInfo* victim);
	static void coalesceFront(MemoryBlockInfo* victim);
	static void coalesceBack(MemoryBlockInfo* victim);

	static void updateSize();
	static MemoryBlockInfo* bestFit(size_t size);
	static void clean();


	friend void* operator new(size_t size);
	friend void operator delete(void* victim);

public:
	static void init();
	static void init(size_t maxMemory);

	static void shutdown();
};

void* operator new(size_t size);
void operator delete(void* victim);

#endif