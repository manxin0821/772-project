//
//  readfile.cpp
//  772project
//
//  Created by xin man on 3/16/16.
//  Copyright (c) 2016 xin man. All rights reserved.
//

#include "readfile.h"

//functions used for read external file into vectors
//trim string


vector<string> split(string str,char delimiter){
    vector<string> internal;
    stringstream ss(str);
    string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

vector<vector<string>> inputFile(istream& data){
    string line;
    vector<vector<string>> input;
    
    int rowNum=0;
    while(getline(data,line,'\r')){
        vector<string> row = split(line, ',');
        
        input.push_back(row);
        //cout<<input[rowNum][0]<<endl;
        rowNum++;
        
    }
    //cout<<endl;
    return input;
}

//numerize rating
int numRating(string rating){
    
    if(rating.compare("AAA")==0)
        return 1;
    else if(rating.compare("AA")==0){
        return 2;
    }else if(rating.compare("A")==0){
        return 3;
    }else if (rating.compare("BBB")==0){
        return 4;
    }else if (rating.compare("BB")==0){
        return 5;
    }else if (rating.compare("B")==0){
        return 6;
    }else if (rating.compare("CCC")==0){
        return 7;
    }else if (rating.compare("D")==0||rating.compare("Govt")==0){
        return 8;
    }else{
        //maybe "govr" in yield matrix
        return 0;
    }
}

//read portfolio
portfolio readPtf(vector<vector<string>> ptf){
    
    vector<security> sec;
    
    for(int i=1;i<=ptf.size()-1;i++){
        
        string nam;
        string typ;
        string cusi;
        int notiona;
        string maturityDat;
        double couponRat;
        int couponPerYea;
        double pric;
        double yiel;
        double tPric;
        int recover;
        
        nam=ptf[i][0];
        typ=ptf[i][1];
        cusi=ptf[i][2];
        notiona=stoi(ptf[i][3]);
        maturityDat=ptf[i][4];
        couponRat=pstod(ptf[i][5]);
        couponPerYea=stoi(ptf[i][6]);
        pric=pstod(ptf[i][7]);
        yiel=pstod(ptf[i][8]);
        tPric=pstod(ptf[i][9]);
        recover=pstod(ptf[i][10]);
        
        security instr(nam,typ,cusi,notiona,maturityDat,couponRat,couponPerYea,pric,yiel,tPric,recover);
        sec.push_back(instr);
    
    }
    portfolio P(sec);
    
    return P;
    
}
//read issuer
vector<issuer> readIssuer(vector<vector<string>> issuers){
    
    vector<issuer> iss;
    
    for(int i=1;i<=issuers.size()-1;i++){
        
        issuer issue(issuers[i][0],numRating(issuers[i][1]),issuers[i][2],stod(issuers[i][3]));
        iss.push_back(issue);
    }
    return iss;
}

//read HistoData.csv,correl.csv,indCorr.csv,transition,yield
//transfer matrix to functions
double get_yield(vector<vector<string>> yield, double term, int rating){
    int i,j;
    i=1;j=1;
    
    while((pstod(yield[i][0])-term)!=0){i++;}
    while(numRating(yield[0][j])!=rating){j++;}
    
    if((i>=9)||(j>=9)){
        cout<<"something wrong in get_yield"<<endl;
    }else{
        return pstod(yield[i][j])/100.0;
    }
    return 0;
}

double get_tran(vector<vector<string>> tran, int from,int to){
    int i,j;
    i=1;j=1;
    
    while(numRating(tran[i][0])!=from){i++;}
    while(numRating(tran[0][j])!=to){j++;}
    
    if((i>=tran.size())||(j>=tran[0].size())){
        cout<<"something wrong in get_tran"<<endl;
    }else{
        return pstod(tran[from][to]);
    }
    return 0;
}
double get_inCorr(vector<vector<string>> inCorr,string industry){
    int i;
    i=1;
    
    while(industry.compare(inCorr[i][0])!=0){i++;}
    
    if(i>inCorr.size()){
        cout<<"something wrong in get_inCorr"<<endl;
    }else{
        //cout<<"industry correlation:"<<inCorr[i][1]<<endl;
        return pstod(inCorr[i][1]);
    }
    return 0;
}
double get_correl(vector<vector<string>> correl,string issuer1,string issuer2){
    int i,j;
    i=1;j=1;
    
    while(correl[i][0].compare(issuer1)!=0){i++;}
    while(correl[0][j].compare(issuer2)!=0){j++;}
    
    if((i>=correl.size())||(j>=correl[0].size())){
        cout<<"something wrong in get_correl"<<endl;
    }else{
        return pstod(correl[i][j]);
    }
    return 0;
}

//forecast price 
//double fcPrice(security instrument,int rating){
//    
//    if(rating==0){
//        return 0;
//    }else if(rating==8){
//        return instrument.get_recovery();
//    }else if((rating>=1)&&(rating<=7)){
//        if(instrument.get_type().compare("Bond")==0){
//            return instrument.get_tPrice();
//        }else if(instrument.get_type().compare("CDS")==0){
//            return randnum();
//            //return double(eps());
//        }
//    }else{
//        cout<<"wrong rating input"<<endl;
//    }
//    return 0;
//}
vector<double> findyr(security instrument,int rating,vector<vector<string>> yield,double st,double t){
    vector<double> yr;
    double term1,term2,y1,y2,r1,r2;
    int i=1;
    while((t>=stod(yield[i][0]))&&(i<yield[0].size())){//find the sup of term
        i++;
    }
    
    if(i==1){
        term1=0;
        term2=stod(yield[i][0]);
        y1=0;
        y2=get_yield(yield,term2,rating);
        
        r1=0;
        r2=get_yield(yield,term2,8);
        
    }else if(i==yield[0].size()-1){
        term1=stod(yield[i][0]);
        term2=stod(yield[i][0]);
        y1=get_yield(yield,term1,rating);
        y2=get_yield(yield,term2,rating);
        
        r1=get_yield(yield,term1,8);
        r2=get_yield(yield,term2,8);
    }else{
        term1=stod(yield[i-1][0]);
        term2=stod(yield[i][0]);
        y1=get_yield(yield,term1,rating);
        y2=get_yield(yield,term2,rating);
        
        r1=get_yield(yield,term1,8);
        r2=get_yield(yield,term2,8);
        
    }
    
    double y=(y1+(y2-y1)*((t-term1)/(term2-term1)));
    double r=(r1+(r2-r1)*((t-term1)/(term2-term1)));
    
    yr.push_back(y);
    yr.push_back(r);
    
    return yr;
    
}


double fcPrice(security instrument,int rating,vector<vector<string>> yield,double st){
    
    double price,s;
    //calculating term according to maturity date
    double md=instrument.get_maturityDate();
    //time_t now=time(0);
    //tm *ltm = localtime(&now);//time now
    double t=md-st;
    //vector<double> yr1=findyr(instrument,rating,yield,st,1);
    double m=instrument.get_couponPerYear();
    
    //calculate yield and r
    //assume yield and r changed linearly between the terms given in yield curve file
    //assume over 30 years, the yield and r curves are flat
    //yield(0)=0
    
    if(t>=0){//maturity day more than 1 year
        
        //find y and r
        vector<double> yr=findyr(instrument,rating,yield,st,t);

        //if apply spread
        
//        vector<double> yrs=findyr(instrument,rating,yield,st,t+1);
//        s=instrument.get_yield()-yrs[0];
//        //cout<<"spread "<<s<<" yield "<<yrs[0]<<endl;
//        yr[0]=yr[0]+s;
        

        //cout<<term1<<" "<<term2<<" "<<y1<<" "<<y2<<" "<<r1<<" "<<r2<<" "<<y<<" "<<r<<endl;
        price=instrument.get_newtPrice(yr[0],yr[1],t,rating);
        
        
    }else{//maturity day less than 1 year
        t=-t;
        vector<double> yr=findyr(instrument,rating,yield,st,t);
        
        double N=0;
        if(rating==8){//if default
            N=instrument.get_newtPrice(yr[0],yr[1],t,rating);
        }else{
            N=instrument.get_notional();
        }
        
        //invest the money into money market after maturity
        price=N*pow((1+double(yr[1])/m),m*t);
    }
    
    //return price*pow((1+double(yr1[1])/m),-m*1);
    return price;

}

//forecast rating for each issuer
//Part 2
int fcRating(vector<vector<string>> indCorr,vector<issuer> issuers,vector<vector<string>> tran,string issuername,int ratingfrom,double epss){
    
    int ratingto=0;
    double xi,xc;
    double corri,corrc;
    
    corri=get_inCorr(indCorr,findInd(issuers,issuername));
    //draw correlated nois for this industry
    xi=epss*corri+sqrt(1-pow(corri,2))*eps();
    //draw asset nois
    corrc=findCorr(issuers,issuername);
    xc=xi*corrc+sqrt(1-pow(corrc,2))*eps();
    
    //find the rating
    ratingto=int(tran[0].size())-1;
    
    double ncdf=pstod(tran[ratingfrom][ratingto]);
    if(ratingfrom==0){
        ratingto=0;
    }else if(ratingfrom!=0){
        while(cdf(xc,0,1)>ncdf){
            if(ratingto>1) {
                ratingto--;
                ncdf=ncdf+pstod(tran[ratingfrom][ratingto]);
            }else{
                ncdf=10;
                ratingto=1;
            }
        }
    }
    
    //if(ratingfrom!=ratingto){
        //cout<<epss<<" xc "<<xc<<" prob in initial file "<<pstod(tran[ratingfrom][ratingto])<<" cdf is "<<cdf(xc,0,1)<<"   ncdf is "<<ncdf<<"   rating "<<ratingfrom<<" "<<ratingto<<endl;
    //}

    //check error
    if(ratingto>0){
        return ratingto;
    }else{
        cout<<"something wrong in fcRating"<<endl;
    }
    return 0;
}

int findRating(vector<issuer> is,string issuername){
    int k=0;
    while(is[k].get_name().compare(issuername)!=0){
        k++;
    }
    return is[k].get_rating();
}
string findInd(vector<issuer> is,string issuername){
    int k=0;
    while(is[k].get_name().compare(issuername)!=0){
        k++;
    }
    return is[k].get_industry();

}

double findCorr(vector<issuer> is,string issuername){
    int k=0;
    while(is[k].get_name().compare(issuername)!=0){
        k++;
    }
    return is[k].get_inCorr();

}

//enhance stod
double pstod(string a){
    
    size_t found = a.find("%");
    
    if(found<a.size()){
        return stod(a)/100;
    }else{
        return stod(a);
    }
}
