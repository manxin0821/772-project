//
//  randomnums.cpp
//  772project
//
//  Created by xin man on 3/29/16.
//  Copyright (c) 2016 xin man. All rights reserved.
//

#include "randomnums.h"

//draw random number
double eps(){
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    normal_distribution<double> distribution(0,1);
    return distribution(generator);
}
//draw random number between 0 and 1
double randnum(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    
    uniform_real_distribution<double> distribution(0.0,1.1);
    return distribution(generator);
    
}
//random number from beta
double randbeta(double rerate){
     //https://www.msci.com/resources/technical_documentation/CMTD1.pdf
     //Page 95 Median: 78.79%
    double md=0.7879;
    double mu=rerate;//expected recovery rate
    
    double alpha,beta;
    alpha=1.0/3.0*(md/mu-1.0);
    beta=(1.0/mu-1.0)/(3.0*(md/mu-1.0));
    
    //cout<<alpha<<beta<<endl;
    
    random_device rd;
    mt19937 gen(rd());
    sftrabbit::beta_distribution<> newbeta(alpha, beta);
    
    return newbeta(gen);
}


//code from http://www.cplusplus.com/forum/beginner/62864/
//calculate cdf for normal distribution
// Returns the erf() of a value (not super precice, but ok)
double erf(double x)
{
    double y = 1.0 / ( 1.0 + 0.3275911 * x);
    return 1 - (((((
                    + 1.061405429  * y
                    - 1.453152027) * y
                   + 1.421413741) * y
                  - 0.284496736) * y
                 + 0.254829592) * y)
    * exp (-x * x);
}

// Returns the probability of x, given the distribution described by mu and sigma.
double pdf(double x, double mu, double sigma)
{
    //Constants
    static const double pi = 3.14159265;
    return exp( -1 * (x - mu) * (x - mu) / (2 * sigma * sigma)) / (sigma * sqrt(2 * pi));
}

// Returns the probability of [-inf,x] of a gaussian distribution
double cdf(double x, double mu, double sigma)
{
    return 0.5 * (1 + erf((x - mu) / (sigma * sqrt(2.))));
}


