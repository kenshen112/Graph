/**************************************************
 * GRAPH.CPP
 * Authors:
 *      Tim, Jessica, and Ken
 * Course:
 *      CS235
 *************************************************/
// DECLARE ALL THE THNGS!!!!
//I declare BANKRUPTCY!!
#include "graph.h"
#include "list.h"

template <class T>
Graph<T>::Graph()
{
	slots = nullptr;

}

template<class T>
Graph<T>::Graph(const Graph<T> &rhs)
{
	this = rhs;
}



/************************************************
 *SIZE
 *returns the number of vertices in the graph
 **********************************************/
template <class T>
int Graph<T>::size()
{
   return slots->size(); //use the set's size to find the num of Vertices?
}

/************************************************
 *SIZE - CONST
 *returns the number of vertices in the graph
 ***********************************************/
template <class T>
int Graph<T>::size() const
{
   return slots->size();
}

/***********************************************
 *EMPTY
 *returns true if there are no vertices in the graph
 *********************************************/
template <class T>
bool Graph<T>::empty()
{
   if(slots->size() == 0)
      return true;
   else
      return false;
}


/************************
* ADD
* Add's to the graph
***********************/
template <class T>
void Graph<T>::add(Vertex v1, Vertex v2)
{
	slots->begin.insert(v1, v2);
}


template <class T>
void Graph<T>::add(Node<T> data, Vertex v1, Vertex v2)
{
	slots->begin.insert(data, v1, v2);
}


/************************************************
 *CLEAR
 *removes all vertices in the graph
 ***********************************************/
template<class T>
void Graph<T>::clear()
{
   slots->clear();
}

/**********************************************
 *CAPACITY
 *returns the list size function
 *********************************************/
template <class T>
int Graph<T>::capacity()
{
	return slots->begin.size();
}
