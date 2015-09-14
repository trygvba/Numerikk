#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

void print_matrix(Mat<double> A){
  int n = A.n_rows;
  int m = A.n_cols;
  
  cout << "[ ";
  
  for (int i=0; i<n; i++){
    for (int j=0; j<m; j++){
      cout << A(i,j) << ", ";
    }
    if (i==(n-1)){
      cout << "]" << endl;
    } else {
      cout << "\n";
    }
  }

}


int main(){
  int n = 3;
  int m = 3;

  // Initialize matrix:
  Mat<double> A(n,m);
  Mat<double> B(m,n);

  for (int i=0; i<n; i++){
    for (int j=0; j<m; j++){
      A(i,j) = (double) i*m + j;
      B(j,i) = 1./float(m);
    }

  }

  cout << "A = ";
  print_matrix(A);

  cout << "\n";
  cout << "B = ";
  print_matrix(B);


  cout << "\nAnd their product:" << endl;
  cout << "A*B = ";
  print_matrix(A*B);
  return 0;

}
