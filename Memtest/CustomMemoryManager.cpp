#include "CustomMemoryManager.h"

size_t CustomMemoryManager::currentMaxSize;
size_t CustomMemoryManager::currentMinSize;

MemoryBlockInfo* CustomMemoryManager::currentBlock;
void* CustomMemoryManager::startingAddress;

void CustomMemoryManager::init()
{
	startingAddress = malloc(MAXMEMORYSIZE);
	currentBlock = reinterpret_cast<MemoryBlockInfo*>(startingAddress);
	currentMaxSize = MAXMEMORYSIZE;
	currentMinSize = MAXMEMORYSIZE;
	currentBlock->memSize = MAXMEMORYSIZE;
	currentBlock->nextMem = 0;
}

void CustomMemoryManager::init(size_t maxMemory)
{
	if (maxMemory < sizeof(MemoryBlockInfo))
	{
		maxMemory = sizeof(MemoryBlockInfo);
	}
	else if (maxMemory % sizeof(size_t) != 0)
	{
		maxMemory += sizeof(size_t)-(maxMemory % sizeof(size_t));
	}
	startingAddress = malloc(maxMemory);
	currentBlock = reinterpret_cast<MemoryBlockInfo*>(startingAddress);
	currentMaxSize = maxMemory;
	currentMinSize = maxMemory;
	currentBlock->memSize = maxMemory;
	currentBlock->nextMem = 0;
}

void CustomMemoryManager::shutdown()
{
	free(startingAddress);
}

void* operator new(size_t size)
{
	if (size < sizeof(size_t))
	{
		size = sizeof(size_t);
	}

	MemoryBlockInfo* temp = CustomMemoryManager::bestFit(size);

	if (temp == NULL)
	{
		throw std::bad_alloc::bad_alloc();
	}
	
	CustomMemoryManager::newedCurrentBlock(temp, size);
	CustomMemoryManager::addSlot(temp, size);
	CustomMemoryManager::updateSize();
	
	char* ret = reinterpret_cast<char*>(temp);

	return ret + sizeof(size_t);
}

void CustomMemoryManager::newedCurrentBlock(MemoryBlockInfo* victim, size_t sizeOfObj)
{
	MemoryBlockInfo* temp = currentBlock;

	MemoryBlockInfo* tempBefore = NULL;
	MemoryBlockInfo* tempAfter = NULL;

	if (currentBlock->nextMem != 0)
	{
		tempAfter = currentBlock->nextMem;
	}

	while (temp && temp != victim)
	{
		tempBefore = temp;
		temp = temp->nextMem;
		if (temp->nextMem != 0)
		{
			tempAfter = temp->nextMem;
		}
		else
		{
			tempAfter = NULL;
		}
	}

	if (tempBefore == NULL && tempAfter == NULL)
	{
		currentBlock = NULL;
	}
	else if (tempBefore == NULL && tempAfter != NULL)
	{
		currentBlock = tempAfter;
	}
	else if (tempBefore != NULL && tempAfter != NULL)
	{
		tempBefore->nextMem = tempAfter;
	}
	else if (tempBefore != NULL && tempAfter == NULL)
	{
		tempBefore->nextMem = NULL;
	}
}

void CustomMemoryManager::addSlot(MemoryBlockInfo* overwrittenSlot, size_t sizeOfObj)
{	
	if (overwrittenSlot->memSize - (sizeOfObj + sizeof(size_t)) >= sizeof(MemoryBlockInfo))
	{
		char* temp = reinterpret_cast<char*>(overwrittenSlot);
		temp = temp + (sizeOfObj + sizeof(size_t));

		MemoryBlockInfo* newBlock = reinterpret_cast<MemoryBlockInfo*>(temp);
		newBlock->memSize = overwrittenSlot->memSize - (sizeOfObj + sizeof(size_t));
		newBlock->nextMem = 0;

		if (currentBlock == NULL)
		{
			currentBlock = newBlock;
		}
		else if (currentBlock->nextMem == NULL)
		{
			currentBlock->nextMem = newBlock;
		}
		else
		{
			for (MemoryBlockInfo* i = currentBlock; i != 0; i = i->nextMem)
			{
				if (i->nextMem == NULL)
				{
					i->nextMem = newBlock;
					break;
				}
			}
		}

		overwrittenSlot->memSize = sizeOfObj + sizeof(size_t);
	}
}

void operator delete(void* victim)
{
	char* temp = reinterpret_cast<char*>(victim)-sizeof(size_t);

	MemoryBlockInfo* memTemp = reinterpret_cast<MemoryBlockInfo*>(temp);

	CustomMemoryManager::deletedCurrentBlock(memTemp);
	CustomMemoryManager::coalesceFront(memTemp);
	CustomMemoryManager::coalesceBack(memTemp);
	CustomMemoryManager::updateSize();
#ifdef _DEBUG
	CustomMemoryManager::clean();
#endif
}

void CustomMemoryManager::deletedCurrentBlock(MemoryBlockInfo* victim)
{
	if (currentBlock == NULL)
	{
		currentBlock = victim;
		victim->nextMem = 0;
	}
	else
	{
		for (MemoryBlockInfo* i = currentBlock; i != 0; i = i->nextMem)
		{
			if (i->nextMem == NULL)
			{
				i->nextMem = victim;
				victim->nextMem = 0;
				return;
			}
		}
	}
}

