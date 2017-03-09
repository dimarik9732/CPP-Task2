#include "Vertices.h"
#include "Edge.h"
#include "Errors.h"
#include <iostream>
using namespace std;
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

	Edge& operator[](int n) throw(Errors);

	List& operator+=(const List & another);

	friend ostream& operator << (ostream& s, const List & a);
	~List();
};
