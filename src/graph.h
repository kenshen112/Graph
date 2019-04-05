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

#include <string>
#include "list.h"
#include "set.h"
#include "vertex.h"
#include "map.h"

class Graph
{
  private:
   custom::set <Vertex> *slots;
   int vertices;

  public:
   //constructors
   Graph();
   Graph(const Graph &rhs);
   Graph(int vertices); //we know how many vertex there are

   //assignment operator
   Graph & operator = (const Graph & rhs) throw (const char *);

   //interface
   int size();
   int size() const; //added const version to fix compiler error
   int capacity();
   bool empty();
   void clear();
   void add(Vertex v1, Vertex v2);
   void add(Vertex v1, custom::set <Vertex> vs);
   void add(Node<Vertex> data, Vertex v1, Vertex v2);
   bool isEdge(Vertex v1, Vertex v2);
   bool isEdge(const Vertex v1, const Vertex v2) const; //added a const version to fix compiler error
   //set <Vertex> findEdges(Vertex v); //i think this is declared right?
   //list <Vertex> findPath(Vertex v1, Vertex v2); //again i think this is right?
  
};




#endif
