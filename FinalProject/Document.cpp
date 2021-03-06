/*
Gus Henry Smith

Document.cpp

The Document class definition file. Contains many of the most important
functions in this program. Here is a list (excluding setters, getters,
constructors, and helper functions):

*loadDocument: loads and parses through a document.
*outputDocument: outputs a document to a specified location.
*parseWords and parseChar: parses words/chars in the document, storing them in lists
*lineLengths: sets up a special linked list described below
*reverseCompare: compares two documents using stacks of words
*hashWords and hashChar: hashes words/chars in the document to hashtables contained in Document object
*printAllChars, printAllCharsOffset, printTopKWord, printBottomKWord, wordTraceK: prints plots as described below
*caesar, vigenere: caesar/vigenere encrypting
*caesar_d, vigenere_d: caesar/vigenere decrypting
*/

//1-3 Document class (cpp file)
#include <Document.h>
#include <Metrics.h>
#include<Plot.h>
#include <ctime>

using namespace std;
using std::cout;

/*
CONSTRUCTORS AND DECONSTRUCTORS
*/
/*
string name, random id
*/
Document::Document(string nameval){
	name = nameval;
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
	defineVariables();
}
/*
string name, int id
*/
Document::Document(string nameval, int idval){
	name = nameval;
	id = idval;
	defineVariables();
}

/*
HELPER FUNCTIONS
*/
/*
helper function to define all variables at once
*/
void Document::defineVariables(){
	pWords = new Stack<string>();
	wordcount = NULL;
	linecount = NULL;
	hashLengthWords = 97;
	hashLengthChars = 8;
}
/*
runInitialFunctions calls all of the data-collection functions simultaneously,
usually directly after a document is created.
*/
void Document::runInitialFunctions(){
	cout<<"Building document:"<<endl;
	cout<<"Parsing words...";
	wordArray = parseWords();
	cout<<"done."<<endl;
	cout<<"Parsing all characters...";
	charArray = parseChar(false);
	cout<<"done."<<endl;
	cout<<"Parsing letters...";
	alphaCharArray = parseChar(true);
	cout<<"done."<<endl;
	cout<<"Reading lines...";
	lineLengths();
	cout<<"done."<<endl;
	cout<<"Hashing words...";
	hashWords();
	cout<<"done."<<endl;
	cout<<"Hashing chars...";
	hashChar();
	getWordcount();
	cout<<"done."<<endl;
	linecount = lineArray.size();
}

/*
SETTERS AND GETTERS
*/
int Document::getId() const{
	return id;
}
void Document::setId(int val){
	id = val;
}
int Document::getLinecount() const{
	return linecount;
}
void Document::setLinecount(int linecountval){
	linecount = linecountval;
}
/*
getWordcount is not simply a passive getter - if the value is not set, then it 
actively gets the value itself.
*/
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
vector<Line> Document::getLineArray() const{
	return vector<Line>(lineArray);
}
void Document::setLineArray(vector<Line> lineArrayval){
	lineArray = lineArrayval;
}
/*
addToLineArray adds a line to the array.
*/
void Document::addToLineArray(Line lineval){
	lineArray.push_back(lineval);
}
string Document::getName() const{
	return name;
}
void Document::setName(string nameval){
	name = nameval;
}
Stack<string>* Document::getpWords() const { 
	return pWords; 
}
vector<char> Document::getCharArray() const{
	return charArray; 
}
vector<char> Document::getAlphaCharArray() const{
	return alphaCharArray;
}
vector<string> Document::setWordArray() const{
	return wordArray;
}
LineNode<int>* Document::getpLineLengthsLinkedList() const{
	return pLineLengthsLinkedList;
}
Node<string>** Document::getHashTableWords() const {
	return hashTableWords;
}
void Document::setHashTableWords(Node<string>** val){
	Document::hashTableWords = val;
}
Node<char>** Document::getHashTableChar() const {
	return hashTableChar;
}
void Document::setHashTableChar(Node<char>** val){
	Document::hashTableChar = val;
}


