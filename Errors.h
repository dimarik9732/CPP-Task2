#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <iostream>
using namespace std;

class Errors{
	const char* error;
public:
	Errors(const char* err):error(err){};
	void name(){
		cerr << error << endl;
	}	
};

#endif