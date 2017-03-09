#include "Set.h"

// Set Node
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
	s << " }";
	return s;
}