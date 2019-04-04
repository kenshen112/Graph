/***********************************************************************
* Header:
*    MAP
* Summary:
*    This will contain the Map class and it's functions
*    
* Author
*    Jessica Smith
*    Ken Smith
*    Tim O'Barr
************************************************************************/
#include "pair.h"
#include "bst.h"
#ifndef MAP_H
#define MAP_H

namespace custom
{
   template <class K, class V>
      
      class map
   {
      
     private:
      BST <custom::pair<K, V>> *bst;
      
      int numElements; // we can either use this or just call BST'S size, Tim.
      
     public:
      //default constructor, all constructor's should be inline in C++ Tim
      map()
      {
         bst = new BST<custom::pair<K, V>>();
         numElements = 0;
      }
	  //copy constructor
	  map(const map <K, V> & rhs)
	  {
		  //         std::cerr << "in copy constructor\n";
		  bst = new BST<custom::pair<K, V>>(*(rhs.bst));
		  /*bst = rhs->bst;*/
		  numElements = rhs.numElements;
	  }

	  map & operator=(const map <K, V> & rhs)
	  {
		  //          std::cerr << "in assignment operator\n";
		  bst = new BST<custom::pair<K, V>>(*(rhs.bst));
		  /*bst = rhs->bst;*/
		  numElements = rhs.numElements;
	  }
      
      //destructor
      ~map()
      {
         bst = nullptr;
         numElements = 0;
         delete bst;
      }
      
      int size() const
      {
         return numElements;
      }
      bool empty() const
      {
         return numElements == 0;
      }
      
      void clear()
      {
         bst->clear();
         numElements = 0;
//         bst = nullptr;
         delete bst;
      }
      
      //access functions
      V & operator[] (const K & k) throw(const char *);
      V operator[] (const K & k)const throw(const char *);
      
      void insert(const K & k, const V & v) throw(const char *);
      void insert(const pair <K, V> & input) throw(const char *);
      
      class iterator;
      
      
      iterator find(K k);
      iterator begin();
      iterator end();
      
   };
   
   /*****************************************************
    *MAP:ITERATOR
    *The iterator for a map
    *****************************************************/
   template <class K, class V>
      class map <K, V> ::iterator
   {
      //trick to this is that basically all of the methods just call
      // the identical method in the BST iterator
     private:
      typename BST <custom::pair<K, V>> ::iterator bsit; // bsit, binary search iterator
      
     public:
      //constructors
      iterator()
      {}
      
      iterator(typename BST <custom::pair<K, V>>::iterator it)
      {
         this->bsit = it;
      }
      
      
      pair<K, V>& getBst()
      {
		  return *bsit;
      }
      
      iterator(const map<K, V>::iterator& it)
      {
         this->bsit = it.bsit;
      }
      
      //operators: =, ++, --, *, ==, !=
      iterator operator = (const iterator &rhs)
         {
            this->bsit = rhs.bsit;
            return *this;
         }
      
      
      /**************************
       * Increment
       * going up
       ********************/
      iterator operator ++ ()
      {
         bsit++;
         return *this;
      }
      
      /*********************
       * Decrement
       * going down
       ********************/
      iterator operator -- ()
      {
         bsit--;
         return *this;
      }
      
      /*****************
       * Dereference operator
       * to get to the actual data
       ***************/
      pair<K, V>& operator*()
      {
         return *bsit;
      }
      
      /******************************
       *Equvalence operator
       * are two iterators pointing to the same thing
       *****************************/
      bool operator == (const iterator it)
      {
         return this->bsit == it.bsit;
      }
      
      /**************************************
       * NOT equals operator
       * do two iterators point to different things
       *************************************/
      bool operator != (const iterator it)
      {
         return this->bsit != it.bsit;
      }
   };
   
   /****************************************
    *ITERATOR FIND
    *finds the key in the bst
    ***************************************/
   template<class K, class V>
      typename map<K, V>::iterator map<K, V>::find(K k)
   {
      pair<K, V> keyFind;

      keyFind.first = k;
      
      map<K, V>::iterator it; 
      
      return bst->find(keyFind);
   }
   
   /************************************
    *ITERATOR::BEGIN
    *returns an iterator to the beginning of the map
    ************************************/
   template <class K, class V>
      typename map<K, V>::iterator map<K, V>::begin()
   {
      return bst->begin();
   }
   
   /***************************************
    *ITERATOR::END
    *returns an iterator to the end of the map
    **************************************/
   template <class K, class V>
      typename map<K, V>::iterator map<K, V>::end()
   {
      return bst->end();
   }
   /*************************************
    *ACCESS OPERATOR
    *allows for random access
    ************************************/
   template <class K, class V>
      V & map<K, V>::operator[] (const K & k) throw(const char *)
   {
      //std::cerr << "in nonconstant access operator\n";
      pair<K, V> keyFind;
      keyFind.first = k;
      map<K, V>::iterator it;

      it = find(k);
 
      
      if (it != iterator(nullptr))
      {
    

         return it.getBst().second;
      }
      
      else
      {
         bst->insert(keyFind);
         numElements++;
         return find(keyFind.first).getBst().second;
      }
   }
   
   /*************************************
    *ACCESS OPERATOR CONST
    *allows for random access
    *************************************/
   template <class K, class V>
      V map<K, V>::operator[] (const K & k) const throw(const char *)
   {
      //std::cerr << "in constant access operator\n";
      pair<K, V> keyFind;
      keyFind.first = k;
      map<K, V>::iterator it;


      it = find(k);
      
      if (it != iterator(nullptr))
      {		 


         return it.getBst().second;
      }
      else
      {
         bst-insert(keyFind);
         return find(keyFind.first).getBst().second;
      }
   }
   
   /*************************************
    *INSERT with K,V
    *inserts a new value with a key
    ************************************/
   template <class K, class V>
      void map<K, V>::insert(const K & k, const V & v) throw(const char *)
   {
      map::iterator *it = bst->find(k);
      
	  if (it != nullptr)
	  {
		  *it = v;
		  numElements++;
	  }
	  else
      {
         bst.insert(k);
         numElements++;
      }
   }
   /************************************
    *INSERT with pair <K, V>
    *inserts a new value using a pair
    ***********************************/
   template <class K, class V>
      void map<K, V>::insert(const pair <K, V> & input) throw(const char *)
   {
      map::iterator *it = bst->find(input);//please make sure I got this right
      
      if (it != nullptr)
         *it = input;
      else
      {
         bst.insert(input);
         numElements++;
      }
   }
}

#endif // MAP_H

