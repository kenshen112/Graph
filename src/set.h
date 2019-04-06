/***********************************************************************
 * Header:
 *    Set
 * Summary:
 *    This class contains the notion of a set: a bucket to hold
 *    data for the user.
 *
 *    This will contain the class definition of:
 *       set             : similar to std::set
 *       set :: iterator : an iterator through the set
 * Author
 *    Br. Helfrich
 * Modified by:
 *      Jessica Smith
 *      Kenny Smith
 ************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>  // because I am paranoid

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{

/************************************************
 * SET
 * A class that holds stuff
 ***********************************************/
template <class T>
class set
{
public:
   // constructors and destructors
   set();
   set(int numCapacity)                  throw (const char *);
   set(const set & rhs)        throw (const char *);
  ~set()                         { delete [] data;   }
   set & operator = (const set & rhs) throw (const char *);
   
   // standard container interfaces
   
   int  size()     const { return numElements;         }
   
   // set-specific interfaces
   // what would happen if I passed -1 or something greater than num?
   set operator || (const set & rhs) throw (const char *); //union operator
   set operator && (const set & rhs) throw (const char *); //intersection operator
   // set operator - (const set & rhs) throw (const char *); //difference operator
   bool empty();
   void clear();

   void insert(T element);
   
   T & operator [] (int index)       throw (const char *)
   {
      return data[index];
   }
   const T & operator [] (int index) const throw (const char *)
   {
      return data[index];
   }
   
   // the various iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();
   iterator find(T t);
   iterator erase(iterator it);
   class const_iterator;
   const_iterator cbegin()   {return const_iterator(data); }
   const_iterator cend();
   
   
   // a debug utility to display the array
   // this gets compiled to nothing if NDEBUG is defined
   void display() const; 
   
private:
   T * data;              // dynamically allocated array of T
   int numCapacity;               // The capacity of the set
   int numElements;       //number of elements in the set
   void resize(int target) throw (const char *); //resizes the array
};

/**************************************************
 * SET ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class set <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }

   //prefix decrement
   iterator & operator --()
   {
      p--;
      return *this;
   }
   
   //postfix decrement
   iterator operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }
   
private:
   T * p;
};


/********************************************
 * SET :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename set <T> :: iterator set <T> :: end ()
{
   return iterator (data + numElements); //using numElements
}

/**********************************************
 * SET : FIND
 * searches for an element within the set
 **********************************************/
template <class T>
typename set <T> :: iterator set <T> :: find (T t)
{
   //search for the element using a binary search pattern would be best
   //if it is there return an iterator/pointer to the element
   //otherwise return set::end();
   //std::cout << "this is a test to find the segfault. is it in find?\n";
   iterator it = data;
   //std::cout << "iterator preped to find\n";
   for(it; it != end(); it++)
   {
      //std::cout << "searching for whatever t is\n";
      if (*it == t)
      {
         //std::cout << "found it\n";
         return it;
      }
   }
   //std::cout << "its not here\n";
   return end();
}

/**********************************************
 * SET : INSERT
 * inserts an element into the set, this is where the primary logic is that makes it into a sorted array
 **********************************************/
template <class T>
void set <T> :: insert (T element)
{
   //first make sure we have room to take in another thing
   //then find where it would go in the set
   //then find out if it is already there
   //if it is, do nothing
   //if it is NOT in the set,
   // shift all the elements in the set over 1 and add it
   //to where it should be in the sorted array
  
   if (numElements == numCapacity)
   {
      if (numCapacity == 0)
         resize(1);
      else
         resize(numCapacity * 2);  
   }

   if(numElements == 0)
   {
      data[0] = element;
      numElements++;
      return;
   }

   //i was going to work through the array rom 0-n, but i think i'll go backwards

   int i = numElements - 1;

   
   if(element > data[i])
   {
      data[numElements] = element;
      numElements++;
      return;
   }

   while(i >= 0)
   {
      if(data[i] == element)
      {   //if we already have the element, then we are done.
         return;
      }
         
      if(data[i] < element)
      {
         i++;
         for(int end = numElements; end > i; end--)
         {
            data[end] = data[end - 1];
         }   
         data[i] = element;
         numElements++;
         return;
      }
      if(data[i] > element)
      {
         if(i == 0)
         {
            for(int end = numElements; end > i; end--)
            {
               data[end] = data[end - 1];
            }
            data[i] = element;
            numElements++;
            return;
         }
         i--;
      }
   }
}
   
