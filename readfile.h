//
//  readfile.h
//  772project
//
//  Created by xin man on 3/16/16.
//  Copyright (c) 2016 xin man. All rights reserved.
//

#ifndef ___72project__readfile__
#define ___72project__readfile__

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
#include <ctime>

#include "portfolio.h"
#include "issuer.h"


using namespace std;


//functions used for read external file into vectors
string trim(string srt);
vector<string>split(string str,char delimiter);
vector<vector<string>> inputFile(istream& data);
//numerize rating
int numRating(string rating);

//read portfolio
portfolio readPtf(vector<vector<string>> ptf);
//read issuer
vector<issuer> readIssuer(vector<vector<string>> issuers);

//transfer matrix to functions
double get_yield(vector<vector<string>> yield,double term, int rating);
double get_tran(vector<vector<string>> tran,int from,int to);
double get_inCorr(vector<vector<string>> inCorr,string industry);
double get_correl(vector<vector<string>> correl,string issuer1,string issuer2);

//forecast possible price
double fcPrice(security instrument,int rating,vector<vector<string>> yield,double st);
//forecast rating
int fcRating(vector<vector<string>> indCorr,vector<issuer> issuers,vector<vector<string>> tran,string issuername,int ratingfrom,double epss);

//search tools
//find rating by issuer name in is
int findRating(vector<issuer> is,string issuername);
//find industry by issuer name in is
string findInd(vector<issuer> is,string issuername);
double findCorr(vector<issuer> is,string issuername);

//enhance stod
double pstod(string a);

#endif /* defined(___72project__readfile__) */
