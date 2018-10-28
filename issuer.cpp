//
//  issuer.cpp
//  772project
//
//  Created by xin man on 3/13/16.
//  Copyright (c) 2016 xin man. All rights reserved.
//

#include "issuer.h"
//constructors
//for issuer.csv

using namespace std;

issuer::issuer(string issuername,int issuerrating,string issuerindustry,double industryCorr){
    name=issuername;
    rating=issuerrating;
    industry=issuerindustry;
    inCorr=industryCorr;
}
issuer::issuer(string nam,int ratin){
    name=nam;
    rating=ratin;
}

//print issuer to screen
void issuer::print(){
    cout<<name<<" "<<rating<<" "<<industry<<" "<<inCorr<<endl;
}
//void output(string filename);


