//: testpoisson.cpp

#include <cmath>
#include <iostream>
#include "poisson1d.h"

using namespace std;

int main(){
  
  Poisson1D testprob("../inputfiles/testspline.txt");
  testprob.print();
  

}
