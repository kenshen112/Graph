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
   this->columns = rhs.columns;
   this->rows = rhs.rows;   
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

/************************************************************
 *ASSIGNMENT operator
 *make one graph into a copy of the other
 ***********************************************************/
Graph & Graph :: operator = (const Graph & rhs) throw (const char *)
{
   try
   {
      slots = new custom::set<Vertex>[rhs.vertices];
   }
   catch(std::bad_alloc)
   {
      throw "Error: Bad allocation";
   }
   
   for(int i = 0; i != rhs.vertices; i++)
   {
      slots[i] = rhs.slots[i];
   }

   rows = rhs.rows;
   columns = rhs.columns;

   return *this;
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

/**************************************
 * Add in bulk
 * this version of add takes a vertex to be the index,
 * and a set of vertices detailing all of its connections, a little trickier? maybe.
 *********************************************/
void Graph::add(Vertex v1, custom::set<Vertex> vs)
{
   slots[v1.index()] = vs;
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
   return slots->size();
}

/**********************************************
 * ISEDGE
 * a crucial function to tell is a connection in a given direction exists
 * includes a constant version
 *********************************************/
bool Graph::isEdge(Vertex v1, Vertex v2)
{
   if(slots[v1.index()].find(v2) == slots[v1.index()].end())
      return false;
   else
      return true;
}

bool Graph::isEdge(const Vertex v1, const Vertex v2) const
{
   if(slots[v1.index()].find(v2) == slots[v1.index()].end())
      return false;
   else
      return true;
}

/************************************************
 * FIND EDGES
 * remember how we could add edges one at a time, or in bulk?
 * well now we can find edges, and we can find edges in bulk!
 ************************************************/
custom::set <Vertex> Graph::findEdges(Vertex v)
{
   return slots[v.index()];
}


/***********************************************
 * FIND HEURISTIC
 * assuming a grid organization, it should be possible to find
 * the 'distance' between two vertices
 ************************************************/
int Graph::findHeuristic(Vertex v1, Vertex v2)
{
   int a = v1.index();
   int b = v2.index();

   a++;
   b++;
   //if solutions aren't working, try switching to divide by rows instead
   int ax = a % columns;
   int ay = a / columns;

   int bx = b % columns;
   int by = b / columns;

   int H;

   H = (bx - ax) + (by - ay); //using the manhattan distances

   return H;
      
}


/*************************************************
 * FIND PATH
 * Traverses the graph in a* method to find the shortest path
 **************************************************/
custom::vector <Vertex> Graph::findPath(Vertex v1, Vertex v2)
{
   custom::vector <Vertex> path;

   custom::list<Vertex> open;
   custom::list<Vertex> closed;

   Vertex current = v1;
   Vertex prior;

   open.push_back(current);
   
   int totalDistance = 0;

   int F = totalDistance + findHeuristic(v1, v2);

   while(current != v2)
   {
      custom::set<Vertex>::iterator it;
      it = slots[current.index()].begin();
      
      for(it; it != slots[current.index()].end(); it++)
      {
         if(!(open.find(*it)) && !(closed.find(*it)))
         {
            open.push_back(*it);
         }

         
            
         
      }
   }
   

   
   
   
   return path;
}

