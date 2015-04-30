/*
 * DirectedFlowGraph_test.cpp
 *
 *  Created on: Apr 27, 2015
 *      Author: Owen Chiaventone
 */

#include "DirectedFlowGraph.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

void edgeTest(DirectedFlowGraph& target, DirectedFlowGraph::Node node);

void TestDirectedFlowGraph(DirectedFlowGraph& target)
{
  cout << "After creation:" << endl;
  cout << target << endl;

  cout << "Populating with random data" << endl;
  target.populateRandom(100, 60);
  cout << target << endl;

  cout << "Edges of node 3" << endl << endl;

  DirectedFlowGraph::Node test_node;
  test_node.index = 3;
  edgeTest(target, test_node);

  cout << "Edges of source" << endl << endl;
  test_node = target.getSource();
  edgeTest(target, test_node);

  cout << "Edges of sink" << endl << endl;
  test_node = target.getSink();
  edgeTest(target, test_node);

  cout << "Maxing out flow from source" << endl;
  std::vector<DirectedFlowGraph::DirectedFlowEdge> source_out_edges;
  source_out_edges = target.getEdgesWithSlack(target.getSource());
  for (unsigned int i = 0; i < source_out_edges.size(); i++)
  {
    target.setFlow(source_out_edges[i], source_out_edges[i].capacity);
  }
  cout << target << endl;

  return;
}

void edgeTest(DirectedFlowGraph& target, DirectedFlowGraph::Node node)
{
  std::vector<DirectedFlowGraph::DirectedFlowEdge> edges;
  cout << "Out edges" << endl;
  edges = target.getOutEdges(node);
  for (unsigned int i = 0; i < edges.size(); i++)
  {
    cout << "Edge from " << edges[i].parent.index << " to "
        << edges[i].child.index << ", capacity = " << edges[i].capacity << endl;
  }
  cout << endl;

  cout << "In edges" << endl;
  edges = target.getInEdges(node);
  for (unsigned int i = 0; i < edges.size(); i++)
  {
    cout << "Edge from " << edges[i].parent.index << " to "
        << edges[i].child.index << ", capacity = " << edges[i].capacity << endl;
  }
  cout << endl;

}

void autotest()
{
	int size, time_start, time_end, total_time, max_flow;
	float percent;
	ofstream output_file;
	vector<DirectedFlowGraph::DirectedFlowEdge> mincut;
	output_file.open("results.csv", ios::trunc);
	
	output_file<<"Graph size, Percent Connections, Maxflow, Total Time"<<endl;
	for(size=MIN_SIZE; size<=MAX_SIZE; size*=2)
	{
		DirectedFlowGraph graph(size);
		percent=rand()%100;
		cout<<"Teseting graph of size "<<size<<"with random number of connections"<<"\n====================="<<endl;
		graph.populateRandom(size, percent);
		
		time_start=clock();
		max_flow=10;//EdmondsKarpMaxFlow(graph);
		time_end=clock();
		//mincut=CalculateMincut(graph);
		total_time=time_end-time_start;
		
		output_file<<size<< ','<<percent<<','<<max_flow<<','<</*mincut<<','<<*/total_time<<endl;
		
		
		output_file.close();
	}
	
	
	return;	
}
