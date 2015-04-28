/*
 * DirectedFlowGraph.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: Owen Chiaventone
 */

#include "DirectedFlowGraph.h"

struct DirectedFlowGraph::Node
{
	int index;
};

struct DirectedFlowGraph::DirectedFlowEdge
{

	int capacity;
	int flow;
	DirectedFlowGraph::Node parent;
	DirectedFlowGraph::Node child;
};

struct DirectedFlowGraph::adjacencyMatrixEntry
{
  int capacity;
  int flow;
};

DirectedFlowGraph::DirectedFlowGraph(int intermediate_nodes)
{
	//Add extra two nodes for source and sink
    m_num_nodes = intermediate_nodes + 2;
	m_adjacency_matrix = new adjacencyMatrixEntry*[m_num_nodes];
	for(int i = 0; i < m_num_nodes; i++)
	{
	  m_adjacency_matrix[i] = new adjacencyMatrixEntry[m_num_nodes];
	}


}

DirectedFlowGraph::~DirectedFlowGraph() {
	// TODO Auto-generated destructor stub

    for(int i = 0; i < m_num_nodes; i ++)
    {
      delete[] m_adjacency_matrix[i];
    }
	delete[] m_adjacency_matrix;
}

