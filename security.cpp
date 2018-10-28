//
//  security.cpp
//  772project
//
//  Created by xin man on 3/16/16.
//  Copyright (c) 2016 xin man. All rights reserved.
//

#include "security.h"

security::security(string nam, string typ, string cusi,int notiona,string maturityDat,double couponRat,int couponPerYea,double pric,double yiel,double tPric,double recover){
    name=nam;
    type=typ;
    cusip=cusi;
    notional=notiona;
    maturityDate=maturityDat;
    cR=couponRat;
    couponPerYear=couponPerYea;
    rPrice=pric;
    yield=yiel;
    tPrice=tPric;
    recovery=recover;
}
//for forecast
security::security(string issuerNam, string typ, int ratin, double newtPric){
    name=issuerNam;
    type=typ;
    rating=ratin;
    tPrice=newtPric;
}

//transfer maturity Date type from string to double (in years)
double security::get_maturityDate(){
    
    double day,month,year;
    vector<double> date;
    string tok;
    istringstream ss(maturityDate);
    
    while(getline(ss,tok,'/')){
        date.push_back(stod(tok));
    }
    
    day=date[0];
    month=date[1];
    year=date[2];
    
    return day/365+month/12+year;
    
}

//Part 3
double security::get_newtPrice(double y,double r,double t,int newrating){
    //calculate the price
    double price,coupon,m;
    coupon=get_cR();
    m=get_couponPerYear();
    
    if(newrating==8){//default case
        double mu=get_recovery()/100.0;
        price=100*randbeta(mu);
        
    }else if((newrating>=1)&&(newrating<=7)){
        if(get_type().compare("Bond")==0){
            price=100*((coupon/y)*(1-1/pow((1+y/m),(m*t)))+1/pow((1+y/m),(m*t)));
        }else if(get_type().compare("CDS")==0){
            price=((y-coupon-r)/y)*(1-1/pow((1+y/m),(m*t)));
        }
        
    }
    //cout<<newrating<<" "<<price<<endl;
    return price;
}


//print to screen and file
void security::printAll(){
    cout<<name<<" "<<type<<" "<<cusip<<" "<<notional<<" "<<maturityDate<<" "<<cR<<" "<<couponPerYear<<" "<<rPrice<<" "<<yield<<" "<<tPrice<<" "<<recovery<<endl;
}
void security::printpPrice(){
    cout<<name<<" "<<type<<" "<<tPrice<<endl;
}
//void security::output(string filename){}
