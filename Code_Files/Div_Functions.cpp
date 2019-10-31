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
void initialize(int n_spins, double temp, mat& spin_matrix, double& E, double& M,string order){
    // set up spin matrix and initial amagnetization
    if (order == "order"){
        spin_matrix.ones();
    }
    else{
        spin_matrix.randu();
        for (uword i = 0; i<n_spins; i++){
            for (uword j = 0; j<n_spins; j++){
                if(spin_matrix(i,j) < 0.5){spin_matrix(i,j) = -1.;}
                else{spin_matrix(i,j) = 1.;}
            }
        }
    }

    for (uword i = 0; i<n_spins; i++){
        for (uword j = 0; j<n_spins; j++){
            M += spin_matrix(i,j);

        }
    }


    // setup spin matrix and intial magnetization
    for(int y = 0; y < n_spins; y++) {
        for (int x = 0; x < n_spins; x++){
            if (temp < 1.5) spin_matrix(y,x) = 1; // spin orientation for the ground state
            M += static_cast<double>(spin_matrix(y,x));
        }
    }
    // setup initial energy
    for(int y =0; y < n_spins; y++) {
        for (int x= 0; x < n_spins; x++){
            E -= static_cast<double>(spin_matrix(y,x)*
                       (spin_matrix(periodic(y,n_spins,-1),x) +
                        spin_matrix(y,periodic(x,n_spins,-1))));
        }
    }
}// end function initialize


// function for changing energy state
void changing_state(mt19937_64 generator, uword i, uword j, vec dE, vec P,mat& spin_matrix, double& Energy, double& Mmoment){

    // Calculating energy difference for flipped spin
    double delta_E = 2*spin_matrix(i,j) * (spin_matrix(i,j-1) + spin_matrix(i,j+1) + spin_matrix(i-1,j) + spin_matrix(i+1,j));

    // Find probability exp(-b dE) from precalculated array
    uvec index = find(dE == delta_E);
    double Prob = P(index(0));

    // Sample rule: Check if new state is accepted
    double r = generate_canonical< double, 128 > (generator);
    if (r < Prob){
        spin_matrix(i,j) = -spin_matrix(i,j);
        Energy = Energy + delta_E;
        Mmoment = Mmoment + 2*spin_matrix(i,j);
    }


} // end function changing_state










