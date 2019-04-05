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
   slots = nullptr;
}

/******************************************
 *Copy Constructor
 * let the lower data types take care of the heavy lifting for you
 *******************************************/
Graph::Graph(const Graph &rhs)
{
   this->slots = rhs.slots;
   this->vertices = rhs.vertices;
}

/*********************************************
 *NON-DEFAULT Constructor
 *we know how many vertices there are, and here we go
 *********************************************/
Graph::Graph(int vertices)
{
   if(vertices == 0)
   {
      slots = nullptr;
      return;
   }

   try
   {
      slots = new custom::set<Vertex>[vertices];
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Bad allocation";
   }
   this->vertices = vertices;
   return;
      
}

/************************************************
 *SIZE
 *returns the number of vertices in the graph
 **********************************************/
int Graph::size()
{
   return vertices;
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
 * Adds an edge connection to the graph
 ***********************/
void Graph::add(Vertex v1, Vertex v2)
{
   slots[v1.index()].insert(v2);
   //slots->insert(v1, v2);
}

/*
void Graph::add(Node<Vertex> data, Vertex v1, Vertex v2)
{
   slots.insert(data, v1, v2);
}
*/

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
   return slots->size();
}

/**********************************************
 * ISEDGE
 * a crucial function to tell is a connection in a given direction exists
 * includes a constant version
 *********************************************/
bool Graph::isEdge(Vertex v1, Vertex v2)
{
   if(slots[v1.index()].find(v2) == nullptr)
      return false;
   else
      return true;
}

bool Graph::isEdge(const Vertex v1, const Vertex v2) const
{
   if(slots[v1.index()].find(v2) == nullptr)
      return false;
   else
      return true;
}
