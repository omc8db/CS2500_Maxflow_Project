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
  int maxflow, slack, current_flow;
  std::vector<DirectedFlowGraph::DirectedFlowEdge> edges;

  //Initialize the flag to true so that we enter the loop
  bool foundSink = true;

  DirectedFlowGraph::Node* parent;
  int* value;
  bool* inserted;
  parent = new DirectedFlowGraph::Node[graph.getNumNodes()];
  value = new int[graph.getNumNodes()];
  inserted = new bool[graph.getNumNodes()];
  maxflow = 0;

  //If our last path found the sink, we can continue searching
  //Breaks out when we can no longer find a path to the sink
  while (foundSink == true)
  {
    foundSink = false;

    //No nodes start out inserted
    for (int i = 0; i < graph.getNumNodes(); i++)
    {
      inserted[i] = false;
      value[i] = 0;
      parent[i] = NULL_NODE;
      //TODO: assert
    }

    //Always start the search at the source
    Q.push_back(graph.getSource());

    inserted[graph.getSource().index] = true;
    value[graph.getSource().index] = INFINITY;
    //parent of source is null

    while (!Q.empty())
    {
      current = Q.front();
      Q.pop_front();

      edges = graph.getAllEdges(current);
      for (unsigned int i = 0; i < edges.size(); i++)
      {
        if (edges[i].parent == current) // Forward flow
        {
          if (!inserted[edges[i].child.index])
          {
            slack = edges[i].capacity - edges[i].flow;
            assert(slack >= 0);
            if (slack > 0)
            {
              Q.push_back(edges[i].child);
              inserted[edges[i].child.index] = true;
              parent[edges[i].child.index] = current;
              //Value calculation is a little complicated
              if (value[current.index] == INFINITY)
                value[edges[i].child.index] = slack;
              else
                value[edges[i].child.index] = std::min(slack,
                    value[current.index]);
            }
          }
        }
        else if (edges[i].child == current) // reverse flow
        {
          if (!inserted[edges[i].parent.index])
          {
            slack = edges[i].flow;
            if (slack > 0)
            {
              Q.push_back(edges[i].parent);
              inserted[edges[i].parent.index] = true;

              // if we're sending flow backwards, when we augment we will go from child to parent
              parent[edges[i].parent.index] = current;
              value[edges[i].parent.index] = slack;
            }
          }
        } else
        {
          cout << "Error: Edge does not connect to current node";
          assert(false);
        }

        if (inserted[graph.getSink().index])
        {

          cout << "Got the sink" << endl;
          foundSink = true;
          //Clear the queue so we know to stop
          Q.clear();
        }
      }
    }

    if(foundSink)
    {
      current_flow = value[graph.getSink().index];
      assert(current_flow > 0);

      temp = graph.getSink();
      while(!(temp == graph.getSource()))
      {
        assert(!(parent[temp.index] == NULL_NODE));
        graph.augment(parent[temp.index], temp, current_flow);
        temp = parent[temp.index];
      }

    }
  }
  //Invariant: A path has been found from the source to the sink

  //Augment the path
  delete[] parent;
  delete[] inserted;
  delete[] value;

  return maxflow;
}

std::vector<DirectedFlowGraph::DirectedFlowEdge> CalculateMinCut(
    DirectedFlowGraph & graph)
{
  DirectedFlowGraph::Node source = graph.getSource();
  return RecursiveMinCut(graph, source);
}

std::vector<DirectedFlowGraph::DirectedFlowEdge> RecursiveMinCut(
    DirectedFlowGraph & graph, DirectedFlowGraph::Node & node)
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
