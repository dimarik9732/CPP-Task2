#include "Queque.h"

void Queque::push(Vertices value){
	Node *temp = new Node(value);
	++size;
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

Vertices Queque::pop(){
	--size;
	Vertices temp = first->elem;
	Node *tmp = first;
	first = first->next;
	if (!first){
		delete tmp;
		last = NULL;
		size = 0;
		return temp;
	}
	tmp->next = NULL;
	delete tmp;
	return temp;
};
