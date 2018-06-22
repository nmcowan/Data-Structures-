#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


void InternalNode::addtoleft(BTreeNode *last){

	((InternalNode*)leftSibling)->insert(children[0]);

  for(int i = 0; i < count - 1; i++)
  {
    children[i] = children[i + 1];
    keys[i] = keys[i + 1];
  }

  children[count - 1] = last;
  keys[count - 1] = last->getMinimum();
  last->setParent(this);
  if(parent)
    parent->resetMin(this);}


void InternalNode::addtoright(BTreeNode *ptr, BTreeNode *last){

	((InternalNode*) rightSibling)->insert(last);
  if(ptr == children[0] && parent)
    parent->resetMin(this);

}

void InternalNode::addtothis(BTreeNode *ptr, int pos){
	for(int in = count -1; in >=pos; in--){

		children[in+1] = children[in];
		keys[in+1] = keys[in];
	}

	children[pos] = ptr;
	keys[pos] = ptr->getMinimum();
	count++;
	ptr->setParent(this);

	if(pos == 0 && parent){
		parent->resetMin(this);
	}

}

BTreeNode* InternalNode::newpoint(BTreeNode *ptr, int pos){

	if(pos == internalSize)
		return ptr;

	BTreeNode *last = children[count -1];


	for( int index = count -2; index >=pos; index--){
		children[index+1] = children[index];
		keys[index+1] = keys[index];
	}

	children[pos] = ptr;
	keys[pos] = ptr->getMinimum();
	ptr->setParent(this);
	return last;
}


InternalNode* InternalNode::insert(int value)
{
	int posIndex;
	for(posIndex = count -1; posIndex > 0 && (keys[posIndex] > value); posIndex--);

	BTreeNode *last;
	BTreeNode *btnPtr = children[posIndex]->insert(value);
	if(!btnPtr){
		return NULL;
	}


	if(count < internalSize){
		addtothis(btnPtr,posIndex+1);
		return NULL;
	}


	last = newpoint(btnPtr,posIndex + 1);

	if(leftSibling && leftSibling->getCount() < internalSize)
	{

		addtoleft(last);
		return NULL;
	}
	
	else 
		if(rightSibling && rightSibling->getCount() < internalSize)
		{
			addtoright(btnPtr,last);
			return NULL;
		}

	else
		return split(last);
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
	children[1] = node2; children[0] = oldRoot;

	keys[1] = node2->getMinimum(); keys[0] = oldRoot->getMinimum();

	count = 1;
	count++;

	//Set Left and Right Siblings
	children[0]->setLeftSibling(NULL);
	children[1]->setLeftSibling(children[0]);

	children[0]->setRightSibling(children[1]);
	children[1]->setRightSibling(NULL);

	bool oldroot1 = true;

	if(oldroot1){

		oldRoot->setParent(this);
		node2->setParent(this);
	}

} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
	  int pos;

  if(newNode->getMinimum() <= keys[0]) // from left sibling
    pos = 0;
  else // from right sibling
    pos = count;

  addtothis(newNode, pos);


} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()

void InternalNode::resetMin(const BTreeNode* child){

	
  for(int i = 0; i < count; i++)
    if(children[i] == child)
    {
      keys[i] = children[i]->getMinimum();
      if(i == 0 && parent)
        parent->resetMin(this);
      break;
    }
}

InternalNode* InternalNode::split(BTreeNode *last)
{
  InternalNode *newptr = new InternalNode(internalSize, leafSize,
    parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(newptr);

  rightSibling = newptr;

  for(int i = (internalSize + 1) / 2; i < internalSize; i++)
  {
    newptr->children[newptr->count] = children[i];
    newptr->keys[newptr->count++] = keys[i];
    children[i]->setParent(newptr);
  }

  newptr->children[newptr->count] = last;
  newptr->keys[newptr->count++] = last->getMinimum();
  last->setParent(newptr);
  count = (internalSize + 1) / 2;
  return newptr;
}




