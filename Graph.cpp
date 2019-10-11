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
	
	

	void printMatrix(){
		
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
	
	/*
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
	}*/

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

	void assemble_simetric_csr_matrix(std::string filePath){
		int M, N, L;
		vector<int> rows, cols;
		vector<double> data;
		
		std::ifstream fin(filePath.c_str());
		// Ignore headers and comments:
		while (fin.peek() == '%') fin.ignore(2048, '\n');
		// Read defining parameters:
		fin >> M >> N >> L;	
		this->rowPtr.push_back(0);
		for (int l = 0; l < L; l++){
			int row, col;
			double d;
			fin >> row >> col >> d;
			rows.push_back(row);
			cols.push_back(col);
			data.push_back(d);
		}
		fin.close();
		for (int l = 1; l <= M; l++){
			for (int k = 0; k < L; k++){
				if (cols[k] == l){
					this->colInd.push_back(rows[k]);
					this->val.push_back(data[k]);					
				}	
				else if (rows[k] == l){
					this->colInd.push_back(cols[k]);
					this->val.push_back(data[k]);				
				}
			}
			this->rowPtr.push_back(this->colInd.size());
		}
		
		this->rowPtr.push_back(this->colInd.size() + 1);
		
	}

};

/*

int main(int argc, char* argv[]) {
	std::string filename = "494_bus.mtx";
	
	Csr asym("lpi_galenet.mtx");

	cout << "Tests for asymetric matrix \n";
	
	cout << "Matrix bandwidth is " << asym.getBandwidth() << '\n';
	
	cout << "Degree of 2: " << asym.getDegree(asym.rowPtr, 2) << '\n';
	
	cout << "Adjs to 2: ";
	
	asym.printArray(asym.getAdjVertices(asym.colInd, asym.rowPtr, 2));
	
	asym.printMatrix();
	
	cout << endl;
	asym.printColInd();
	asym.printVal();
	cout << endl;
	asym.printRowPtr();
	cout << endl;
	cout << asym.getEdge(5, 6);
	return 0;
	
}


*/
/*
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



*/
