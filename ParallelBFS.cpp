#include <iostream>
#include "Bags.cpp"
#include <limits>
#include <list>

using namespace std;
/*
void ParallelBFS(Graph G, Vertex v0) {

	int i = 0;
	while (G.vertex[i] != NULL) {
		G.vertex.dist = std::numeric_limits<int>::max();
		i++;
	}
	v0.dist = 0;
	
	list<Bag<Vertex> > V;
	
	V.push_back();
	
	
	while () {
		
	}
	
}
*/


int main(int argc, char **argv) {
	
	list< Bag<int> > lista;
	
	Bag<int> c(5);
	c.insert(5);
	c.insert(234);
	c.insert(9);
	
	Bag<int> b(5);
	b.insert(5);
	b.insert(10);

	Bag<int> a(5);
	a.insert(3);

	lista.push_back(c);
	lista.push_back(b);
	lista.push_back(a);
	
	int i = 0;
	for (list< Bag<int> >::iterator it = lista.begin(); it != lista.end(); ++it) {
		(*it).insert(i);
	}

	for (list< Bag<int> >::iterator it = lista.begin(); it != lista.end(); ++it) {
		cout << "cagueeei";
		
		cout << endl<< endl<< endl<< endl; 
	}


	return 0;
}

