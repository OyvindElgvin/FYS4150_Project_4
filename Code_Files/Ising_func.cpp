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

#include "pro4_functions.h"

using namespace std;
using namespace arma;
using namespace chrono;



void Ising_Func(vec T,int L,int N,string file,string order,int test){

    // start function here


    // Initiaize Random Number Generator
    unsigned seed = system_clock::now().time_since_epoch().count();
    mt19937_64 generator (seed);

    // Vectors for storing E, M, Cv and X for different Temperatures
    vec E_t = vec(T.n_elem,fill::zeros);
    vec M_t = vec(T.n_elem,fill::zeros);
    vec Cv_t = vec(T.n_elem,fill::zeros);
    vec X_t = vec(T.n_elem,fill::zeros);
    vec AC_t = vec(T.n_elem,fill::zeros);

    // Loop over Temperatures

    for (uword i=0;i<T.n_elem;i++){
    vec dE = ("-8 -4 0 4 8");
    vec P = vec(5,fill::zeros);
    for (uword i=0;i<5;i++){
        P(i) = exp(-dE(i)/T(i));
    }


    // initialize
    double E = 0; //expression for initial energy
    double M = 0; //expression for inital magnetization
    double Cv = 0; //Heat Capacity
    double X = 0; //Susceptibility
    int accepted_configurations = 0;


    double E_mean = 0;
    double E2_mean = 0;
    double M_mean = 0;
    double M2_mean = 0;
    double M_abs_mean = 0;


    mat S_matrix = mat(L,L,fill::zeros);
    vec Energies  = vec(N,fill::zeros);

    initialize(L,S_matrix,E,M,order);


    // Loop over Monte Carlo Cycles
    for(int j = 0;j<N;j++){

        int ix = static_cast<int>( (generate_canonical< double, 128 > (generator))*static_cast<double>(L*L) );
        int iy = static_cast<int>( (generate_canonical< double, 128 > (generator))*static_cast<double>(L*L) );

        changing_state(generator, ix, iy, dE, P,S_matrix, E, M,accepted_configurations);


    Energies(j) = E;
    E_mean += E;
    E2_mean += E*E;
    M_mean += M;
    M2_mean += M*M;
    M_abs_mean += fabs(M);
    } // end of Monte Carlo loop


    E_mean /= N;
    E2_mean /= N;
    M_mean /= N;
    M2_mean /= N;
    M_abs_mean /= N;

    double Variance_E = (1/N)*(E2_mean-E_mean*E_mean);
    double Variance_M = (1/N)*(M2_mean-M_mean*M_mean);
    Cv = Variance_E/(T(i)*T(i));
    X = Variance_M/T(i);

    E_t(i) = E_mean;
    M_t(i) = M_abs_mean;
    Cv_t(i) = Cv;
    X_t(i) = X;
    AC_t(i) = accepted_configurations;

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



    // Printing results to terminal
    /*
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


    } // End of temperature loop

    if (test != 1){
        string filename = file + "_N_" + to_string(N) + "_L_" + to_string(L) + ".txt" ;
        ofstream output_Results;
        output_Results.open(filename,ios::out);
        output_Results << T << endl << endl;
        output_Results << E_t << endl << endl;
        output_Results << M_t << endl << endl;
        output_Results << Cv_t << endl << endl;
        output_Results << X_t << endl << endl;
        output_Results << AC_t << endl;
        output_Results.close();
    }

return;
} // End of Ising_func
