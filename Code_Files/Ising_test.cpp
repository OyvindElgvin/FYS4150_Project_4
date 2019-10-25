#include<iostream>
#include "armadillo"
#include <vector>
#include "time.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#define EPS 3.0e-14
#define MAXIT 10

using namespace std;
using namespace arma;


void Ising_Func(int N, int L, int test);
vector<int> readvalues(string file);


int Ising_Test(){

    int L = 2;
    int N = 100;

    Ising_Func(N,L,1);

    return 0;

} // end of test