/**********************************************
 * SET : ERASE
 * Deletes an element from the set
 **********************************************/
template <class T>
   typename set <T> :: iterator set <T> :: erase(iterator it)
{   
   //we  already have the iterator pointing us to what we want.
   //'delet     e' the 'it' element by shifting everything to the left one
   //and reduce numElements
   //wait isn't this thing supposed to have a return value?????
   //std::cout << "attempting to erase the thing we found\n";
   iterator next = it;
   iterator place = it;
   next++;
   //std::cout << "iterators are prepped\n";
   
   for(next; next != end(); place++)
   {
      //std::cout << "we are shifting items\n";
      *place = *next++;
   }
   //std::cout << "done shifting, decrement the number of things, and lets get out of here\n";          
   numElements--;
   return it;
} 
/**********************************************
 * SET : UNION OPERATOR
 * performs a union, combines the two sets into a new set
 **********************************************/
template <class T>
   set <T> set <T> :: operator || (const set <T> & rhs) throw (const char *)
{
   //make a new set
   //loop thru both sets, adding the lhs to the new set first
   //then add the rhs to the set
   //return the new set

   set <T> newSet;
   
   int iLhs = 0;
   int iRhs = 0;
   
   while(iLhs < this-> numElements || iRhs < rhs.numElements)
   {
      if(iLhs == this->numElements)
         newSet.insert(rhs.data[iRhs++]);
      else if(iRhs == rhs.numElements)
         newSet.insert(this->data[iLhs++]);
      else if(this->data[iLhs] == rhs.data[iRhs])
      {
         newSet.insert(this->data[iLhs]);
         iLhs++;
         iRhs++;
      }
      else if(this->data[iLhs] < rhs.data[iRhs])
         newSet.insert(this->data[iLhs++]);
      
      else
         newSet.insert(rhs.data[iRhs++]);
   }
   
   return newSet;            
}

/**********************************************
 * SET : INTERSECTION OPERATOR
 * returns a new set with what is in both sets
 **********************************************/
template <class T>
   set <T> set <T> :: operator && (const set <T> & rhs) throw (const char *)
{
   //make a new set
   //loop thru both sets, if there is an element in the lhs and the rhs
   // add that element to the new set
   //return the new set

   set <T> newSet;
   int iLhs = 0;
   int iRhs = 0;

   while(iLhs < this->numElements || iRhs < rhs.numElements)
   {
      if(iLhs == this-> numElements)
         return newSet;
      else if(iRhs == rhs.numElements)
         return newSet;
      else if(this->data[iLhs] == rhs.data[iRhs])
      {
         newSet.insert(this->data[iLhs]);
         iLhs++;
         iRhs++;            
      }
      else if(this->data[iLhs] < rhs.data[iRhs])
         iLhs++;
      else
         iRhs++;
   }
   
   return newSet;
}

/**********************************************
 * SET : DIFFERENCE OPERATOR
 * returns what is in the lhs set but NOT the rhs
*********************************************/
/*template <class T>
   set <T> set <T> :: operator - (const set <T> & rhs) throw (const char *)
{
   //make a new set
   //loop thru both sets
   //if an element is in the lhs set but NOT in the rhs
   //add that to the new set
   //return the new set

   set <T> newSet;
   int iLhs = 0;
   int iRhs = 0;

   while(iLhs < this->numElements || iRhs < rhs.numElements)
   {
      T tmpVal = this->data[iLhs];
      T newVal = rhs.find(tmpVal); //kept getting an error I couldn't figure out
      if(iLhs == this->numElements)
         return newSet;
      else if(iRhs == rhs.numElements)
         return newSet;
      else if(this->data[iLhs] == *newVal)
      {
         iLhs++;
         iRhs++;
      }
      else if(this->data[iLhs] != *newVal)
      {
         newSet.insert(this->data[iLhs]);
         iLhs++;
      }
      else
         iRhs++;
   }

   return newSet;

}
*/
/*******************************************
 * SET :: Assignment
 *******************************************/
