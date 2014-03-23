#include <Node.h>
template<class T>
class LinkedList{
public:
	int length;
	//construct with length and value
	LinkedList<T>(int);

	//add at index
	void add(int, T);

	Node<T>* getHead() const;
	void setHead(Node<T>*);
private:
	Node<T>* head;
};