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
  target.populateRandom(10, 40);
  cout << target << endl;
}
