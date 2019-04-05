/***********************************************************************
 * Header:
 *    QUEUE
 * Summary:
 *    A custom Queue class. First in first out
 * Author
 *    Kenyon Bunker and Tim O'Barr
 ************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H
#include <assert.h>

namespace custom {
   template <class T>
      class queue {
     private:
      T *data;
      int numPush;
      int numPop;
      int numCapacity;
      bool isEmpty;

      //Private function prototypes
      void resize(int newCapacity);
      int iHead();
      int iTail();
     public:
      //Constructors
      //Default Cosntructor
      queue();
      //Non-default cosntructor
      queue(int c);
      //Copy Constructor
      queue(queue<T> &rhs);
      //Destructor
      ~queue();

      /********************************************
       * ASSIGNMENT OPERATOR
       *******************************************/
      queue<T> & operator=(queue<T> & rhs)
      {
         numPush = 0;
         numPop = 0;
         if (rhs.numCapacity == 0)
         {
            numPop = 0;
            numPush = 0;
            numCapacity = 0;
            delete [] data;
            data = NULL;

            return *this;
         }

         if (numCapacity < rhs.size())
         {
            resize(rhs.size());
         }

            try
         {
            data = new T[rhs.numCapacity];
         }
         catch (std::bad_alloc)
         {
            throw "ERROR: Unable to allocate buffer";
         }

         numCapacity = rhs.numCapacity;
         int tempPop = rhs.numPop;

         for (int i = rhs.numPop; i < rhs.numPush; i++)
         {
            push(rhs.data[i % rhs.numCapacity]);
         }

         return *this;
      }

      //Function Prototypes
      T & front();
      T & back();
      int size();
      void push(const T &element);
      void clear();
      void pop();
      bool empty();
   };

   /********************************************
    * QUEUE: FRONT
    * Retireves the front element of the queue
    *******************************************/
   template <class T>
      T& queue<T>::front()
   {
      if (empty() == true)
      {
         throw "ERROR: attempting to access an element in an empty queue";
      }
      else
      {
         return data[iHead()];
      }
   }

   /********************************************
    * QUEUE: BACK
    * Retireves the back element of the queue
    *******************************************/
   template <class T>
      T& queue<T>::back()
   {
      if (empty() == true)
      {
         throw "ERROR: attempting to access an element in an empty queue";
      }
      else
      {
         return data[iTail()];
      }
   }

   /********************************************
    * QUEUE: POP
    * removes the front element of the queue
    *******************************************/
   template <class T>
      void queue <T>::pop()
   {
      if (empty() == true)
      {
         return;
      }
      else
      {
         numPop++;
      }
   }

   /********************************************
    * CONSTRUCTOR: DEFAULT
    *******************************************/
   template<class T>
      queue<T>::queue()
   {
      numPush = 0;
      numPop = 0;
      numCapacity = 0;
      data = new T[numCapacity];
      isEmpty = true;
   }

   /********************************************
    * CONSTRUCTOR: NON-DEFAULT
    *******************************************/
   template<class T>
      queue<T>::queue(int c)
   {
      numPush = 0;
      numPop = 0;
      numCapacity = c;
      data = new T[numCapacity];
      isEmpty = true;
   }

   /********************************************
    * CONSTRUCTOR: COPY
    *******************************************/
   template<class T>
      queue<T>::queue(queue<T>& rhs)
   {
      numPush = 0;
      numPop = 0;

      if (numCapacity < rhs.size())
      {
         resize(rhs.size());
      }

            try
            {
               data = new T[rhs.numCapacity];
            }
            catch (std::bad_alloc)                                                                                                                                                                                                                       {
               throw "ERROR: Unable to allocate buffer";
            }
            numCapacity = rhs.numCapacity;
            int tempPop = rhs.numPop;

            for (int i = rhs.numPop; i < rhs.numPush; i++)
            {
               push(rhs.data[i % rhs.numCapacity]);
            }
   }

   /********************************************
    * DESTRUCTOR
    *******************************************/
   template<class T>
      inline queue<T>::~queue()
   {
      clear();
   }


   /********************************************
    * Queue : SIZE
    * gets the queue size
    *******************************************/
   template<class T>
      int queue<T>::size()
   {
      return numPush - numPop;
   }

   /********************************************
    * Queue : RESIZE
    * resizes the queue buffer
    *******************************************/
    template<class T>
       void queue<T>::resize(int capacityNew)
    {
       // do nothing if there is nothing to do
       if (capacityNew < numCapacity)
       {
          return;
       }
          try
          {
             T *dataNew = new T[capacityNew];

             for (int i = numPop; i < numPush; i++) {
                dataNew[i] = data[i];
             }

             data = dataNew;
             numCapacity = capacityNew;
          }
          catch (std::bad_alloc) {
             throw "ERROR: Unable to allocate new buffer for queue";
          }
    }

    /********************************************
     * Queue : iHead
     * keeps track of the beggining of the queue
     *******************************************/
    template<class T>
       int queue<T>::iHead()
    {
       return numPop % numCapacity;
    }

    /********************************************
     * Queue : iTail
     * keeps track of the end of the queue
     *******************************************/
    template<class T>
       int queue<T>::iTail()
    {
       return (numPush -1) % numCapacity;
    }

    /********************************************
     * Queue : PUSH
     * Adds an element to the back of the queue
     *******************************************/
    template<class T>
       void queue<T>::push(const T & element)
    {
       if (numCapacity == 0)
       {
          resize(1);
       }
       else if (numPush == numCapacity)
       {

          resize(numCapacity *= 2);
       }
       numPush++;
       data[iTail()] = element;
    }

    /********************************************
     * queue : CLEAR
     * frees queue memory
     *******************************************/
    template <class T>
       void queue <T> ::clear()
    {
       data = NULL;
       delete[] data;
       numPush = 0;
       numPop = 0;
       numCapacity = 0;
    }
    /********************************************
     * queue : EMPTY
     * Checks if queue is empty
     *******************************************/
     template<class T>
        bool queue<T>::empty()
     {
        if (numPush == numPop)
        {
           isEmpty = true;
        }
        else
        {
           isEmpty = false;
        }
        return isEmpty;
     }

}// namespace custom
#endif /* QUEUE_H */
