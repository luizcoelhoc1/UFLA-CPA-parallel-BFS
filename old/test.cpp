#include <iostream>
#include <chrono>
#include <ctime>
#include <limits>
#include <list>
#include <string>

#include "Graph.cpp"

#include "AdjacencyMatrix.cpp"

#include "Bags.cpp"
#include "Csr.cpp"

#include "BFS.cpp"



#include "print.cpp"

using namespace std;

int main(int argc, char **argv) {
	testWithMatrixAndSequencial();
	return 0;
}


void testWithMatrixAndSequencial() {
	cout << "for matrix and sequencial: \n" << endl; 
	AdjacencyMatrix<edge> g("mtx/mycielskian3.mtx");
	
	auto start = std::chrono::system_clock::now();
	vector<int> v = BFS(g, 2);
	auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

void testWithCSRAndSequencial() {
	cout << "for matrix and sequencial: \n" << endl; 
	csr<edge> g("mtx/mycielskian3.mtx");
	
	auto start = std::chrono::system_clock::now();
	vector<int> v = BFS(g, 2);
	auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
