#include <iostream>
#include "Csr.cpp"
#include "print.cpp"
#include <limits>
#include <list>
#include <string>  
#include <queue>


using namespace std;

typedef int vertex; 
typedef double edge; 
const int infinit = numeric_limits<int>::max();


vector<int> BFS(Csr<edge> G, vertex v0) {
	vector<int> distances;
	queue<vertex> queue;
	vector<vertex> adjs;
	vertex u;
	for(int i = 1; i <= G.size(); i++){
		distances.push_back(infinit);
	}	
	distances[v0] = 0;
	
	queue.push(v0);

	while (!queue.empty()) {
		u = queue.front();
		queue.pop();
		cout << u << endl;
		adjs = G.getAdjVertices(u);
		for (auto &v : adjs) {
			cout << v << endl;
			if (distances[v] == infinit) {
				distances[v] = distances[u] + 1;
				queue.push(v);
			}
		}
		cout << endl;
	}
	
	
	return distances;
}


int main(int argc, char **argv) {

	Csr<edge> g("mtx/mycielskian3.mtx");
	
	g.printVal();
	g.printColInd();
	g.printRowPtr();
	cout << endl;
	g.printMatrix();
	
	g.getAdjVertices(5);
	
	
	vector<int> v = BFS(g, 2);
	cout << endl << endl << "result:" << endl;
	for (auto &x : v) {
		cout << x << endl;
	}
	
	return 0;
}
