#pragma once
#include <iostream>
//#include "node.h"


template <class T>
class BNode
{

private:


public:
	T data;
	bool red;
	bool black;
	bool parent;
	BNode <T> *pParent;
	BNode <T> *pLeft;
	BNode <T> *pRight;


	BNode()
	{
		pParent = nullptr;
		pLeft = nullptr;
		pRight = nullptr;

	}

	BNode(T newItem)
	{
		data = newItem;
		pParent = nullptr;
		pLeft = nullptr;
		pRight = nullptr;
	}

	//friend std::ostream& operator<<(std::ostream & out, const BNode <T> *rhs);
	//   BNode operator << (const BNode <T> *thing);          
};

/******************************************
 * COPY
 *Copies one binary Tree into another
*****************************************/
template<class T>
BNode <T> * copyBTree(const BNode<T> *source)
{
	if (source == nullptr)
	{
		return nullptr;
	}

	BNode<T> *destination = new BNode<T>(source->data);


	destination->pLeft = copyBTree(source->pLeft);
	if (destination->pLeft != nullptr)
	{
		destination->pLeft->pParent = destination;
	}

	destination->pRight = copyBTree(source->pRight);

	if (destination->pRight != nullptr)
	{
		destination->pRight->pParent = destination;
	}

	return destination;

}

/*********************************************
 *DELETE
 * deletes each node of the binary tree
********************************************/
template <class T>
void deleteBTree(BNode <T> *&bnode)
{
	if (bnode == nullptr)
	{
		return;
	}

	deleteBTree(bnode->pLeft);
	deleteBTree(bnode->pRight);

	delete bnode;

	bnode = nullptr;
	if (bnode == NULL)
	{
		std::cerr << "its null now\n";
	}
}


template <class T>
void displayLVR(const BNode <T> * pHead)
{
	if (pHead == nullptr)
	{
		return;
	}

	displayLVR(pHead->pLeft);      // L    
	std::cout << pHead->data << ' ';      // V    
	displayLVR(pHead->pRight);     // R 
}

/********************
* INPUT OPERATOR
*******************/
template <class T>
inline std::ostream& operator << (std::ostream & out, const BNode <T> & rhs)
{
	//out << "we made it in\n";

	displayLVR(&rhs);

	/*out << rhs->pLeft;
	out << rhs->data;
	out << rhs->pRight;*/
	return out;
}
/*
template<class T>
BNode <T> :: operator << (const BNode<T> * thing)
{
   std::cout << "did we even get to this point\n";
   displayLVR(thing);
   return *this;
   }*/



   /***********************************************************************
	* ADD LEFT/RIGHTs:
	* Takes a pointer to a Node, and gives it a child, to the left or right
	* specified in the name of the function. one version is passed a T item
	* and makes a new node, the other is passed a node that is already made
	* and simply attaches it in the correct location
	**********************************************************************/
	/*******************************************************************
	 *ADDLEFT, TEMPLATE
	 * This adsds a left hand child with the passed template data
	 ********************************************************************/
template <class T>
void addLeft(BNode <T> *pNode, const T & t)
{
	BNode <T> *itemNode = new BNode<T>(t); //making a new node

	//and now we just set the pointers
	pNode->pLeft = itemNode; //the referenced one points forward to the new one.

	//the new one needs to point to the passed one
	itemNode->pParent = pNode; //the new one points backward to the referenced one
}

/*******************************************************************
 *ADDLEFT, NODE
 * This adsds a Left hand child with the passed Node pointer
 ********************************************************************/
template <class T>
void addLeft(BNode <T> *pNode, BNode <T> *pChild)
{
	if (pChild == nullptr)
	{
		pNode->pLeft = nullptr;
		return;
	}
	//and now we just set the pointers
	pNode->pLeft = pChild; //the referenced one points forward to the new one.

	//the new one needs to point to the passed one
	pChild->pParent = pNode; //the new one points backward to the referenced one
}


/*******************************************************************
 *ADDRIGHT, TEMPLATE
 * This adsds a right hand child with the passed template data
 ********************************************************************/
template <class T>
void addRight(BNode <T> *pNode, const T & t)
{
	BNode <T> *itemNode = new BNode<T>(t); //making a new node

	//and now we just set the pointers
	pNode->pRight = itemNode; //the referenced one points forward to the new one.

	//the new one needs to point to the passed one
	itemNode->pParent = pNode; //the new one points backward to the referenced one
}

/*******************************************************************
 *ADDRIGHT, NODE
 * This adsds a right hand child with the passed Node pointer
 ********************************************************************/
template <class T>
void addRight(BNode <T> *pNode, BNode <T> *pChild)
{
	if (pChild == nullptr)
	{
		pNode->pLeft = nullptr;
		return;
	}
	//and now we just set the pointers
	pNode->pRight = pChild; //the referenced one points forward to the new one.

	//the new one needs to point to the passed one
	pChild->pParent = pNode; //the new one points backward to the referenced one
}

/**************************************************
 * SIZE
 * returns an int of how many nodes there are in the tree
 *****************************************************/
template <class T>
int sizeBTree(BNode <T> *pNode)
{
	if (pNode == nullptr)
		return 0;
	else
		return (sizeBTree(pNode->pLeft) + 1 + sizeBTree(pNode->pRight));
}
