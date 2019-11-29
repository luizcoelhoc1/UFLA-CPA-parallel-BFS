#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h> 
#include <limits>
#include <algorithm>

using namespace std;
template <typename Edge> 
class AdjacencyMatrix {
public:
	Edge*** adjMatrix;
	int size;

	AdjacencyMatrix(int size) {
		this->size = size;
		adjMatrix = new Edge**[size];
		for (int i = 0; i < size; i++) {
			adjMatrix[i] = new Edge*[size];
			for (int j = 0; j < size; j++)
				adjMatrix[i][j] = NULL;
		}
	}
	
	
	AdjacencyMatrix(std::string filePath) {
		int M, N;
		
		std::ifstream fin(filePath.c_str());
		while (fin.peek() == '%') fin.ignore(2048, '\n');
		
		fin >> M >> N >> size;

		adjMatrix = new Edge**[size];
		for (int i = 0; i < size; i++) {
			adjMatrix[i] = new Edge*[size];
			for (int j = 0; j < size; j++)
				adjMatrix[i][j] = NULL;
		}
		
		int row, col;
		Edge d;
		for (int i = 0; i < size; i++) {
			fin >> row >> col >> d;
			adjMatrix[row][col] = new Edge(d);
			
		}
		
		fin.close();
	}
	
	int getSize() {
		return size;
	}	
	
	vector<int> getAdjVertices(int i) {
		vector<int> adjVertexs;
		for (int k = 0; k < size; k++) {
			if (adjMatrix[i][k] != NULL) {
				adjVertexs.push_back(k);
			}
		}
		return adjVertexs;
	}
	
};
