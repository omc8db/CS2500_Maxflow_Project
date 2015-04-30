/*
 * tester.h
 *
 *  Created on: Apr 29, 2015
 *      Author: mrdtdev
 */

#ifndef TESTER_H_
#define TESTER_H_

#include "EdmondsKarp.h"

const int MIN_SIZE=4;
const int MAX_SIZE=8192;//2^16

void autotest();
void TestDirectedFlowGraph(DirectedFlowGraph& target);
void edgeTest(DirectedFlowGraph& target, DirectedFlowGraph::Node node);
std::ostream& operator<<(std::ostream & out, vector<DirectedFlowGraph::DirectedFlowEdge>& input);


#endif /* TESTER_H_ */
