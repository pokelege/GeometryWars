#ifndef MEMORYBLOCKINFO
#define MEMORYBLOCKINFO

struct MemoryBlockInfo
{
	size_t memSize;
	MemoryBlockInfo* nextMem;
};

#endif