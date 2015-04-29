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
  DirectedFlowGraph::Node current, temp;
  int maxflow, slack;
  std::vector<DirectedFlowGraph::DirectedFlowEdge> edges;
  DirectedFlowGraph::Node* parent;
  int* value;
  bool* inserted;





  current = graph.getSource();
  value[current.index] = INFINITY;
  inserted[graph.getSource().index] = false;
  Q.push_back(current);

  while(!Q.empty())
  {
    current = Q.front();
    Q.pop_front();

    //No nodes start out inserted
    inserted = new bool[graph.getNumNodes()];
    value = new int[graph.getNumNodes];
    for(int i = 0; i < graph.getNumNodes(); i++)
    {
      inserted[i] = false;
      value[i] = 0;
      //TODO: assert
    }

    edges = graph.getOutEdges(current);
    for(int i = 0; i < edges.size(); i++)
    {
      if(inserted[edges[i].child.index] == false)
      {
        slack = edges[i].capacity - edges[i].flow;
        assert(slack >= 0);
        if(slack > 0)
        {
          temp = edges[i].child;

        }
      }

      delete[] inserted;
      delete[] value;
    }


  }

  delete[] inserted;
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
