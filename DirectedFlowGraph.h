/*
 * DirectedFlowGraph.h
 *
 *  Created on: Apr 27, 2015
 *      Author: Owen Chiaventone
 */

#ifndef DIRECTEDFLOWGRAPH_H_
#define DIRECTEDFLOWGRAPH_H_

#include <iostream>
#include <vector>
#include <stdlib.h>

class DirectedFlowGraph
{
public:
//---------------Types----------------------//
  struct Node
  {
    int index;
  };

  struct DirectedFlowEdge
  {
    int capacity;
    int flow;
    DirectedFlowGraph::Node parent;
    DirectedFlowGraph::Node child;
  };

//---------------Constructor / Destructor----------------------//

// Create a new directed flow graph
// Inputs: Number of intermediate nodes. If zero, graph will just have source and sink
  DirectedFlowGraph(int intermediate_nodes);

  virtual ~DirectedFlowGraph();

//---------------Accessors----------------------//

// Outputs the directed flow graph in the form of XML
  friend std::ostream& operator<<(std::ostream& out, DirectedFlowGraph& rhs);

  //Outputs the number of nodes in the graph, including source and sink
  int getNumNodes();

  //Returns a node object referring to the source or sink, respectively
  Node getSource();
  Node getSink();

  // Returns a list of all edges flowing out of the given node, whether or not
  // there is any slack
  std::vector<DirectedFlowEdge> getOutEdges(const Node& start_node);
  std::vector<DirectedFlowEdge> getInEdges(const Node& start_node);
  std::vector<DirectedFlowEdge> getAllEdges(const Node& start_node);

  //Returns a list of the edges flowing out of the given node with slack
  std::vector<DirectedFlowEdge> getOutEdgesWithSlack(const Node& start_node);
  std::vector<DirectedFlowEdge> getInEdgesWithSlack(const Node& start_node);
  std::vector<DirectedFlowEdge> getAllEdgesWithSlack(const Node& start_node);

//--------------Mutators----------------------//
  //Assigns a set of random capacities.
  // Inputs: max_capacity - All assigned capacities will be less than or equal to this value
  //         percent_connectedness - Chance for a connection to exist between any two nodes. 0 to 100
  void populateRandom(int max_capacity, int percent_connectedness);

private:
//---------------Types----------------------//
  struct adjacencyMatrixEntry
  {
    int capacity;
    int flow;
  };

//---------------Members----------------------//

  //Data is accessed as m_adjacency_matrix[from][to]
  //index 0 is reserved for source, 1 is sink
  adjacencyMatrixEntry** m_adjacency_matrix;
  int m_num_nodes;
};

#endif /* DIRECTEDFLOWGRAPH_H_ */
