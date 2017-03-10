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
		Node(const Node *);
		friend ostream& operator << (ostream& s, const Node &a);
		void insert(const Vertices &);
		void merge(const Node *);
		Node *del(const Vertices &);
		Node *findWithParent(const Vertices &, Node *&);
		int upsize() const;
		friend bool operator == (const Node&, const Node&);
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
	Set(const Set &);
	Set(const char*)throw(Errors);
	void insert(const Vertices &);
	void del(const Vertices &);
	bool contains(const Vertices &) const;
	void clear();
	Set& operator=(const Set &);
	Set& operator+=(const Set &);
	int get_size();
	// friend Set operator+ (const Set &, const Set &);
	friend ostream& operator << (ostream& s, const Set &a);
	friend ostream& operator << (ostream& s, const Node &a);
	friend bool operator == (const Node&, const Node&);
	friend bool operator== (const Set&, const Set&);
	~Set(){
		this->clear();
	}
};
#endif