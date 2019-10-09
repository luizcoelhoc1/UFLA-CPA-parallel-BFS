#include <iostream>
#include "bags.cpp"

using namespace std;

int main(int argc, char **argv)
{
	
	Bag<int> b(5);
	Element<int> e(5);
	
	b.backbone[3] = &e;
	
	b.print();

	return 0;
}

