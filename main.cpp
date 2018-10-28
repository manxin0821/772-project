// Include standard libraries:
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <iomanip>

// Include your own libraries:
#include "readfile.h"

// Note that in 'main.cpp', we only need to
// include 'readfile.h' because we use
// the function 'read_ptf_from_file()'.
// So how does it know what a 'portfolio' is?
// The file 'readfile.h' includes 'portfolio.h', hence
// by transitivity, main also includes 'portfolio.h'.

int main(int argc, const char * argv[]) {
	
    srand(unsigned(time(NULL)));
    setprecision(8);
    
	// === STEP 1 ===
	
	// Read a portfolio form a file:
    /*ifstream data1("/Users/manxin0821/Dropbox/McMaster/Math772/project/772project/772project/data/issuers.csv");
    ifstream data2("/Users/manxin0821/Dropbox/McMaster/Math772/project/772project/772project/data/portfolio_for_project.csv");
    ifstream data3("/Users/manxin0821/Dropbox/McMaster/Math772/project/772project/772project/data/yield_curve_for_project.csv");
    ifstream data4("/Users/manxin0821/Dropbox/McMaster/Math772/project/772project/772project/data/transition_matrix_for_project.csv");
    ifstream data5("/Users/manxin0821/Dropbox/McMaster/Math772/project/772project/772project/data/correl.csv");
    ifstream data6("/Users/manxin0821/Dropbox/McMaster/Math772/project/772project/772project/data/indCorr.csv");*/
    
    
    ifstream data1("./issuers.csv");
    ifstream data2("./portfolio_for_project.csv");
    ifstream data3("./yield_curve_for_project.csv");
    ifstream data4("./transition_matrix_for_project.csv");
    ifstream data5("./correl.csv");
    ifstream data6("./indCorr.csv");
     

    
    vector<vector<string>> issu=inputFile(data1);
    vector<vector<string>> ptfmatrix=inputFile(data2);
    vector<vector<string>> yield=inputFile(data3);
    vector<vector<string>> transition=inputFile(data4);
    vector<vector<string>> correl=inputFile(data5);
    vector<vector<string>> indCorr=inputFile(data6);
    
    vector<issuer> issuers;
    issuers=readIssuer(issu);
    
    portfolio ptf;
    ptf=readPtf(ptfmatrix);
	
	// === STEP 2 ===
    cout<<"======STEP 2======"<<endl;
    double rvalue,tvalue;
    rvalue=ptf.get_rvalue();
    cout<<"initial real value of this portfolio is:"<<rvalue<<endl;
    
    tvalue=ptf.get_tvalue();
    cout<<"initial theotical value of this portfolio is:"<<tvalue<<endl;
	
	// === STEP 3 ===
    double pp[ptf.get_count()][transition.size()-1];
    //for each rating give each instrument a forecast possible price
    
    cout<<"=====STEP 3====="<<endl;
    
    //start date is 1/18/16
    double st=17.0+1.0/12.0+18.0/365.0;
    
    for(int j=0;j<ptf.get_count();j++){
        
       //cout<<get_yield(yield,term1,rating)
        for(int i=1;i<=8;i++){
            pp[j][i]=fcPrice(ptf.get_security(j),i,yield,st);
            
            cout<<pp[j][i]<<"\t";
        }
        cout<<endl;
    }
	//==== STEP 4 ===
    //forecast rating for each senario
    
    
    //cout<<"======STEP 4======"<<endl;
    
    int N=2000;//simulate N times
    vector<vector<issuer>> RatingFor;

    for(int i=0;i<N;i++){
        double epss=eps();
        vector<issuer> line;
        
        for(int j=0;j<issuers.size();j++){
            
            string issuername=issuers[j].get_name();
            int newrating=fcRating(indCorr,issuers,transition,issuername,issuers[j].get_rating(),epss);
            issuer newissuer(issuername,newrating);
            
            line.push_back(newissuer);
        }
        RatingFor.push_back(line);
    }
    //==== STEP 5 ====
    //forecast portfolio value and portfolio value change for each senario
    //construct forecast matrix
    vector<portfolio> fc;
    
    for(int i=0;i<N;i++){
        vector<security> pt;
        for(int j=0;j<ptf.get_count();j++){
            
            security sec=ptf.get_security(j);
            string sec_name=sec.get_name();
            string sec_type=sec.get_type();
            int newRating=findRating(RatingFor[i],sec_name);
            double newPrice=fcPrice(sec,newRating,yield,st);
            
            security newsec(sec_name,sec_type,newRating,newPrice);
            pt.push_back(newsec);
            
            //newsec.printpPrice();
            
        }
        portfolio p(pt);
        fc.push_back(p);
    }
    
    double pv[N],pvcr[N];
    
    for(int i=0;i<N;i++){
        pv[i]=fc[i].get_tvalue();
        pvcr[i]=fc[i].get_tvalue()-rvalue;
        
        //cout<<pvcr[i]<<endl;
        
    }
    
    //==== STEP 6 ====
    double avc;//average change in portfolio
    double std;//standard deviation of change in value
    double var95;
    double var99;
    double cvar98;
    
    cout<<"=====STEP 6======"<<endl;
    avc=0;
    for(int i=0;i<N;i++){
        avc=avc+pvcr[i];
    }
    avc=avc/N;
    
    std=0;
    for(int i=0;i<N;i++){
        std +=pow(pvcr[i]-avc,2);
    }
    std=pow((std/(N-1)),0.5);
    
    //sort the portfolio change
    vector<double> pvcrv(pvcr,pvcr+N);
    sort(pvcrv.begin(), pvcrv.end());
    
    //calculate 95% 99% Var and 98%Cvar
    var95=-pvcrv[N*0.05+1];
    var99=-pvcrv[N*0.01+1];
    cvar98=0;
    for(int i=0;i<N*0.02;i++){
        cvar98=cvar98+pvcrv[i];
    }
    cvar98=-(1/(N*0.02))*cvar98;
    
    cout<<"the forecast average change in value is :"<<avc<<endl;
    cout<<"standard deviation of change in value is :"<<std<<endl;
    cout<<"95th percentile VaR is :"<<var95<<endl;
    cout<<"99th percentile VaR is :"<<var99<<endl;
    cout<<"98th percentile VaR is :"<<cvar98<<endl;

    return 0;
}
