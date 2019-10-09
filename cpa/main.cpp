#include <iostream>
#include "Bags.cpp"

using namespace std;

int main(int argc, char **argv)
{
	Bag<int> b(13);
	char corner = 192;

	cout << corner << endl; // outputs ╔ as expected
	cout << "╔" << endl; // outputs ?  
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	
	b.insert(5);
	b.insert(3);
	b.insert(1);
	b.insert(8);

	b.insert(114);
	b.insert(50);
	b.insert(55);
	b.insert(6);
	b.print();
	
	/*
	Element<int> e(5);
	b.insert(&e);
		
	Element<int> x(3);
	b.insert(&x);
	
	b.print();
	Element<int> y(4);
	b.insert(&y);
*/
	
	
	return 0;
}
