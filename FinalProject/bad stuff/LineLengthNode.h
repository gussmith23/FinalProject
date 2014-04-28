#include <Node.h>
class LineLengthNode : public Node {
public:
	LineLengthNode(int,char);
	int getWordCount() const;
	void setWordCount(int);
	char getFinalChar() const;
	void setFinalChar(char);
	LineLengthNode* getNext();
private:
	int wordCount;
	char finalChar;
};