#include <iostream>
using namespace std;



template <typename Data> 
class Graph {
private:
	Data*** adjMatrix;
	int size;
public:
	Graph(int size) {
		this->size = size;
		adjMatrix = new Data**[size];
		for (int i = 0; i < size; i++) {
			adjMatrix[i] = new Data*[size];
			for (int j = 0; j < size; j++)
				adjMatrix[i][j] = NULL;
		}
	}
 
	void addEdge(int i, int j, Data value) {
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
	
	Data getEdge(int i, int j) {
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
