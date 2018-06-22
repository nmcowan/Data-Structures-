
#include "mynew.h"


using namespace std;

class IndexHashTable //corresponds with disk[]
{

	private:

		int array[500000];
		int reverse[500000];

		int currentSize, modded, currentPos, finalValue, check, tempValue;
	
	public:
		IndexHashTable()
		{

			currentSize = 0;
			modded = 0;
			currentPos = 0;
			finalValue = 0;
			check = 0;
			tempValue = 0;
		} 

		void insert(int originalIndex, int newLocation)
		{
			
			array[originalIndex] = newLocation;
			reverse[newLocation] = originalIndex;
			if(reverse[originalIndex] != 0){
				tempValue = reverse[originalIndex];
				array[tempValue] = newLocation;
				reverse[originalIndex] = 0;
				reverse[newLocation] = tempValue;
			}		
			
		}

		void remove(int index)
		{
			if( array[index] != 0)
				array[index] = 0;
		}
		
		int find(int originalIndex)
		{
			return array[originalIndex];
			
		}

};