#include <iostream>
#include "Bags.cpp"
#include "Csr.cpp"
#include <limits>
#include <list>
#include <string>


#define GraInSize 10
#define infinit numeric_limits<int>::max()

using namespace std;

typedef int vertex;
typedef double edge;


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


/*
Bag<vertex> getBag (vector < Bag<vertex> > v, int i) {
	vector< Bag<vertex> >::iterator it = v.begin() + i;
	return  *it;
}

int get(vector<int> v, int i) {
	vector<int>::iterator it = v.begin() + i;
	return *it;
}
*/


void eachValueProcess(Csr<edge>* G, Element<vertex>* element, Bag<vertex>* outBag, vector<vertex>* distances, int distance) {
	std::cout << element->data << '\n';
	vector<int> adjVerteces = G->getAdjVertices(element->data);

	for (int v = 0; (unsigned int) v < adjVerteces.size(); v++) {
		if ((*distances)[adjVerteces[v]] == infinit) {
			(*distances)[adjVerteces[v]] = distance+1;
			outBag->insert(adjVerteces[v]);
		}
	}

	if (element->left != NULL)
		eachValueProcess(G, element->left, outBag, distances, distance);

	if (element->right != NULL)
		eachValueProcess(G, element->right, outBag, distances, distance);
}

void processPennant(Csr<edge>* G, Bag<vertex> inBag, int inPennant, Bag<vertex>* outBag, vector<int>* distances, int distance) {
	if (inBag.pennantSize(inPennant) < GraInSize) {
		eachValueProcess(G, inBag.backbone[inPennant], outBag, distances, distance);
	}

	/*
	Element<vertex>* newPennant = inBag.pennantSplit(inBag.backbone[inPennant]);
	processPennant(G, inBag, inBag.getIndex(newPennant), outBag, distances, distance);
	processPennant(G, inBag, inPennant, outBag, distances, distance);
	*
	* */

}

void processLayer(Csr<edge>* G, Bag<vertex> inBag, Bag<vertex>* outBag, vector<int>* distances, int distance) {
	#pragma omp parallel for
	for (int k = 0; k < inBag.getSize(); k++ ) {
		std::cout << k << '\n';
		if (inBag.backbone[k] != NULL) {
			processPennant(G, inBag, k, outBag, distances, distance);
		}
	}

}

vector<int> parallelBFS(Csr<edge> G, int v0) {
	int distance = 0;
	vector<int> distances;

	for(int i = 0; i < G.size(); i++){
		distances.push_back(infinit);
	}
	distances[v0] = 0;

	vector< Bag<int> > Vd;
	Bag<int> V0(GraInSize);
	V0.insert(v0);
	Vd.push_back(V0);

	while (Vd[distance].count() != 0) {
		Bag<int> vdp1(GraInSize);
		Vd.push_back(vdp1);
		processLayer(&G, Vd[distance], &vdp1, &distances, distance);
		distance++;
	}

	return distances;
}


int main(int argc, char **argv) {
	Csr<edge> graph("mtx/mycielskian3.mtx");

	vector<int> v = parallelBFS(graph, 2);
	print(v);

	return 0;
}
