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
   custom::set <Vertex> *slots;

  public:
   //constructors
   Graph();
   Graph(const Graph &rhs);

   //assignment operator


   //interface
   int size();
   int size() const; //added const version to fix compiler error
   int capacity();
   bool empty();
   void clear();
   void add(Vertex v1, Vertex v2);
   bool isEdge(Vertex v1, Vertex v2);
   bool isEdge(const Vertex v1, const Vertex v2) const; //added a const version to fix compiler error
   //set <Vertex> findEdges(Vertex v); //i think this is declared right?
   //list <Vertex> findPath(Vertex v1, Vertex v2); //again i think this is right?


   
};




#endif
