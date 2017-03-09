#include "Vertices.h"
// operator ==
bool operator == (const Vertices &a, const Vertices &b){
	return a.num == b.num;
}

// operator <
bool operator < (const Vertices &a, const Vertices &b){
	return a.num < b.num;
}

// operator >
bool operator > (const Vertices &a, const Vertices &b){
	return a.num > b.num;
}

using namespace std;
// operator << 
ostream& operator << (ostream & s, const Vertices &a){
	s << "(" << a.num << ")";
	return s;
}