#include <iostream>
using namespace std;

template <typename Data> 
class Element {
public: 
	Element* right;
	Element* left;
	Data data;
	
	Element(Data data) {
		this->right = NULL;
		this->left = NULL;
		this->data = data;
	}
	
	
};



template <typename Data>
class Bag {
public:
	typedef Element<Data>* Pennant;
	Pennant* backbone;
	int size;
	
	Bag(int size) {
		backbone = new Pennant[size];
		for (int i = 0; i < 5; i++) {
			backbone[i] = NULL;
		}
	}
	
	
	Pennant pennantUnion(Pennant x, Pennant y) {
		y->right = x->left;
		x->left = y->right;
		return x;
	}
	
	Pennant pennantSplit(Pennant x) {
		Pennant y;
		y = x->left;
		x->left = y->right;
		y->right = NULL;
		return y;
	}
	
	bool insert(Pennant x) {		
		int k = 0;
		while (backbone[k] == NULL && k == size) {
			x = pennantUnion(backbone[k], x);
			backbone[k] = NULL;
			k++;
		}
		backbone[k] = x;
		return true;
	}
	
	bool insert(Data x) {
		Element<Data> e(x);
		return insert(&e);
	}
	
	void print() {
		for (int i = 0; i < 5; i++) {
			cout << "|"  << i << ": ";
			if (this->backbone[i] == NULL) {
				cout << "nulo";
			} else {
				cout << this->backbone[i]->data;
			}
			cout << "|\t";
		}	
	}
	
	
};


