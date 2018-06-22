#include <iostream>
#include "StackLi.h" 

using namespace std;


class LongInt
{
 
	public: 

    LongInt operator+(LongInt& c);
	friend istream& operator>>(istream& input, LongInt& int1);
    friend ostream& operator<<(ostream& output, LongInt& final);	 
    StackLi<int>& getInfo();


	private:
		
	int temp;
	StackLi<int> ls;

};

