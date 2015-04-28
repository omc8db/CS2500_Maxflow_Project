/*
 * DirectedFlowGraph.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: Owen Chiaventone
 */

#include "DirectedFlowGraph.h"

//---------------Constructor / Destructor----------------------//

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

  for (int i = 0; i < m_num_nodes; i++)
  {
    delete[] m_adjacency_matrix[i];
  }
  delete[] m_adjacency_matrix;
}

//---------------Accessors----------------------//

std::ostream& operator<<(std::ostream& out, DirectedFlowGraph& rhs)
{
  for (int i = 0; i < rhs.getNumNodes(); i++)
  {
    out << "-----\t\t";
  }
  out << std::endl;
  for (int i = 0; i < rhs.getNumNodes(); i++)
  {
    for (int j = 0; j < rhs.getNumNodes(); j++)
    {
      out << "| " << rhs.m_adjacency_matrix[i][j].flow << " / "
          << rhs.m_adjacency_matrix[i][j].capacity << "     \t";
    }
    out << "|" << std::endl;
  }
  for (int i = 0; i < rhs.getNumNodes(); i++)
  {
    out << "-----\t\t";
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

std::vector<DirectedFlowGraph::DirectedFlowEdge> DirectedFlowGraph::getOutEdges(
    const Node& start_node)
{
  std::vector<DirectedFlowGraph::DirectedFlowEdge> result;
  DirectedFlowGraph::DirectedFlowEdge buffer;

  for (int i = 0; i < getNumNodes(); i++)
  {
    //From start_node.index to node i
    if (m_adjacency_matrix[start_node.index][i].capacity > 0)
    {
      buffer.capacity = m_adjacency_matrix[start_node.index][i].capacity;
      buffer.flow = m_adjacency_matrix[start_node.index][i].flow;
      buffer.parent = start_node;
      buffer.child.index = i;

      result.push_back(buffer);
    }
  }
  return result;
}

std::vector<DirectedFlowGraph::DirectedFlowEdge> DirectedFlowGraph::getInEdges(
    const Node& start_node)
{
  std::vector<DirectedFlowGraph::DirectedFlowEdge> result;
  DirectedFlowGraph::DirectedFlowEdge buffer;

  for (int i = 0; i < getNumNodes(); i++)
  {
    //From i to start_node.index
    if (m_adjacency_matrix[i][start_node.index].capacity > 0)
    {
      buffer.capacity = m_adjacency_matrix[i][start_node.index].capacity;
      buffer.flow = m_adjacency_matrix[i][start_node.index].flow;
      buffer.parent.index = i;
      buffer.child = start_node;

      result.push_back(buffer);
    }
  }
  return result;
}

std::vector<DirectedFlowGraph::DirectedFlowEdge> DirectedFlowGraph::getAllEdges(
    const Node& start_node)
{
  std::vector<DirectedFlowGraph::DirectedFlowEdge> out_edges, in_edges, result;

  out_edges = getOutEdges(start_node);
  in_edges = getInEdges(start_node);

  result.insert(result.end(), out_edges.begin(), out_edges.end());
  result.insert(result.end(), out_edges.begin(), out_edges.end());
  return result;
}

std::vector<DirectedFlowGraph::DirectedFlowEdge> DirectedFlowGraph::getEdgesWithSlack(
    const Node& start_node)
{
  std::vector<DirectedFlowGraph::DirectedFlowEdge> result;
  std::vector<DirectedFlowGraph::DirectedFlowEdge> temp;

  temp = DirectedFlowGraph::getOutEdges(start_node);
  for (unsigned int i = 0; i < temp.size(); i++)
  {
    if (temp[i].flow < temp[i].capacity)
    {
      result.push_back(temp[i]);
    }
  }

  temp = DirectedFlowGraph::getInEdges(start_node);
  for (unsigned int i = 0; i < temp.size(); i++)
  {
    if (temp[i].flow > 0)
    {
      result.push_back(temp[i]);
    }
  }

  return result;
}

//--------------Mutators----------------------//

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

//Eliminate loops
  for (int i = 0; i < getNumNodes(); i++)
  {
    for (int j = 0; j < getNumNodes(); j++)
    {
      //If capacities from i to j and from j to i are nonzero
      //Delete one of them
      if ((m_adjacency_matrix[i][j].capacity != 0)
          && (m_adjacency_matrix[j][i].capacity != 0))
      {
        //50 / 50 chance for which edge to delete
        if (rand() % 2)
        {
          m_adjacency_matrix[i][j].capacity = 0;
        }
        else
        {
          m_adjacency_matrix[j][i].capacity = 0;
        }
      }
    }
  }
  return;
}

void DirectedFlowGraph::setFlow(DirectedFlowEdge& edge, int flow)
{
  assert(flow <= edge.capacity);
  assert(flow > 0);

  //Flow from parent to child = flow
  m_adjacency_matrix[edge.parent.index][edge.child.index].flow = flow;
  edge.flow = flow;
}
