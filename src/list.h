#pragma once
#include "node.h"

namespace custom
{


	template <class T>
	class list
	{
	private:
		int numElements;
		Node <T> *pHead;
		Node <T> *pTail;
	public:
		
		class iterator;
		class reverse_iterator;
		

		list()
		{
			pHead = nullptr;
			pTail = nullptr;
			numElements = 0;
		}

		list(const list <T> &rhs)
		{
			bool first = true;
			Node <T> *pTemp = rhs.pHead;
			numElements = rhs.numElements;

			for (int i = rhs.numElements; i > 0; i--)
			{
				Node <T> *pNew;
				try
				{
					pNew = new Node <T>;
				}
				catch (std::bad_alloc)
				{
					throw "Error: Unable to accolcate new Node for list";
				}

				pNew->data = pTemp->data;
				
				if (first)
				{
					pHead = pNew;
					first = false;
					pNew->pPrev = nullptr;
				}
				//Not done here yet
				else
				{
					pNew->pPrev = pTail;
					pTail->pNext = pNew;
				}
				pTail = pNew;
			}
		}

		//the copy constructor and the assignment operator should be basically the same
		// making a new version of the list that is passed to it. new, and seperate.
		//we can also take advantage of new attributes to the list class that weren't there last week
		//like the numElements variable.
		list operator=(list rhs)
		{
			bool first = true;
			Node <T> *pTemp = rhs.pHead;
			numElements = rhs.numElements;
			for (int i = rhs.numElements; i > 0; i--)
			{
				Node <T> *pNew;
				try
				{
					pNew = new Node <T>;
				}
				catch (std::bad_alloc)
				{
					throw "Error: Unable to accolcate new Node for list";
				}

				pNew->data = pTemp->data;

				if (first)
				{
					pHead = pNew;
					first = false;
					pNew->pPrev = nullptr;
				}
				//Not done here yet
				else
				{
					pNew->pPrev = pTail;
					pTail->pNext = pNew;
				}
				pTail = pNew;
			}
			return *this;
		}


		int size() { return numElements; }

		bool empty() { return pHead == nullptr; }

		void clear();
		void push_back(T item);
		void push_front(T item);
		void pop_back();
		void pop_front();

		
		 T &front();
		 T &back();

		typename list<T>::iterator insert(list <T> ::iterator it, const T & t);
		



		bool find(const T & t);
		void erase(list <T> ::iterator it);
		list <T> ::iterator end();
		list <T> ::iterator begin();


		list <T> ::reverse_iterator rend();
		list <T> ::reverse_iterator rbegin();


		~list()
		{
			clear();
		}


	};

	template <class T>
	 T &list<T>::front()
	{
		if (empty())
		{
			throw "ERROR: unable to access data from an empty list";
		}

		else
		{
			return pHead->data;
		}
	}

	template <class T>
	 T &list<T>::back()
	{
		if (empty())
		{
			throw "ERROR: unable to access data from an empty list";
		}

		else
		{
			return pTail->data;
		}
	}

	template <class T>
	void list<T>::clear()
	{
		for (numElements; numElements >= 1; numElements--)
		{
			pop_front();
		}
	}

	// These seem flawed...


	template <class T>
	void list<T>::push_back(T item)
	{
		Node <T> *itemNode;
		try
		{	
			itemNode = new Node<T>(item); //making a new node
			numElements++;
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: unable to allocate a new node for a list";
		}

		if (pTail == nullptr)
		{
			pTail = itemNode;
			pHead = itemNode;
		}

		else 
		{
			
			itemNode->pPrev = pTail;

			pTail = itemNode;
			numElements++;
		}

	}

	template <class T>
	void list<T>::push_front(T item)
	{
		Node <T> *itemNode;
		try
		{
			itemNode = new Node<T>(item); //making a new node
			numElements++;
		}
		catch (std::bad_alloc)
		{
			throw "ERROR: unable to allocate a new node for a list";
		}

		if (pHead == nullptr)
		{
			pHead = itemNode;
			pTail = itemNode;
		}

		else
		{
			itemNode->pNext = pHead;
			pHead = itemNode;

			numElements++;
		}

	}

	template <class T>
	void list<T>::pop_front()
	{
		if (empty())
			return;
		if (numElements == 1)
		{
			delete pHead;
			pHead = nullptr;
			pTail = nullptr;
			return;
		}
		pHead = pHead->pNext;
		delete pHead->pPrev;
		pHead->pPrev = nullptr;
		numElements--;
		return;
	}

	template<class T>
	void list<T>::pop_back()
	{
		if (empty())
			return;
		if (numElements == 1)
		{
			delete pTail;
			pHead = nullptr;
			pTail = nullptr;
			return;
		}
		pTail = pTail->pPrev;
		delete pTail->pNext;
		pTail->pNext = nullptr;
		numElements--;
		return;
	}



	template <class T>
	class list <T> ::iterator
	{

          public:
           Node<T> *p;

		
			//Constructors/Destructor
			iterator()
			{
				p = nullptr;
			}

