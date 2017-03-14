#include "Graph.h"
#include <iostream>
using namespace std;

int main(void)
{
	int suc = 0, total = 0;
	Edge e1(2, 3);
	Graph g2("( {(1), (2)} [|(1) (2)|] )");
	Graph g3("( {(1), (2), (3)} [|(1) (2)|] )");
	Graph g4("( {(1), (2), (3)}) [|(1) (2)|, |(2) (3)|] )");
	List l1("[|(1) (2)|]");

	g2 += 3;
	if (g2 == g3)
		cout << "operator += for Vertice Test +" << endl , ++suc, ++total;
	else 
		cout << "operator += for Vertice Test -" << endl, ++total;

	g2 += e1;
	if (g2 == g4)
		cout << "operator += for Edge Test +" << endl, ++suc, ++total ;
	else 
		cout << "operator += for Edge Test -" << endl, ++total;

	g3 += g4;

	if (g3 == g4)
		cout << "operator += for Graph Test +" << endl, ++suc, ++total;
	else 
		cout << "operator += for Graph Test -" << endl, ++total;

	if( l1 == g3.out(1))
		cout << "Graph::out function Test +" << endl, ++suc, ++total;
	else 
		cout << "Graph::out function Test -" << endl, ++total;

	if (g2.istherepath(1, 3)){
		cout << "istherepath Test +" << endl, ++suc, ++total;
	}
	else
		cout << "istherepath Test -" << endl, ++total;

	cout << suc << " tests succseed from " << total << endl;	 
	return 0;
}