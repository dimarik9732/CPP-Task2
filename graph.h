#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <cstring>
using namespace std;

class errors{
	const char* error;
public:
	errors(const char* err):error(err){};
	void name(){
		cerr << error << endl;
	}	
};

class Vertices{
	int num;
public:
	Vertices(int n = 0): num(n){};
	friend ostream& operator << (ostream & s, const Vertices &a);
	friend bool operator == (const Vertices &a, const Vertices &b);
	friend bool operator >  (const Vertices &a, const Vertices &b);
	friend bool operator < (const Vertices &a, const Vertices &b);
};

class Edge{
	Vertices from;
	Vertices to;
	int weight;
public:
	Edge (Vertices f, Vertices t, int w = 1): from(f), to(t), weight(w){};
	Edge (const char*);
	friend ostream& operator << (ostream& s, const Edge & a);
	friend bool operator == (const Edge &a, const Edge &b);
};

// LIST
class List{

	struct Node{
		Edge elem;
		Node *next;
		Node(Edge value): elem(value){ this->next = NULL;}
		Node(const Node *);
		~Node(){
			if (this->next)
				delete this->next;
		}
	};

	Node *first;
	Node *last;
	int length;

public:
	List(){
		first = NULL;
		last = NULL;
		length = 0;
	}

	List(const List & another);

	void append(Edge value);

	int get_length() const;

	void clear();

	Edge& operator[](int n) throw(errors);

	friend ostream& operator << (ostream& s, const List & a);
	~List();
};


// SET
class Set{
	struct Node{
		Vertices elem;
		Node *right;
		Node *left;
		Node(const Vertices &a):elem(a), right(NULL), left(NULL){};
		Node(const Node &);
		friend ostream& operator << (ostream& s, const Set::Node &a);
		void insert(const Vertices &) throw (errors);
		Node *del(const Vertices &);
		Node *findWithParent(const Vertices &, Node *&);
		~Node(){
			if (this->left)
				delete this->left;
			if (this->right)
				delete this->right;
		}
	};

	Node *root;
	int size;
public:
	Set(): root(NULL), size(0){};
	void insert(const Vertices &);
	void del(const Vertices &);
	bool contains(const Vertices &) const;
	// friend Set operator+ (const Set &, const Set &);
	friend ostream& operator << (ostream& s, const Set &a);
	friend ostream& operator << (ostream& s, const Set::Node &a);
	void clear();

	~Set(){
		this->clear();
	}
};
#endif