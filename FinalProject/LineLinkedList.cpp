#include <LineLinkedList.h>
LineLinkedList::Node::Node(int wordCount, char finalChar){
	Node::wordCount = wordCount;
	Node::finalChar = finalChar;
}
LineLinkedList::Node* LineLinkedList::Node::getNext() const{
	return next;
}
void LineLinkedList::Node::setNext(LineLinkedList::Node* next){
	Node::next = next;
}
int LineLinkedList::Node::getWordCount() const{
	return wordCount;
}
void LineLinkedList::Node::setWordCount(int val){
	wordCount = val;
}
char LineLinkedList::Node::getFinalChar() const{
	return finalChar;
}
void LineLinkedList::Node::setFinalChar(char val){
	finalChar = val;
}
LineLinkedList::LineLinkedList(){
	head = 0;
	tail = 0;
	length = 0;
}
void LineLinkedList::add(int wordCount, char finalChar){
	//if the lsit is empty
	if(head == 0){
		Node* n = new Node(wordCount,finalChar);
		head = n;
		tail = n;
	}
	else{
		Node* n = new Node(wordCount, finalChar);
		tail->setNext(n);
		tail = n;
	}
	length++;
}
LineLinkedList::Node* LineLinkedList::get(int index){
	//return 0 if the index is out of bounds
	if(index > length - 1) return 0;
	Node* n = head;
	for(int i = 0; i < index; i++){
		n = n->getNext();
	}
	return n;
}
