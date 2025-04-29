#include "HullWhiteonefactor.h"
#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>

using namespace std;

float* HullWhiteonefactor(float r0, float a, float sigma, int t[], int sizeT, float f[], int sizeF) {
    int* deltat = (int*)malloc(sizeT*sizeof(int));
    float* alpha = (float*)malloc(sizeF*sizeof(float));
    float* e = (float*)malloc(sizeF*sizeof(float));
    float* v = (float*)malloc(sizeF*sizeof(float));
    float* r = (float*)malloc(sizeF*sizeof(float));
    
    if (deltat == NULL || alpha == NULL || e == NULL || v == NULL || r == NULL) {
        cout << "Memory Allocation Failed";
        exit(1);
    }
    
    r[0] = r0;

    static random_device rd{};

    static mt19937 gen{rd()};



    for (int i = 0; i < 30; i++) {
        alpha[i] = f[i] + (pow(sigma, 2))/(2*pow(a, 2))*pow(1-exp(-a*t[i]), 2);
    }

    for (int el = 1; el < 30; el++) {
        deltat[el] = t[el] - t[el - 1];
        e[el] = r[el - 1] * exp(-a*deltat[el]) + alpha[el] - alpha[el - 1] * exp(-a*deltat[el]);
        v[el] = pow(sigma, 2)/(2 * a) * (1 - exp(-2 * a * deltat[el]));
        uniform_real_distribution<float> d{e[el], sqrt(v[el])};
        r[el] = d(gen);
        }
    return r;

    free(deltat);
    free(alpha);
    free(e);
    free(v);
    }