#include <Line.h> 

void Line::setStr(std::string strval){
	str = strval;
}
std::string Line::getStr() const{
	return str;
}
void Line::setWordcount(int wordcountval){
	wordcount = wordcountval;
}
int Line::getWordcount() const{
	return wordcount;
}
void Line::setCharcount(int charcountval){
	charcount = charcountval;
}
int Line::getCharcount() const{
	return charcount;
}

//sets id to random number
Line::Line(){
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
}
//sets id to random number and str to value
Line::Line(std::string strval){
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
	str = strval; 
}
//sets id to value and str to value
Line::Line(std::string strval, int idval){
	id = idval;
	str = strval; 
}
//destructor deletes the string
Line::~Line(){
	str.clear();
}