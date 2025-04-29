# HullWhiteonefactor

This is a c++ version of the Hull-White one factor simulator found [here](https://github.com/open-source-modelling/one_factor_Hull_White_python).

As per the original version, "A popular choice of model in practice is the Hull-White model. This is an extension of the Vasicek model, that is able to completely replicate the initial term structure. This allows to construct no-arbitrage curves using current market structure of interest rates. This is achieved by allowing the reversion-level parameter theta which is constant in the classical Vasicek model to vary in time with the observable future rates. The one factor version presented in this repository models the short rate using the dynamics described in the [Wiki](https://en.wikipedia.org/wiki/Hull%E2%80%93White_model)."

## What's Different?

Due to the nature of c++, in order to allow for dynamic input array lengths, `malloc` is used in the function. The function frees the local variables `deltat`, 'alpha`, `e`, and `v` after returning a N x 1 pointer array of the simulated rates. In order to create a normal distribution of real numbers, `static random_device rd{}`, `static mt19937 gen{rd()}`, and `uniform_real_distribution<float>`. Also, to use the function in another script, one must `#include "HullWhiteonefactor.h` for the header file.

## Input

As per the original version, the function inputs are as follow:
* `r0` (float): starting interest rate of the Hull-White process.
* `a` (float): speed of reversion parameter that is related to the velocity at which such trajectories will regroup around the forward rate theta.
* `sigma` (float): instantaneous volatility measures instant by instant the amplitude of randomness entering the system.
* `t` (array of floats): representing times at which the output is generated.
* `sizeT` (int): number of elements in `t` array, corresponding to the number of years being simulated. Must be same as `sizeF`.
* `f` (array of floats):
* `sizeF` (int): number of elements in `f` array. Must be same as `sizeT`.

## How to use

```
#include "HullWhiteonefactor.h"
#include <iostream>

using namespace std;

int main()
{
    float* ptr;

    float out[10][2] = {};
    int time[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float forwards[10] = {0.30, 0.30, 0.30, 0.30, 0.30, 0.30, 0.30, 0.30, 0.30, 0.30};
    float sigma = 0.2;
    float alpha = 0.40;
    float r0 = 0.20;
    int sizeT = 10;
    int sizeF = 10;

    ptr = onefactorHullWhite(r0, alpha, sigma, time, sizeT, forwards, sizeF);
    
    for (int i = 0; i < 10; i++) {
        out[i][0] = time[i];
        out[i][1] = ptr[i];
    }

    //free the pointer to r
    free(ptr);
}
```
