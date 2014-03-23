#include <LinkedList.h>
#include <LineLengthNode.h>
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