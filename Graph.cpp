#include <iostream>
using namespace std;

Template <typename Data>
class Vertex {
	Data data;
	int dist;
	Vertex (Data data, int dist) {
		this->data = data;
		this->dist = dist;
	}
	
	
}

template <typename Edge> 
class Graph {
private:
	Vertex* vertex;
	Edge*** adjMatrix;
	int size;
public:
	Graph(int size) {
		this->size = size;
		adjMatrix = new Edge**[size];
		for (int i = 0; i < size; i++) {
			adjMatrix[i] = new Edge*[size];
			for (int j = 0; j < size; j++)
				adjMatrix[i][j] = NULL;
		}
		
		for (int i = 0; i < size; i++) {
			vertex[i] = NULL;
		}
		
	}
	
	bool addVertex(Vertex v) {
		if (vertex[size-1] != NULL) {
			return false;
		}
		int i = 0;
		while (vertex[i] != NULL) {
			i++;
		}
		
		vertex[i] = v;
	}
 
	void addEdge(int i, int j, Edge value) {
		adjMatrix[i][j] = &value;
		adjMatrix[j][i] = &value;
    }
 
	void removeEdge(int i, int j) {
		adjMatrix[i][j] = NULL;
		adjMatrix[j][i] = NULL;
    }
 
	bool existsEdge(int i, int j) {
		return adjMatrix[i][j] != NULL;
	}
    
	void toString() {
		cout << "  ";
		for (int i = 0; i < size; i++) {
			cout << i << "\t";
		}
		cout << endl;
		for (int i = 0; i < size; i++) {
			cout << i << ": ";
			for (int j = 0; j < size; j++)
				if (adjMatrix[i][j] != NULL) {
					cout << *adjMatrix[i][j] << "\t";
				} else {
					cout << "nulo" << "\t";
				}
			cout << "\n";
		}
	}
	
	Edge getEdge(int i, int j) {
		return *adjMatrix[i][j];
	}
 
	~Graph() {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
				delete[] adjMatrix[i][j];
			delete[] adjMatrix[i];
		}
		delete[] adjMatrix;
	}
};
