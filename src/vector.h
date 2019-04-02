/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of a Vector: an expandable bucket to hold
 *    data for the user.
 *
 *    This will contain the class definition of:
 *       Vector            : similar to std::vector
 *       vector :: iterator : an iterator through the vector
 * Author
 *    Br. Helfrich
 *    adapted by Ken Smith
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>  // because I am paranoid
#include <iostream> // because it is useful in debugging

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom
{
   /************************************************
    * VECTOR
    * A class that holds stuff
    ***********************************************/
   template <class T>
      class vector
      
   {
     public:
      // constructors and destructors
      vector()
      {
         this->num = 0;
         this->data = NULL;
         this->numPlaces = 0;
      }
      vector(int num)                  throw (const char *);
      vector(const vector & rhs)        throw (const char *);
      ~vector()                         { delete [] data;   }
      vector & operator = (const vector & rhs) throw (const char *);
      
      // standard container interfaces
      int  size()     const { return num;                       }
      int  capacity() const { return numPlaces;                 }
      bool empty()
      {
         if (size() == 0)
            return true;
         else
            return false;
         
      }
      
      // Vector-specific interfaces            do i need to change this too?
      // what would happen if I passed -1 or something greater than num?
      T & operator [] (int index)       throw (const char *)
      {
         if (index < 0)
            throw "ERROR: Invalid index";
         if (index > num)
            throw "Error: Invalid index";
         
         return data[index];
      }
      const T & operator [] (int index) const throw (const char *)
      {
         if (index < 0)
            throw "ERROR: Invalid index";
         if (index > num)
            throw "Error: Invalid index";
         
         
         return data[index];
      }
      void clear()
      {
         num = 0;
         return;
      }
      void push_back(T t);
      
      // the various iterator interfaces
      class iterator;
      iterator begin()      { return iterator (data); }
      iterator end();
      
      // a debug utility to display the array
      // this gets compiled to nothing if NDEBUG is defined
      void display() const;
      
     private:
      T * data;              // dynamically allocated array of T
      int num;               // and the number of elements
      int numPlaces;         // and the number of element places allocated
      void resize(const int capacity) throw (const char *);
      // if we ever go allocated +1
   };
   
   /**************************************************
    * VECTOR ITERATOR
    * An iterator through vector
    *************************************************/
   template <class T>
      class vector <T> :: iterator
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
      
     private:
      T * p;
   };
   
   
   /********************************************
    * VECTOR :: END
    * Note that you have to use "typename" before
    * the return value type
    ********************************************/
   template <class T>
      typename vector <T> :: iterator vector <T> :: end ()
   {
      
      return iterator (data + num);
   }
   
   /*******************************************
    * VECTOR :: Assignment
    * operator overload for easier use of vector
    *******************************************/
   template <class T>
      vector <T> & vector <T> :: operator = (const vector <T> & rhs)
      throw (const char *)
      {
         // we can only copy arrays of equal size. Vectors are not this way!
         // so this will have to be changed to lead to allocating new memory            
         if (rhs.size() != size())
         {
            num = rhs.size();
            data = new T[rhs.num];
            numPlaces = rhs.size();
         }
         
         assert(num == rhs.num);
         for (int i = 0; i < num; i++) // move the data
            data[i] = rhs.data[i];
         
         return *this;
      }
   
   /*******************************************
    * VECTOR :: COPY CONSTRUCTOR
    *******************************************/
   template <class T>
      vector <T> :: vector(const vector <T> & rhs) throw (const char *)
   {
      assert(rhs.num >= 0);
      
      // do nothing if there is nothing to do
      if (rhs.num == 0)
      {
         
         num = 0;
         data = NULL;
         numPlaces = 0;
         return;
      }
      
      // attempt to allocate
      try
      {
         data = new T[rhs.num];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
      
      // copy over the capacity and quantity
      numPlaces = rhs.num;
      num = rhs.num;
      
      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < num; i++)
         data[i] = rhs.data[i];
   }
   
   /**********************************************
    * VECTOR : NON-DEFAULT CONSTRUCTOR
    * Preallocate the vector to "capacity"
    **********************************************/
   template <class T>
      vector <T> :: vector(int num) throw (const char *)
   {
      assert(num >= 0);
      
      // do nothing if there is nothing to do.
      // BUT we can grow a vector so this will stay
      if (num == 0)
      {
         this->num = 0;
         this->data = NULL;
         this->numPlaces = 0;
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
      this->numPlaces = num;
      this->num = num;
   }
   
   /********************************************
    * VECTOR : DISPLAY
    * A debug utility to display the contents of the vector
    *******************************************/
   template <class T>
      void vector <T> :: display() const
   {
#ifndef NDEBUG
      std::cerr << "vector<T>::display()\n";
      std::cerr << "\tnum = " << num << "\n";
      for (int i = 0; i < num; i++)
         std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif //        NDEBUG
   }
   
   /*******************************************************
    * Vector : RESIZE
    * Should we run out of room, more memory is allocated.
    *******************************************************/
   template <class T>
      void vector <T> :: resize(int b) throw (const char *)
   {
      
      // attempt to allocate space
      if (numPlaces == 0)
         numPlaces++;
      
      numPlaces += numPlaces;
      
      try
      {
         T * newData = new T[numPlaces];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
      
      T * newData = new T[numPlaces];
      
      //move old data into new space
      for (int i = 0; i < b; i++)
         newData[i] = data[i];
      
      data = newData; //change reference address
      
      return;
   }
   
   /*******************************************************
    * Vector : PUSH_BACK
    * we need to add more items.
    *******************************************************/
   
   template <class T>
      void vector <T> :: push_back(T t)
   {
      if (num == numPlaces)
         resize(num);
      
      data[(num++)] = t;
      
      return;
   }
   
}; // namespace custom

#endif // VECTOR_H


