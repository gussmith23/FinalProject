#ifndef NODE_H
#define NODE_H
template<class T>
class Node{
	public:
		Node();
		Node(T);
		Node<T>* getNext() const;
		void setNext(Node<T>*);
		T getKey() const;
		void setKey(T);
	protected:
		T key;
		Node<T>* next;
};
template<class T>
Node<T>::Node(T key){
	Node<T>::key = key;
	next = 0;
}
template<class T>
Node<T>::Node(){
	next = 0;
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
T Node<T>::getKey() const{
	return key;
}
template<class T>
void Node<T>::setKey(T val){
	key = val;
}
#endif