void CustomMemoryManager::coalesceFront(MemoryBlockInfo* victim)
{
	MemoryBlockInfo* temp = currentBlock;

	char* test = reinterpret_cast<char*>(victim)+victim->memSize;

	while (temp)
	{
		if (temp == reinterpret_cast<MemoryBlockInfo*>(test))
		{
			MemoryBlockInfo* temps = currentBlock;

			MemoryBlockInfo* tempBefore = NULL;
			MemoryBlockInfo* tempAfter = NULL;

			if (temps->nextMem != 0)
			{
				tempAfter = temps->nextMem;
			}

			while (temps && temp != temps)
			{
				tempBefore = temps;
				temps = temps->nextMem;
				if (temps->nextMem != 0)
				{
					tempAfter = temps->nextMem;
				}
				else
				{
					tempAfter = NULL;
				}
			}

			if (tempBefore == NULL && tempAfter == NULL)
			{
				currentBlock = victim;
			}
			else if (tempBefore != NULL && tempAfter == NULL)
			{
				if (tempBefore == victim)
				{
					victim->nextMem = NULL;
				}
				else if (victim->nextMem == tempBefore)
				{
					tempBefore = NULL;
				}
				else
				{
					tempBefore->nextMem = victim;
				}
			}
			else if (tempBefore != NULL && tempAfter != NULL)
			{
				if (tempBefore == victim)
				{
					victim->nextMem = tempAfter;
				}
				else if (tempAfter == victim)
				{
					tempBefore->nextMem = victim;
				}
				else
				{
					tempBefore->nextMem = victim;
					victim->nextMem = tempAfter;
				}
			}

			else if (tempBefore == NULL && tempAfter != NULL)
			{
				if (tempAfter == victim)
				{
					currentBlock = victim;
				}
				else
				{
					currentBlock = tempAfter;
				}
			}

			//if (victim-> nextMem == victim)
			//{
			//	victim->nextMem = NULL;
			//}

			victim->memSize = victim->memSize + temp->memSize;
			return;
		}

		temp = temp->nextMem;
	}
}

void CustomMemoryManager::coalesceBack(MemoryBlockInfo* victim)
{
	MemoryBlockInfo* temp = currentBlock;

	while (temp)
	{
		char* test = reinterpret_cast<char*>(temp) + temp->memSize;

		if (reinterpret_cast<MemoryBlockInfo*>(test) == victim)
		{
			MemoryBlockInfo* temps = currentBlock;

			MemoryBlockInfo* tempBefore = NULL;
			MemoryBlockInfo* tempAfter = NULL;

			if (temps->nextMem != NULL)
			{
				tempAfter = temps->nextMem;
			}

			while (temps && temps != victim)
			{
				tempBefore = temps;
				temps = temps->nextMem;
				if (temps->nextMem != 0)
				{
					tempAfter = temps->nextMem;
				}
				else
				{
					tempAfter = NULL;
				}
			}

			if (tempBefore == NULL && tempAfter == NULL)
			{
				currentBlock = temp;
			}
			else if (tempBefore != NULL && tempAfter == NULL)
			{
				if (tempBefore == temp)
				{
					temp->nextMem = NULL;
				}
				else if (temp->nextMem == tempBefore)
				{
					tempBefore->nextMem = NULL;
				}
				else
				{
					tempBefore->nextMem = temp;
				}
			}
			else if (tempBefore != NULL && tempAfter != NULL)
			{
				if (tempBefore == temp)
				{
					temp->nextMem = tempAfter;
				}
				else if (tempAfter == temp)
				{
					tempBefore->nextMem = temp;
				}
				else
				{
					tempBefore->nextMem = temp;
					temp->nextMem = tempAfter;
				}
			}
			else if (tempBefore == NULL && tempAfter != NULL)
			{
				if (tempAfter == temp)
				{
					currentBlock = temp;
				}
				else
				{
					currentBlock = temp->nextMem;
				}
			}

			//if (currentBlock = temp->nextMem)
			//{
			//	//if (currentBlock->nextMem != 0)
			//	temp->nextMem = NULL;
			//}

			temp->memSize = temp->memSize + victim->memSize;
			return;
		}

		temp = temp->nextMem;
	}
}

MemoryBlockInfo* CustomMemoryManager::bestFit(size_t size)
{
	MemoryBlockInfo* temp = NULL;

	size += sizeof(size_t);

	if (size < currentMinSize)
	{
		size = currentMinSize;
	}

	if (size > currentMaxSize)
	{
		return temp;
	}

	for (size_t i = size; i <= currentMaxSize; i += sizeof(size_t))
	{
		temp = currentBlock;

		while (temp)
		{
			if (temp->memSize >= size)
			{
				return temp;
			}
			temp = temp->nextMem;
		}
	}

	return temp;
}

void CustomMemoryManager::updateSize()
{
	size_t theSize = 0;

	MemoryBlockInfo* temp = currentBlock;

	while (temp)
	{
		if (temp->memSize > theSize)
		{
			theSize = temp->memSize;
		}

		temp = temp->nextMem;
	}

	currentMaxSize = theSize;
	temp = currentBlock;

	while (temp)
	{
		if (temp->memSize <= theSize)
		{
			theSize = temp->memSize;
		}

		temp = temp->nextMem;
	}

	currentMinSize = theSize;
}

void CustomMemoryManager::clean()
{
	MemoryBlockInfo* temp = currentBlock;

	while (temp)
	{
		size_t a = temp->memSize - sizeof(MemoryBlockInfo);
		a = a / sizeof(size_t);

		for (size_t i = 0; i < a; i++)
		{
			size_t* victim = (reinterpret_cast<size_t*>(temp)) + (sizeof(MemoryBlockInfo) / sizeof(size_t));
			victim += i;
			*victim = 0xcdcdcdcd;
		}

		temp = temp->nextMem;
	}
}