
#include "mynew.h"

using namespace std;

class HashTable
{
	private:
		//vector<DiskBlock*> array;
		unsigned tableSize=13250, size=0;
		int pos;

		DiskBlock** array = new DiskBlock*[13250];
		

	public:

		unsigned getCurrentSize(){ return size; }

		int getPosition() { return pos;}

		void insert(DiskBlock & currentBlock)
		{
			array[size] = new DiskBlock(currentBlock);
			size++;	
		}
		
		DiskBlock * find(unsigned index)
		{
			if(index == -1)
				return NULL;
						
                        return array[index];
			
	
		}



	
};