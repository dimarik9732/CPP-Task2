#ifndef __SET_H__
#define __SET_H__
#include "Vertices.h"
#include <iostream>
using namespace std;
// SET
class Set{
	struct Node{
		Vertices elem;
		Node *right;
		Node *left;
		Node(const Vertices &a):elem(a), right(NULL), left(NULL){};
		Node(const Node &);
		friend ostream& operator << (ostream& s, const Node &a);
		void insert(const Vertices &);
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
	friend ostream& operator << (ostream& s, const Node &a);
	void clear();

	~Set(){
		this->clear();
	}
};
#endif