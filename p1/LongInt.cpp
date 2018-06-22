#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "LongInt.h"

using namespace std;

  LongInt LongInt::operator+(LongInt& c)
		{
	

			int num1,num2, sum, tempsum = 0;
			LongInt tempstack;
			while(!this->ls.isEmpty() && !c.ls.isEmpty())
			{
				num1= this->ls.top();
		 		num2 = c.ls.top();
				sum = num1 + num2 + tempsum; 
						
	 
				if(sum > 9)
				{
					tempsum = 1;
					sum = sum - 10;
					this->ls.pop();
					c.ls.pop();
					tempstack.ls.push(sum);}
				
				else 
				{
					tempsum = 0;
					this->ls.pop();
					c.ls.pop();
					tempstack.ls.push(sum);
				}
	

			}

			while(!this->ls.isEmpty())
			{
				num1 = this->ls.top();
				sum = num1 + tempsum;
				if(sum > 9) {

					tempsum = 1;
					sum = sum - 10; 
					this->ls.pop();
					tempstack.ls.push(sum);}
				else{
					tempsum = 0;
					this->ls.pop();
					tempstack.ls.push(sum);}
				}
	
			while(!c.ls.isEmpty())
			{
				num2 = c.ls.top();
				sum = num2 + tempsum;
				if(sum > 9) 
				{
					tempsum = 1;
					sum = sum - 10; 
					c.ls.pop();
					tempstack.ls.push(sum);}
	

				else{
					tempsum = 0;
					c.ls.pop();
					tempstack.ls.push(sum);}
			}
	

	

		if( tempsum == 1) 
			{
	

				(tempstack.ls).push(tempsum);
			}
	return tempstack;} 



  istream& operator>>(istream &in, LongInt &num) {
	char charstring;

	while(in.get(charstring)) {
		if(isdigit(charstring)) 
			num.getInfo().push(charstring - '0');
		if(!isdigit(in.peek())) 
			return in;
	}

	return in;
} 


ostream& operator<<(std::ostream &out, LongInt &num) {
	StackLi<int> stack = num.getInfo();

	while(!stack.isEmpty()) {
		cout << stack.topAndPop();
;
	}

	return out;
}



StackLi<int>& LongInt::getInfo() {
	return ls;
}