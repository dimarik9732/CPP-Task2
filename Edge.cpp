#include "Edge.h"
using namespace std;

Edge::Edge(const char *s) throw(Errors){
	char *ns = new char[strlen(s)+1];
	strcpy(ns, s);
	char *ch1 = strchr(ns, '(');
	char *ch2 = strchr(ch1, ')');

	if (!ch1 || !ch2){
		throw Errors("Bad construct Edge");
	}
	*(ch2+1) = '\0';
	from = ch1;
	ch1 = strchr(ch2 + 2, '\"');
	weight = 1;
	if (ch1){ 
		ch2 = strchr(ch1 + 1, '\"');
		*(ch2) = '\0';
		weight = atoi(ch1+1);
	}
	ch1 = strchr(ch2 + 2, '(');
	ch2 = strchr(ch1 + 1, ')');
	if (!ch1 || !ch2) 
		throw Errors("Bad construct Edge");
	*(ch2+1) = '\0';
	to = ch1;
	delete[] ns;
}
// operator <<
ostream& operator << (ostream & s, const Edge &a){
	s << "|" << a.from << " \"" << a.weight << "\" " << a.to << "|";
	return s;
}
// operator ==
bool operator == (const Edge &a, const Edge &b){
	return (a.from == b.from) && (a.to == b.to); 
}