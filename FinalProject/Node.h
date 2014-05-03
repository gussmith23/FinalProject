#ifndef NODE_H
#define NODE_H
template<class T>
class Node{
	public:
		Node();
		Node(T);

		Node<T>* getNext() const;
		void setNext(Node<T>*);
		Node<T>* getPrev() const; //new
		void setPrev(Node<T>*); //new
		T getKey() const;
		void setKey(T);
		int getCount() const;
		void setCount(int);
		int getFirst() const;
		void setFirst(int);
		int getLast() const;
		void setLast(int);

		//moves to index
		Node<T>* moveTo(int,Node<T>*); //new

		//takes the head of the list and the desired index.
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
		//for word trace
		int first;
		int last;
};
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

//takes the head of the list and the desired index.
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