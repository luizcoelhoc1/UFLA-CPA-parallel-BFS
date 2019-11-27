#include <vector>
#include <iostream>

void print(vector<int> v, char keep) {
	if (v.size() == 0) {
		std::cout<< "empty";
		return;
	}
	for (int i = 0; i < (int)v.size(); i++) {
		std::cout << i << "- " << v[i] << keep;
	}
}

void print(vector<int> v) {
	print(v, '\n');
}
