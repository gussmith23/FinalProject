#include <Node.h>
template<class T>
class LineNode : public Node<T>{
public:
	//takes wordcount (stores in key) and finalchar
	LineNode(T,char);
	char getFinalChar() const;
	void setFinalChar(char);
	LineNode<T>* getNext() const;
	void setNext(LineNode<T>*);
private:
	char finalChar;
};
template<class T>
char LineNode<T>::getFinalChar() const{
	return LineNode::finalChar;
}
template<class T>
void LineNode<T>::setFinalChar(char val){
	finalChar = val;
}
template<class T>
LineNode<T>::LineNode(T wordCount, char finalChar){
	key = wordCount;
	LineNode<T>::finalChar = finalChar;
	next = 0;
}
template<class T>
LineNode<T>* LineNode<T>::getNext() const{
	return next;
}
template<class T>
void LineNode<T>::setNext(LineNode<T>* next){
	LineNode<T>::next = next;
}