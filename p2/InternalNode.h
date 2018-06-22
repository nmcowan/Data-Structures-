#ifndef InternalNodeH
  #define InternalNodeH

#include "BTreeNode.h"

class InternalNode:public BTreeNode
{
  int internalSize;
  BTreeNode **children;
  int *keys;
public:
  InternalNode(int ISize, int LSize, InternalNode *p,
    BTreeNode *left, BTreeNode *right);
  int getMinimum()const;
  InternalNode* insert(int value); // returns pointer to new InternalNode
    // if it splits else NULL
  void insert(BTreeNode *oldRoot, BTreeNode *node2); // if root splits use this
  void insert(BTreeNode *newNode); // from a sibling
  void print(Queue <BTreeNode*> &queue);
InternalNode* split(BTreeNode *last);
void resetMin(const BTreeNode* child);
BTreeNode* newpoint(BTreeNode *ptr, int pos);
void addtothis(BTreeNode *ptr, int pos);
void addtoright(BTreeNode *ptr,BTreeNode *last);
void addtoleft(BTreeNode *last);
}; // InternalNode class

#endif
