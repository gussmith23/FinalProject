class LineLinkedList{
	class Node{
	public:
		Node(int,char);
		Node* getNext() const;
		void setNext(Node*);
		int getWordCount() const;
		void setWordCount(int);
		char getFinalChar() const;
		void setFinalChar(char);
	private:
		int wordCount;
		char finalChar;
		Node* next;
	};
public:
	LineLinkedList();
	void add(int,char);
	//get at index
	Node* get(int);
private:
	Node* head;
	Node* tail;
	int length;
};