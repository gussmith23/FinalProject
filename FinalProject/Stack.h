#ifndef STACK_H
#define STACK_H
#include <Node.h>
template<class T>
class Stack{ 
	public:
	//the first Node in the stack
	Node<T>* head;
	//constructor takes initial value.
	Stack(T value);
	//push value onto stack (returns new head)
	Node<T>* push(T value);
	//pop value from stack (returns value)
	T pop();
};
/* Stack constructor creates a new node with given 
value.*/
template<class T>
Stack<T>::Stack(T value){
	//Set head to initial value node.
	head = new Node<T>(value);
}
/* push puts new node on the stack, and returns the
new head.*/
template<class T>
Node<T>* Stack<T>::push(T value){
	//create node with given value
	Node<T>* n = new Node(value);
	//set node's next node to current head
	n->next = head;
	//set stack head to new node
	head = n;
	return head;
}
/* pop value from top of stack. returns the value. */
template<class T>
T Stack<T>::pop(){
	//save the current head
	Node<T>* oldHead = head;
	//set the new head to the second item on the list
	head = head->getNext();
	return oldHead->getKey();
}
#endif