
#include "mynew.h"

using namespace std;

class IntHashTable //corresponds with disk[]
{

	private:

		int* array = new int[100000];

		int currentSize, modded, currentPos;
	
	public:
//		IntHashTable(unsigned size):array(size){ makeEmpty(); }

		void makeEmpty()
		{
			currentSize = 0;
			for(int i = 0; i < 100000; i++)
			array[i] = 0;
		}

		void insert(int next, int index)
		{
			modded = index % 100000;	
			cout << "check if duplicate" << endl;
			if(find(next)!= -1)
				remove(getFound());

			while ( array[modded] != 0)
			{
				modded++;
				if( modded >= 100000)
					modded -= 100000;
			}

			array[modded] = next;
		}
		
		int getInsert() { return modded;}

		int getFound() {return currentPos;}

		void remove(int index)
		{
			if( array[index] != 0)
				array[index] = 0;
		}
		
		int find(int next)
		{

			currentPos = next % 100000;
			while( (array[currentPos] != next)){

				currentPos ++;
				if( currentPos >= 100000)
					currentPos -= 100000;
				if( array[currentPos] == 0)
					cout << "return -1" << endl;
                                	return -1;
			}
			cout << "find " << currentPos << endl;		

			return currentPos;

		}

};