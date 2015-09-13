#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(){
	
	int n = 5;
	vec testvector = zeros<vec>(n);

	cout << "The first vector:\n\t";
	cout << "[";
	for (int i=0; i<n; i++){
		testvector(i) = (double) i;
		cout << testvector(i) <<" ";
	}
	cout <<"]" << endl;

	vec testvector2 = zeros<vec>(n);

	cout << "The second vector:\n\t";
	cout << "[";
	for (int i=0; i<n; i++){
		testvector2(i) = double(i)/double(n);
		cout << testvector2(i) << " ";
	}
	cout << "]" << endl;

	// do the dot product:
	double dotp = dot(testvector, testvector2);

	cout << "Their dot product: " << dotp << endl;
	return 0;
}
