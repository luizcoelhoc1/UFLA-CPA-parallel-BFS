#include <iostream>
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
	
	Element (Data data, Element* left, Element* right) {
		this->right = right;
		this->left = left;
		this->data = data;
	}
	
	~Element() { 
		delete left; 
		delete right; 
	}
	
	Element<Data> copy () {
		return copy(this);
	}
	
	Element<Data> copy (Element<Data> e) {
		if (left == NULL && right == NULL) {
			return new Element<Data>(e->data);
		}
		if (left == NULL && right != NULL) {
			return new Element<Data>(e->data, NULL, copy(e->right));
		}
		if (left != NULL && right == NULL) {
			return new Element<Data>(e->data, copy(e->left), NULL);
		}
		if (left != NULL && right != NULL) {
			return new Element<Data>(e->data, copy(e->left), copy(e->right));
		}
	}
	
	ostream& print(ostream& os) {
		return print(os, "", true, true);    
	}
	
	ostream& print(ostream& os, const std::string& prefix, bool isLeft, bool first) {
		//print prefix
		os << prefix;
		char firstSimbol = 218;
		char rightSimbol = 192;
		char leftSimbol = 195;
		char minus = 196;
		if (first) {
			os << firstSimbol << minus << " ";
		} else {
			if (isLeft) {
				os << leftSimbol << minus << " ";
			} else {
				os << rightSimbol << minus << " ";
			}
		}
		
		//print
		os << this->data << std::endl;
        
		//print childs
		if (left != NULL) 
			left->print(os, prefix + (isLeft ? "|  " : "   "), right != NULL, false);			
		if (right != NULL)
			right->print(os, prefix + (isLeft ? "|  " : "   "), false, false);
		return os;
	}
	
	
	
};

template <typename Data>
ostream& operator<<(ostream& os, Element<Data>& e){
	return e.print(os);
}


template <typename Data>
class Bag {
public:
	typedef Element<Data>* Pennant;
	Pennant* backbone;
	int size;
	int descricao;
	
	Bag(int size, int descricao) {
		this->descricao = descricao;
		size = ceil(log2(size));
		backbone = new Pennant[size];
		for (int i = 0; i < size; i++) {
			backbone[i] = NULL;
		}
		this->size = size;
	}
	
	~Bag() {
		cout <<"destruindo bag " << descricao << endl;
	}
	
	Pennant pennantUnion(Pennant x, Pennant y) {
		if (x == NULL) {
			cout << "X null";
		}
		
		if (y == NULL) {
			cout << "y null";
		}
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
	
	Pennant tableDecision(int k, Pennant s2, Pennant carry) {
		if (carry == NULL) {
			if (this->backbone[k] == NULL && s2 == NULL) {
				this->backbone[k] = NULL;
				return NULL;
			}
			if (this->backbone[k] == NULL && s2 != NULL) {
				this->backbone[k] = s2;
				cout << "oiiii";
				return NULL;
			}
			if (this->backbone[k] != NULL && s2 == NULL) {
				this->backbone[k] = this->backbone[k];
				return NULL;
			}
			if (this->backbone[k] != NULL && s2 != NULL) {
				Pennant result = pennantUnion(this->backbone[k],s2);
				this->backbone[k] = NULL;
				return result;
			}
		} else {
			if (this->backbone[k] == NULL && s2 == NULL) {
				this->backbone[k] = carry;
				return NULL;
			} else if (this->backbone[k] == NULL && s2 != NULL) {
				this->backbone[k] = NULL;
				return pennantUnion(s2, carry);
			} else if (this->backbone[k] != NULL && s2 == NULL) {
				Pennant result = pennantUnion(this->backbone[k], carry);
				this->backbone[k] = NULL;
				return result;
			} else if (this->backbone[k] != NULL && s2 != NULL) { 
				return pennantUnion(s2, carry);
			}
		}
	}
	
	int pennantSize(int i) {
		if (backbone[i] == NULL) {
			return 0;
		} 
		return pow(2, i);
	}
	
	int getIndex (Pennant p) {
		for (int i = 0; i < size; i++) {
			if (p == backbone[i]) {
				return i;
			}
		}
		return -1;
	}
	
	
	
	/*
	 * INUTILIZA A OTHER
	 * */
	bool bagUnion (Bag<Data> other) {
		Pennant y = NULL;
		for (int k = 0; k < size; k++) {
				y = tableDecision(k, other.backbone[k], y);
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
	
	ostream& print(ostream& os) {
		for (int i = 0; i < this->size; i++) {
			os << i << ": " << endl;
			if (this->backbone[i] == NULL) {
				os << "nulo";
			} else {
				os << *this->backbone[i];
			}
			os << endl << endl;
		}
		return os;
	}
	
};

template <typename Data>
ostream& operator<<(ostream& os, Bag<Data>& bag){
	return bag.print(os);
}

/*
int main(int argc, char **argv) {
	
	Bag<int> b(20);
	
	b.insert(50);
	b.insert(34);
	b.insert(1);
	
	cout << b;
	
	return 0;
}*/