template <class T>
set <T> & set <T> :: operator = (const set <T> & rhs)
          throw (const char *)
{
   //check if the current set has enough capacity
   if (numCapacity < rhs.size())
   {
      //      std::cout << "calling resize cuz numCap is < rhs.size()\n";
      resize(rhs.size());
   }
   

   for(int i = 0; i < rhs.size(); i++)
   {
      data[i] = rhs.data[i]; //copy over the elements one by one
   }

   numElements = rhs.size();

   return *this;
}

/**********************************************
 * SET : DEFAULT CONSTRUCTOR
 * Preallocate the set to 0 or null
 **********************************************/
template <class T>
set <T> :: set()
{
   numElements = 0;
   numCapacity = 0;
   data = NULL;
}

/*******************************************
 * SET :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
set <T> :: set(const set <T> & rhs) throw (const char *)
{
   assert(rhs.size() >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.numElements == 0)
   {
      numCapacity = 0;
      numElements = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.size()];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity
   numCapacity = rhs.size();
   numElements = rhs.size();

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numCapacity; i++)
      data[i] = rhs.data[i];
}

/**********************************************
 * SET : NON-DEFAULT CONSTRUCTOR
 * Preallocate the set to "capacity"
 **********************************************/
template <class T>
set <T> :: set(int num) throw (const char *)
{
   assert(num >= 0);
   
   // do nothing if there is nothing to do.
   if (num == 0)
   {
      this->numCapacity = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[num];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // copy over the stuff
   this->numCapacity = num;
   this->numElements = 0;

}

/**********************************************
 * SET : EMPTY()
 * check to see if the set is empty
 **********************************************/
template <class T>
bool set <T> :: empty()
{
   if(numElements == 0)
   {
      return true;
   }
   else
   {
      return false;
   }

}

/**********************************************
 * SET : CLEAR()
 * remove all the elements in the set
 **********************************************/
template <class T>
void set <T> :: clear()
{
   numCapacity = 0;
   numElements = 0;
}

/**********************************************
 * SET : RESIZE
 * Resizes the array as needed
 **********************************************/
template <class T>
void set <T> :: resize(int target) throw(const char *)
{
   //   std::cout << "target is: " << target << std::endl;
   T * newData;
   // attempt to allocate
   try
   {
      newData = new T[target];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   if(data == NULL)
   {
      //std::cout << "first reallocation\n";
      data = newData;
      numCapacity = target;
      return;
   }
   
   // std::cout << "about to move the data\n";
   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numElements; i++) //Change to use the iterator??
   {
      newData[i] = data[i];
   }
   
   data = newData;
   numCapacity = target;
}

/********************************************
 * SET : DISPLAY
 * A debug utility to display the contents of the set
 *******************************************/
template <class T>
void set <T> :: display() const
{
#ifndef NDEBUG
   std::cerr << "set<T>::display()\n";
   std::cerr << "\tnum = " << numElements << "\n";
   for (int i = 0; i < numElements; i++)
      std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
}


/**************************************************
 * SET ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class set <T> :: const_iterator
{
public:
   // constructors, destructors, and assignment operator
   const_iterator()      : p(NULL)      {              }
   const_iterator(T * p) : p(p)         {              }
   const_iterator(const iterator & rhs) { *this = rhs; }
   const_iterator & operator = (const const_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }

   //prefix decrement
   const_iterator & operator --()
   {
      p--;
      return *this;
   }
   
   //postfix decrement
   const_iterator operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p--;
      return tmp;
   }
   
private:
   T * p;
};

/********************************************
 * SET :: END
 * Note that you have to use "typename" before
 * the return value type
 ********************************************/
template <class T>
typename set <T> :: const_iterator set <T> :: cend ()
{
   return const_iterator (data + numElements); //using numElements
}





}; // namespace custom

#endif // SET_H

