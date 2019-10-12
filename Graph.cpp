#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h> 
#include <limits>

using namespace std;

class Csr {

public:
	Csr(std::string filePath) {
		assembleCsrMatrix(filePath);
	}
	
	vector<double> val;
	vector<int>	colInd;
	vector<int> rowPtr;

	template <typename Value>
	void printArray(vector<Value> v){
		for(int i = 0; (unsigned int) i < v.size(); i++)
			cout << v[i] << ' ';
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
	
	

	void printMatrix() {
		
		int cont = 0;
		for(int i = 1; (unsigned int) i < this->rowPtr.size(); i++){
			int row_start = this->rowPtr[i-1] - 1;
			int row_end = this->rowPtr[i] - 1;
			vector<int>::const_iterator first = this->colInd.begin() + row_start;
			vector<int>::const_iterator last = this->colInd.begin() + row_end;	
			vector<int> row(first, last);
			for(int j = 1; (unsigned int) j < this->rowPtr.size(); j++){
				if(std::count(row.begin(), row.end(), j) == 0)
					cout << '0' << '\t';
				else{
					cout << this->val[cont] << '\t';
					cont++;
				}
			}
			std::cout << std::endl;
		}
	}
	
	
	double getEdge(int i, int j) {

		int k = rowPtr[i];
		cout << "k no inicio " << k << endl;;
		while (colInd[k] != j) {
			k++;
			cout << "col = " << colInd[k] << "; k = " << k << "; val = " << val[k] << endl;

		}
		cout << "k no final " << k << endl;;
		cout << colInd[k] << endl;
		if (colInd[k] != j) {
			return 0;
		}
		return val[k];
	}

	int getDegree(vector<int> rowPtr, int vertex){
		return rowPtr[vertex] - rowPtr[vertex - 1];
	}

	vector<int> getAdjVertices(vector<int> colInd, vector<int> rowPtr, int vertex){
		int row_start = rowPtr[vertex - 1];
		int row_end = rowPtr[vertex];
		vector<int>::const_iterator first = colInd.begin() + row_start;
		vector<int>::const_iterator last = colInd.begin() + row_end;
		vector<int> adjVertices(first, last);
		return adjVertices;
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
		// Read defining parameters:
		fin >> M >> N >> L;
		
		int last_col = 1;
		this->rowPtr.push_back(0);
		for (int l = 0; l < L; l++){
			int row, col;
			double data;
			fin >> row >> col >> data;
			this->colInd.push_back(row);
			this->val.push_back(data);
			if (col > last_col){
				last_col = col;
				this->rowPtr.push_back(this->colInd.size() - 1);
			}	
		}
		this->rowPtr.push_back(this->colInd.size() + 1);
		fin.close();
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
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++)
				delete[] adjMatrix[i][j];
			delete[] adjMatrix[i];
		}
		delete[] adjMatrix;
	}
	
	
	
};


/*
int main(int argc, char **argv) {
	Graph<double> g("mycielskian3.mtx");
	
	vector<int> x = g.getAdjVertices(2);
	
	for (int i = 0; (unsigned int)i < x.size(); i++) {
		cout << x[i] << endl;
	}
	
	return 0;
}*/
