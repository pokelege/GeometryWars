#include <iostream>
using namespace std;
#include "CustomMemoryManager.h"

struct BadAllignedStruct
{
	char a;
	__int64 b;
	float c;
	bool d;
	__int16 e;
};

int main()
{
	CustomMemoryManager::init(64);
	char* z = new char;
	*z = 'b';
	int* a = new int;
	*a = 1;
	int* b = new int;
	*b = 2;
	int* c = new int;
	*c = 1;
	
	__int64* v = new __int64;
	*v = 1000;

	delete b;
	delete c;

	__int64* d = new __int64;
	*d = 10;
	int* ch = new int;
	*ch = 'ch';
	delete a;
	delete v;
	delete d;
	delete z;

	BadAllignedStruct* f = new BadAllignedStruct;
	f->a = 1;
	f->b = 2;
	f->c = 3;
	f->d = false;
	f->e = 5;

	CustomMemoryManager::shutdown();
	return 0;
}