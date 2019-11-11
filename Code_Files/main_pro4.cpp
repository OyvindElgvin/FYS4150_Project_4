#include<iostream>
#include <armadillo>
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

#include "pro4_functions.h"

using namespace std;
using namespace arma;


//void Ising_Func(vec T, int L, int N, int test);
//int Ising_Test();
void test_dE();
vector<int> readvalues(string file);


int main(){

    //void test_dE();

    // Running test for L = 2 and N = 100, T = 1


    //vec T = vec("1.0 1.2 1.6 2.4");


    //Ising_Func(T,20,10000000,"Test_stuff","order",0);


    // Starts clock for general time
    clock_t start, finish;
    start = clock();

    Task_c();


    finish = clock();
    double timeused = double (finish - start)/(CLOCKS_PER_SEC );
    timeused = timeused / 3600;
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << setprecision(10) << setw(20) << "Hours used for the total calculation = " << timeused << endl;






/*

    // Reading T, N and L values from file
    vector<int> Nvalues = readvalues("Pro4_Nvalues.txt");
    vector<int> Lvalues = readvalues("Pro4_Lvalues.txt");
    //vector<int> Tvalues = readvalues("Pro4_Tvalues.txt");

    // Calculating for all N for all L
    for (vector<int>::size_type i=0;i< Lvalues.size();i++){
    for (vector<int>::size_type j=0;j< Nvalues.size();j++){
    //for (vector<int>::size_type k=0;k< Nvalues.size();k++){

    int L = Lvalues[i];
    // int T = Tvalues[j];
    int N = Nvalues[j];

    Ising_Func(T,L,N,"Results_4b",0);

    } // end of N loop
    //} // end of T loop
    } // end of L loop

*/
} // end of main
