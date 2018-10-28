//
//  issuer.h
//  772project
//
//  Created by xin man on 3/13/16.
//  Copyright (c) 2016 xin man. All rights reserved.
//

#ifndef ___72project__issuer__
#define ___72project__issuer__

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

//#include "readfile.h"

using namespace std;

class issuer{
    
private:

    string name;
    int rating;
    string industry;
    double inCorr;
    
public:
    
    //constructor
    issuer(){};
    issuer(string nam,int ratin,string industr,double inCor);
    issuer(string nam,int ratin);
    
    //get value
    string get_name(){return name;}
    int get_rating(){return rating;}
    string get_industry(){return industry;}
    double get_inCorr(){return inCorr;}
    
    //set value
    void set_name(string nam){name=nam;}
    void set_rating(int ratin){rating=ratin;}
    void set_industry(string industr){industry=industry;}
    void set_inCor(double inCor){inCorr=inCor;}
    
    //output
    void print();
    //void output(string filename);
};


#endif /* defined(___72project__issuer__) */
