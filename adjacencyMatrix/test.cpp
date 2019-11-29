#include <iostream>
#include "AdjacencyMatrix.cpp"
#include <chrono>
#include <ctime>
#include <limits>
#include <list>
#include <string>

#include "BFS.cpp"
#include "ParallelBFS.cpp"

using namespace std;

void sequencial() {
	cout << "for sequencial: \n" << endl; 
	AdjacencyMatrix<edge> g("../mtx/mycielskian3.mtx");
	
	auto start = std::chrono::system_clock::now();
	vector<int> v = BFS(g, 2);
	auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}




void parallel() {
	cout << "for parallel bags";
	AdjacencyMatrix<edge> graph("../mtx/mycielskian3.mtx");
	auto start = std::chrono::system_clock::now();
	vector<int> v = parallelBFS(graph, 2);
	auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    for (auto &vs : v) {
		cout << vs << endl;
	}
}

int main(int argc, char **argv) {
	cout << "with Matrix" << endl;
	parallel();
	return 0;
}

