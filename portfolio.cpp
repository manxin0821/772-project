#include "portfolio.h"


portfolio::portfolio(vector<security> v){
	// Create a portfolio from a vector
	// (i.e. list of) securities:
	securities = v;
}
int portfolio::get_count(){
    return int(securities.size());
}

security portfolio::get_security(int index){
    return securities[index];
}

double portfolio::get_rvalue(){
	double v = 0;
	for(int i=0; i<securities.size();i++){
        if(securities[i].get_type().compare("Bond")==0){
            v += securities[i].get_notional()*securities[i].get_rPrice()/100;
        }else if(securities[i].get_type().compare("CDS")==0){
            v += securities[i].get_notional()*securities[i].get_tPrice()/100;
        }
    }
	return v;
}

double portfolio::get_tvalue(){
    double v=0;
    double N=0;//notional
    for(int i=0; i<securities.size();i++){
        
        if(securities[i].get_type().compare("Bond")==0){
            N=7;
        }else if(securities[i].get_type().compare("CDS")==0){
            N=5;
        }
        
        v += N*securities[i].get_tPrice()/100;
    }
    return v;
}
//print to screen
void portfolio::printAll(){
    for(int i=0;i<securities.size();i++){
        securities[i].printAll();
    }
}
void portfolio::printpPrice(){
    for(int i=0;i<securities.size();i++){
        securities[i].printpPrice();
    }
}
//void output(string filename);
