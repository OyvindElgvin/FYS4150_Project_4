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
#include <mpi.h>

#include "pro4_functions.h"

using namespace std;
using namespace arma;
using namespace chrono;

// Terminal:
//Øyvind:
/*
mpiCXX -O2 -o 4e_mpi_exe -std=c++11 main_pro4.cpp Div_Functions.cpp Ising_func_para.cpp Ising_func_para_e_MPI.cpp Ising_func_para_e.cpp -L/usr/local/Cellar/armadillo/9.600.6/lib/ -L/usr/local/lib -I/usr/local/Cellar/armadillo/9.600.6/include/ -larmadillo

mpirun 4e_mpi_exe -n 4
*/


//Henrik Mac:
/*
c++ -O2 -o exe -std=c++11 main_pro4.cpp Div_Functions.cpp Ising_func_copy.cpp -L/usr/local/Cellar/armadillo/9.800.1/lib/ -L/usr/local/lib -I/usr/local/Cellar/armadillo/9.800.1/include/ -larmadillo -lomp
*/
//Henrik Windows:
/*
c++ -O2 -o exe -std=c++11 main_pro4.cpp Div_Functions.cpp Ising_func_copy.cpp -larmadillo -lomp
*/

void Ising_Func_Para_mpi_e(vec T,int L,int N,string file,string order,int test,int stepsize,string probability){

    // start function here



    // Initiaize Random Number Generator


    // Vectors for storing E, M, Cv and X for different Temperatures
    mat E_t = mat(T.n_elem,N/stepsize,fill::zeros);
    mat M_t = mat(T.n_elem,N/stepsize,fill::zeros);
    mat Mabs_t = mat(T.n_elem,N/stepsize,fill::zeros);
    mat Cv_t = mat(T.n_elem,N/stepsize,fill::zeros);
    mat X_t = mat(T.n_elem,N/stepsize,fill::zeros);
    mat X_abs_t = mat(T.n_elem,N/stepsize,fill::zeros);
    mat AC_t = mat(T.n_elem,N/stepsize,fill::zeros);
    int energy_mesh = 10000000;
    mat Energies  = mat(T.n_elem,energy_mesh,fill::zeros);
    vec Sample_Variance_E = vec(T.n_elem,fill::zeros);
    vec Sample_E_mean_t = vec(T.n_elem,fill::zeros);

    double inverse_period = 1./RAND_MAX;

    // starting clock for time keeping
    high_resolution_clock::time_point time1 = high_resolution_clock::now();

    unsigned seed = system_clock::now().time_since_epoch().count();
    mt19937_64 generator (seed);

    double E_mean = 0;
    double E2_mean = 0;
    double M_mean = 0;
    double M2_mean = 0;
    double M_abs_mean = 0;

    int numprocs, my_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);



    int no_intervals = T.n_elem/numprocs;
    int myloop_begin = my_rank*no_intervals;
    int myloop_end = (my_rank + 1)*no_intervals;
    if( (my_rank == numprocs-1) && (myloop_end<T.n_elem) ) myloop_end = T.n_elem;


    // Loop over Temperatures
    for (uword i = myloop_begin; i < myloop_end; i++){
        cout << "T = " <<T(i) << endl;
        //cout << "myloop_begin" << myloop_begin << endl;
        //cout << "myloop_end" << myloop_end << endl;

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
        double X_abs = 0; //Absolute susceptibility
        int accepted_configurations = 0;

        E_mean = 0;
        E2_mean = 0;
        M_mean = 0;
        M2_mean = 0;
        M_abs_mean = 0;

        mat S_matrix = mat(L,L,fill::zeros);

        initialize(L,S_matrix,E,M,order);

        int energy_index = 0;
        double Sample_E_mean = 0;
        double Sample_E2_mean = 0;
        for(int j = 0;j<N;j++){

            //int ix = static_cast<int>( (generate_canonical< double, 128 > (generator))*static_cast<double>(L) );
            //int iy = static_cast<int>( (generate_canonical< double, 128 > (generator))*static_cast<double>(L) );

            int ix = int(double(rand())*inverse_period*L);
            int iy = int(double(rand())*inverse_period*L);

            //changing_state(generator, ix, iy, dE, P,L,S_matrix, E, M,accepted_configurations);
            changing_state(inverse_period, ix, iy, dE, P,L,S_matrix, E, M,accepted_configurations);
            
            if ((j+1) >= stepsize){
            E_mean += E;
            E2_mean += E*E;
            M_mean += M;
            M2_mean += M*M;
            M_abs_mean += fabs(M);
            }
    
            if ((j+1) % stepsize == 0){

                double norm = (j+1)-stepsize;
                double perSpin = L*L;
                double Variance_E = (E2_mean/norm-E_mean/norm*E_mean/norm)/perSpin;
                double Variance_M = (M2_mean/norm-M_mean/norm*M_mean/norm)/perSpin;
                double Variance_M_abs = (M2_mean/norm-M_abs_mean/norm*M_abs_mean/norm)/perSpin;

                E_t(i,((j+1)/stepsize)-1) = E_mean/norm/perSpin; //Per spin
                M_t(i,((j+1)/stepsize)-1) = M_mean/norm/perSpin;
                Mabs_t(i,((j+1)/stepsize)-1) = M_abs_mean/norm/perSpin;
                Cv_t(i,((j+1)/stepsize)-1) = Variance_E/(T(i)*T(i));
                X_t(i,((j+1)/stepsize)-1) = Variance_M/T(i);
                X_abs_t(i,((j+1)/stepsize)-1) = Variance_M_abs/T(i);
                AC_t(i,((j+1)/stepsize)-1) = accepted_configurations/norm;
            }

        } // end of Monte Carlo loop
        double normalize = N-stepsize;
        double perSpin = L*L;
        E_mean /= normalize; //Per spin
        E2_mean /= normalize;
        M_mean /= normalize;
        M2_mean /= normalize;
        M_abs_mean /= normalize;

        double Variance_E = (E2_mean-E_mean*E_mean)/L/L;
        double Variance_M = (M2_mean-M_mean*M_mean)/L/L;
        double Variance_M_abs = (M2_mean-M_abs_mean*M_abs_mean)/L/L;

        E_mean /= L*L; //Per spin
        E2_mean /= L*L;
        M_mean /= L*L;
        M2_mean /= L*L;
        M_abs_mean /= L*L;

        Cv = Variance_E/(T(i)*T(i));
        X = Variance_M/T(i);
        X_abs = Variance_M_abs/T(i);

        // end calculations here

        // Run test if so desired
        if (test == 1){

            double eps = pow(10,-2);
            double exact_Em = -1.995982086; //Per spin
            double exact_Cv = 0.03208233186;
            double exact_Mm = 0.0;
            double exact_abs_Mm = 0.9986607327;
            double exact_X = 3.993303776;
            double exact_X_abs = 0.004010739516;


            if (abs(exact_Em - E_mean) < eps){
                cout << "Mean energy equals exact value with at least precision " << eps << endl
                    << "Computed: " << E_mean << endl
                    << "Exact: " << exact_Em << endl;
            }
            else{
                cout << "MEAN ENERGY DOES NOT EQUAL EXACT VALUE" << endl
                     << "Computed: " << E_mean << endl
                    << "Exact: " << exact_Em << endl;
            }
            if (abs(exact_Cv - Cv) < eps){
                    cout << "Heat Capacity equals exact value with at least  precision " << eps << endl
                    << "Computed: " << Cv << endl
                    << "Exact: " << exact_Cv << endl;
            }
            else{
                    cout << "HEAT CAPACITY DOES NOT EQUAL EXACT VALUE" << endl
                         << "Computed: " << Cv << endl
                         << "Exact: " << exact_Cv << endl;
            }
            if (abs(exact_Mm - M_mean) < eps){
                    cout << "Mean Magnetic Moment equals exact value with at least  precision " << eps << endl
                    << "Computed: " << M_mean << endl
                    << "Exact: " << exact_Mm << endl;
            }
            else{
                    cout << "MEAN MAGNETIC MOMENT DOES NOT EQUAL EXACT VALUE" << endl
                         << "Computed: " << M_mean << endl
                         << "Exact: " << exact_Mm << endl;
            }
            if (abs(exact_abs_Mm - M_abs_mean) < eps){
                    cout << "Mean Absolute Magnetic Moment equals exact value at least  with precision " << eps << endl
                    << "Computed: " << M_abs_mean << endl
                    << "Exact: " << exact_abs_Mm << endl;
            }
            else{
                    cout << "MEAN ABSOLUTE MAGNETIC MOMENT DOES NOT EQUAL EXACT VALUE" << endl
                         << "Computed: " << M_abs_mean << endl
                         << "Exact: " << exact_abs_Mm << endl;
            }
            if (abs(exact_X - X) < eps){
                    cout << "Susceptibility equals exact value with at least  precision " << eps << endl
                    << "Computed: " << X << endl
                    << "Exact: " << exact_X << endl;
            }
            else{
                    cout << "SUSCEPTIBILITY DOES NOT EQUAL EXACT VALUE" << endl
                         << "Computed: " << X << endl
                         << "Exact: " << exact_X << endl;
            }
            if (abs(exact_X_abs - X_abs) < eps){
                    cout << "Absolute Susceptibility equals exact value with at least  precision " << eps << endl
                    << "Computed: " << X_abs << endl
                    << "Exact: " << exact_X_abs << endl;
            }
            else{
                    cout << "ABSOLUTE SUSCEPTIBILITY DOES NOT EQUAL EXACT VALUE" << endl
                         << "Computed: " << X_abs << endl
                         << "Exact: " << exact_X_abs << endl;
            }

        }

    } // End of temperature loop

    // Stops the clock
    high_resolution_clock::time_point time2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(time2-time1);
    double runtime = time_span.count();
    runtime = runtime/3600;

    cout << "runtime = " << runtime << " hours" << endl;




    // Save mean values to file
    if (test == 0){
        string filename = file + "_N_" + to_string(N) + "_L_" + to_string(L) + "_R_" + to_string(my_rank) + ".txt" ;
        ofstream output_Results;
        output_Results.open(filename,ios::out);
        output_Results << T << endl;
        output_Results << E_t << endl;
        output_Results << M_t << endl;
        output_Results << Mabs_t << endl;
        output_Results << Cv_t << endl;
        output_Results << X_t << endl;
        output_Results << X_abs_t << endl;
        output_Results << AC_t << endl;
        output_Results.close();
    }










    /*
    // Save mean values to file
    if (test == 0){
        string filename = file + "_N_" + to_string(N) + "_L_" + to_string(L) + ".txt" ;
        ofstream output_Results;
        output_Results.open(filename,ios::out);
        output_Results << T << endl;
        output_Results << E_t << endl;
        output_Results << M_t << endl;
        output_Results << Mabs_t << endl;
        output_Results << Cv_t << endl;
        output_Results << X_t << endl;
        output_Results << X_abs_t << endl;
        output_Results << AC_t << endl;
        output_Results.close();
    }
    */
return;
} // End of Ising_func
