#include <iostream>
#include "Bags.cpp"
#include <limits>
#include <list>
#include <string>
#include <chrono>
#include <ctime>    

#define GraInSize 128
#define infinit numeric_limits<int>::max()

using namespace std;

typedef int vertex;
typedef double edge;

void eachValueProcess(Csr<edge>* G, Element<vertex>* element, Bag<vertex>* outBag, vector<vertex>* distances, int distance) {
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

void processPennant(Csr<edge>* G, Bag<vertex> inBag, Element<vertex>* inPennant, int sizePennant, Bag<vertex>* outBag, vector<int>* distances, int distance) {
	if (sizePennant < GraInSize) {
		eachValueProcess(G, inPennant, outBag, distances, distance);
		return;
	}
	
	Element<vertex>* newPennant = inBag.pennantSplit(inPennant);
	processPennant(G, inBag, newPennant, sizePennant >> 1, outBag, distances, distance);
	processPennant(G, inBag, inPennant, sizePennant >> 1, outBag, distances, distance);
}

void processLayer(Csr<edge>* G, Bag<vertex> inBag, Bag<vertex>* outBag, vector<int>* distances, int distance) {
	#pragma omp parallel for
	for (int k = 0; k < inBag.getSize(); k++ ) {
		if (inBag.backbone[k] != NULL) {
			processPennant(G, inBag, inBag.backbone[k], inBag.pennantSize(k), outBag, distances, distance);
		}
	}

}

vector<int> parallelBFS(Csr<edge> G, int v0) {
	int distance = 0;
	vector<int> distances;

	for(int i = 0; i < G.getSize(); i++){
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
