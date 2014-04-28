#include <Node.h>
class LinkedList{
public:
	int length;
	//construct with length and value
	LinkedList(int);

	//add at index
	void add(int, int);

	Node* getHead() const;
	void setHead(Node*);
private:
	Node* head;
};