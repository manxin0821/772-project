//
//  security.h
//  772project
//
//  Created by xin man on 3/16/16.
//  Copyright (c) 2016 xin man. All rights reserved.
//

#ifndef ___72project__security__
#define ___72project__security__

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

#include "randomnums.h"

using namespace std;

// define the class representing each instrument
class security{
    
private:
    
    string name;
    string type; // type of security (CDS, Bonds)
    string cusip;
    int notional;// 7MM for Bond, 5 MM for CDS
    string maturityDate;
    double cR;
    int couponPerYear;//2 for all instruments
    double rPrice;//real price
    double yield;//yield for each instrument
    double tPrice;//theoretical price
    int recovery;//recovery rate
    
    //for forecast possible price
    int rating;
    
public:
    
    //constructor
    security(){}
    security(string nam, string typ, string cusi,int notiona,string maturityDat,double couponRat,int couponPerYea,double pric,double yiel,double tPric,double recover);
    security(string issuerNam, string typ,int ratin,double newtPric);
    
    //get value
    string get_name(){return name;}
    string get_type(){return type;}
    int get_notional(){return notional;}
    
    double get_maturityDate();//transfer maturity Date type from string to double
    double get_yield(){return yield;}
    double get_cR(){return cR;}
    int get_couponPerYear(){return couponPerYear;}
    double get_rPrice(){return rPrice;}
    double get_tPrice(){return tPrice;}
    int get_recovery(){return recovery;}

    //set value
    void set_name(string nam){name=nam;}
    void set_type(string typ){type=typ;}
    void set_cusip(string cusi){cusip=cusi;}
    void set_notional(int notiona){notional=notiona;}
    void set_maturityDate(string maturityDat){maturityDate=maturityDat;}
    void set_cR(double c){cR=c;}
    void set_couponPerYear(int couponPerYea){couponPerYear=couponPerYea;}
    void set_rPrice(double rPric){rPrice=rPric;}
    void set_yield(double yiel){yield=yiel;}
    void set_tPrice(double tPric){tPrice=tPric;}
    void set_recovery(double recover){recovery=recover;}
    
    //Part 3
    double get_newtPrice(double y,double r,double t,int rating);
    
    //print to screen and file
    void printAll();
    void printpPrice();
    //void output(string filename);
    
};

#endif /* defined(___72project__security__) */
