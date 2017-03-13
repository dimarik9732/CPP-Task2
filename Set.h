#ifndef __SET_H__
#define __SET_H__
#include "Vertices.h"
#include <iostream>
using namespace std;
// SET
class Set{
	struct Node{
		Vertices elem;
		unsigned char height;
		Node *right;
		Node *left;
		Node(const Vertices &a):elem(a), height(1), right(NULL), left(NULL){};
		Node(const Node *);
		unsigned int upsize() const;
		~Node(){
			if (this->left)
				delete this->left;
			if (this->right)
				delete this->right;
		}
	};

	Node *root;
	unsigned int size;
	unsigned char height(Node *) const;
	int bfactor(Node *) const;
	void fixheight(Node *);
	Node *rotateRight(Node *);
	Node *rotateLeft(Node *);
	Node *balance(Node *);
	Node *insert(Node *, const Vertices &);
	Node *findRmMin(Node *, Node *&);
	Node *remove(Node *, const Vertices &);
	void merge(Node *&, const Node *);
	bool contains(Node *, const Vertices &) const;

public:
	Set(): root(NULL), size(0){};
	Set(const Set &);
	Set(const char*)throw(Errors);	
	void insert(const Vertices &);
	bool contains(const Vertices &) const;
	void remove(const Vertices &);
	void clear();

	Set& operator=(const Set &);
	Set& operator+=(const Set &);
	int get_size();
	// friend Set operator+ (const Set &, const Set &);
	friend ostream& operator << (ostream& s, const Set &a);
	friend ostream& operator << (ostream& s, const Node &a);
	// friend bool operator == (const Node&, const Node&);
	// friend bool operator== (const Set&, const Set&);
	~Set(){
		this->clear();
	}
};
#endif