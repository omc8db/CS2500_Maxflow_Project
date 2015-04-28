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
  for (int i = 0; i < m_num_nodes; i++)
  {
    m_adjacency_matrix[i] = new adjacencyMatrixEntry[m_num_nodes];
  }

}

DirectedFlowGraph::~DirectedFlowGraph()
{
  // TODO Auto-generated destructor stub

  for (int i = 0; i < m_num_nodes; i++)
  {
    delete[] m_adjacency_matrix[i];
  }
  delete[] m_adjacency_matrix;
}

std::ostream& operator<<(std::ostream& out, DirectedFlowGraph& rhs)
{
  for (int i = 0; i < rhs.getNumNodes(); i++)
  {
    out << "-----\t";
  }
  out << std::endl;
  for (int i = 0; i < rhs.getNumNodes(); i++)
  {
    for (int j = 0; j < rhs.getNumNodes(); j++)
    {
      out << "| " << rhs.m_adjacency_matrix[i][j].flow << " / "
          << rhs.m_adjacency_matrix[i][j].capacity << "\t";
    }
    out << "|" << std::endl;
  }
  for (int i = 0; i < rhs.getNumNodes(); i++)
  {
    out << "-----\t";
  }
  return out;
}

int DirectedFlowGraph::getNumNodes()
{
  return m_num_nodes;
}

DirectedFlowGraph::Node DirectedFlowGraph::getSource()
{
  DirectedFlowGraph::Node result;
  result.index = 0;
  return result;
}

DirectedFlowGraph::Node DirectedFlowGraph::getSink()
{
  DirectedFlowGraph::Node result;
  result.index = 1;
  return result;
}

void DirectedFlowGraph::populateRandom(int max_capacity,
    int percent_connectedness)
{

  //Fill with random data
  for (int i = 0; i < getNumNodes(); i++)
  {
    for (int j = 0; j < getNumNodes(); j++)
    {
      //Roll the dice to see if we create a connection
      if ((rand() % 100) < percent_connectedness)
      {
        m_adjacency_matrix[i][j].capacity = rand() % max_capacity;
      }
      else
      {
        m_adjacency_matrix[i][j].capacity = 0;
      }
    }
  }

  //Eliminate self-connections
  for (int i = 0; i < getNumNodes(); i++)
  {
    m_adjacency_matrix[i][i].capacity = 0;
  }

  //Make sure that source has no connections going in
  for (int i = 1; i < getNumNodes(); i++)
  {
    m_adjacency_matrix[i][0].capacity = 0;
  }

  //Make sure that sink has no connections going out
  for (int i = 1; i < getNumNodes(); i++)
  {
    m_adjacency_matrix[1][i].capacity = 0;
  }

  return;
}
