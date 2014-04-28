#include <Node.h>
Node::Node(int value){
	Node::key = value;
}	
int Node::getKey() const{
	return key;
}
void Node::setKey(int key){
	Node::key = key;
}
Node* Node::getNext() const{
	return next;
}
void Node::setNext(Node* value){
	next = value;
}