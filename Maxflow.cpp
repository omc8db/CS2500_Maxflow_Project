//============================================================================
// Name        : Maxflow.cpp
// Author      : Owen Chiaventone
// Version     :
// Copyright   : (c) 2015 Owen Chiaventone
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tester.h"
//#include "DirectedFlowGraph_test.cpp"
using namespace std;


extern void TestDirectedFlowGraph(DirectedFlowGraph& target);

int main()
{
  cout << "Beginning Test" << endl; // prints !!!Hello World!!!
 // srand(time(NULL));
  DirectedFlowGraph test(6);
  TestDirectedFlowGraph(test);
  int choice;
  cout<<"Maxflow Tester"<<endl;
	
	do
	{
		cout<<"Options: "<<endl;
		cout<<"\t1. Run automated tester "<<endl;
		cout<<"\t2. Exit"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1://auto tester
				cout<<"Starting automatic testing. Results will output to file: "<<endl;
				autotest();
				cout<<"Results in result.csv file"<<endl;
				
				break;
			
			case 2://exit
				break;
			
			default:
				cout<<"Command not recognized. Try again"<<endl;
				
		}
	}while(choice!=2);


  return 0;
}
