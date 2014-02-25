#include <Line.h> 
#include <iostream>

using namespace std;

//sets id to random number
Line::Line(){
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
	
	//set wordcount to null
	wordcount = NULL;
}
//sets id to random number and str to value
Line::Line(std::string strval){
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
	str = strval; 

	//set wordcount to null
	wordcount = NULL;
}
//sets id to value and str to value
Line::Line(std::string strval, int idval){
	id = idval;
	str = strval; 

	//set wordcount to null
	Line::wordcount = NULL;
}
//destructor deletes the string
Line::~Line(){
	str.clear();
}


void Line::setStr(std::string strval){
	str = strval;
}
std::string Line::getStr() const{
	return str;
}
void Line::setWordcount(int wordcountval){
	wordcount = wordcountval;
}
/*1-5 Change the getWordCount getter in Line to do the following: if wordcount is not set, 
count the words in the sentence, set the value, and return the value, else just return the value.*/
int Line::getWordcount(){
	
	//if the wordcount isn't set..
	if(wordcount == NULL){

		//the string to iterate through.
		string text = Line::str;
		//the wordcount
		int wordcounter = 0;

		/*we use these to find words. to find a word, first the firstChar must be found,
		and then the space after the word must be found.*/
		bool foundFirstChar = false;
		bool foundSpace = false;

		/*we can treat a string like an array. we use this to our advantage.
		we iterate through each char in the string.*/
		for(int i=0; i<text.length(); i++){

			//if we haven't yet found the firstChar, check if we find a char.
			if(!foundFirstChar){
				//if the char equals any of these characters, we didn't find the start
				if((text[i] == '.')||(text[i] == '!')||(text[i] == '?')||(text[i] == ' '));
				else foundFirstChar = true;
			}

			//check if we've found a space
			//OR if we've found the end of the string. either case will indicate the end of a word.
			if((text[i] == ' ')||(i == text.length()-1)){
				//if we have, set variable to true
				foundSpace = true;
			}else foundSpace = false;

			//now, if we'be both found the first char and found a space, we've found a word.
			if(foundSpace&&foundFirstChar){
				//when we find a word, we increase our wordcount
				wordcounter++;
				//and reset our variables
				foundFirstChar = false;
				foundSpace = false; 
			}

		}

		wordcount = wordcounter;
		return wordcount;

	}

	//else we just return our wordcount
	else return wordcount;
}
void Line::setCharcount(int charcountval){
	charcount = charcountval;
}
int Line::getCharcount() const{
	return charcount;
}

