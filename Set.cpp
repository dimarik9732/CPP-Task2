#include "Set.h"

// Set Node
Set::Node::Node(const Node* another):elem(another->elem), right(NULL), left(NULL){
	if (another->left)
		left = new Node(another->left);
	if (another->right)
		right = new Node(another->right);
}

void Set::Node::insert(const Vertices &v){
	if (v == this->elem){
		return;
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

void Set::Node::merge(const Node * another){
	if(!another) return;
	this->insert(another->elem);
	this->merge(another->left);
	this->merge(another->right);
}

int Set::Node::upsize() const{
	if (this == NULL)
		return 0;
	else 
		return this->left->upsize() + 1 + this->right->upsize();
}

//Set
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
		root->insert(ch1+1);
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
	root->merge(another.root);
	size = root->upsize();
	return *this;
}

int Set::get_size(){
	return this->size;
}

bool operator == (const Set::Node & a, const Set::Node & b){

	if (!&a && !&b) return true;

	if (!(&a && &b)) return false;

	bool res = (a.elem == b.elem) && *a.right == *b.right && *a.left == *b.left;
	return res;
}	
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
bool operator== (const Set& a, const Set& b){
	if (a.size != b.size) return false;


}