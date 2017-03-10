#ifndef __VERTICES_H__
#define __VERTICES_H__
#include <iostream>
#include "Errors.h"
#include <cstring>
#include <cstdlib>
using namespace std;

class Vertices{
	int num;
public:
	Vertices(int n = 0): num(n){};
	Vertices(const char*);

	friend ostream& operator << (ostream & s, const Vertices &a);
	friend bool operator == (const Vertices &a, const Vertices &b);
	friend bool operator >  (const Vertices &a, const Vertices &b);
	friend bool operator < (const Vertices &a, const Vertices &b);
};
#endif