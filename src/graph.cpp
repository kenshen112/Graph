/**************************************************
 * GRAPH.CPP
 * Authors:
 *      Tim, Jessica, and Ken
 * Course:
 *      CS235
 *************************************************/
// DECLARE ALL THE THNGS!!!!
//I declare BANKRUPTCY!!
//thats not how the force works!!

#include "graph.h"
#include "list.h"

/******************************************
 *Constructors
 * Because we aren't really storing any data, we don't need much here
 ********************************************/
Graph::Graph()
{
   
}

/******************************************
 *Copy Constructor
 * let the lower data types take care of the heavy lifting for you
 *******************************************/
Graph::Graph(const Graph &rhs)
{
   slots = rhs.slots;
}

/************************************************
 *SIZE
 *returns the number of vertices in the graph
 **********************************************/
int Graph::size()
{
   int size = 0;

   for(int i = 0; i != slots->size(); i++);
   {
      size += slots[i].size();
   }
   
   return size;
}

/************************************************
 *SIZE - CONST
 *returns the number of vertices in the graph
 ***********************************************/
int Graph::size() const
{
   return slots->size();
}

/***********************************************
 *EMPTY
 *returns true if there are no vertices in the graph
 *********************************************/
bool Graph::empty()
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
void Graph::add(Vertex v1, Vertex v2)
{
   slots->begin.insert(v1, v2);
}


void Graph::add(Node<Vertex> data, Vertex v1, Vertex v2)
{
   slots->begin.insert(data, v1, v2);
}


/************************************************
 *CLEAR
 *removes all vertices in the graph
 ***********************************************/
void Graph::clear()
{
   slots->clear();
}

/**********************************************
 *CAPACITY
 *returns the list size function
 *********************************************/
int Graph::capacity()
{
   return slots->begin.size();
}
