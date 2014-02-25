//1-3 Document class (cpp file)
#include <Document.h>
#include <iostream>
#include <fstream>

using namespace std;


//constructors and deconstructors
//string name, random id
Document::Document(string nameval){
	name = nameval;
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
}
//string name, int id
Document::Document(string nameval, int idval){
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
string Document::getName() const{
	return name;
}
void Document::setName(string nameval){
	name = nameval;
}

//functions
/*1-4 loaddocument function: 4. Add a function call loadDocument that takes the name of the file. 
The function will read in the text file and create a new Line for each sentence read with Line id 
	equal to the location in the text file. After, set the linecount.*/
void Document::loadDocument(string filename){
	ifstream filestream; 
	filestream.open(filename);

	/*now we iterate for every character in the stream.*/
	//the line we'll be appending to
	string line = "";
	//the index, to track where we are
	int index = 0;
	//the linecount, to count how many lines we generated
	int linecount = 0;

	//while there are chars to read
	while(filestream.good()){

		//the next char from the stream.
		char c = filestream.get();

		//no matter what the file is, we append it to the current string.
		line = line + c;

		//now we check if we need to create a new line object.
		if (c == ('.'||'!'||'?')){
			//if true, we create a new line object.
			Line(line, index);
			//we reset the line string to empty
			line = "";
			//we increase the linecount
			linecount++;
		}

		//increase the index
		index++;
	}
	
	//if the text didn't end with punctuation, then we make one more line with the remaining sentence
	if(!line.empty()){
		//if true, we create a new line object.
		Line(line, index);
		//we reset the line string to empty
		line = "";
		//we increase the linecount
		linecount++;
	}


	//set linecount
	Document::linecount = linecount;

	//must close the file
	filestream.close();
}