/*
 * EdmondsKarp.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: Owen Chiaventone
 */

#include "EdmondsKarp.h"

int EdmondsKarpMaxflow(DirectedFlowGraph& graph)
{
  std::deque<DirectedFlowGraph::Node> Q;
  DirectedFlowGraph::Node current;
  int maxflow;


  //No nodes start out inserted
  bool* inserted = new bool[graph.getNumNodes()];
  for(int i = 0; i < graph.getNumNodes(); i++)
  {
    inserted[i] = false;
    //TODO: assert
  }

  Q.push_back(graph.getSource());
  inserted[graph.getSource().index] = false;


  //Dummy value
  return 1;
}

std::vector<DirectedFlowGraph::DirectedFlowEdge> CalculateMinCut(
    DirectedFlowGraph& graph)
{
  DirectedFlowGraph::Node source = graph.getSource();
  return RecursiveMinCut(graph, source);
}

std::vector<DirectedFlowGraph::DirectedFlowEdge> RecursiveMinCut(
    DirectedFlowGraph& graph, DirectedFlowGraph::Node& node)
{
  std::vector<DirectedFlowGraph::DirectedFlowEdge> out_edges, result;
  out_edges = graph.getOutEdges(node);

  //If no edges going out, return empty set
  if (out_edges.size() == 0)
  {
    return result;
  }

  for (unsigned int i = 0; i < out_edges.size(); i++)
  {

    if (out_edges[i].flow == out_edges[i].capacity)
    {
      //This edges is in the mincut, so add it
      result.push_back(out_edges[i]);
    }
    else
    {
      std::vector<DirectedFlowGraph::DirectedFlowEdge> temp;

      //This edge is not in the mincut, so continue to search outward
      temp = RecursiveMinCut(graph, out_edges[i].child);
      result.insert(result.end(), temp.begin(), temp.end());
    }
  }

  return result;
}
