class Node{
public:
	Node();
	//create node with value
	Node(int);
	
	int getKey() const;
	void setKey(int);
	Node* getNext() const;
	void setNext(Node*);
private:
	int key;
	Node* next;
};