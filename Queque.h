#ifndef __QUEQUE_H__
#define __QUEQUE_H__
#include "Vertices.h"

class Queque
{
	struct Node{
	Vertices elem;
	Node *next;
	Node(Vertices value): elem(value){ this->next = NULL;}
	~Node(){
		if (this->next)
			delete this->next;
		}
	};

	Node *first;
	Node *last;
	int size;

public:
	Queque():first(NULL), last(NULL), size(0){};
	void push(Vertices value);
	Vertices pop();
	bool empty() const {
		return size == 0;
	}
	void clear();
	
	~Queque(){
		if (!this->empty())
			delete first;
	}
};
#endif