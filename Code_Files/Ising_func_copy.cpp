#include<iostream>
#include <armadillo>
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
#include <omp.h>

#include "pro4_functions.h"

using namespace std;
using namespace arma;
using namespace chrono;

// Terminal:
//Øyvind:
/*
c++ -O2 -o exe -std=c++11 main_pro4.cpp Div_Functions.cpp Ising_func.cpp Ising_func_copy.cpp -L/usr/local/Cellar/armadillo/9.600.6/lib/ -L/usr/local/lib -I/usr/local/Cellar/armadillo/9.600.6/include/ -larmadillo -lomp
*/
//Henrik:
/*
c++ -O2 -o exe -std=c++11 main_pro4.cpp Div_Functions.cpp Ising_func.cpp Ising_func_copy.cpp -L/usr/local/Cellar/armadillo/9.800.1/lib/ -L/usr/local/lib -I/usr/local/Cellar/armadillo/9.800.1/include/ -larmadillo -lomp
*/

void Ising_Func_Para(vec T,int L,int N,string file,string order,int test){

    // start function here

    cout << "Calculating.." << endl;


    // Initiaize Random Number Generator


    // Vectors for storing E, M, Cv and X for different Temperatures
    mat E_t = mat(T.n_elem,N/100000,fill::zeros);
    mat M_t = mat(T.n_elem,N/100000,fill::zeros);
    mat Mabs_t = mat(T.n_elem,N/100000,fill::zeros);
    mat Cv_t = mat(T.n_elem,N/100000,fill::zeros);
    mat X_t = mat(T.n_elem,N/100000,fill::zeros);
    //mat AC_t = mat(T.n_elem,N/1000,fill::zeros);
    vec AC_t = vec(T.n_elem,fill::zeros);

    // starting clock for time keeping
    high_resolution_clock::time_point time1 = high_resolution_clock::now();

    // parallelizing 4 threads and making a seperate seed for each thread
    //#pragma omp parallel num_threads(2)
    #pragma omp parallel num_threads(4)
    {
    unsigned seed = system_clock::now().time_since_epoch().count();
    mt19937_64 generator (seed);
    double E_mean = 0;
    double E2_mean = 0;
    double M_mean = 0;
    double M2_mean = 0;
    double M_abs_mean = 0;

    // parallelizing for different temperatures
    #pragma omp parallel for reduction (+:E_mean, E2_mean, M_mean, M2_mean, M_abs_mean)

    // Loop over Temperatures
    for (uword i=0;i<T.n_elem;i++){

        vec dE = ("-8 -4 0 4 8");
        vec P = vec(5,fill::zeros);
        for (uword j=0;j<5;j++){
            P(j) = exp(-dE(j)/T(i));
        }

        // initialize
        double E = 0; //expression for initial energy
        double M = 0; //expression for inital magnetization
        double Cv = 0; //Heat Capacity
        double X = 0; //Susceptibility
        int accepted_configurations = 0;

        E_mean = 0;
        E2_mean = 0;
        M_mean = 0;
        M2_mean = 0;
        M_abs_mean = 0;

        mat S_matrix = mat(L,L,fill::zeros);
        vec Energies  = vec(N,fill::zeros);

        initialize(L,S_matrix,E,M,order);

        for(int j = 0;j<N;j++){

            int ix = static_cast<int>( (generate_canonical< double, 128 > (generator))*static_cast<double>(L) );
            int iy = static_cast<int>( (generate_canonical< double, 128 > (generator))*static_cast<double>(L) );

            changing_state(generator, ix, iy, dE, P,L,S_matrix, E, M,accepted_configurations);

            //Energies(j) = E;
            E_mean += E;
            E2_mean += E*E;
            M_mean += M;
            M2_mean += M*M;
            M_abs_mean += fabs(M);

<<<<<<< HEAD
            if ((j+1) % 100000000 == 0){
=======
            if ((j+1) % 100000 == 0){
>>>>>>> f3f282292178a37fd6f8fcc19e6a7f2eb8a5199c
                E_mean /= (j+1);
                E2_mean /= (j+1);
                M_mean /= (j+1);
                M2_mean /= (j+1);
                M_abs_mean /= (j+1);

                double Variance_E = (E2_mean-E_mean*E_mean);
                double Variance_M = (M2_mean-M_mean*M_mean);
                Cv = Variance_E/(T(i)*T(i));
                X = Variance_M/T(i);

                E_t(i,((j+1)/100000)-1) = E_mean/(L*L); //Per spin
                M_t(i,((j+1)/100000)-1) = M_mean/(L*L);
                Mabs_t(i,((j+1)/100000)-1) = M_abs_mean/(L*L);
                Cv_t(i,((j+1)/100000)-1) = Cv/(L*L);
                X_t(i,((j+1)/100000)-1) = X/(L*L);
            }

        } // end of Monte Carlo loop


        AC_t(i) = accepted_configurations;

/*
        cout << "<E>   = " << E_mean << endl
             << "<M>   = " << M_mean << endl;
        cout << "<E^2> = " <<E2_mean << endl
             << "<M^2> = " <<M2_mean << endl;
        cout << "Cv    = " << Cv << endl
             << "X     = " << X << endl;
*/


        // end calculations here

        // Run test if so desired
        if (test == 1){

            double eps = pow(10,-6);
            double exact_Em = -7.983928344;
            double exact_Mm = 0.0;
            double exact_Cv = 0.1283293234;
            double exact_X = 15.9732151;

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
            if (abs(exact_Cv - Cv) < eps){
                    cout << "Heat Capacity equals exact value with precision " << eps << endl;
            }
            else{
                    cout << "HEAT CAPACITY DOES NOT EQUAL EXACT VALUE" << endl
                         << "Computed: " << Cv << endl
                         << "Exact: " << exact_Cv << endl;
            }
            if (abs(exact_X - X) < eps){
                    cout << "Susceptibility equals exact value with precision " << eps << endl;
            }
            else{
                    cout << "SUSCEPTIBILITY DOES NOT EQUAL EXACT VALUE" << endl
                         << "Computed: " << X << endl
                         << "Exact: " << exact_X << endl;
            }

        }



    }
    } // End of temperature loop

    // stops the clock
    high_resolution_clock::time_point time2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(time2-time1);
    double runtime = time_span.count();
    runtime = runtime/3600;

    cout << "runtime = " << runtime << " hours" << endl;


    if (test != 1){
        string filename = file + "_N_" + to_string(N) + "_L_" + to_string(L) + ".txt" ;
        ofstream output_Results;
        output_Results.open(filename,ios::out);
        output_Results << T << endl;
        output_Results << E_t << endl;
        output_Results << M_t << endl;
        output_Results << Mabs_t << endl;
        output_Results << Cv_t << endl;
        output_Results << X_t << endl;
        output_Results << AC_t << endl;
        output_Results.close();
    }



return;
} // End of Ising_func
