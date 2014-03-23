#include <Node.h>
template<class T>
Node<T>::Node(T value){
	Node<T>::key = value;
}	
template<class T>
T Node<T>::getKey() const{
	return key;
}
template<class T>
void Node<T>::setKey(T key){
	Node<T>::key = key;
}
template<class T>
Node<T>* Node<T>::getNext() const{
	return next;
}
template<class T>
void Node<T>::setNext(Node<T>* value){
	next = value;
}