/* 
 * File:   Bags.cpp
 * Author: luizc
 * 
 * Created on October 8, 2019, 9:48 PM
 */


#include <math.h>
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
	~Element() { 
		delete left; 
		delete right; 
	}
	
	void print(const std::string& prefix, bool isLeft, bool first) {
		//print prefix
		cout << prefix;
		char firstSimbol = 218;
		char rightSimbol = 192;
		char leftSimbol = 195;
		char minus = 196;
		if (first) {
			cout << firstSimbol << minus << " ";
		} else {
			if (isLeft) {
				cout << leftSimbol << minus << " ";
			} else {
				cout << rightSimbol << minus << " ";
			}
		}
		
		//print
        cout << this->data << std::endl;

		//print childs
        if (left != NULL) 
			left->print( prefix + (isLeft ? "|  " : "   "), right != NULL, false);			
		if (right != NULL)
			right->print( prefix + (isLeft ? "|  " : "   "), false, false);

	}
	void print() {
		print("", true, true);    
	}
	
	
	
};



template <typename Data>
class Bag {
public:
	typedef Element<Data>* Pennant;
	Pennant* backbone;
	int size;
	
	Bag(int size) {
		size = ceil(log2(size));
		backbone = new Pennant[size];
		for (int i = 0; i < size; i++) {
			backbone[i] = NULL;
		}
		this->size = size;
	}
	
	
	Pennant pennantUnion(Pennant x, Pennant y) {
		y->right = x->left;
		x->left = y;
		return x;
	}
	
	Pennant pennantSplit(Pennant x) {
		Pennant y;
		y = x->left;
		x->left = y->right;
		y->right = NULL;
		return y;
	}
	
	Pennant tableDecision(Pennant s1, Pennant s2, Pennant carry) {
		if (carry == NULL) {
			if (s1 == NULL) {
				s1 = s2;
				return NULL;
			} else if (s2 == NULL) {
				s1 = s1;
				return NULL;
			} else {
				s1 = NULL;
				return pennantUnion(s1, s2);
			}
		} else {
			/*
			if (s1 == NULL) {
				if (s2 == NULL) {
					s1 = carry;
					return NULL;
				} else {
					return pennantUnion(s2, carry);
				}
			} else {
				if (s2 == NULL) {
					s1 = NULL;
					return pennantUnion(s1, carry);
				} else {
					return pennantUnion(s2, carry);
				}
			}*/
			if (s1 == NULL && s2 == NULL) {
				s1 = carry;
				return NULL;
			} else if (s1 == NULL && s2 != NULL) {
				s1 = NULL;
				return pennantUnion(s2, carry);
			} else if (s1 != NULL && s2 == NULL) {
				s1 = NULL;
				return pennantUnion(s1, carry);
			} else if (s1 != NULL && s2 != NULL) { 
				return pennantUnion(s2, carry);
			} 
		}
	}
	
	bool bagUnion (Bag other) {
		Pennant y = NULL;
		for (int k = 0; k < size; k++) {
			y = tableDecision(this->backbone[k], other->backbone[k], y);			
		}
		return true;
	}
	
	int count() {
		int result = 0;
		for (int i = this->size-1; i >= 0; i--) {
			if (this->backbone[i] == NULL) {
				result = result << 1;
			} else {
				result = (result << 1) + 1;
			}
		}
		return result;
	}
	
	bool insert(Pennant x) {
		if (pow(size,2) == this->count()) {
			return false;
		}
		
		int k = 0;
		while (backbone[k] != NULL) {
			x = pennantUnion(backbone[k], x);
			backbone[k] = NULL;
			k++;
		}
		backbone[k] = x;
		return true;
	}
	
	//acho que deu bom
	bool insert(Data x) {
		return this->insert(new Element<Data>(x));
	}
	
	void print() {
		for (int i = 0; i < this->size; i++) {
			cout << i << ": " << endl;
			if (this->backbone[i] == NULL) {
				cout << "nulo";
			} else {
				this->backbone[i]->print();
			}
			cout << endl << endl;
		}
	}
	
	void print(int index) {
		this->backbone[index]->print();
	}
	
};


