#include "Set.h"

// Set Node
Set::Node::Node(const Node* another):elem(another->elem), right(NULL), left(NULL), height(another->height){
	if (another->left)
		left = new Node(another->left);
	if (another->right)
		right = new Node(another->right);
}

unsigned int Set::Node::upsize() const{
	if (this == NULL)
		return 0;
	else 
		return this->left->upsize() + 1 + this->right->upsize();
}

//Set
// Private
unsigned char Set::height(Node *p) const{
	return p ? p->height : 0;
}

int Set::bfactor(Node* p) const{
	return height(p->left) - height(p->right);
}

void Set::fixheight(Node* p){
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1; 
}

Set::Node *Set::rotateRight(Set::Node *p){
	Node * q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

Set::Node *Set::rotateLeft(Set::Node *q){
	Node * p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

Set::Node *Set::balance(Set::Node* p){
	fixheight(p);
	if (bfactor(p) == 2){
		if (bfactor(p->left) < 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	if (bfactor(p) == -2){
		if (bfactor(p->right) > 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	return p;
}

Set::Node *Set::insert(Node *p, const Vertices &v){
	if (!p) return new Node(v);
	if (v == p->elem) return p;
	if (v < p->elem)
		p->left = insert(p->left, v);
	else
		p->right = insert(p->right, v);
	return balance(p); 
}

Set::Node* Set::findRmMin(Set::Node* p, Set::Node *&min){
	if (!p->left) {
		min = p;
		return p->right;
	}
	else {
		p->left = findRmMin(p->left, min);
		return balance(p);
	}
}

Set::Node* Set::remove(Set::Node* p, const Vertices& v){
	if (!p) return NULL;
	if ( v < p->elem){
		p->left = remove(p->left, v);
	}
	if ( v > p->elem){
		p->right = remove(p->right, v);
	}

	if ( v == p->elem) {
		Node * q = p->left;
		Node * r = p->right;
		delete p;

		if (!r) return q;
		Node *min;
		r = findRmMin(r, min);
		min->right = r;
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

bool Set::contains(Set::Node* p, const Vertices &v) const{
	if (!p) return false;
	if (p->elem == v) return true;
	if (v > p->elem) return contains(p->right, v);
	else return contains(p->left, v);
}

void Set::merge(Set::Node*& it , const Node * another){
	if(!another) return;
	it = insert(it, another->elem);
	merge(it, another->left);
	merge(it, another->right);
	return;
}

// Public
Set::Set(const Set &another):root(NULL){
	size = another.size;
	if (another.root)
		root = new Node(another.root);
}

Set::Set(const char*s)throw(Errors){

	char *ns = new char[strlen(s)+1];
	strcpy(ns, s);

	char *ch1 = strchr(ns, '{');
	if (!ch1)
		throw Errors("Bad Construct Set");
	char *ch2 = strchr(ns, ',');

	if (!ch2){
		root = new Node(ch1+1);
		size = 1;
		delete[] ns;
		return;
	}

	*ch2 = '\0';
	root = new Node(ch1+1);
	size = 1;
	ch1 = ch2 + 1;
	ch2 = strchr(ch1+1, ',');
	while (ch1 || (ch1 && ch2)){
		if (ch2)
			*ch2 = '\0';
		root = insert(root, ch1+1);
		if (ch2){
			ch1 = ch2 + 1;
			ch2 = strchr(ch1+1, ',');
		}
		else ch1 = NULL;
		++size;
	}
	delete[] ns;
}

void Set::insert(const Vertices & v){
	root = insert(root, v);
	++size;
}

bool Set::contains(const Vertices &v) const{
	return contains(root, v);
}

void Set::remove(const Vertices &v){
	root = remove(root, v);
	--size;
}

void Set::clear(){
	if(root){ 
		delete root;
		root = NULL;
		size = 0;
	}
}

Set &Set::operator= (const Set & another){
	if (this == &another){
		return *this;
	}

	this->clear();
	if (another.root)
		root = new Node(another.root);
	size = another.size;
	return *this;
}

Set &Set::operator+= (const Set &another){
	merge(root, another.root);
	size = root->upsize();
	return *this;
}


int Set::get_size(){
	return this->size;
}

/*bool operator == (const Set::Node & a, const Set::Node & b){

	if (!&a && !&b) return true;

	if (!(&a && &b)) return false;

	bool res = (a.elem == b.elem) && *a.right == *b.right && *a.left == *b.left;
	return res;
}*/	

// operator <<
using namespace std; 
ostream& operator << (ostream& s, const Set::Node &a){

	if (a.left)
		s << (*a.left);

	s << a.elem << " ";

	if (a.right)
		s << (*a.right);
	
	return s;
}
ostream& operator << (ostream& s, const Set &a){
	s << "{ ";

	if (a.root)
		s << (*a.root);
	else
		s << "empty";
	s << "}";
	return s;
}

/*bool operator== (const Set& a, const Set& b){
	if (a.size != b.size) return false;


}*/