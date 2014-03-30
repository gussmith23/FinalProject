//1-3 Document class (cpp file)
#include <Document.h>
using namespace std;
//constructors and deconstructors
//string name, random id
Document::Document(string nameval){
	name = nameval;
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
	wordcount = NULL;
	/*initialize the stack of words, and fill it right off the bat so that we don't have
	to worry about it being un-initialized*/
	words = new Stack<string>();
	parseWords();
}
//string name, int id
Document::Document(string nameval, int idval){
	name = nameval;
	id = idval;
	wordcount = NULL;
	/*initialize the stack of words, and fill it right off the bat so that we don't have
	to worry about it being un-initialized*/
	words = new Stack<string>();
	parseWords();
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
Stack<string>* Document::getWords() const { 
	return words; 
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
			//we also add the words to our main stack of all words
			Document::words->push(wordsToAdd.at(j));
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
		vector<char> charsToAdd = lineArray.at(i).parseChar();
		//now we iterate for each of the chars to add, and add them
		for(size_t j = 0; j < charsToAdd.size(); j++){
			chars.push_back(charsToAdd.at(j));
		}

	}

	return chars;
}
/*
2-3 The function should search through all the Lines. Each line will be a new node that 
stores the word count of that line and the symbol that ended the sentence (., ?, !, etc).

this function has no return - it simply creates the linked list, setting 
Document::lineLengthsLinkedList equal to the head.
*/
void Document::lineLengths(){
	//for the first line, we create the inital node (which is the head of the linked list
	LineNode<int>* head = new LineNode<int>(lineArray.at(0).getWordcount(),lineArray.at(0).getPunctuation());	
	//we use this in the scope of the function to keep track of the tail for easy adding
	LineNode<int>* tail = head;
	//as we've done the first one already, start with the second line
	for(int i = 1; i < lineArray.size(); i++){
		//the new node to be added
		LineNode<int>* newNode = new LineNode<int>(lineArray.at(i).getWordcount(),lineArray.at(i).getPunctuation());
		//set the old tail to point to this one
		tail->LineNode::setNext(newNode);
		//set the newNode as the new tail
		tail = newNode;
	}
	lineLengthsLinkedList = head;
}
LineNode<int>* Document::getLineLengthsLinkedList() const{
	return lineLengthsLinkedList;
}
/*
2-5 reverseCompare
Create a function called reverseCompare in Document that takes in a Document as 
input. The function needs to create a stack of words in the calling document. Next 
examine the words of the passed Document form the end to the beginning with those 
words on the stack. If the words are different, cout different, else cout same.
*/
void Document::reverseCompare(Document d){

	parseWords();
	d.parseWords();

	//the stacks for the master and external
	Stack<string>* master = Stack<string>::copyStack(Document::words);
	Stack<string>* external = Stack<string>::copyStack(d.getWords());

	//indicating how the comparisons will be notated.
	cout << "MASTER vs. EXTERNAL" << endl;

	//our escape boolean
	bool running = false;
	/*
	the master and external strings to compare.
	because of how the Node and Stack classes are defined, if the end of the list
	has been reached, one of these will be empty.
	*/
	string masterStr = master->pop();
	string externalStr = external->pop();
	//if neither is empty, then we'll actually execute our loop.
	if(!((masterStr.empty())&&(externalStr.empty()))) running = true;
	else{
		cout << "Error: One of the selected documents is empty!" << endl;
		return;
	}
	while(running){
		//comparison goes at the top
		string word;
		if(!masterStr.compare(externalStr)) word = "SAME";
		else word = "DIFFERENT";
		cout<< masterStr << " vs. " <<externalStr << ": " << word << endl;

		//getting new strings goes at the bottom - we decide if we run through one more time		
		masterStr = master->pop();
		externalStr = external->pop();

		if((external->getHead() == 0)||(master->getHead() == 0)) running = false;
		/*
		//if both are empty...
		if((masterStr.empty())&&(externalStr.empty())){
			cout << "Reached the end of both strings!" << endl; 
			running = false;
		}
		//else if either of them is empty...
		else if(masterStr.empty()){
			cout << "Reached the end of MASTER document!" << endl;
			running = false;
		}
		else if(externalStr.empty()){
			cout << "Reached the end of EXTERNAL document!" << endl;
			running = false;
		}
		*/
	}


	cout << "End of comparison." << endl;
}
/*
2-7 hashWords - hashes words into a hashtable.
*/
void Document::hashWords(){
	
	hashLength = 2;
	hashTable = new Node<string>*[hashLength]();
	//we initialize the hash table to the appropriate length
	for(int i = 0; i < hashLength; i++){
		hashTable[i] = new Node<string>();
	}
	//the stack of words
	Stack<string>* s = Stack<string>::copyStack(words);
	//cycle for every word
	while((s->getHead())!=0){
		string word = s->pop();
		int h = 0, a = 127;
		//h will be between 0 and hashLength-1
		for(int i = 0; i<word.length(); i++) h = (a*h + word[i]) % hashLength;
		//put the word in the table
		Node<string>* head = hashTable[h];
		//we keep iterating until we find the last node
		while(head->getNext() != 0){
			head = head->getNext();
		}
		//we create the new node on the end with a value of the initial string
		head->setNext(new Node<string>(word));	
	}
}
Node<string>** Document::getHashTable() const {
	return hashTable;
}
