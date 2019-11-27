#include <omp.h>
#include <iostream>
#include <limits>
#include <list>
#include <string>


void name(int i) {
  std::cout << "oi " << i << '\n';
}

int main(int argc, char **argv) {
    #pragma omp parallel for
    for (int i = 0; i < 10;  i++) {
        name(i);
    }

	return 0;
}
