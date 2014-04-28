#include <LineLengthNode.h>
LineLengthNode::LineLengthNode(int wordCount, char finalChar){
	LineLengthNode::wordCount = wordCount;
	LineLengthNode::finalChar = finalChar;
}
int LineLengthNode::getWordCount() const {
	return wordCount;
}
void LineLengthNode::setWordCount(int val){
	wordCount = val;
}
char LineLengthNode::getFinalChar() const {
	return finalChar;
}
void LineLengthNode::setFinalChar(char val){
	finalChar = val;
}