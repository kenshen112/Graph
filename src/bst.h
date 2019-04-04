/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother <your instructor name here>, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    Create a binary search tree
 ************************************************************************/
#include "bnode.h"
#include "queue.h"
#ifndef BST_H
#define BST_H
using std::cout;
using std::endl;
using std::cin;
namespace custom
{
   
   template <class T>
      class BST{
      
     private:
      int numElements;
      BNode <T> *root;
      
      
     public:
      
      class iterator; // Always remeber dear knights always forward declare thine classes!
      
      iterator find(T itemToFind);
      iterator begin();
      iterator end();
      iterator rbegin();
      iterator rend();


      BST()
      {
         root = nullptr;
         numElements = 0;
      }
      ~BST()
      {
         // deleteBinaryTree(root);
         // numElements = 0;
      }
	  BST(const BST <T> *rhs)
	  {
		  if (rhs == nullptr)
		  {
			  return;
		  }


		  // push the head of the tree onto the queue
		  queue <BNode <T> *> q;

		  q.push(rhs->root);
		  // while there are still sub-trees to visit…
		  while (!q.empty())
		  {
			  // add the left and right sub-tree to the queue
			  if (q.front()->pLeft != nullptr)
				  q.push(q.front()->pLeft);
			  if (q.front()->pRight != nullptr)
				  q.push(q.front()->pRight);
			  // visit the current node
			  insert(q.front()->data);
			  q.pop();
		  }
	  }

	  BST operator= (const BST <T> & rhs) throw (const char *)
	  {

		  if (rhs.root == nullptr)
		  {
			  return nullptr;
		  }


		  // push the head of the tree onto the queue
		  queue <BNode <T> *> q;

		  q.push(rhs.root);
		  // while there are still sub-trees to visit…
		  while (!q.empty())
		  {
			  // add the left and right sub-tree to the queue
			  if (q.front()->pLeft != nullptr)
				  q.push(q.front()->pLeft);
			  if (q.front()->pRight != nullptr)
				  q.push(q.front()->pRight);
			  // visit the current node
			  insert(q.front()->data);
			  q.pop();
		  }

		  return *this;

	  }
      
      int size()   { return numElements; }
      bool empty() { return numElements == 0; }
      void clear();
      void insert(T item); // The Big Mac on the plate though this won't be too difficult equation wise if (item > left == true)  isRight = true;
      void erase(iterator it);
      void deleteNode(BNode <T> *nodeToDelete, bool isRight);
      void deleteBinaryTree(BNode <T> *deletor);
      void copyBinaryTree(const BNode<T> * pSrc, BNode<T> * pDest);
      void balence(BST<T>* tree);

   };

    template <class T>
       class BST <T> ::iterator
    {

      public:
       BNode <T> *p;
	   

       //Constructors/Destructor
       iterator()
       {
          p = nullptr;
	   }

       iterator(BNode <T> *pNewit)
       {
          this->p = pNewit;
       }

       iterator(const iterator &rhs)
       {
          this->p = rhs.p;
       }

       iterator operator = (const iterator &rhs)
       {
		   if (rhs.p == nullptr)
		   {
			   return iterator(nullptr);
		   }

          //std::cerr << "iterator assignment operator\n";
          return p = rhs.p;
       }

	   
       bool operator!=(iterator it)
       {
          //std::cerr << "not equeals operator\n";
          return this->p != it.p;
	  
       }
       
       bool operator==(iterator it)
       {
          return this->p == it.p;
       }
       

       //OPERATORS, delcare em, stub em, define em right here.
       // even you couldn't say no to that.
       //                     OH YES WE COULD

       iterator operator++();
       iterator operator++(int);//postfix
       iterator operator--();
       iterator operator--(int);//postfix
	   
