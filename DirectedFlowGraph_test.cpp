/*
 * DirectedFlowGraph_test.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: mrdtdev
 */

#include "DirectedFlowGraph.h"
using namespace std;

void TestDirectedFlowGraph(DirectedFlowGraph& target)
{
  cout << "After creation:" << endl;
  cout << target << endl;

  cout << "Populating with random data" << endl;
  target.populateRandom(100, 60);
  cout << target << endl;

  cout << "Edges of node 3" << endl << endl;
  std::vector<DirectedFlowGraph::DirectedFlowEdge> edges;
  DirectedFlowGraph::Node node_3;
  node_3.index = 3;

  cout << "Out edges" << endl;
  edges = target.getOutEdges(node_3);
  for (int i = 0; i < edges.size(); i++)
  {
    cout << "Edge from " << edges[i].parent.index << " to "
        << edges[i].child.index << ", capacity = " << edges[i].capacity << endl;
  }
  cout << endl;

  cout << "In edges" << endl;
  edges = target.getInEdges(node_3);
  for (int i = 0; i < edges.size(); i++)
  {
    cout << "Edge from " << edges[i].parent.index << " to "
        << edges[i].child.index << ", capacity = " << edges[i].capacity << endl;
  }
  cout << endl;

}
