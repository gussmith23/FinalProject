//1-3 Document class (header file)
#include <Line.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <LineNode.h>
#include <Stack.h>

using namespace std;

class Document{
	public:
		
		
		//constructors and destructors
		Document(std::string);
		Document(std::string,int);

		//setters and getters
		int getId() const; void setId(int);
		int getLinecount() const;void setLinecount(int);
		int getWordcount(); void setWordcount(int);
		vector<Line> getLineArray() const; void setLineArray(vector<Line>);
		void addToLineArray(Line);
		std::string getName() const;
		void setName(std::string);
		Stack<string>* getpWords() const;
		Node<string>** getHashTableWords() const;
		void setHashTableWords(Node<string>**);
		Node<char>** getHashTableChar() const;
		void setHashTableChar(Node<char>**);
		vector<char> getCharArray() const; 
		vector<char> getAlphaCharArray() const;
		vector<string> setWordArray() const;

		//functions
		//1-4 loadDocument functions
		int loadDocument(std::string);
		//1-7 outputDocument
		void outputDocument(string);
		//1-11 parseWords
		vector<string> parseWords();
		//1-12 parseChar
		vector<char> parseChar(bool);
		//2-3 linelengths
		void lineLengths();
		LineNode<int>* getpLineLengthsLinkedList() const;
		//2-5 reversecompare
		void reverseCompare(Document);
		//2-7 hashWords();
		void hashWords();
		void hashChar();
		//3-4
		void printParsedChars();
		void printParsedCharsByFrequency();
		void printAllChars();
		void printTopKWord(int);
		void printBottomKWord(int);
		void wordTraceK(string*,int);
		//ciphers
		vector<Line> caesar(int);
		vector<Line> vigenere(string);
		//deciphers
		vector<Line> caesar_d(int);
		vector<Line> vigenere_d(string);
		//helper function
		 void runInitialFunctions();

	private:
		int id;
		int linecount;
		int wordcount;
		//array of lines on the heap using the vector class
		vector<Line> lineArray;
		//the words in the document...
		vector<string> wordArray;
		//the chars in the document (all chars)
		vector<char> charArray;
		//the alpha chars in the document
		vector<char> alphaCharArray;
		//helper function
		void defineVariables();
		//
		std::string name;
		//null terminated linked list with wordcounts and final chars
		LineNode<int>* pLineLengthsLinkedList;
		//a stack of all words in the doc
		Stack<string>* pWords;
		//a double pointer for a chaining hash table.
		Node<string>** hashTableWords;
		//char hashtable.
		Node<char>** hashTableChar;
		//the length of the outer array of both hash tables
		int hashLengthWords;int hashLengthChars;

};