       T& operator*()
       {
          if(p)
          {
             return p->data;
          }
       }
       
    };
       

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. 
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
   template <class T>
      typename BST<T>::iterator BST<T>::iterator::operator--()
   {

      // do nothing if we have nothing
      if (p == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left node, take it
      if (nullptr != p->pLeft)
      {
         // go left
         p = p->pLeft;
         
         //jig right - there might be more right-most children
         while (p->pRight)
            p = p->pRight;
         return *this;
      }
      
      // there are no left children, the right are done
      assert(nullptr == p->pLeft);
      BNode<T> * pSave = p;

      // go up
      p = p->pParent;

      // if the parent is the NULL, we are done!
      if (nullptr == p)
         return *this;

      // if we are the right-child, got to the parent.
      if (pSave == p->pRight)
         return *this;

      // we are the left-child, go up as long as we are the left child!
      while (nullptr != p && pSave == p->pLeft)
      {
         pSave = p;
         p = p->pParent;
      }
      
      return *this;
   }

/**************************************************
 * BST ITERATOR :: DECREMENT POSTFIX
 *     advance by one.
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
   template <class T>
      typename BST<T>::iterator BST<T>::iterator::operator--(int)
   {
           
      // do nothing if we have nothing
      if (p == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left node, take it
      if (nullptr != p->pLeft)
      {
         // go left
         p = p->pLeft;
         
         //jig right - there might be more right-most children
         while (p->pRight)
            p = p->pRight;
         return *this;
      }
      
      // there are no left children, the right are done
      assert(nullptr == p->pLeft);
      BNode<T> * pSave = p;
      
      // go up
      p = p->pParent;
      
      // if the parent is the NULL, we are done!
      if (nullptr == p)
         return *this;
      
      // if we are the right-child, got to the parent.
      if (pSave == p->pRight)
         return *this;
// we are the left-child, go up as long as we are the left child!
      while (nullptr != p && pSave == p->pLeft)
      {
         pSave = p;
         p = p->pParent;
      }
      
      return *this;
   }
   
/**************************************************
* Reverse Begin
***************************************************/
   
   template <class T>
      typename BST<T>::iterator BST<T>::rbegin()	  
   {
      if(root == nullptr)
      {
         return iterator(nullptr);
      }
      
      BNode <T> *pNew;
      pNew = root;
      
      while(pNew->pRight)
      {
         pNew = pNew->pRight;
      }
      
      return iterator (pNew);
      
   }
   
   template <class T>  
      typename BST<T>::iterator BST<T>::rend()
   {
      return iterator(nullptr);
   }
   
/**************************************************
 *BST ITERATOR::INCREMENT PREFIX
 *so I copied the decrement operator above and
 *  just switched pLeft to pRight and vice versa
 *************************************************/
   template <class T>
   typename BST <T>::iterator BST<T>::iterator::operator++()
   {

	  //std::cerr << "MMM Prefix Donught" << std::endl;

      // do nothing if we have nothing
      if (p == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left *right* node, take it
      if (nullptr != p->pRight)
      {
         // go left *right*
         p = p->pRight;
            
         //jig right *left?* - there might be more right*left*-most children
         while (p->pLeft)
            p = p->pLeft;
         return *this;
      }
      
      // there are no left *right* children, the right *left* are done
      assert(nullptr == p->pRight);
      BNode<T> * pSave = p;
      
      // go up
      p = p->pParent;
      
      // if the parent is the NULL, we are done!
      if (nullptr == p)
         return *this;
      
      // if we are the right*left*-child, got to the parent.
      if (pSave == p->pLeft)
         return *this;
      // we are the left*right*-child, go up as long as we are the left *right* child!
      while (nullptr != p && pSave == p->pRight)
      {
         pSave = p;
         p = p->pParent;
      }
      
      return *this;
   }

/**************************************************
 *BST ITERATOR::INCREMENT POSTFIX
 *so I copied the decrement operator above and
 *  just switched pLeft to pRight and vice versa
 *************************************************/
   template <class T>
      typename BST <T>::iterator BST<T>::iterator::operator++(int)
   {
    
		  //std::cerr << "MMM Postfix donught" << std::endl;

      // do nothing if we have nothing
      if (p == nullptr) // rember always use nullptr instead of NULL
         return *this;
      
      //   if there is a left *right* node, take it
      if (nullptr != p->pRight)
      {
         // go left *right*
         p = p->pRight;
         
         //jig right *left?* - there might be more right*left*-most children
         while (p->pLeft)
            p = p->pLeft;
         return *this;
      }
      
      // there are no left *right* children, the right *left* are done
      assert(nullptr == p->pRight);
      BNode<T> * pSave = p;
      // go up
      p = p->pParent;
      
      // if the parent is the NULL, we are done!
      if (nullptr == p)
         return *this;
      
      // if we are the right*left*-child, got to the parent.
      if (p == p->pLeft)
         return *this;
      // we are the left*right*-child, go up as long as we are the left *right* child!
      while (nullptr != p && pSave == p->pRight)
      {
         pSave = p;
         p = p->pParent;
      }
      
      return *this;
   }

/****************************************************
 *DELETE BINARY TREE
 *deletes an entire BST
 ****************************************************/
template <class T>
   void BST <T> :: deleteBinaryTree(BNode <T> *deletor)
   {

      if(deletor == nullptr)
      {
         return;
      }
      
      deleteBinaryTree(deletor->pLeft);
      deleteBinaryTree(deletor->pRight);
      deletor = nullptr;
      delete deletor;
   }   

   /**********************************************
 * COPY BINARY TREE
 * Copy pSrc->pRight to pDest->pRight and
 * pSrc->pLeft onto pDest->pLeft
 *********************************************/
   template <class T>
   void BST <T> ::copyBinaryTree(const BNode<T> * pSrc, BNode<T> * pDest) 
   {	   
	   std::cerr << "copyBTree" << std::endl;

	   BNode<T> * p = nullptr;
	   assert(pSrc && pDest);
	   assert(pDest->pLeft == nullptr && pDest->pRight == nullptr);


	   try
	   {
		   if (pSrc->pRight)
		   {			   std::cerr << "pRight copy" << std::endl;

			   p = new BNode<T>(pSrc->pRight->data);
			   p->red = pSrc->pRight->red;
			   pDest->pRight = p;
			   copyBinaryTree(pSrc->pRight, pDest->pRight);
		   }
		   if (pSrc->pLeft)
		   {			   std::cerr << "pLeft copy" << std::endl;

			   p = new BNode<T>(pSrc->pLeft->data);
			   p->red = pSrc->pLeft->red;
			   pDest->pLeft = p;
			   copyBinaryTree(pSrc->pLeft, pDest->pLeft);
		   }
	   }
	   catch (...)
	   {
		   throw "ERROR: Unable to allocate a node";
	   }
   }



   
   template<class T>
   void BST<T>::clear()
   {
	   deleteBinaryTree(root);
	   numElements = 0;
           root = nullptr;
   }

   /***************************************************
    * INSERT FOR BST
    ************************************************/
   template<class T>
      void BST<T>::insert(T item)
   {
//      cout << "we are in insert\n";
      BNode <T> * pNew;
      try
      {
         //make a new node
         pNew = new BNode <T> (item);
         //              cout << "We just made a new node\n";
      }
      catch (std::bad_alloc)
      {
         throw "Error: Unable to allocate a node";
      }
      
      //if the tree is currently empty
      if (root == nullptr) // case 1 tree is black
      {
         // cout << "the tree is empty\n";
         root = pNew; // This node is black yo!
         root->black = true;
         root->parent = true;
         numElements++;
         return;
      }
      
      //another pointer, to keep track of where we are as we find a home for pNew
      BNode <T> * pPlace = root;
      bool home = false; //to keep track of if we have found what we are looking for
      bool left; //to tell us if we are adding left or right
      
      while(!home)
      {
         if(item <= pPlace->data) //otherwise do we need to go left?
         {
            if(pPlace->pLeft == nullptr)
            {
               home = true;
               left = true;
               //             		   pPlace->pLeft = pNew;
            }
            else
               pPlace = pPlace->pLeft;
         }
         else if(item >= pPlace->data) //or right?
         {
            if(pPlace->pRight == nullptr)
            {
               home = true;
               left = false;
//               	   pPlace->pRight = pNew;
            }
            else
               pPlace = pPlace->pRight;
         }
      }
      //attach the pointers to link the new item into the tree.
      
      if(left)
      {
         //    cout << "it needs to go in the left\n";
         pPlace->pLeft = pNew;
         pNew->pParent = pPlace;
      }
      else
      {
         // cout << "it needs to go on the right\n";
         pPlace->pRight = pNew;
         pNew->pParent = pPlace;
      }
      numElements++;
      
      
/*      if (item > root->data)
      {
         BNode <T> * pNew = new BNode<T>(item);
         numElements++;
      }
      
      else if (item < root->data)
      {
         root->pLeft = new BNode<T>(item);
         numElements++;
      }*/

      // cout << "we made it through insert!\n";
   }

/*********************************************
 *ERASE
 *erases a node from the BST
 ********************************************/
   template <class T>
      void BST<T>::erase(iterator it)
   {

      //CASE 1: NO children
      if (it.p->pRight == nullptr && it.p->pLeft == nullptr) // there aint no children up in here mmm hmmm das what i'm sayin.
      {

         //        std::cerr << "Case 1" << std::endl;
         
         if (it.p->pParent != nullptr && it.p->pParent->pRight == it.p)
         {//we are on the right of a parent
            it.p->pParent->pRight = nullptr;
            it.p = nullptr;
            delete it.p;
         }
         else if (it.p->pParent != nullptr && it.p->pParent->pLeft == it.p)
         {//we are on the left of a parent
            it.p->pParent->pLeft = nullptr;
            it.p = nullptr;
            delete it.p;
         } 
         else if (it.p->pParent == nullptr)
         {//there is no parent
            it.p = nullptr;
            delete it.p;
         }
      }

      //CASE 2: One Child
      else if (it.p->pRight != nullptr && it.p->pLeft == nullptr)
      {//we have a right child, but no left children

//	std::cerr << "Case 2" << std::endl;
	
         it.p->pRight->pParent = it.p->pParent;
         
         if (it.p->pParent != nullptr && it.p->pParent->pRight == it.p) //we are the right child
         {
            it.p->pParent->pRight = it.p->pRight;
         }
         
         if (it.p->pParent != nullptr && it.p->pParent->pLeft == it.p) //we are the left child
         {
            it.p->pParent->pLeft = it.p->pRight;
         }
         it.p = nullptr;
         delete it.p;
      }
      
      else if (it.p->pRight == nullptr && it.p->pLeft != nullptr)
      {//we have a left child but not a right one
         it.p->pLeft->pParent = it.p->pParent;
         
         if (it.p->pParent != nullptr && it.p->pParent->pRight == it.p) //we are the right child
         {
            it.p->pParent->pRight = it.p->pLeft;
         }
         
         if (it.p->pParent != nullptr && it.p->pParent->pLeft == it.p) // we are the right child
         {
            it.p->pParent->pLeft = it.p->pLeft;
         }
         it.p = nullptr;
         delete it.p;
      }
      
      //CASE 3: Two Children
      else if(it.p->pRight != nullptr && it.p->pLeft != nullptr)
      {//with this one, we need to properly map the logic.
         // stipulations
         // we have two children.
         // one of them, (either the right child, or one of its descendants), is the guarateed successor.
         // with that in mind...
         // what variables are there???
         // we have a parent or we don't.
         // we are on the left or right of that parent. (i think this has been forgotten here)
         // the successor is the imediate child, or it is one of its descendants
         // 

/*         char response;
         std::cout << "continue into case 3?\n";
         std::cin >> response;
*/
         
         //       std::cerr << "Case 3" << std::endl;

         iterator ios = it;

         // std::cerr << "making a new iterator and setting it to our current one\n";

         /*      
         std::cout << "iterate the new iterator?\n";
         std::cin >> response;
         
         std::cerr << "incrementing iterator\n";
         */ios++;
         
         //std::cerr << "asserting that ios does not have a left child\n";
         assert(ios.p->pLeft == nullptr); //ios should NOT have a left child

         /*std::cout << "delete the node?\n";
         std::cin >> response;
         */
         //IF it has a parent it needs to point to ios
         if(it.p->pParent)
         {
            // std::cerr << "first we take care of the bottom of the tree, and then the top\n";
            
            if(ios.p == it.p->pRight) //if our successor is the imediate right child
            {  //we need to link it to the left child.
               // std::cerr << "immediate right child, link it with the left\n";
               
               //std::cout << "1st if statement: our ios is the right child\n";
               // std::cin >> response;
               
               it.p->pLeft->pParent = ios.p;
               ios.p->pLeft = it.p->pLeft; //what does this do?
            }
            else //the successor is one of the right childs descendants.
            {
               if(ios.p->pRight) //we need to link any potential descendants, so we don't loose them
               {
                  
                  // std::cerr << "linking all kids from the successor\n";
                  
                  //std::cout << "the ios is it.p's right side grandchild\n";
                  //std::cin >> response;
                  
                  ios.p->pParent->pLeft = ios.p->pRight;
                  ios.p->pRight->pParent = ios.p->pParent; //Ithink thisline works but there's a chance it wouldn't...
               }
               else //there are no descendants to worry about
               {
                  //std::cerr << "successor is a leaf, the the parents left pointer is now null\n";
                  ios.p->pParent->pLeft = nullptr;
                  //std::cout << "the ios had no children, but now will be linked to it's children\n";
                  //std::cin >> response;
               }
               
               //and then link to it's left child anyway
               //std::cerr << "linking with it's left child\n";
               it.p->pLeft->pParent = ios.p;
               ios.p->pLeft = it.p->pLeft; //is that how pointers work?
               
               //std::cerr << "linking with it's right child\n";
               it.p->pRight->pParent = ios.p;
               ios.p->pRight = it.p->pRight; //is that how pointers work?
               
               
               
            }
            
/*                          //and then link to it's left child anyway
                            std::cout << "linking to left child anyway\n";
                            std:    :cin >> response;
               
               it.p->pLeft->pParent = ios.p; //you're making ios.p take the place of it.p here
               ios.p->pLeft = it.p->pLeft; 

               ios.p->pRight = it.p->pRight;
*/       
            //std::cerr << "now we take care of the top by \n";
            //std::cerr << "making it.p's parent node point to ios instead, and making ios point to it's parent\n";
            if(it.p->pParent->pLeft == it.p)
            {
               
               // std::cerr << "the one being deleted is a left child\n, connect successor with new parent and vice-versa\n";
               
               //std::cout << "making ios point to it, left side?\n";
               //std::cin >> response;
               
               //w e need to link it.p's children to ios.p
               if(it.p->pLeft)
               {
                  ios.p->pLeft = it.p->pLeft;
               }
               else if(it.p->pRight)
               {
                  ios.p->pRight = it.p->pRight;
               }
               else
               {
                  ios.p->pLeft = nullptr;
                  ios.p->pRight = nullptr;
               }
               
               it.p->pParent->pLeft = ios.p;
               ios.p->pParent = it.p->pParent;
            }
            else
            {
               
               //std::cerr << "the one being deleted is a right child\n connect succesor with new parent...\n";
               
//               std::cout << "making ios point to it, right side?\n";
               //             std::cin >> response;
               
               //we need to link it.p's children to ios.p
               /*if(it.p->pLeft) //i think something is wrong here
               {
                  ios.p->pLeft = it.p->pLeft;
               }
               else if(it.p->pRight)
               {
                  ios.p->pRight = it.p->pRight;
               }
               else
               {
                  ios.p->pLeft = nullptr;
                  ios.p->pRight = nullptr;
                  }*/
               
               it.p->pParent->pRight = ios.p;
               ios.p->pParent = it.p->pParent;
            }
            
            
         }
         else //we don't have a parent
         {
//            std::cerr << "there is no parent to what we are deleting, so\n";
            //          std::cerr << "first we take care of the bottom of the tree\n";
            if(ios.p == it.p->pRight) //if our successor is the imediate right child
            {  //we need to link it to the left child.
               it.p->pLeft->pParent = ios.p;
               ios.p->pLeft = it.p->pLeft;
            }
            else //the successor is one of the right childs descendants.
            {
               if(ios.p->pRight) //we need to link any potential descendants, so we don't loose them
               {
                  ios.p->pParent->pLeft = ios.p->pRight;
                  ios.p->pRight->pParent = ios.p->pParent;
               }
               //and then link to it's left child anyway
               it.p->pLeft->pParent = ios.p;
               ios.p->pLeft = it.p->pLeft;
            }        
         }
         /*
         //if it has children, they need to point to ios.
         if(it.p->pLeft)
            it.p->pLeft->pParent = ios.p;
         if(it.p->pRight)
            it.p->pRight->pParent = ios.p;
         std::cerr << "the children of it now point to it's parent instead of it\n";
         
         //if, ios has a right child, that child takes ios's spot.
         if(ios.p->pRight)
         {
            ios.p->pParent->pLeft = ios.p->pRight;
            ios.p->pRight->pParent = ios.p->pParent;
            std::cerr << "i think there is something wrong with these statements, review later\n";
         }
         
         //ios need to point to it's parent.
         ios.p->pParent = it.p->pParent;
         */
         
         it.p = nullptr;
         delete it.p;
      }
      
   }
   
   
   template<class T>
      void BST<T>::balence(BST<T>* tree)
   {
      if (tree->root == nullptr) // case 1 tree is black
      {
         tree->root->black = true;
         tree->root->parent = true;
      }
      
      //   A Baisc structure of Red Black Balencing 	   
      if (tree->black == true && tree->parent == true) //case 2 Might we be missing a circumstance here?
      {
         tree->root->pParent->red = true;
      }
      
      
      if (tree->root->black && root->pParent->red && root->pRight->red) // Case 3 the recolor
      {
         tree->root->black = false;
         tree->root->red = true;
         tree->root->pParent->red = false;
         tree->root->pParent->black = true;
         tree->root->pRight->red = false;
         tree->root->pRight->black = true;
      } 
   }
   
   template<class T>   
   typename BST<T>::iterator BST<T>::begin()
   {


      if(root == nullptr)
      {		 
         return iterator(nullptr);
      }


      BNode <T> *pNew = root;
      

      while(pNew->pLeft)
      {
         pNew = pNew->pLeft;
         
      }
      

      return iterator (pNew);
   }
   
   template<class T>
      typename BST<T>::iterator BST<T>::end()
   {
      return iterator(nullptr);
   }
   
   
/************************************************
* Find:
* Searches the Binary Search Tree for an item.
v************************************************/
   template <class T>
   typename BST<T>::iterator BST<T>::find(T itemToFind)
   {

	   if (root == nullptr)
	   {
              return iterator (nullptr);
	   }

      for (iterator it = begin(); it != nullptr; it++)
      {

         if (*it == itemToFind)
         {
            return it;
         }
      }
      
      return end();
   }
   
} 

#endif // BST_H
