#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include "List.h"
#include "Set.h"
#include "Queque.h"

using namespace std;

class Graph{
	Set vert;
	List edges;

public:
	Graph(): vert(), edges(){};
	Graph(const Graph & another): vert(another.vert), edges(another.edges){};
	Graph(const char* s)throw(Errors);
	Graph & operator+=(const Graph &another){
		vert += another.vert;
		edges += another.edges;
		return *this;
	};
	Graph & operator+=(const Edge &a){
		if (edges.contains(a)) return *this;
		else edges.append(a);
		if (!vert.contains(a.get_from())) vert.insert(a.get_from());
		if (!vert.contains(a.get_to())) vert.insert(a.get_to());
	}
	Graph & operator+=(const Vertices & v){
		if (!vert.contains(v)) vert.insert(v);
		return *this;
	}
	void remove(const Vertices& v);
	void remove(const Edge &a){
		if (!edges.contains(a)) return;
		else edges.remove(a);
	}
	// List in(const Verices &);
	List out(const Vertices &) const;
	bool istherepath(const Vertices& v1, const Vertices& v2)const; 
	friend ostream& operator << (ostream &, const Graph&);
	friend bool operator== (const Graph&, const Graph&);
};

#endif