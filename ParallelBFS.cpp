#include <iostream>
#include "Bags.cpp"
#include "Graph.cpp"
#include <limits>
#include <list>

using namespace std;


Bag<int> getBag (vector < Bag<int> > v, int i) {
	vector< Bag<int> >::iterator it = v.begin() + i;
	return  *it;
}

int get(vector<int> v, int i) {
	vector<int>::iterator it = v.begin() + i;
	return *it;
}


void eachValueProcess(Csr G, Element<int>* element, vector<int> distances, int distance, Bag<int> outBag) {
	vector<int> adjVerteces = G.getAdjVertices(G.colInd, G.rowPtr, element->data);
	for (vector<int>::iterator v = adjVerteces.begin(); v < adjVerteces.end(); v++) {
		if (get(distances, *v) == numeric_limits<int>::max()) {
			*v = distance + 1;
			outBag.insert(*v);
		}
	}
	
	if (element->left != NULL) 
		eachValueProcess(G, element->left, distances, distance, outBag);
		
	if (element->right != NULL) 
		eachValueProcess(G, element->right, distances, distance, outBag);
}


void processPennant(Csr G, Bag<int> inBag, int pennant, Bag<int> outBag, vector<int> distances, int distance) {
	//inBag.backbone[i] == inPennant         GraInSize????
	if (inBag.pennantSize(pennant)< 500) {
		eachValueProcess(G, inBag.backbone[pennant], distances, distance, outBag);
	}
}


void processLayer(Csr G, Bag<int> inBag, Bag<int> outBag, vector<int> distances, int distance) {
					//size é log ou n????
	for (int k = 0; k < inBag.size; k++ ) {
		if (inBag.backbone[k] != NULL) {
			processPennant(G, inBag, k, outBag, distances, distance);
		}
		
	}
}



vector<int> parallelBFS(Csr G, int v0) {
	int sizeMaxBag = 500;
	int distance = 0;
	vector<int> distances;
	
	for(int i = 1; (unsigned int) i < G.rowPtr.size(); i++){
		if (v0 == i) {
			distances.push_back(0);
		} else {
			distances.push_back(numeric_limits<int>::max());
		}
	}
	
	vector< Bag<int> > Vd;
	Bag<int> V0(sizeMaxBag);
	V0.insert(v0);
	Vd.push_back(V0);
	
	while (getBag(Vd, distance).count() != 0) {
		Bag<int> vd(sizeMaxBag);
		Bag<int> vdp1(sizeMaxBag);
		Vd.push_back(vd);
		Vd.push_back(vdp1);
		processLayer(G, vd, vdp1, distances, distance);
		distance++;
	}
	
	return distances;
}

int main(int argc, char **argv) {
	
	Csr graph("lpi_galenet.mtx");
	
	vector<int> v = parallelBFS(graph, 5);
	
	int i = 0;
	for (vector<int>::iterator it = v.begin(); it < v.end(); it++) {
		cout << i++; 
		cout << ' ' << *it << endl;
	}
	
	return 0;
}

