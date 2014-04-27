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
		int getCount() const;
		void setCount(int);
	protected:
		T key;
		Node<T>* next;
		int count;
};
template<class T>
Node<T>::Node(T key){
	Node<T>::key = key;
	next = NULL;
	count = 1;
}
template<class T>
Node<T>::Node(){
	next = NULL;
	key = T();
	count = 1;
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
template<class T>
int Node<T>::getCount() const{
	return count;
}
template<class T>
void Node<T>::setCount(int val){
	count = val;
}
#endif