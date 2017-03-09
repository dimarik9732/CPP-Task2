#include "List.h"

// List Node
List::Node::Node(const Node *another): elem(another->elem){
	if (another->next)
		next = new Node(another->next);
}

// LIST
List::List(const List & another){

	if (another.length == 0){
		first = NULL;
		last = NULL;
		length = 0;
		return;
	}
	else{
		first = new Node(another.first);
		length = another.length;
		Node *cur = first;
		for (int i = 0; i < length - 1; ++i)
			cur = cur->next;
		last = cur;
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

Edge& List::operator[](int n) throw(Errors){
	if (n > length -1)
		throw Errors("Out of index");

	if (n == length - 1)
		return last->elem;

	Node* cur = first;
	for (int i = 0; i < n; ++i)
		cur = cur->next;

	return cur->elem;
}

List& List::operator+=(const List & another){
	this->length += another.length;
	this->last->next = new Node (another.first);
	Node *cur = this->last->next;
	for (int i = 0; i < another.length - 1; ++i)
 		cur = cur->next;
 	this->last = cur;
 	return *this;
} 

void List::clear(){
	if (!first) return;
	delete first;
	first = NULL;
	last = NULL;
	length = 0;
	return;
}

List::~List(){
	this->clear();
}

using namespace std;
// operator <<
ostream& operator << (ostream& s, const List & a){
	s << "[ ";
	for (List::Node * cur = a.first; cur; cur = cur->next)
		s << cur->elem << " ";
	s << "]";
	return s;
}
