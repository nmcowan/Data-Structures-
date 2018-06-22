#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "CPUTimer.h"
#include "LinkedList.h"
#include "CursorList.h"
#include "StackAr.h"
#include "StackLi.h"
#include "QueueAr.h"
#include "SkipList.h"

vector<CursorNode <int> > cursorSpace(500001);

using namespace std;

int getChoice()
{
  cout << "      ADT Menu" << endl;
  cout << "0. Quit" << endl;
  cout << "1. LinkedList" << endl;
  cout << "2. CursorList" << endl;
  cout << "3. StackAr" << endl;
  cout << "4. StackLi" << endl;
  cout << "5. QueueAr" << endl;
  cout << "6. SkipList" << endl;
  cout << "Your choice >> ";

  int choice;
  cin >> choice;

  return choice;
} 


void Runlist(char *file)
{
  List<int> list;
  ListItr<int> listIt = list.zeroth();
  ifstream in(file);
  char com, i[512];
  int num;
  in.getline(i, 512);
  while(in >> com >> num)
  {
    if (com == 'i')
    {
      list.insert(num, listIt);
    }
    else
    {
      list.remove(num);
    }
  }

} 

void RunCursorlist(char *file)
{
  CursorList<int> clist(cursorSpace);
  CursorListItr<int> CursorlistItr = clist.zeroth();
  ifstream in(file);
  char com, i[512];
  int num;
  in.getline(i,512);

  while(in >> com >> num)
  {
    if (com == 'i')
    {
      clist.insert(num, CursorlistItr);
    }
    else
    {
      clist.remove(num);
    }
  }
  
}


void RunStackAr(char *filename)
{
  StackAr<int> s(500000);
  ifstream inf(filename);
  char comment, yo[512];
  int value;
  inf.getline(yo,512);

  while(inf >> comment >> value)
  {
    if (comment == 'i')
    {
      s.push(value);
    }
    else
    {
      s.pop();
    }

  }
} //RunStackAr()

void RunStackLi(char* filename)
{
  StackLi<int> s;
  ifstream inf(filename);
  char comment, yo[512];
  int value;
  inf.getline(yo,512);

  while(inf >> comment >> value)
  {
    if (comment == 'i')
    {
      s.push(value);
    }
    else
    {
      s.pop();
    }

  }
} //RunStackLi()

void RunQueueAr(char *file)
{
  Queue <int> q(2500000);
  ifstream in(file);
  char com, i[512];
  int num;
  in.getline(i,512);

  while(in >> com >> num)
  {
    if (com == 'i')
    {
      q.enqueue(num);
    }
    else
    {
      q.dequeue();
    }

  }

}

void RunSkipList (char *file)
{
  SkipList<int> list(0,2500001);
  ifstream in(file);
  char com, i[512];
  int num;
  in.getline(i,512);

  while(in >> com >> num)
  {
    if (com == 'i')
    {
      list.insert(num);
    }
    else
    {
      list.deleteNode(num);
    }

  }

} 



int main()
{
  int choice;
  char filename[256];
  CPUTimer ct;

    cout << "Filename >> " ;
    cin >> filename;

  
  do
  {

    //cout << endl << endl;
    choice = getChoice();
    ct.reset();

    switch (choice)
    {
      case 1: Runlist(filename); break;
      case 2: RunCursorlist(filename); break;
      case 3: RunStackAr(filename); break;
      case 4: RunStackLi(filename); break;
      case 5: RunQueueAr(filename); break;
      case 6: RunSkipList(filename); break;
      
    } 

    cout << "CPU time: " << ct.cur_CPUTime() << endl;
  } while(choice > 0);

} //main()