#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h> 
#include <limits>
#include <algorithm>

using namespace std;






template <typename EdgeType>
class Csr {
	
public:
	Csr(std::string filePath) {
		assembleCsrMatrix(filePath);
	}
	//~ vector<Vertex> valVertex;
	vector<EdgeType> val;
	vector<int> colInd;
	vector<int> rowPtr;
	
	
	Csr<EdgeType>& operator<<(const Csr<EdgeType>& obj);

	template <typename Value>
	void printArray(vector<Value> v){
		for(int i = 0; (unsigned int) i < v.size(); i++)
			cout << v[i] << '\t';
		cout << '\n';
	}
	
	void printColInd() {
		printArray(colInd);
	}
	
	void printRowPtr() {
		printArray(rowPtr);
	}
	
	void printVal() {
		printArray(val);
	}
	
	void printTesteGetEdge() {
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {
				cout << this->getEdge(i, j) << "\t";
			}
			cout << endl;
		}
	}
	
	void printMatrix() {
		printMatrix('\t');
	}
	
	void printMatrix(char separator) {
		int cont = 0;
		for(int i = 0; (unsigned int) i < this->rowPtr.size(); i++){
			int row_start = this->rowPtr[i-1] - 1;
			int row_end = this->rowPtr[i] - 1;
			vector<int>::const_iterator first = this->colInd.begin() + row_start;
			vector<int>::const_iterator last = this->colInd.begin() + row_end;	
			vector<int> row(first, last);
			for(int j = 1; (unsigned int) j < this->rowPtr.size(); j++){
				if(std::count(row.begin(), row.end(), j) == 0)
					cout << '0' << separator;
				else{
					cout << this->val[cont] << separator;
					cont++;
				}
			}
			std::cout << std::endl;
		}
	}
	
	EdgeType getEdge(int i, int j) {
		for (int k = rowPtr[i-1]-1; k < rowPtr[i]-1; k++) 
			if (colInd[k] == j) 
				return val[k];
		return 0;
	}

	int getDegree(vector<int> rowPtr, int vertex){
		return rowPtr[vertex] - rowPtr[vertex - 1];
	}

	vector<int> getAdjVertices(int v){
		vector<int> adjVertices;
		int row_start = rowPtr[v - 1];
		int row_end = rowPtr[v];
		for (int i = row_start; i < row_end; i++) 
			if (v != colInd[i - 1]) 
				adjVertices.push_back(colInd[i-1]);
				
		return adjVertices;
	}
	
	int size() {
		return this->rowPtr.size();
	}

	int getBandwidth(){
		int bandwidth = std::numeric_limits<int>::min();
		for(int i = 1; (unsigned int) i < this->rowPtr.size() - 1; i++){
			int row_start = this->rowPtr[i-1];
			int row_end = this->rowPtr[i];
			if (row_end - row_start == 1)
				continue;
			for (int j = row_start; j < row_end;j++){
				if (abs(this->colInd[j] - i) > bandwidth){
					bandwidth = abs(this->colInd[j] - i);
				}
			}
		}
		return bandwidth;
	}

	void assembleCsrMatrix(std::string filePath){
		int M, N, L;
		std::ifstream fin(filePath.c_str());
		// Ignore headers and comments:
		while (fin.peek() == '%') fin.ignore(2048, '\n');
		
		//define Edge for row, col and value work together
		struct Edge {
			int row;
			int col;
			EdgeType value;
		};
		
		// Read file and put no vector
		fin >> M >> N >> L;
		vector<Edge> v;
		for (int l = 0; l < L; l++) {
			int row, col;
			EdgeType value;
			fin >> row >> col >> value;
			Edge currentRow = {row, col, value};
			v.push_back(currentRow);
		}
		fin.close();
		
		//sort by row
		std::sort(v.begin(), v.end(),  
			[](const Edge &a, const Edge &b){
				return a.row < b.row; 
			}
		);
		
		//assimile
		int lastRow = 0;
		this->rowPtr.push_back(1);
		for (auto &edge : v) {
			this->colInd.push_back(edge.col);
			this->val.push_back(edge.value);
			if (edge.row > lastRow) { //if change row
				while (edge.row != lastRow) { //skip until new row
					lastRow++;
					this->rowPtr.push_back(this->colInd.size());
				}
			} 
		}
		this->rowPtr.push_back(this->colInd.size() + 1);
	}
};




template <typename Edge> 
class Graph {
public:
	Edge*** adjMatrix;
	int size;

	Graph(int size) {
		this->size = size;
		adjMatrix = new Edge**[size];
		for (int i = 0; i < size; i++) {
			adjMatrix[i] = new Edge*[size];
			for (int j = 0; j < size; j++)
				adjMatrix[i][j] = NULL;
		}
	}
	
	Graph(std::string filePath) {
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
			adjMatrix[--row][--col] = new Edge(d);
			
		}
		
		fin.close();
	}
	
	
	void print () {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (adjMatrix[i][j] == NULL) {
					cout << 0 << "\t";
				} else {
					cout << *adjMatrix[i][j] << "\t";
				}
			}
			cout << endl;
		}
	}
 
	void addEdgeNondirected(int i, int j, Edge value) {
		adjMatrix[i][j] = &value;
		adjMatrix[j][i] = &value;
	}
	
 	void addEdge(int i, int j, Edge value) {
		adjMatrix[i][j] = &value;
	}
 
	void removeEdge(int i, int j) {
		adjMatrix[i][j] = NULL;
		adjMatrix[j][i] = NULL;
	}
 
	bool existsEdge(int i, int j) {
		return adjMatrix[i][j] != NULL;
	}
	

	
	Edge getEdge(int i, int j) {
		return *adjMatrix[i][j];
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
	
 
	~Graph() {
		cout << "graph destruido";
	}
	
	
	
};


int main(int argc, char **argv) {


	Csr<edge> g("mycielskian3.mtx");
	
	vector<int> v = BFS(g, 2);

	cout << endl << endl << "result:" << endl;
	print(v);
	
	return 0;
}
