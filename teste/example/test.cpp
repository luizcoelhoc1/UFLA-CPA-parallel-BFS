#include "../csr_formatter.h"

int main(int argc, char* argv[]){
	
	
	CSR asym = assemble_csr_matrix("mycielskian3.mtx");

	cout << "Tests for asymetric matrix \n";
	
	printArray(asym.row_ptr);
	
	cout << "Matrix bandwidth is " << getBandwidth(asym) << '\n';
	
	cout << "Degree of 2: " << getDegree(asym.row_ptr, 1) << '\n';
	
	cout << "Adjs to 2: ";
	printArray(getAdjVertices(asym.col_ind, asym.row_ptr, 1));
	cout << endl;
	printMatrix(asym);
	
}
