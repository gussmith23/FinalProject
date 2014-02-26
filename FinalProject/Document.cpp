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
	wordcount = NULL;
}
//string name, int id
Document::Document(string nameval, int idval){
	name = nameval;
	id = idval;
	wordcount = NULL;
}

//setters and geters
int Document::getLinecount() const{
	return linecount;
}
void Document::setLinecount(int linecountval){
	linecount = linecountval;
}
/*1-6 Change the getWordCount getter in Document to do the following: if wordcount is not set,
sum up the word counts for each line, set the value and return the value, else just return
the value.*/
int Document::getWordcount() {

	//if wordcount not set...
	if(wordcount == NULL){

		int wordcount = 0;
		
		//we iterate for every line in the doc's lineArray
		for(size_t i = 0; i<lineArray.size(); i++){
			
			//we add the number of words in each line to the wordcount
			wordcount = wordcount + lineArray.at(i).getWordcount();
		}

		Document::wordcount = wordcount;
		return Document::wordcount;

	}
	else return wordcount;
}
void Document::setWordcount(int wordcountval){
	wordcount = wordcountval;
}
//returns a copy of the line array
vector<Line> Document::getLineArray() const{
	return vector<Line>(lineArray);
}
void Document::setLineArray(vector<Line> lineArrayval){
	lineArray = lineArrayval;
}
//adds a line to the array
void Document::addToLineArray(Line lineval){
	lineArray.push_back(lineval);
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
	equal to the location in the text file. After, set the linecount.
	My version of loadDocument returns 0 if it fails.*/
int Document::loadDocument(string filename){
	ifstream filestream; 
	filestream.open(filename, std::ifstream::in);

	//if we failed to open our document
	if(filestream.fail()){
		cout<<"Document failed to open.\n";
		//returns 0 if failed.
		return 0;
	}

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
		if ((c=='.')||(c=='!')||(c=='?')){
			//if true, we create a new line object.
			Line l = Line(line, index);
			//we push the Line onto the Document's lineArray
			lineArray.push_back(l);
			//we reset the line string to empty
			line = "";
			//we increase the linecount
			linecount++;


		}

		//increase the index
		index++;
	}
	
	//if the text didn't end with punctuation, then we make one more line with the remaining sentence
	if((!line.compare(" "))&&(!line.compare(""))){
		//if true, we create a new line object.
		Line l = Line(line, index);
		//we push the Line onto the Document's lineArray
		lineArray.push_back(l);
		//we reset the line string to empty
		line = "";
		//we increase the linecount
		linecount++;
	}


	//set linecount
	Document::linecount = linecount;

	//must close the file
	filestream.close();

	//return 1 if successful.
	return 1;
}
/*Add a function outputDocument in Document that takes in a string and outputs the document to a 
file at a location given by the string.*/
void Document::outputDocument(string filename){
	ofstream file; 
	file.open(filename);
	
	//we iterate for every line
	for(size_t i = 0; i < lineArray.size(); i++){
		file << lineArray.at(i).getStr();
	}
}
/*1-11 Create a function in Document called parseWords that returns an array of
words (Similar to Line).*/
vector<string> Document::parseWords(){
	//all we need to do in this function is get all of the words from each line and return them.

	//the vector we return
	vector<string> words;

	//iterate for each line
	for(size_t i = 0; i < lineArray.size(); i++){
		//the line we're working with
		Line l = lineArray.at(i);
		//the words in the line
		vector<string> wordsToAdd = l.parseWords();
		//iterate for each word to add
		for(size_t j = 0; j < wordsToAdd.size(); j++){
			//add the word
			words.push_back(wordsToAdd.at(j));
		}
	}

	return words;

}
/*1-12 Create a function in Document called parseChar that returns an
array of char (similar to Line).*/
vector<char> Document::parseChar(){
	//so, we gotta get the chars for each line.

	//the vector we'll return
	vector<char> chars; 

	//we iterate for each line.
	for(size_t i = 0; i < lineArray.size(); i++){
		//the chars to add
		//we have to call parsechar with an arg until i figure out what booth wants
		vector<char> charsToAdd = lineArray.at(i).parseChar(1);
		//now we iterate for each of the chars to add, and add them
		for(size_t j = 0; j < charsToAdd.size(); j++){
			chars.push_back(charsToAdd.at(j));
		}

	}

	return chars;
}