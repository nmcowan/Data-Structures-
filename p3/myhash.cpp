
#include "myhash.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) : array(size)
{
	makeEmpty();

}

bool  HashTable::isActive(int currentPos)
{
	return array[currentPos] != NULL;
}


HashTable::~HashTable()
{
	for(int i = 0; i < array.size(); i++){
		if(isActive(i))
			delete (array[i]);
	}
}
	
void HashTable::makeEmpty()
{
	currentSize = 0;
	for(int i = 0; i < array.size(); i++)
		array[i] = NULL;
}

void HashTable::insert(const DiskBlock & currentBlock, int index)
{
	if(isActive(index))
		return;

	array[index] = new DiskBlock(currentBlock);
}

	
void HashTable::remove(int index)
{
	if( isActive(index)){
		delete array[index];

}

DiskBlock* HashTable::find(int index) const
{
	if(isActive(index))
		return array[index];
}