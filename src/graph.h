/******************************************************
 * GRAPH.H
 * Authors:
 *      Ken, Tim, and Jessica
 * course:
 *      CS235
 ****************************************************/
//remember guys, this is not a template class, so only prototypes can go here!

#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"
#include "set.h"
#include "vertex.h"

class Graph
{
  private:
   set <Vertex> *slots;

  public:
   //constructors
   Graph();
   Graph(const Graph &rhs);

   //assignment operator


   //interface
   int size();
   int capacity();
   bool empty();
   void clear();
   void add(Vertex v1, Vertex v2);
   bool isEdge(Vertex v1, Vertex v2);
   //set <Vertex> findEdges(Vertex v); //i think this is declared right?
   //list <Vertex> findPath(Vertex v1, Vertex v2); //again i think this is right?


   
};




#endif
