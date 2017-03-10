#include "List.h"

// List Node
List::Node::Node(const Node *another): elem(another->elem), next(NULL){
	if (another->next)
		next = new Node(another->next);
}
List::Node* List::Node::findWithPrevious(const Edge& elem, List::Node*& previous){
	Node * current = this;
	previous = NULL;

	while (current){

		if (elem == current->elem)
			break;
		
		previous = current;
		current = current->next;	
	}

	return current;
}
// LIST
List::List(const char* s) throw (Errors){
	
	char *ns = new char[strlen(s)+1];
	strcpy(ns, s);

	char *ch1 = strchr(ns, '[');
	if (!ch1)
		throw Errors("Bad Construct List");
	char *ch2 = strchr(ns, ',');

	if (!ch2){
		first = new Node(ch1+1);
		last = first;
		length = 1;
		delete[] ns;
		return;
	}

	*ch2 = '\0';
	first = new Node(ch1+1);
	last = first;
	length = 1;
	ch1 = ch2 + 1;
	ch2 = strchr(ch1+1, ',');
	while (ch1 || (ch1 && ch2)){
		if (ch2)
			*ch2 = '\0';
		this->append(ch1+1);
		if (ch2){
			ch1 = ch2 + 1;
			ch2 = strchr(ch1+1, ',');
		}
		else ch1 = NULL;
	}
	delete[] ns;
}

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

Edge& List::operator[](int n) const throw(Errors){
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
	List temp(another);
	for (int i = 0; i < temp.length; ++i)
		if(this->contains(temp[i])) temp.del(temp[i]);

	this->length += another.length;
	this->last->next = new Node (temp.first);
	Node *cur = this->last->next;
	for (int i = 0; i < temp.length - 1; ++i)
 		cur = cur->next;
 	this->last = cur;
 	return *this;
} 

List& List::operator=(const List &another){
	if (this == &another){
		return *this;
	}

	this->clear();

	if (another.first == NULL){
		return *this;
	}

	first = new Node(another.first);
	length = another.length;
	Node *cur = first;
	for (int i = 0; i < length - 1; ++i)
		cur = cur->next;
	last = cur;

	return *this;
}

bool List::contains(Edge elem){
	Node* previous;
	return first && first->findWithPrevious(elem, previous);
}

void List::del(Edge elem){
	Node *prev;
	Node * to_del = first->findWithPrevious(elem, prev);
	if (!to_del) return;
	if (first == to_del){
		if (last != to_del){
			first = to_del->next;
			to_del->next = NULL;
			delete to_del;
			--length;
			return;
		}
		else {
			first = last = NULL;
			--length;
			delete to_del;
		}
	}

	if (last == to_del){
		delete to_del;
		--length;
		last = prev;
		last->next = NULL;
		return;
	}

	prev->next = to_del->next;
	to_del->next = NULL;
	delete to_del;
	--length;
	return;
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

bool operator == (const List&a, const List&b){
	if(a.length != b.length) return false;

	bool res = true;
	for (int i = 0; i < a.length; ++i)
	{
		res = res && (a[i] == b[i]);
		if (!res) break;
	}
	return res;
}
