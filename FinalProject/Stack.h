#ifndef STACK_H
#define STACK_H
#include <Node.h>
template<class T>
class Stack{ 
public:
	//constructor takes initial value or nothing
	Stack(T value);
	Stack();
	//push value onto stack (returns new head)
	Node<T>* push(T value);
	//pop value from stack (returns value)
	T pop();
	//copy function
	static Stack<T>* copyStack(Stack<T>*);
	Node<T>* getHead() const;
private:
	//the first Node in the stack
	Node<T>* head;
};
/* Stack constructor creates a new node with given 
value.*/
template<class T>
Stack<T>::Stack(T value){
	//Set head to initial value node.
	head = new Node<T>(value);
}
/* Stack constructor: starts empty.*/
template<class T>
Stack<T>::Stack(){
	head = 0;
}
/* push puts new node on the stack, and returns the
new head.*/
template<class T>
Node<T>* Stack<T>::push(T value){
	//create node with given value
	Node<T>* n = new Node<T>(value);

	//if the stack is empty
	if(head == 0){
		head = n;
	}
	//else we just need to make a minor adjustment
	else{
		//set node's next node to current head
		n->setNext(head);
		//set stack head to new node
		head = n;
	}
	return head;
}
/* pop value from top of stack. returns the value. */
template<class T>
T Stack<T>::pop(){
	//return null for a null head
	if(head == 0) return 0;
	//save the current head
	Node<T>* oldHead = head;
	//set the new head to the second item on the list
	head = head->getNext();
	return oldHead->getKey();
}
/*
copy function
debug - this is NOT good for memory. it's making 2 unneeded stacks each time.
*/
template<class T>
Stack<T>* Stack<T>::copyStack(Stack<T>* toCopy){
	Stack<T>* copy1 = new Stack<T>();
	Stack<T>* returnCopy = new Stack<T>();

	//first we copy the toCopy stack into copy 1, where it will be backwards.
	while(toCopy->head!=0){
		T val = toCopy->pop();
		copy1->push(val);
	}
	//now we copy 1 into toCopy and returnCopy
	while(copy1->head!=0){
		T val = copy1->pop();
		toCopy->push(val);
		returnCopy->push(val);
	}
	return returnCopy;
}
template<class T>
Node<T>* Stack<T>::getHead() const{
	return head;
}
#endif