/*
 * EdmondsKarp.h
 *
 *  Created on: Apr 28, 2015
 *      Author: Owen Chiaventone
 */

#ifndef EDMONDSKARP_H_
#define EDMONDSKARP_H_

#include "DirectedFlowGraph.h"
#include <queue>
#include <vector>

using namespace std;

// Calculates the maxflow for a given DirectedFlowGraph
// Inputs: graph to calculate maxflow for
// Outputs: Returns maxflow value
//          graph modified with flow values
// Precondition: Graph must have a path from source to sink
//
// Warning: Modifies graph
int EdmondsKarpMaxflow(DirectedFlowGraph& graph);

// Returns the list of edges in the minCut
// Operates as a recursive graph traversal
//
std::vector<DirectedFlowGraph::DirectedFlowEdge> CalculateMinCut(
    DirectedFlowGraph& graph);

std::vector<DirectedFlowGraph::DirectedFlowEdge> RecursiveMinCut(
    DirectedFlowGraph& graph, DirectedFlowGraph::Node& node);

#endif /* EDMONDSKARP_H_ */
