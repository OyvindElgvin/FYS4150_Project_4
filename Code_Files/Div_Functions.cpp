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

// Read a Coloumn Vector from a file
vector<int> readvalues(string file){
    string line;
    vector<int> N_values;
    ifstream values;
    values.open(file,ios::in);
    while (getline(values,line)){
        if (atoi(line.c_str()) != 0){
        N_values.push_back(atoi(line.c_str()));
        }
       else{}
   }
    values.close();
    return N_values;
    }


// inline function for periodic boundary conditions
inline int periodic(int i, int limit, int add) {
    return (i+limit+add) % (limit);
}



// function to initialise energy, spin matrix and magnetization
void initialize(int n_spins, double temp, int **spin_matrix, double& E, double& M){
    // setup spin matrix and intial magnetization
    for(int y = 0; y < n_spins; y++) {
        for (int x = 0; x < n_spins; x++){
            if (temp < 1.5) spin_matrix[y][x] = 1; // spin orientation for the ground state
            M += double spin_matrix[y][x];
        }
    }
    // setup initial energy
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            E -= double spin_matrix[y][x]*
                       (spin_matrix[periodic(y,n_spins,-1)][x] +
                        spin_matrix[y][periodic(x,n_spins,-1)]);
        }
    }
}// end function initialise













