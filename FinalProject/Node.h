template<class T>
class Node{
public:
	Node();
	//create node with value
	Node(T);
	
	T getKey() const;
	void setKey(T);
	Node* getNext() const;
	void setNext(Node*);
private:
	T key;
	Node* next;
};