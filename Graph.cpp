#include "Graph.h"

Graph::Graph(const char* s)throw(Errors){


	char *ns = new char[strlen(s)+1];
	strcpy(ns, s);

	char* ch1 = strchr(ns, '{');
	char* ch2 = strchr(ns, '}');

	if (!ch1 && !ch2){
		throw Errors("Bad Construct Graph");
	}

	*(ch2 + 1) = '\0';
	vert = ch1;

	ch1 = strchr(ch2 + 2, '[');
	ch2 = strchr(ch1, ']');

	if (!ch1 && !ch2){
		throw Errors("Bad Construct Graph");
	}

	*(ch2+1) = '\0';
	edges = ch1;

	delete[] ns;
}

List Graph::out(const Vertices &v) const{
	List l1;
	if (!vert.contains(v)) return l1;
	for (int i = 0; i < edges.get_length(); ++i)
	{
		if(edges[i].get_from() == v){
			l1.append(edges[i]);
		}
	}
	return l1;
}

bool Graph::istherepath(const Vertices& v1, const Vertices& v2)const {
	if (!vert.contains(v1) || !vert.contains(v2) ) return false;
	Queque q1;
	q1.push(v1);
	Set used;
	List l1;
	used.insert(v1);
	Vertices cur;
	while(!q1.empty()){
		cur = q1.pop();
		l1 = this->out(cur);
		for (int i = 0; i < l1.get_length(); ++i){
			Vertices w = l1[i].get_to();

			if (w == v2){
				return true;
			}

			if (used.contains(w))
				continue;

			q1.push(w);
			used.insert(w);
		}
	}
	return false;
}

using namespace std;
ostream& operator << (ostream& s, const Graph& g){
	s << "( ";
	s << g.vert;
	s << " ";
	s << g.edges;
	s << " )";
	return s;
}

bool operator == (const Graph& a, const Graph&b){
	return (a.vert == b.vert) && (a.edges == b.edges);
} 