#include <LineLengthLinkedList.h>
class LineLengthLinkedList : public LinkedList{
public:
	//construct with length and value
	LineLengthLinkedList(int);
	LineLengthLinkedList();

	//add at index (index, wordcount, finalchar)
	void add(int, int,char);

	LineLengthNode* getHead() const;
	void setHead(LineLengthNode*);
private:
	LineLengthNode* head;
};
void LineLengthLinkedList::add(int index, int wordCount, char finalChar){
	//if it's out of bounds
	if(index > length) return;
	//if it's the first one
	else if(index == 0){
		LineLengthNode* n = new LineLengthNode(wordCount,finalChar);
		n->setNext(head);
		head = n;
	}
	//if it's the last one
	else if(index = length){
		LineLengthNode* n = head;
		//get the last node
		for(int i = 0; i < length-1; i++){
			n = n->getNext();
		}
		LineLengthNode* newN = new LineLengthNode(wordCount,finalChar);
		n->setNext(newN);
	}
	//else it's in the middle
	else{
		//we need the node before and after. 
		LineLengthNode* before = head;
		LineLengthNode* n = new LineLengthNode(wordCount,finalChar);
		LineLengthNode* after;
		for(int i = 0; i < index - 1; i++){
			before = (LineLengthNode) (before->getNext());
		}
		after = before->getNext();
		before->setNext(n);
		n->setNext(after);
	}

	length++;
}