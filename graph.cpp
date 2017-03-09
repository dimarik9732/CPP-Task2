#include "graph.h"
using namespace std;

// LIST
List::List(const List & another){

	if (another.length == 0){
		first = NULL;
		last = NULL;
		length = 0;
		return;
	}
	else{
		first = new Node(another.first->elem);
		length = 1;
		Node *current = first;
		Node *an_cur = another.first->next;
		while (an_cur){
			current->next = new Node(an_cur->elem);
			++length;
			if (!an_cur->next){
				last = current->next;
				return;
			}
			an_cur = an_cur->next;
			current = current->next;
		}
		return;
	}
}

void List::append(Edge value){
	Node *temp = new Node(value);
	++length;
	if (first == NULL){
		first = temp;
		last = temp;
		return;
	}
	else {
		last->next = temp;
		last = last->next;
		return;
	}	
}

int List::get_length() const{
	return this->length;
}

Edge& List::operator[](int n) throw(errors){
	if (n > length -1)
		throw errors("Out of index");

	if (n == length - 1)
		return last->elem;

	Node* cur = first;
	for (int i = 0; i < n; ++i)
		cur = cur->next;

	return cur->elem;
}

void List::clear(){
	if (!first) return;
	Node *cur = first;
	while (cur){
		Node *temp = cur->next;
		delete cur;
		cur = temp;
	}
	first = NULL;
	length = 0;
	return;
}

List::~List(){
	this->clear();
}

// Set Node
void Set::Node::insert(const Vertices &v) throw (errors){
	if (v == this->elem){
		throw errors("Bad insert");
	}
	if (v > this->elem){
		if (this->right)
			this->right->insert(v);
		else this->right = new Node (v);
	}
	if (v < this->elem){
		if (this->left){
			this->left->insert(v);
		}
		else this->left = new Node(v);
	}
	return; 
}

Set::Node* Set::Node::findWithParent(const Vertices &v, Set::Node* &parent){
	Node * current = this;
	parent = NULL;

	while (current){

		if (v == current->elem)
			break;
		
		parent = current;
		if (v  > current->elem)
			current = current->right;
		else 
			current = current->left;	
	}

	return current;
}

Set::Node* Set::Node::del(const Vertices &v){
	Node *parent, *current; 
	current = this->findWithParent(v, parent);
	if (!current->right){
		// Node hasn`t got right child
		if(!parent){
			Node *temp = current->left;
			current->left = NULL;
			delete current;
			return temp;
		}
		if (parent->left == current)
			parent->left = current->left;
		else 
			parent->right = current->left;
	}
	else 
		if (!current->right->left){
			// Node has got right child, which hasn`t got left child
			current->right->left = current->left;
			if(!parent){
				Node *temp = current->right;
				current->right = NULL;
				current->left = NULL;
				delete current;
				return temp;		
			}
			if (parent->left == current)
				parent->left = current->right;
			else 
				parent->right = current->right;		
		}
	else {
		// Node has got right child, which has got left child
		Node *cur = current->right;
		while(cur->left->left)
			cur = cur->left;
		Node *tmp = cur->left;
		cur->left = tmp->right;
		tmp->left = current->left;
		tmp->right = current->right;
		if (!parent){
			current->right = NULL;
			current->left = NULL;
			delete current;
			return tmp;
		}
		if (parent->left == current)
			parent->left = tmp;
		else 
			parent->right = tmp;		
	}
	current->right = NULL;
	current->left = NULL;
	delete current;
	return this;
}

//Set
void Set::insert(const Vertices & v){
	if (this->root)
		this->root->insert(v);
	else 
		this->root = new Node(v);
	++size;
}

bool Set::contains(const Vertices &v) const{
	Node * parent;
	return root && (root->findWithParent(v, parent));
}

void Set::del(const Vertices &v){
	if (root){
		root = root->del(v);
		--size;
	}
}

void Set::clear(){
	if(root){ 
		delete root;
		root = NULL;
		size = 0;
	}
}

// operator << 
ostream& operator << (ostream & s, const Vertices &a){
	s << "(" << a.num << ")";
	return s;
}
ostream& operator << (ostream & s, const Edge &a){
	s << "[" << a.from << " \"" << a.weight << "\" " << a.to << "]";
	return s;
}
ostream& operator << (ostream& s, const List & a){
	s << "[ ";
	for (List::Node * cur = a.first; cur; cur = cur->next)
		s << cur->elem << " ";
	s << "]";
}
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
	s << " }";
	return s;
}

// operator ==
bool operator == (const Edge &a, const Edge &b){
	return (a.from == b.from) && (a.to == b.to); 
}

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


