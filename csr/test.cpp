#include <iostream>
#include <chrono>
#include <ctime>
#include <limits>
#include <list>
#include <string>

#include "Csr.cpp"
#include "BFS.cpp"
#include "ParallelBFS.cpp"

using namespace std;

void sequencial() {
	cout << "for sequencial";
	auto start = std::chrono::system_clock::now();

	Csr<edge> graph("../mtx/cage14.mtx");

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "Time to load: " << elapsed_seconds.count() << "s\n";


	start = std::chrono::system_clock::now();
	vector<int> v = BFS(graph, 2);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end-start;
	std::cout << "Time to BFS: " << elapsed_seconds.count() << "s\n";
}


void parallel() {
	cout << "for parallel bags";
	auto start = std::chrono::system_clock::now();

	Csr<edge> graph("../mtx/cage14.mtx");

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::cout << "Time to load: " << elapsed_seconds.count() << "s\n";


	start = std::chrono::system_clock::now();
	vector<int> v = parallelBFS(graph, 2);
	end = std::chrono::system_clock::now();
	elapsed_seconds = end-start;
	std::cout << "Time to PBFS: " << elapsed_seconds.count() << "s\n";
}

int main(int argc, char **argv) {
	cout << "with csr" << endl;
	parallel();
	return 0;
}

