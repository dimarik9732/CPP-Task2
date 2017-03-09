#include "Edge.h"
using namespace std;
// operator <<
ostream& operator << (ostream & s, const Edge &a){
	s << "[" << a.from << " \"" << a.weight << "\" " << a.to << "]";
	return s;
}
// operator ==
bool operator == (const Edge &a, const Edge &b){
	return (a.from == b.from) && (a.to == b.to); 
}