/*
FUNCTIONS
*/
/*
loadDocument: Takes the filename as an argument. Reads in the text file and 
creates a new Line for each sentence read with Line id equal to the location 
in the text file. After, the function sets the linecount.
My version of loadDocument returns 0 if it fails.
*/
int Document::loadDocument(string filename){
	//using an ifstream to read in our file
	ifstream filestream; 
	filestream.open(filename, std::ifstream::in);
	//if we failed to open our document
	if(filestream.fail()){
		cout<<"Document failed to open.\n";
		//returns 0 if failed.
		return 0;
	}

	/*
	now we iterate for every character in the stream.
	*/
	//the line we'll be appending to
	string line = "";
	//the index, to track where we are
	int index = 0;
	//the linecount, to count how many lines we generated
	int linecount = 0;

	cout<<"Reading filestream...";

	//while there are chars to read
	while(filestream.good()){

		//the next char from the stream.
		char c = filestream.get();

		//no matter what the file is, we append it to the current string.
		line = line + c;

		//now we check if we need to create a new line object by checking for punctuation.
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
	cout<<"done."<<endl;
	
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
	
	//now that the document is loaded, we can run our analysis functions
	runInitialFunctions();

	//return 1 if successful.
	return 1;
}
/*
outputDocument: takes in a string (filename) and outputs the document to a 
file at a location given by the string.
*/
void Document::outputDocument(string filename){
	ofstream file; 
	file.open(filename);
	
	//we iterate for every line
	for(size_t i = 0; i < lineArray.size(); i++){
		file << lineArray.at(i).getStr();
	}
}
/*
parseWords: for each line, we pull all the words from the line. we add all those words into our
central vector of ALL words in the document. This vector is then returned.
*/
vector<string> Document::parseWords(){
	
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
			Document::pWords->push(wordsToAdd.at(j));
		}
	}
	return words;
}
/*
parseChar: returns an array of chars.
This function takes a boolean representing whether or not we want ALL
characters parsed, or only the letters.
We want all characters parsed when we handle the ciphers; otherwise,
when doing data analysis, we only want letters.
*/
vector<char> Document::parseChar(bool onlyAlpha){
	//the vector we'll return
	vector<char> chars; 

	//we iterate for each line.
	for(size_t i = 0; i < lineArray.size(); i++){
		//the chars to add
		vector<char> charsToAdd = lineArray.at(i).parseChar();
		//now we iterate for each of the chars to add, and add them
		for(size_t j = 0; j < charsToAdd.size(); j++){
			char c = charsToAdd.at(j);
			//continue if the char will break isalpha (non-unicode)
			if(!(c >= -1 && c <= 255)) continue;
			//if we only want alpha...
			if(onlyAlpha&&!isalpha(tolower(c))) continue;
			chars.push_back(c);
		}

	}

	return chars;
}
/*
lineLengths: searches through all the Lines. Each line is a new node with word count
and terminating symbol stored.
this function has no return - it simply creates the linked list, setting 
Document::pLineLengthsLinkedList equal to the head.
*/
void Document::lineLengths(){
	//return if the lineArray hasn't been initialized
	if(lineArray.size()<1) return;
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
	pLineLengthsLinkedList = head;
}
/*
reverseCompare: takes in a Document. The function gets the stack of words from the
Document in the argument and the calling document. It then pops off one word at
a time and compares them. In the end, it outputs a count of the number of words that 
are different.
*/
void Document::reverseCompare(Document d){

	//the stacks for the master and external
	Stack<string>* master = Stack<string>::copyStack(Document::pWords);
	Stack<string>* external = Stack<string>::copyStack(d.getpWords());

	//the number of different words
	int numDifferent = 0;

	//indicating how the comparisons will be notated.
	std::cout << name << " vs. " << d.getName() << endl;

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
		std::cout << "Error: One of the selected documents is empty!" << endl;
		return;
	}
	while(running){
		//if our words aren't the same
		if(masterStr.compare(externalStr)!=0){
			numDifferent++;
		}

		//getting new strings goes at the bottom - we decide if we run through one more time		
		masterStr = master->pop();
		externalStr = external->pop();

		//if one of the strings is empty
		if((external->getHead() == 0)||(master->getHead() == 0)){
			if((external->getHead() == 0)) std::cout << d.getName() << " ran out of words!" << endl;
			if((master->getHead() == 0)) std::cout << name << " ran out of words!" << endl;
			running = false;
		}
	}
	std::cout << "Number of words different: " << numDifferent << endl;
	std::cout << "End of comparison." << endl;
}
/*
hashWords: hashes words into a hashtable using chaining.
*/
void Document::hashWords(){
	
	//the amount of spaces in the outer array
	int hashLength = Document::hashLengthWords;

	hashTableWords = new Node<string>*[hashLength]();
	//we initialize the hash table to the appropriate length
	for(int i = 0; i < hashLength; i++){
		hashTableWords[i] = new Node<string>();
	}
	//the stack of words
	vector<string> s = wordArray;
	//cycle for every word
	for(int i = 0; i < s.size(); i++){
		string word = s.at(i);
		//convert to lowercase...
		for(int i = 0; i < word.length(); i++) word[i] = tolower(word[i]);

		int h = 0, a = 127;
		//h will be between 0 and hashLength-1
		for(int i = 0; i<word.length(); i++) h = (a*h + word[i]) % hashLength;
		
		/*
		put the word in the table.
		we either create a new node if one doesn't exist, or we increment count
		on the already existing node.
		*/
		//first find the head of the chain
		Node<string>* head = hashTableWords[h];
		//we keep iterating until we find the last node OR until we find a node whose key is the same
		while((head!=nullptr)&&(head->getNext() != nullptr)&&(head->getKey().compare(word)!=0)){
			//debug
			//cout<<h<<" "<<head->getKey()<<endl;
			
			head = head->getNext();
		}


		if(!(head==nullptr)){

			//if we found a node whose key is the same...
			if(Metrics::equals(head->getKey(),word)){
				//increment the count
				head->setCount(head->getCount() + 1);
				//log that this was (up to now) the LAST time we saw the node
				head->setLast(i+1);
			}
			//otherwise, create a new node on the end
			else{
				//the new node
				Node<string>* n = new Node<string>(word);
				//we log that this was the FIRST appearance of this node (i plus 1 because i=0 represents the 1st word)
				n->setFirst(i+1);
				//set new node's prev to the previous node (current end of list)
				n->setPrev(head);
				//set the current end of the list's next to the new node (adding it to list)
				head->setNext(n);	
			}
		}
	}
}
/*
hashChar: hashes chars into a hashtable using chaining.
*/
void Document::hashChar(){
	
	//the amount of spaces in the outer array
	int hashLength = Document::hashLengthChars;

	hashTableChar = new Node<char>*[hashLength]();
	//we initialize the hash table to the appropriate length
	for(int i = 0; i < hashLength; i++){
		hashTableChar[i] = new Node<char>();
	}
	//the stack of words
	vector<char> s = charArray;
	//cycle for every word
	for(int i = 0; i < s.size(); i++){
		char c = s.at(i);
		//convert to lowercase...
		c = tolower(c);

		//the hash itself
		int h = 0, a = 127;
		h = (a*h + c) % hashLength;
		
		/*
		put the word in the table.
		we either create a new node if one doesn't exist, or we increment count
		on the already existing node.
		*/
		//first find the head of the chain
		Node<char>* head = hashTableChar[h];
		//we keep iterating until we find the last node OR until we find a node whose key is the same
		while((head->getNext() != nullptr)&&(head->getKey() != c)) head = head->getNext();

		//if we found a node whose key is the same, we increment the counter
		if(Metrics::equals(head->getKey(),c)) head->setCount(head->getCount() + 1);
		//otherwise, create a new node on the end
		else{
			//the new node
			Node<char>* n = new Node<char>(c);
			//set new node's prev to the previous node (current end of list)
			n->setPrev(head);
			//set the current end of the list's next to the new node (adding it to list)
			head->setNext(n);	
		}
		
	}
	
	setHashTableChar(hashTableChar);
}
/*
printAllChars: prints a histogram of the frequency of letters a-z.
*/
void Document::printAllChars(){
	
	//to hold the frequencies
	double* freq = new double[26];

	//the actual symbols
	char* symbols = new char[26];

	//iterate for every char a-z and find their frequencies.
	for(char c = 97; c < 123; c++){

		//add the symbol into the array
		symbols[((int)c)-97] = c;

		//set the freq of the char to 0 by default
		freq[((int)c)-97] = 0;

		//first we have to find the char in the hash.
		int h = 0, a = 127;
		h = (a*h + c) % Document::hashLengthChars;

		//the head of the list
		Node<char>* head = hashTableChar[h];

		//iterate until we find the node, or until we reach the end
		while(head != nullptr){
			//if we find our key
			if(head->getKey() == c){
				freq[((int)c)-97] = head->getCount();
				break;
			}
			head = head->getNext();
		}
	}

	//plot.
	Plot p = Plot();
	p.histogram(freq,symbols,26);
}
/*
printAllCharsOffset: prints letters with frequencies.
Takes an int, representing the offset. The offset determines which
char of the alphabet we begin with - i.e. an offset of 1 begins at 'b'.
*/
void Document::printAllCharsOffset(int offset){
	
	//return if offset is too large
	if(offset<0||offset>25) return;

	//to hold the frequencies
	double* freq = new double[26-offset];

	//the actual symbols
	char* symbols = new char[26-offset];

	//iterate for every char a+offset-z and find their frequencies.
	for(int c = 97+offset,i=0; c < 123; c++, i++){

		//add the symbol into the array
		symbols[i] = (char)c;

		//set the freq of the char to 0 by default
		freq[i] = 0;

		//first we have to find the char in the hash.
		int h = 0, a = 127;
		h = (a*h + (char)c) % Document::hashLengthChars;

		//the head of the list
		Node<char>* head = hashTableChar[h];

		//iterate until we find the node, or until we reach the end
		while(head != nullptr){
			//if we find our key
			if(head->getKey() == (char)c){
				freq[i] = head->getCount();
				break;
			}
			head = head->getNext();
		}
	}

	//plot.
	Plot p = Plot();
	p.histogram(freq,symbols,26-offset);
}
/*
printTopKWord: prints the top k words, where k is some integer.
The function goes through each chain of the hash, compiling every node
into one master list. It then merge sorts them by their count and pulls
the first k elements from that list.
*/
void Document::printTopKWord(int k){
	//for plotting
	Plot* pPlot = new Plot();
	//used for sorts
	Metrics* pMetrics = new Metrics();
	//the master list
	Node<string>* pHead = new Node<string>();
	//the first node
	Node<string>* pOrigin = pHead;
	//the array of frequencies
	double* freq = new double[k];
	//the words for the plot
	string* words = new string[k];
	//keep track of the length of the list
	int length = 0;

	//for every chain...
	for(int i = 0; i < hashLengthWords; i++){
		//first of the list (remember - first is a dummy node)
		Node<string>* pIndex = getHashTableWords()[i]->getNext();

		//while wehave nodes left
		while(pIndex != nullptr){

			//duplicate the node
			Node<string>* pNode = new Node<string>(pIndex->getKey());
			pNode->setCount(pIndex->getCount());

			//increment length
			length++;

			//add the node to the master list
			pHead->setNext(pNode);
			pHead->getNext()->setPrev(pHead);

			//advance our two lists
			pHead = pHead->getNext();
			pIndex = pIndex->getNext();
		}

	}

	//advance by one (first node is a dummy node)
	pOrigin = pOrigin->getNext();
	//sort the list
	pOrigin=pMetrics->mergeSortLinkedListByCount(pOrigin);

	/*
	now we pull the top k elements and compile them into arrays to pass to the plot...
	*/
	//for k iterations. j counts from the last index backwards.
	for(int i = 0; i < k; i++){
		//the Node 
		Node<string>* pLast = Node<string>::get(length-1-i,pOrigin);		
		//if it's equal to nullptr, break
		if(pLast == nullptr) break;
		//otherwise, add its info to the arrays
		freq[i] = pLast->getCount();
		words[i] = pLast->getKey();
	}

	//now we plot.
	pPlot->histogram(freq,words,k);

}
/*
Bottom k word: prints the bottom k words.
Note: in addition to the k words, we also print the MOST frequent word, for
reference.
*/
void Document::printBottomKWord(int k){
	//for plotting
	Plot* pPlot = new Plot();
	//used for sorts
	Metrics* pMetrics = new Metrics();
	//the master list
	Node<string>* pHead = new Node<string>();
	//the first node
	Node<string>* pOrigin = pHead;
	//the array of frequencies
	double* freq = new double[k+1];
	//the words for the plot
	string* words = new string[k+1];
	//keep track of the length of the list
	int length = 0;

	//for every chain...
	for(int i = 0; i < hashLengthWords; i++){
		//first of the list (remember - first is a dummy node)
		Node<string>* pIndex = getHashTableWords()[i]->getNext();

		//while wehave nodes left
		while(pIndex != nullptr){

			//duplicate the node
			Node<string>* pNode = new Node<string>(pIndex->getKey());
			pNode->setCount(pIndex->getCount());

			//increment length
			length++;

			//add the node to the master list
			pHead->setNext(pNode);
			pHead->getNext()->setPrev(pHead);

			//advance our two lists
			pHead = pHead->getNext();
			pIndex = pIndex->getNext();
		}

	}

	//advance by one (first node is a dummy node)
	pOrigin = pOrigin->getNext();
	//sort the list
	pOrigin=pMetrics->mergeSortLinkedListByCount(pOrigin);


	/*
	now we pull the bottom k elements and compile them into arrays to pass to the plot...
	*/
	//we first add the MOST frequent word to the list.
	Node<string>* pMostFreq = Node<string>::get(length-1,pOrigin);
	freq[0] = pMostFreq->getCount();
	words[0] = pMostFreq->getKey();
	//the last Node in the list
	Node<string>* pFirst = pOrigin;
	//for k iterations. 
	for(int i = 1; i < k+1; i++){
		//if it's equal to nullptr, break
		if(pFirst == nullptr) break;
		//otherwise, add its info to the arrays
		freq[i] = pFirst->getCount();
		words[i] = pFirst->getKey();
		//move backwards
		pFirst = pFirst->getNext();
	}

	//now we plot.
	pPlot->histogram(freq,words,k+1);

}
/*
wordTraceK: creates a plot, where for each point x represents first appearance
of the word and y represents last appearance.
x and y themselves will actually represent word number in the document divided by
the average number of words per sentence.
*/
void Document::wordTraceK(string* words, int k){
	Plot* pPlot = new Plot();	
	//average words per sentence
	double averageWordsPerSentence = wordcount/linecount;
	//the list of x and y points
	double* x = new double[k]; double* y = new double[k];
	//the symbols representing the words (letters a through however many we need)
	char* symbols = new char[k];

	//for each word...
	for(int i = 0; i<k; i++){
		/*
		Now we use our hash to search for the word...
		*/
		string word = words[i];
		//convert to lowercase...
		for(int i = 0; i < word.length(); i++) word[i] = tolower(word[i]);

		int h = 0, a = 127;
		//h will be between 0 and hashLength-1
		for(int i = 0; i<word.length(); i++) h = (a*h + word[i]) % hashLengthWords;
		
		//find the head of the chain
		Node<string>* pHead = hashTableWords[h];
		//we keep progressing until we find the last node OR until we find a node whose key is the same
		while((pHead!=nullptr)&&(pHead->getNext() != nullptr)&&(pHead->getKey().compare(word)!=0)) pHead = pHead->getNext();

		//if it's nullptr...
		if(pHead == nullptr){
			//set both points to zero (the word did not appear!)
			x[i] = 0; y[i] = 0;
		}else{ //else, the word DID appear...
			//we represent the word as 
			x[i] = pHead->getFirst()/averageWordsPerSentence;
			y[i] = pHead->getLast()/averageWordsPerSentence;
		}

		//set the symbol of the word
		symbols[i] = 'a' + i;
	}
	//plot the points
	pPlot->plot2DScale(x,y,symbols,k);

	cout<<"(letter used:word indicated)"<<endl;
	//print the key - matching the letter used as a point to the word it indicates
	for (int i = 0; i < k; i++)
	{
		cout<<symbols[i]<<": "<<words[i]<< " First: " << floor(x[i]) << " Last: " << floor(y[i]) <<endl;
	}

}
/*
caesar: encrypts the document using a caesar cipher, which increments
each char by a certain amount.
NOTE: this function does NOT alter the document object. Instead, it returns
a set of lines which can be used to construct an encrypted document object.
*/
vector<Line> Document::caesar(int offset){

	//the linearray to return
	vector<Line> newLineArray = lineArray;

	//we iterate for each line.
	for(size_t i = 0; i < lineArray.size(); i++){
		//the string representing the line of the doc we're ciphering
		string line = lineArray.at(i).getStr();
		
		//for every char in the string...
		for (int j = 0; j < line.size(); j++)
		{
			//continue if the char will break isalpha
			if(!(line[j] >= -1 && line[j] <= 255)) continue;
			//only cipher if isalpha
			if(isalpha(line[j])){

				bool mustResetToCapital = false;
				//if the letter is capital, we must remember that
				if(tolower(line[j])!=line[j]) mustResetToCapital = true;

				//set it to lowercase (makes offsetting way easier
				line[j] = tolower(line[j]);

				//offset it, making sure that z+1 goes to a (and not the character after z, '(')
				line[j] = (((line[j] - 'a') + offset)%26) + 'a';

				//reset to capital
				if(mustResetToCapital) line[j] = toupper(line[j]);
			}

		}

		//replace the old line with the new one
		newLineArray.at(i).setStr(line);


	}

	return newLineArray;

}
/*
vigenere: encrypts the document using a vigenere cipher, which increments
each char based on a keyword.
NOTE: this function does NOT alter the document object. Instead, it returns
a set of lines which can be used to construct an encrypted document object.
*/
vector<Line> Document::vigenere(string key){

	//the linearray to return
	vector<Line> newLineArray = lineArray;

	//we iterate for each line.
	for(size_t i = 0; i < lineArray.size(); i++){
		//the string representing the line of the doc we're ciphering
		string line = lineArray.at(i).getStr();
		
		//for every char in the string...
		for (int j = 0; j < line.size(); j++)
		{
			//continue if the char will break isalpha
			if(!(line[j] >= -1 && line[j] <= 255)) continue;
			//only cipher if isalpha
			if(isalpha(line[j])){

				bool mustResetToCapital = false;
				//if the letter is capital, we must remember that
				if(tolower(line[j])!=line[j]) mustResetToCapital = true;

				//set it to lowercase (makes offsetting way easier)
				line[j] = tolower(line[j]);

				//offset it, making sure that z+1 goes to a (and not the character after z, '(')
				line[j] = (((line[j] - 'a') + (key[j%key.length()] - 'a'))%26) + 'a';

				//reset to capital
				if(mustResetToCapital) line[j] = toupper(line[j]);
			}

		}

		//replace the old line with the new one
		newLineArray.at(i).setStr(line);


	}

	return newLineArray;

}
/*
caesar_d: deciphers a caesar-encrypted document, by decrementing each char 
by some offset.
NOTE: this function does NOT alter the document object. Instead, it returns
a set of lines which can be used to construct an encrypted document object.
*/
vector<Line> Document::caesar_d(int offset){

	//the linearray to return
	vector<Line> newLineArray = lineArray;

	//we iterate for each line.
	for(size_t i = 0; i < lineArray.size(); i++){
		//the string representing the line of the doc we're ciphering
		string line = lineArray.at(i).getStr();
		
		//for every char in the string...
		for (int j = 0; j < line.size(); j++)
		{
			//continue if the char will break isalpha
			if(!(line[j] >= -1 && line[j] <= 255)) continue;
			//only cipher if isalpha
			if(isalpha(line[j])){

				bool mustResetToCapital = false;
				//if the letter is capital, we must remember that
				if(tolower(line[j])!=line[j]) mustResetToCapital = true;

				//set it to lowercase (makes offsetting way easier
				line[j] = tolower(line[j]);

				//offset it, making sure that a-1 loops back to z.
				line[j] = (((line[j] - 'a') - offset + 26)%26) + 'a';

				//reset to capital
				if(mustResetToCapital) line[j] = toupper(line[j]);
			}

		}

		//replace the old line with the new one
		newLineArray.at(i).setStr(line);


	}

	return newLineArray;

}
/*
vigenere_d: deciphers a vigenere-encrypted document, by performing the inverse
operation which vigenere() performs.
NOTE: this function does NOT alter the document object. Instead, it returns
a set of lines which can be used to construct an encrypted document object.
*/
vector<Line> Document::vigenere_d(string key){

	//the linearray to return
	vector<Line> newLineArray = lineArray;

	//we iterate for each line.
	for(size_t i = 0; i < lineArray.size(); i++){
		//the string representing the line of the doc we're ciphering
		string line = lineArray.at(i).getStr();
		
		//for every char in the string...
		for (int j = 0; j < line.size(); j++)
		{
			//continue if the char will break isalpha
			if(!(line[j] >= -1 && line[j] <= 255)) continue;
			//only cipher if isalpha
			if(isalpha(line[j])){

				bool mustResetToCapital = false;
				//if the letter is capital, we must remember that
				if(tolower(line[j])!=line[j]) mustResetToCapital = true;

				//set it to lowercase (makes offsetting way easier
				line[j] = tolower(line[j]);

				//offset it, making sure that a-1 loops back to z.
				line[j] = (((line[j] - 'a') - (key[j%key.length()] - 'a') + 26)%26) + 'a';

				//reset to capital
				if(mustResetToCapital) line[j] = toupper(line[j]);
			}

		}

		//replace the old line with the new one
		newLineArray.at(i).setStr(line);


	}

	return newLineArray;

}