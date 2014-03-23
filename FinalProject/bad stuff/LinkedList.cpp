#include <LinkedList.h>
LinkedList::LinkedList(int length){
	Node* p = 0;
	Node* f = 0; 
	LinkedList::length = length;
	for(int i = 0; i < length; i++){
		Node* n = new Node();

		//mark head
		if (i==0) f = n;

		if(p != 0){
			//set the previous one to point to this one
			p->setNext(n);
		}
		p = n;
	}
	head = f;
}
void LinkedList::add(int index, int value){
	//if it's out of bounds
	if(index > length) return;
	//if it's the first one
	else if(index == 0){
		Node* n = new Node(value);
		n->setNext(head);
		head = n;
	}
	//if it's the last one
	else if(index = length){
		Node* n = head;
		//get the last node
		for(int i = 0; i < length-1; i++){
			n = n->getNext();
		}
		Node* newN = new Node<T>(value);
		n->setNext(newN);
	}
	//else it's in the middle
	else{
		//we need the node before and after. 
		Node* before = head;
		Node* n = new Node(value);
		Node* after;
		for(int i = 0; i < index - 1; i++){
			before = before->getNext();
		}
		after = before->getNext();
		before->setNext(n);
		n->setNext(after);
	}

	length++;
}
Node* LinkedList::getHead() const{
	return head;
}
void LinkedList::setHead(Node* n){
	head = n;
}
