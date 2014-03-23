#include <LinkedList.h>
template<class T>
LinkedList<T>::LinkedList(int length){
	Node<T>* p = 0;
	Node<T>* f = 0; 
	LinkedList<T>::length = length;
	for(int i = 0; i < length; i++){
		Node<T>* n = new Node<T>();

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
template<class T>
void LinkedList<T>::add(int index, T value){
	//if it's out of bounds
	if(index > length) return;
	//if it's the first one
	else if(index == 0){
		Node<T>* n = new Node<T>(value);
		n->setNext(head);
		head = n;
	}
	//if it's the last one
	else if(index = length){
		Node<T>* n = head;
		//get the last node
		for(int i = 0; i < length-1; i++){
			n = n->getNext();
		}
		Node<T>* newN = new Node<T>(value);
		n->setNext(newN);
	}
	//else it's in the middle
	else{
		//we need the node before and after. 
		Node<T>* before = head;
		Node<T>* n = new Node<T>(value);
		Node<T>* after;
		for(int i = 0; i < index - 1; i++){
			before = before->getNext();
		}
		after = before->getNext();
		before->setNext(n);
		n->setNext(after);
	}

	length++;
}
template<class T>
Node<T>* LinkedList<T>::getHead() const{
	return head;
}
template<class T>
void LinkedList<T>::setHead(Node<T>* n){
	head = n;
}
