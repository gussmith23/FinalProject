/*
Gus Henry Smith

LineNode.h

The LineNode class describes a special type of node, thus it inherits Node.
As it is a templated class, all functions are defined in the header.
A single LineNode represents one line of the document. All LineNodes
will be of type int, so that we can store their wordCount int object in
the "key" variable. Additionally, we add a finalChar field.
*/

#include <Node.h>
template<class T>
class LineNode : public Node<T>{
public:
	LineNode(T,char);
	char getFinalChar() const;
	void setFinalChar(char);
	LineNode<T>* getNext() const;
	void setNext(LineNode<T>*);
private:
	//the terminating character of the line
	char finalChar;
};

/*
SETTERS AND GETTERS
*/
/*
Constructor takes wordcount (stores in key) and finalchar.
*/
template<class T>
char LineNode<T>::getFinalChar() const{
	return LineNode::finalChar;
}
template<class T>
void LineNode<T>::setFinalChar(char val){
	finalChar = val;
}
template<class T>
LineNode<T>* LineNode<T>::getNext() const{
	return next;
}
template<class T>
void LineNode<T>::setNext(LineNode<T>* next){
	LineNode<T>::next = next;
}

/*
CONSTRUCTORS AND DECONSTRUCTORS
*/
template<class T>
LineNode<T>::LineNode(T wordCount, char finalChar){
	key = wordCount;
	LineNode<T>::finalChar = finalChar;
	next = 0;
}
