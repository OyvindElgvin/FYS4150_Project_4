#include<iostream>
#include "armadillo"
#include <vector>
#include "time.h"
#include <random>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#define EPS 3.0e-14
#define MAXIT 10
#include <chrono>

using namespace std;
using namespace arma;
using namespace chrono;

void Ising_Func(vec T,int L,int N,int test){

    // start function here

    // initialize
    double E_mean = 0;
    double E2_mean = 0;
    double M_mean = 0;
    double M2_mean = 0;
    double M_abs_mean = 0;
    double Cv = 0;
    double X = 0;

    unsigned seed = system_clock::now().time_since_epoch().count();
    mt19937_64 gen (seed);

    // Loop over Temperatures
    for (uword i;i<T.n_elem;i++){
    double accepted_configurations = 0;

    vec dE = ("-8 -4 0 4 8");
    vec P = vec(5,fill::zeros);
    for (uword i;i<5;i++){
        P(i) = exp(-dE(i)*T(i));
    }

    mat S_matrix(static_cast<uword>(L),static_cast<uword>(L),fill::ones);
    vec Energies;
    vec M_Moments;
    double E = 0;//expression for initial energy
    double M = 0;//expression for inital magnetization
    // Loop over Monte Carlo Cycles
    for(int i = 0;i<N;i++);



    E_mean += E;
    E2_mean += E*E;
    M_mean += M;
    M2_mean += M*M;
    M_abs_mean += fabs(M);
    }
    // end calculations here

    // Run test if so desired
    if (test == 1){

        double eps = pow(10,-8);
        double exact_Em = 0;
        double exact_Mm = 0;
        double exact_C = 0;
        double exact_X = 0;

        if (abs(exact_Em - E_mean) < eps){
            cout << "Mean energy equals exact value with precision " << eps << endl;
        }
        else{
            cout << "MEAN ENERGY DOES NOT EQUAL EXACT VALUE" << endl
                 << "Computed: " << E_mean << endl
                 << "Exact: " << exact_Em << endl;
        }
        if (abs(exact_Mm - M_mean) < eps){
            cout << "Mean Magnetic Moment equals exact value with precision " << eps << endl;
        }
        else{
            cout << "MEAN MAGNETIC MOMENT DOES NOT EQUAL EXACT VALUE" << endl
                 << "Computed: " << M_mean << endl
                 << "Exact: " << exact_Mm << endl;
        }
        if (abs(exact_C - Cv) < eps){
            cout << "Heat Capacity equals exact value with precision " << eps << endl;
        }
        else{
            cout << "HEAT CAPACITY DOES NOT EQUAL EXACT VALUE" << endl
                 << "Computed: " << Cv << endl
                 << "Exact: " << exact_C << endl;
        }
        if (abs(exact_X - X) < eps){
            cout << "Susceptibility equals exact value with precision " << eps << endl;
        }
        else{
            cout << "SUSCEPTIBILITY DOES NOT EQUAL EXACT VALUE" << endl
                 << "Computed: " << X << endl
                 << "Exact: " << exact_X << endl;
        }
        return;
    }


    /*
    // Printing results to terminal
    if (test != 1){
       cout << "--------------------------------------" << endl;
       cout << "Temperature = " << T << endl;
       cout << "N = " << N << "     " << "L = " << L << endl;
       cout << "Mean energy = " << E_mean << endl;
       cout << "Mean magnetic moment = " << M_mean << endl;
    }

    // Writing results to file
    if (test != 1){
        string filename = "Energies_N_" + to_string(N) + "_L_" + to_string(L) + ".txt" ;
        ofstream output_E;
        output_E.open(filename,ios::out);
        output_E << E_mean << endl << endl;
        output_E << Energies << endl;
        output_E.close();

        filename = "Mmoments_N_" + to_string(N) + "_L_" + to_string(L) + ".txt" ;
        ofstream output_M;
        output_M.open(filename,ios::out);
        output_M << M_mean << endl << endl;
        output_M << M_Moments << endl;
        output_M.close();

    }

*/
return;

} // End of Ising_func
