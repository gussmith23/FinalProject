//1-3 Document class (cpp file)
#include <Document.h>


//constructors and deconstructors
//string name, random id
Document::Document(std::string nameval){
	name = nameval;
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
}
//string name, int id
Document::Document(std::string nameval, int idval){
	name = nameval;
	id = idval;
}

//setters and geters
int Document::getLinecount() const{
	return linecount;
}
void Document::setLinecount(int linecountval){
	linecount = linecountval;
}
int Document::getWordcount() const{
	return wordcount;
}
void Document::setWordcount(int wordcountval){
	wordcount = wordcountval;
}
Line* Document::getLineArray() const{
	return lineArray;
}
void Document::setLineArray(Line* lineArrayval){
	lineArray = lineArrayval;
}
std::string Document::getName() const{
	return name;
}
void Document::setName(std::string nameval){
	name = nameval;
}