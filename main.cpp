#include "Graph.h"
#include <iostream>
using namespace std;

int main(void)
{

	// Graph g2("( {(1), (2), (3)} [|(1) (2)|, |(3) (1)|] )");
	
	Edge e1(2, 3);

	Graph g2("( {(1), (2)} [|(1) (2)|] )"), g3("( {(1), (2), (3)} [|(1) (2)|] )"), g4("( {(1), (2), (3)}) [|(1) (2)|, |(2) (3)|] )");	
	g2 += 3;
	if (g2 == g3)
		cout << "operator += for Vertice Test +" << endl;
	else 
		cout << "operator += for Vertice Test -" << endl;

	g2 += e1;
	if (g2 == g4)
		cout << "operator += for Edge Test +" << endl;
	else 
		cout << "operator += for Edge Test -" << endl;

	g3 += g4;

	// cout << g3;
	cout << g3 << endl;
	// cout << g4 << endl;

	
	// if (g3 == g4)
		// cout << "operator += for Graph Test +" << endl;
	// else 
		// cout << "operator += for Graph Test -" << endl;

	if (g2.istherepath(1, 3)){
		cout << "istherepath Test +" << endl;
	}
	else
		cout << "istherepath Test -" << endl; 
	return 0;
}