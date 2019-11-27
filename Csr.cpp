#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h> 
#include <limits>

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
	
	void printMatrix() {
		printMatrix('0', '\t');
	}
	
	void printMatrix(char valueZero, char separator) {
		for(int i = 0; (unsigned int) i < this->rowPtr.size(); i++){
			int k = rowPtr[i];
			for(int j = 0; (unsigned int) j < this->rowPtr.size(); j++) {
				if(colInd[k] == j && rowPtr[i] <= k && k < rowPtr[i+1]) {
					cout << this->val[k] << separator;
					k++;
				} else {
					cout << valueZero << separator;
				}
			}
			std::cout << std::endl;
		}
	}
	
	EdgeType getEdge(int i, int j) {
		for (int k = rowPtr[i]; k < rowPtr[i+1]; k++) 
			if (colInd[k] == j) 
				return val[k];
		return 0;
	}
	
	int getDegree(vector<int> rowPtr, int v){
		return rowPtr[v + 1] - rowPtr[v];
	}
	
	vector<int> getAdjVertices(int v){
		return getAdjVertices(v, false);
	}
	
	vector<int> getAdjVertices(int v, bool himself){
		vector<int> adjVertices;
		int row_start = rowPtr[v];
		int row_end = rowPtr[v+1];
		for (int k = row_start; k < row_end; k++) {
			if (himself) {
				adjVertices.push_back(colInd[k]);
			} else {
				if (colInd[k] != v)
					adjVertices.push_back(colInd[k]);
			}
		}
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
		this->rowPtr.push_back(0);
		for (auto &edge : v) {
			this->colInd.push_back(edge.col);
			this->val.push_back(edge.value);
			if (edge.row > lastRow) { //if change row
				while (edge.row != lastRow) { //skip until new row
					this->rowPtr.push_back(this->colInd.size() - 1);
					lastRow++;
				}
			} 
		}
		this->rowPtr.push_back(this->colInd.size());
	}
};

/*
int main(int argc, char **argv) {


	Csr<double> g("mtx/mycielskian3.mtx");
	
	
	g.printVal();
	g.printColInd();
	g.printRowPtr();
	cout << endl; 
	g.printMatrix();
	cout << endl << endl;
	
	vector<int> vs = g.getAdjVertices(5);
	
	for (auto &u : vs) {
		cout << u << endl; 
	}
	
	return 0;
}*/

