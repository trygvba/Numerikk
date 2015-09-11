#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void print_vector(double* vec, int n){
  cout << "["

  for (int i=0; i<n; i++){
    cout << " " << vec[i];
  }
  cout << "]" << endl;

}

// main function
int main(){

  int n = 5;

  Colvec<double> vec = colvec(n);
  Colvec<double> vec2 = colvec(n);

  vec2.fill(1.)
  for (int i=0; i<n; i++){
    vec[i] = 
  }

  cout << "First vector: " << endl;
  cout << "\t";
  print_vector(vec, n);

  cout << "Second vector: " << endl;
  cout << "\t";
  print_vector(vec2, n);
  cout << "The dot product is: " << dotproduct << endl;

  delete vec
  return 0;
}
