#include <iostream>
#include "AdjacencyMatrix.cpp"
#include "print.cpp"
#include <limits>
#include <list>
#include <string>  
#include <queue>
#include <chrono>
#include <ctime>    


using namespace std;

typedef int vertex; 
typedef double edge; 
const int infinit = numeric_limits<int>::max();


vector<int> BFS(Graph<edge> G, vertex v0) {
	vector<int> distances;
	queue<vertex> queue;
	vector<vertex> adjs;
	vertex u;
	
	//set
	for(int i = 1; i <= G.getSize(); i++){
		distances.push_back(infinit);
	}
	distances[v0] = 0;
	
	queue.push(v0);

	while (!queue.empty()) {
		u = queue.front();
		queue.pop();
		adjs = G.getAdjVertices(u);
		for (auto &v : adjs) {
			if (distances[v] == infinit) {
				distances[v] = distances[u] + 1;
				queue.push(v);
			}
		}
	}
	
	
	return distances;
}


int main(int argc, char **argv) {

	return 0;
}
