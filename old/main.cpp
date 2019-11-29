#include <iostream>
#include "Bags.cpp"
#include "Graph.cpp"

using namespace std;

int main(int argc, char **argv)
{
	
	Bag<int> b(20);
	
	
	b.insert(5);
	b.print();
	
	Bag<int> x(20);

	x.insert(114);
	x.insert(50);
	x.insert(55);
	x.print();
	
	cout << "apatir daqui";
	
	x.bagUnion(b);
	
	x.print();
	
	
		 
	return 0;
}
