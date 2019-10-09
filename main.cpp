#include <iostream>
#include "Bags.cpp"
#include "Graph.cpp"

using namespace std;

int main(int argc, char **argv)
{
	/*
	Bag<int> b(20);
	
	
	b.insert(5);
	b.insert(3);
	b.insert(1);
	b.insert(8);

	b.insert(114);
	b.insert(50);
	b.insert(55);
	b.insert(6);
	b.print();
	
	cout << b.size;
	*/
	
	Graph<int> g(5);
	
	g.addEdge(0,0,66);
	g.toString();
	
	return 0;
}