			iterator(Node <T> *pNewit)    //I think its just supposed to copy the iterator, meaning just the pointer - Ken
			{
				this->p = pNewit;
				/*
				Node <T> *copyNode = nullptr;
				Node <T> *tempNode = pNewit;
				Node <T> *pHead = nullptr;
				bool first = true;
				do
				{
					if (first)
					{
						pHead = tempNode;
						copyNode = pHead;
						first = false;
						tempNode = tempNode->pNext;
					}
					else
					{
						
						tempNode = tempNode->pNext;
						copyNode = copyNode->pNext;
					}
				} while (tempNode != nullptr);*/
	
			}

			iterator(const iterator &rhs)
			{
				this->p = rhs.p;
			}

			//Operators
			iterator operator=(const iterator &rhs)
			{
				p = rhs.p;
				/*
				Node <T> *copyNode = nullptr;
				Node <T> *tempNode = rhs.p;
				Node <T> *pHead = nullptr;
				bool first = true;
				do
				{
					if (first)
					{
						pHead = tempNode;
						copyNode = pHead;
						first = false;
						tempNode = tempNode->pNext;
					}
					else
					{

						tempNode = tempNode->pNext;
						copyNode = copyNode->pNext;
					}
				} while (tempNode != nullptr);

				return pHead;*/
				return p;
			}

			iterator operator++()
			{
				if (p->pNext)
				{
					p = p->pNext;
				}
				return *this;
			}

			iterator operator--()
			{
				if (p->pPrev)
				{
					p = p->pPrev;
				}
				return *this;
			}

			bool operator==(iterator it)
			{
				return *this == it;
			}

			bool operator!=(iterator it)
			{
				return this->p != it.p;
			}

			T operator*()
			{
				if (p)
				{
					return p->data;
				}
				else
				{
					throw "ERROR: Cannot dereference a NULL pointer";
				}
			}

		};

	template <class T>
	class list <T> ::reverse_iterator
	{

		private:
			Node<T> *p;

		public:
			reverse_iterator()
			{
				p = nullptr;
			}

			reverse_iterator(Node <T> *pNew)
			{
				p = pNew;
                        }

			reverse_iterator operator++()
			{
                           if (p->pNext)
				{
                                   p = p->pNext;
				}
				return *this;
			}
                        
			reverse_iterator operator--()
			{
                           if (p->pPrev)
				{
                                   p = p->pPrev;
				}
			}
                        
			bool operator==(reverse_iterator it)
			{
                           return *this == it;
			}
                        
			bool operator!=(reverse_iterator it)
			{
                           return this->p != it.p;
			}
                        
			T operator*()
			{
                           return this->p->data;
			}
                        
        };

	//C++ is wack yo, Timanese Translator's note ("C++ wants all mentions of iterators to be after the definition of the iterators in question)

	template <class T>
	typename list<T>::iterator list<T>::begin()
	{
		return list<T>::iterator(this->pHead);
	}

	template<class T>
	typename list<T>::reverse_iterator list<T>::rend()
	{
		return list<T>::reverse_iterator(this->pHead);
	}

	template<class T>
	typename list<T>::reverse_iterator list<T>::rbegin()
	{
		return list<T>::reverse_iterator(nullptr);
	}

	template <class T>
	typename list<T>::iterator list<T>::end()
	{
		return list<T>::iterator(nullptr);
	}

	template<class T>
	bool list<T>::find(const T & t)
	{
		if (pHead == nullptr)
		{
			return false;
		}

		for (Node <T> *tempNode = pHead; tempNode; tempNode = tempNode->pNext)
		{
			if (tempNode->data == t)
			{
				return true;
			}
		}

		return false;
	}

	template <class T>
	void list<T>::erase(list <T> ::iterator it)
	{
		Node<T> *TempNode = new Node<T>;
		TempNode = it.p;
		if (TempNode == nullptr)
		{
			return;
		}
		
		if (TempNode->pNext == nullptr)
		{
			TempNode->pPrev->pNext = nullptr;
		}
		else if (TempNode->pPrev == nullptr)
		{
			TempNode->pNext->pPrev = nullptr;
		}
		else
		{
			TempNode->pNext->pPrev = TempNode->pPrev;
			TempNode->pPrev->pNext = TempNode->pNext;
		}

		delete TempNode;
		return;
	}

	template <class T>
	typename list<T>::iterator list<T>::insert(list <T>::iterator it, const T & t)
	{
		Node <T> *pNew;
		try
		{
			pNew = new Node<T>(t);
		}
		catch (std::bad_alloc)
		{
			throw "unable to allocate a new node for a list";
		}

		if (it != NULL)
		{
			pNew->pNext = it.p;
			pNew->pPrev = it.p->pPrev;
			it.p->pPrev = pNew;

			if (pNew->pPrev != nullptr)
			{
				pNew->pPrev->pNext = pNew;
			}
		}

		return pNew;
	}




}
