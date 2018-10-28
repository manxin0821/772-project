#ifndef __template_772__portfolio__
#define __template_772__portfolio__


#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

#include "security.h"
// we need to include 'security.h'
// because it is used in the code below:


using namespace std;

class portfolio{
	
private:
    
	string name;//portfolio name
    vector<security> securities;//components of the portfolio
    
    int count;
	double rvalue;//real value of the portfolio
    double tvalue;//theoretical value of the protfolio
    double chvalue;//change value
	
public:
    
    portfolio(){};
	portfolio(vector<security> v);//constructor
    
    int get_count();//get number of instruments in this portfolio
    security get_security(int index);
	double get_rvalue();//get real value
    double get_tvalue();//get theoretical value
    //print to screen and file
    void printAll();
    void printpPrice();
    //void output(string filename);
	
};

#endif /* defined(__template_772__portfolio__) */
