#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addleft(int value, int end)
{

	int valInt = values[0];
  leftSibling->insert(valInt);
	int minCount = count -1;

	
  for(int index = 0; index < minCount; index++)
    values[index] = values[index + 1];

  values[count - 1] = end;

	if(parent)
	    parent->resetMin(this);
} 
void LeafNode::addright(int value, int end)
{
  rightSibling->insert(end);
	
	int valueInt = values[0];

  if(parent && value == valueInt)
    parent->resetMin(this);
} 

void LeafNode::addthis(int value)
{
  int i;
  for(i = count - 1; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(parent && value == values[0])
    parent->resetMin(this);
} 

void LeafNode::addValue(int value, int &end)
{
  int i;

  if(value > values[count - 1])
    end = value;
  else
  {
    end = values[count - 1];

    for(i = count - 2; i >= 0 && values[i] > value; i--)
      values[i + 1] = values[i];

    values[i + 1] = value;
  }
} 

int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int end;

  if(count < leafSize)
  {
    addthis(value);
    return NULL;
  } 

  addValue(value, end);

	//This full. Look Left
  if(leftSibling && leftSibling->getCount() < leafSize)
  {
    addleft(value, end);
    return NULL;
  }
  else if(rightSibling && rightSibling->getCount() < leafSize)
	//Left Leaf Full. Look Right
    {
      addright(value, end);
      return NULL;
    }
    else 
	//Both leaves full. Need to split
      return split(value, end);
}  

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()



LeafNode* LeafNode::split(int value, int end)
{
  LeafNode *splitP = new LeafNode(leafSize, parent, this, rightSibling);

	//First we check if there exists a right sibling. 
	//If so, we need to set the left sibling
  if(rightSibling)
    rightSibling->setLeftSibling(splitP);

 	 rightSibling = splitP;

int leafplus = leafSize +1;

  for(int i = leafplus / 2; i < leafSize; i++)
    splitP->values[splitP->count++] = values[i];

  splitP->values[splitP->count++] = end;
  count = (leafplus) / 2;

	int valInt = values[0];

  if(parent && value == valInt)
    parent->resetMin(this);
  return splitP;
} 

