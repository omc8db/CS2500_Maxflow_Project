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

//Interface struct


//Used internally. Not recommended for external use.

class DirectedFlowGraph {
public:
//---------------Types----------------------//
	struct Node;
	struct DirectedFlowEdge;

//---------------Constructor / Destructor----------------------//


	// Create a new directed flow graph
	// Inputs: Number of intermediate nodes. If zero, graph will just have source and sink
	DirectedFlowGraph(int intermediate_nodes);

	virtual ~DirectedFlowGraph();


//---------------Accessors----------------------//


	// Outputs the directed flow graph in the form of XML
	friend std::ostream& operator<<(std::ostream& lhs, DirectedFlowGraph& rhs);

	//Returns a node object referring to the source or sink, respectively
	Node* getSource();
	Node* getSink();

	// Returns a list of all edges flowing out of the given node, whether or not
	// there is any slack
	std::vector<DirectedFlowEdge>getOutEdges(const Node& start_node);
	std::vector<DirectedFlowEdge>getInEdges(const Node& start_node);
	std::vector<DirectedFlowEdge>getAllEdges(const Node& start_node);

	//Returns a list of the edges flowing out of the given node with slack
	std::vector<DirectedFlowEdge>getOutEdgesWithSlack(const Node& start_node);
    std::vector<DirectedFlowEdge>getInEdgesWithSlack(const Node& start_node);
    std::vector<DirectedFlowEdge>getAllEdgesWithSlack(const Node& start_node);


//--------------Mutators----------------------//
    void populateRandom();

private:
//---------------Types----------------------//
	struct adjacencyMatrixEntry;

//---------------Members----------------------//
	adjacencyMatrixEntry** m_adjacency_matrix;
	int m_num_nodes;
};



#endif /* DIRECTEDFLOWGRAPH_H_ */
