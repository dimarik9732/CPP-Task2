#ifndef __EDGE_H__
#define __EDGE_H__
#include <iostream>
#include "Vertices.h"
using namespace std;

class Edge{
	Vertices from;
	Vertices to;
	int weight;
public:
	Edge (Vertices f, Vertices t, int w = 1): from(f), to(t), weight(w){};
	// Edge (const char*);
	friend ostream& operator << (ostream& s, const Edge & a);
	friend bool operator == (const Edge &a, const Edge &b);
};
#endif