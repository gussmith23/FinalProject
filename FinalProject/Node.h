/*
Gus Henry Smith

Node.h

The Node class defintion defines a simple Node to be used in Linked Lists.
The class is templated to take any type of value in its "key" field. Beca-
use it is templated, all of its functions must be defined in the header.

The Node class includes two very crucial functions:
*moveTo: moves a Node to the specified index relative to the head of the list
*get: gets the node at an index relative to the head of the list
*/

#ifndef NODE_H
#define NODE_H
template<class T>
class Node{
	public:
		//constructors
		Node();
		Node(T);
		
		//setters and getters
		Node<T>* getNext() const;
		void setNext(Node<T>*);
		Node<T>* getPrev() const; 
		void setPrev(Node<T>*); 
		T getKey() const;
		void setKey(T);
		int getCount() const;
		void setCount(int);
		int getFirst() const;
		void setFirst(int);
		int getLast() const;
		void setLast(int);

		//moves to index
		Node<T>* moveTo(int,Node<T>*); 
		/*
		NOTE: THIS MUST BE DEFINED HERE, OR THE COMPILATION THROWS LINKER ERRORS
		get: takes the head of the list, and the index of the Node we desire.
		Returns the node at that index, or nullptr if we go out of the bounds
		of the list.
		*/
		template<class T>
		static Node<T>* get(int index, Node<T>* head){
			Node<T>* n = head;
			for(int i = 0; i < index; i++){
				n = n->getNext();
				if(n == nullptr) return nullptr;
			}
		return n;
		}

	protected:
		T key;
		Node<T>* next;
		Node<T>* prev;
		int count;
		//for word trace: keeps the first and last occurence of the word
		int first; int last;
};

/*
CONSTRUCTORS
*/
template<class T>
Node<T>::Node(T key){
	Node<T>::key = key;
	next = nullptr;
	prev = nullptr;
	count = 1;
	first = NULL;
	last = NULL;
}
template<class T>
Node<T>::Node(){
	next = nullptr;
	prev = nullptr;
	key = T();
	count = 1;
	first = NULL;
	last = NULL;
}

/*
SETTERS AND GETTERS
*/
template<class T>
Node<T>* Node<T>::getNext() const{
	return next;
}
template<class T>
void Node<T>::setNext(Node<T>* next){
	Node<T>::next = next;
}
template<class T>
Node<T>* Node<T>::getPrev() const{
	return prev;
}
template<class T>
void Node<T>::setPrev(Node<T>* prev){
	Node<T>::prev = prev;
}
template<class T>
T Node<T>::getKey() const{
	return key;
}
template<class T>
void Node<T>::setKey(T val){
	key = val;
}
template<class T>
int Node<T>::getCount() const{
	return count;
}
template<class T>
void Node<T>::setCount(int val){
	count = val;
}
template<class T>
int Node<T>::getFirst() const{
	return first;
}
template<class T>
void Node<T>::setFirst(int val){
	first = val;
}
template<class T>
int Node<T>::getLast() const{
	return last;
}
template<class T>
void Node<T>::setLast(int val){
	last = val;
}

/*
FUNCTIONS
*/
/*
moveTo: takes the head of the list and the desired index which we want to move
this Node to. Returns the new head of the list, with the node inserted at the
correct point.
*/
template<class T>
Node<T>* Node<T>::moveTo(int index, Node<T>* head){
	//if it's to be the new head
	if(index == 0){

		//return if it's already the head
		if(this == head) return this;

		//set prev's "next" to next
		if(this->getPrev() != nullptr) this->getPrev()->setNext(this->getNext());
		//set next's "prev" to prev
		if(this->getNext() != nullptr) this->getNext()->setPrev(this->getPrev());
		//set new next to old head
		this->setNext(head);
		//set old head's prev to this
		head->setPrev(this);
		return this;
	}
	//get the node currently at the index
	Node<T>* insertBeforeThis = Node<T>::get(index, head);
	//insert at end if it's null
	if(insertBeforeThis == nullptr){
		//get last node
		Node<T>* i = head;
		while(i->getNext() != nullptr) i = i->getNext();
		//set prev's "next" to next
		if(this->getPrev() != nullptr) this->getPrev()->setNext(this->getNext());
		//set next's "prev" to prev
		if(this->getNext() != nullptr) this->getNext()->setPrev(this->getPrev());		
		//set previous to last node
		this->setPrev(i);
		//set last node to point to this
		i->setNext(this);
		return head;
	}

	//set prev's "next" to next
	if(this->getPrev() != nullptr) this->getPrev()->setNext(this->getNext());
	//set next's "prev" to prev
	if(this->getNext() != nullptr) this->getNext()->setPrev(this->getPrev());
	//set new next
	this->setNext(insertBeforeThis);
	//set new prev
	this->setPrev(insertBeforeThis->getPrev());
	//point to this from behind 
	if(insertBeforeThis->getPrev() != nullptr) insertBeforeThis->getPrev()->setNext(this);
	//point to this from the front
	if(insertBeforeThis->getNext() != nullptr) insertBeforeThis->setPrev(this);

	return head;
}

#endif