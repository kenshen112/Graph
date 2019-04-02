#ifndef NODE_H
#define NODE_H
#include <iostream>

template <class T>
class Node
{
  public:
   T data;
   Node <T> *pNext;
   Node <T> *pPrev;

/************************
 * Default Constructor:
 * Create a NULL object.
 ***********************/
   Node()
   {
      pNext = nullptr;
      pPrev = nullptr;
   }  

/**********************************
 * Non Default Constructor:
 * create object with data in it.
 *********************************/  
   Node(T dat)
   {
      data = dat;
      pNext = nullptr;
      pPrev = nullptr;
   }
};

/**********************************
 * Create copy of Linked List.
 *********************************/
template<class T>
Node <T> *copy (Node <T> *pFront )
{
   Node <T> *copyNode = nullptr;
   Node <T> *tempNode = pFront;
   Node <T> *pHead = nullptr;
   bool first = true;
   do
   {
      if(first)
      {
         pHead = insert(tempNode->data, copyNode);
         copyNode = pHead;
         first = false;
         tempNode = tempNode->pNext;
      }
      else
      {
         insert(tempNode->data, copyNode, true);
         tempNode = tempNode->pNext;
         copyNode = copyNode->pNext;
      }
   } while (tempNode != nullptr);
   
   return pHead;
}

/**********************************
* Remove:
* A simple function that removes an Node
***************************************/

template <class T>
Node <T>* remove(Node <T> *pRemove)
{
	Node <T>* pReturn;

	if (pRemove == nullptr)
	{
		return pRemove;
	}

	if (pRemove->pPrev != nullptr)
	{
		pRemove->pPrev->pNext = pRemove->pNext;
	}
	if (pRemove->pNext != nullptr)
	{
		pRemove->pNext->pPrev = pRemove->pPrev;
	}

	if (pRemove->pPrev != nullptr)
	{
		pReturn = pRemove->pPrev;
	}
	else
	{
		pReturn = pRemove->pNext;
	}

	delete pRemove;

	return pReturn;
}

/****************************************
 * Find:
 * Searches the linked list for an item.
 ***************************************/
template <class T>
Node <T> *find(Node <T> *pFront, T finding)
{
   if (pFront == nullptr)
   {
      return nullptr;
   }

   for (Node <T> *tempNode = pFront; tempNode; tempNode = tempNode->pNext)
   {
      if (tempNode->data == finding)
      {
         return tempNode;
      }
   }

   return NULL;
}


/************************************************************
 * << Operator:
 * This loops through the list and prints the items it finds
 *************************************************************/
template<class T>
std::ostream& operator<<(std::ostream &output, Node <T> *pFront)
{
   Node <T> *outputNode = pFront;
   while (outputNode != nullptr)
   {
      if (outputNode->pNext == nullptr)
      {
         output << outputNode->data;
      }

      else
      {
         output << outputNode->data << ", ";
      }
      outputNode = outputNode->pNext;
   }

   return output;
}

/*******************************************************************
 * freeData:
 * this loops through the list and deletes each node
 * by copying into two temp pointers one to loop through the nodes
 * and the other to free them both are assigned to each other then
 * outside the loop pFront is assigned the NULL value each time.
 ******************************************************************/
template <class T>
void freeData(Node <T> *&pFront)
{
   Node <T> *deleteNode = nullptr;
   Node <T> *tempNode = deleteNode = pFront; //i dont understand this line
   while(tempNode != nullptr)
   {
      deleteNode = tempNode;
      tempNode = tempNode->pNext;
      delete deleteNode;
   }

   pFront = tempNode;
}
   
#endif /* NODE_H */
