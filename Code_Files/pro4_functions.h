#ifndef PRO4_FUNCTIONS_H
#define PRO4_FUNCTIONS_H

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

#include <random>
#include <chrono>

using namespace std;
using namespace arma;
using namespace chrono;


void changing_state(mt19937_64 generator, uword i, uword j, vec dE, vec P,mat& spin_matrix, double& Energy, double& Mmoment);
vector<int> readvalues(string file);
void Ising_Func(vec T,int L,int N,int test);

#endif // PRO4_FUNCTIONS_H
