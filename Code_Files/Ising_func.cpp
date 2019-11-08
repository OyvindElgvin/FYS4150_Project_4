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

    cout << "Calculating.." << endl;


    // Initiaize Random Number Generator
    unsigned seed = system_clock::now().time_since_epoch().count();
    mt19937_64 generator (seed);

    // Vectors for storing E, M, Cv and X for different Temperatures
    vec E_t = vec(T.n_elem,fill::zeros);
    vec M_t = vec(T.n_elem,fill::zeros);
    vec Mabs_t = vec(T.n_elem,fill::zeros);
    vec Cv_t = vec(T.n_elem,fill::zeros);
    vec X_t = vec(T.n_elem,fill::zeros);
    vec AC_t = vec(T.n_elem,fill::zeros);



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


        double E_mean = 0;
        double E2_mean = 0;
        double M_mean = 0;
        double M2_mean = 0;
        double M_abs_mean = 0;


        mat S_matrix = mat(L,L,fill::zeros);
        vec Energies  = vec(N,fill::zeros);




        initialize(L,S_matrix,E,M,order);



        for(int j = 0;j<N;j++){

            int ix = static_cast<int>( (generate_canonical< double, 128 > (generator))*static_cast<double>(L) );
            int iy = static_cast<int>( (generate_canonical< double, 128 > (generator))*static_cast<double>(L) );

            changing_state(generator, ix, iy, dE, P,L,S_matrix, E, M,accepted_configurations);
            // cout << "-----------------" << endl;
            //cout << S_matrix << endl;
            //cout << ix << "      " << iy << endl;
            //cout << E << endl;
            //cout << M << endl;
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

        cout << "<E>   = " << E_mean << endl
             << "<M>   = " << M_mean << endl;

        cout << "<E^2> = " <<E2_mean << endl
             << "<M^2> = " <<M2_mean << endl;

        double Variance_E = (1/1)*(E2_mean-E_mean*E_mean);
        double Variance_M = (1/1)*(M2_mean-M_mean*M_mean);
        Cv = Variance_E/(T(i)*T(i));
        X = Variance_M/T(i);

        cout << "Cv    = " << Cv << endl
             << "X     = " << X << endl;

        E_t(i) = E_mean;
        M_t(i) = M_mean;
        Mabs_t(i) = M_abs_mean;
        Cv_t(i) = Cv;
        X_t(i) = X;
        AC_t(i) = accepted_configurations;

        // end calculations here

        // Run test if so desired
        if (test == 1){

            double eps = pow(10,-2);
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



        // Printing results to terminal

        if (test != 1){
            cout << "--------------------------------------" << endl;
            cout << "Temperature = " << T << endl;
            cout << "N = " << N << "     " << "L = " << L << endl;
            cout << "Mean energy = " << E_mean << endl;
            cout << "Mean magnetic moment = " << M_mean << endl;
        }

        ofstream output_energy;
        output_energy.open("Test_energies.txt",ios::out);
        output_energy << Energies << endl;
        output_energy.close();


    } // End of temperature loop

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
