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

    current = graph.getSource();
    value[current.index] = INFINITY;
    Q.push_back(current);
    inserted[current.index] = true;

    while (!Q.empty() && foundSink == false)
    {
      current = Q.front();
      Q.pop_front();

      //vector edges = edges out of current node
      //Getting all edges for which the current node is the parent node
      edges = graph.getOutEdges(current);
      for (unsigned int i = 0; i < edges.size(); i++)
      {
        if (inserted[edges[i].child.index] == false)
        {
          //slack of edge i = capacity of edge - flow on the edge
          slack = edges[i].capacity - edges[i].flow;
          assert(slack >= 0);

          if (slack > 0)
          {
            //add the child node to the queue and update its properties
            temp = edges[i].child;
            Q.push_back(temp);
            inserted[edges[i].child.index] = true;
            parent[edges[i].child.index] = current;

            //Check if the parent can source infinite flow (i.e. is the source)
            if (value[edges[i].parent.index] == INFINITY)
              value[edges[i].child.index] = slack;
            else
              value[edges[i].child.index] = std::min(slack,
                  value[current.index]);
          }

          //check if we've found the sink
          if (edges[i].child.index == graph.getSink().index)
          {
            std::cout << "FOUND SINK!" << std::endl;
            foundSink = true;
          }

        }

      }

      //Get all edges for which the current node is the child
      edges = graph.getInEdges(current);
      for (unsigned int i = 0; i < edges.size(); i++)
      {
        if (inserted[edges[i].parent.index] == false)
        {
          slack = edges[i].flow;
          assert(slack >= 0);

          //Check if we can push flow backwards
          if (slack > 0)
          {
            temp = edges[i].parent;
            Q.push_back(temp);
            inserted[edges[i].parent.index] = true;
            //Flow will go backwards here, so from the current node to the parent
            parent[edges[i].parent.index] = current;
            value[edges[i].parent.index] = std::min(slack,
                value[current.index]);
          }
        }
      }
    }

    //Invariant: A path has been found from the source to the sink

    //Augment the path
    if (foundSink)
    {
      //Work backwards from sink to source
      temp = graph.getSink();
      current_flow = value[temp.index]; //Amount of flow we could push to the sink
      while (temp.index != graph.getSource().index)
      {
        graph.augment(parent[temp.index], temp, current_flow);
        temp = parent[temp.index];
      }

      maxflow += current_flow;
    }
  }
  delete[] parent;
  delete[] inserted;
  delete[] value;
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
