//============================================================================
// Name        : Maxflow.cpp
// Author      : Owen Chiaventone
// Version     :
// Copyright   : (c) 2015 Owen Chiaventone
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "DirectedFlowGraph.h"
//#include "DirectedFlowGraph_test.cpp"
using namespace std;


extern void TestDirectedFlowGraph(DirectedFlowGraph& target);

int main()
{
  cout << "Beginning Test" << endl; // prints !!!Hello World!!!
  srand(time(NULL));
  DirectedFlowGraph test(3);
  TestDirectedFlowGraph(test);


  return 0;
}
