//1-3 Document class (cpp file)
#include <Document.h>
#include <Metrics.h>
#include<Plot.h>
#include <ctime>

using namespace std;
//constructors and deconstructors
//string name, random id
Document::Document(string nameval){
	name = nameval;
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
	defineVariables();
}
//string name, int id
Document::Document(string nameval, int idval){
	name = nameval;
	id = idval;
	defineVariables();
}
//helper function to define all variables at once
void Document::defineVariables(){
	pWords = new Stack<string>();
	wordcount = NULL;
	linecount = NULL;
	hashLengthWords = 97;
	hashLengthChars = 8;
}
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
	cout<<"done."<<endl;
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

	cout<<"Reading filestream...";

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
	
	//now that the document is loaded, we can define our variables.
	runInitialFunctions();

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
			Document::pWords->push(wordsToAdd.at(j));
		}
	}

	return words;

}
/*1-12 Create a function in Document called parseChar that returns an
array of char (similar to Line).
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
2-3 The function should search through all the Lines. Each line will be a new node that 
stores the word count of that line and the symbol that ended the sentence (., ?, !, etc).

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
	Stack<string>* master = Stack<string>::copyStack(Document::pWords);
	Stack<string>* external = Stack<string>::copyStack(d.getpWords());

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

			//if we found a node whose key is the same, we increment the counter
			if(Metrics::equals(head->getKey(),word)) head->setCount(head->getCount() + 1);
			//otherwise, create a new node on the end
			else{
				//the new node
				Node<string>* n = new Node<string>(word);
				//set new node's prev to the previous node (current end of list)
				n->setPrev(head);
				//set the current end of the list's next to the new node (adding it to list)
				head->setNext(n);	
			}
		}
	}
}
/*
hashes chars.
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
3-4 printParsedChars
it firsts parses all chars into a hash table
*/
void Document::printParsedChars(){
	
	time_t c1 = clock();
	
	Metrics* m = new Metrics();
	Plot* p = new Plot();

	//we first set the hashlength to 1 and hash the chars...
	int previousHashLength = hashLengthChars;
	hashLengthChars = 1;
	hashChar();
	//this effectively gives us a linked-list of chars.

	//we now sort the linked list.
	//remember, the hash table's chains begin with a dummy node, so we use getNext...
	Node<char>* head = m->mergeSortLinkedList(getHashTableChar()[0]->getNext());

	//we find the length of the list.
	int length = 1;
	Node<char>* index = head;
	while(index->getNext()!=nullptr){
		length++;
		index = index->getNext();
	}

	double* frequencies = new double[20];
	char* symbols = new char[20];

	//find the 10 first and final chars..
	for(int i = 0; i < 10; i++){
		
		//the node near the start
		Node<char>* beginning = Node<char>::get(i,head);
		//the node near the end
		Node<char>* end = Node<char>::get(length-1-i,head);

		frequencies[i] = (double) beginning->getCount(); symbols[i] = beginning->getKey();
		frequencies[i+10] = (double) end->getCount(); symbols[i+10] = end->getKey();
		//cout<<symbols[i];

	}
	p->histogram(frequencies,symbols,20);

	//reset hash length
	hashLengthChars = previousHashLength;

	//print time
	cout<<((double)clock()-(double)c1)/CLOCKS_PER_SEC << " seconds to generate.\n";

}
void Document::printParsedCharsByFrequency(){
	
	time_t c1 = clock();
	
	Metrics* m = new Metrics();
	Plot* p = new Plot();

	//we first set the hashlength to 1 and hash the chars...
	int previousHashLength = hashLengthChars;
	hashLengthChars = 1;
	hashChar();
	//this effectively gives us a linked-list of chars.

	//we now sort the linked list.
	//remember, the hash table's chains begin with a dummy node, so we use getNext...
	Node<char>* head = m->mergeSortLinkedListByCount(getHashTableChar()[0]->getNext());

	//we find the length of the list.
	int length = 1;
	Node<char>* index = head;
	while(index->getNext()!=nullptr){
		length++;
		index = index->getNext();
	}

	double* frequencies = new double[20];
	char* symbols = new char[20];

	//find the 10 first and final chars..
	for(int i = 0; i < 10; i++){
		
		//the node near the start
		Node<char>* beginning = Node<char>::get(i,head);
		//the node near the end
		Node<char>* end = Node<char>::get(length-1-i,head);

		frequencies[i+10] = (double) beginning->getCount(); symbols[i+10] = beginning->getKey();
		frequencies[i] = (double) end->getCount(); symbols[i] = end->getKey();
		//cout<<symbols[i];

	}
	p->histogram(frequencies,symbols,20);

	//reset hash length
	hashLengthChars = previousHashLength;

	//print time
	cout<<((double)clock()-(double)c1)/CLOCKS_PER_SEC << " seconds to generate.\n";

}
/*
Print letters a-z with frequencies.
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
Top k word: prints the top k words, where k is some integer.
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