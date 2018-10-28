//
//  randomnums.h
//  772project
//
//  Created by xin man on 3/29/16.
//  Copyright (c) 2016 xin man. All rights reserved.
//

#ifndef ___72project__randomnums__
#define ___72project__randomnums__

#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <random>

#include "beta.cpp"

using namespace std;

//all rundom number generators for this project

//draw rand number
//normal distribution
double eps();
//random number between 0 and 1
double randnum();
//random number from beta, mean of this beta
double randbeta(double rerate);

//code from http://www.cplusplus.com/forum/beginner/62864/
//calculate cdf for normal distribution
double erf(double x);
double pdf(double x, double mu, double sigma);
double cdf(double x, double mu, double sigma);

#endif /* defined(___72project__randomnums__) */
