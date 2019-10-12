#include <iostream>
#include "Bags.cpp"
#include "Graph.cpp"
#include <limits>
#include <list>

#define GraInSize 10

using namespace std;

typedef int vertex; 


void print(vector<int> v, char keep) {
	if (v.size() == 0) {
		cout<< "empty";
		return;
	}
	for (int i = 0; i < (int)v.size(); i++) {
		cout << i << "- " << v[i] << keep;
	}
}

void print(vector<int> v) {
	print(v, '\n');
}



Bag<vertex> getBag (vector < Bag<vertex> > v, int i) {
	vector< Bag<vertex> >::iterator it = v.begin() + i;
	return  *it;
}

int get(vector<int> v, int i) {
	vector<int>::iterator it = v.begin() + i;
	return *it;
}


void eachValueProcess(Graph<double>* G, Element<vertex>* element, Bag<vertex>* outBag, vector<vertex>* distances, int distance) {
	cout << "process " << *element << endl; 
	vector<int> adjVerteces = G->getAdjVertices(element->data);
	cout << "adjVertices of " << element->data << " is: ";
	print(adjVerteces, ';');
	cout << endl;
	for (int v = 0; (unsigned int) v < adjVerteces.size(); v++) {
		if ((*distances)[adjVerteces[v]] == numeric_limits<int>::max()) {
			(*distances)[adjVerteces[v]] = distance+1;
			outBag->insert(adjVerteces[v]);
		}
	}
	
	if (element->left != NULL) 
		eachValueProcess(G, element->left, outBag, distances, distance);
		
	if (element->right != NULL) 
		eachValueProcess(G, element->right, outBag, distances, distance);
}

void processPennant(Graph<double>* G, Bag<vertex> inBag, int inPennant, Bag<vertex>* outBag, vector<int>* distances, int distance) {
	
	if (inBag.pennantSize(inPennant) < GraInSize) {
		
		eachValueProcess(G, inBag.backbone[inPennant], outBag, distances, distance);
		
	} else {
		cout << "grainsize > pennant size";
	}
	
	/*
	Element<vertex>* newPennant = inBag.pennantSplit(inBag.backbone[inPennant]);
	processPennant(G, inBag, inBag.getIndex(newPennant), outBag, distances, distance);
	processPennant(G, inBag, inPennant, outBag, distances, distance);
	* 
	* */
	
}


void processLayer(Graph<double>* G, Bag<vertex> inBag, Bag<vertex>* outBag, vector<int>* distances, int distance) {
	//size é log ou n????

	for (int k = 0; k < inBag.size; k++ ) {
		cout << "process " << k << " pennanat " << endl;
		if (inBag.backbone[k] != NULL) {
			processPennant(G, inBag, k, outBag, distances, distance);
		} else {
			cout << "k is null" << endl;
		}
	}
	
}



vector<int> parallelBFS(Graph<double> G, int v0) {
	int distance = 0;
	vector<int> distances;
	
	for(int i = 0; i < G.size; i++){
		if (v0 == i) {
			distances.push_back(0);
		} else {
			distances.push_back(numeric_limits<int>::max());
		}
	}
	
	vector< Bag<int> > Vd;
	Bag<int> V0(GraInSize);
	V0.insert(v0);
	Vd.push_back(V0);
	
	cout << "matriz inicial" << endl;
	print(distances);
	cout << endl;
	while (Vd[distance].count() != 0) {
		Bag<int> vdp1(GraInSize);
		cout << "new Distance " << distance << endl;
		Vd.push_back(vdp1);
		cout << "start process layer " << distance << endl;
		processLayer(&G, Vd[distance], &vdp1, &distances, distance);
		cout << "end process layer" << endl;
		print(distances);
		distance++;

	}
	
	return distances;
}

int main(int argc, char **argv) {
	
	
	Graph<double> graph("mycielskian3.mtx");
	
	
	vector<int> v = parallelBFS(graph, 4);
	
	cout << v.size(); 


	return 0;
}

