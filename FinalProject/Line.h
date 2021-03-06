/*
Gus Henry Smith

Line.h

The Line class represents a single line in the document. Each
Line object contains a string holding the sentence which it
represents. Also included are the wordcount and charcount for 
the line.
*/

//1-2 creating class line (header file)
#include <string>
#include <vector>

using namespace std;

class Line{
	public:
		int id;

		//constructors and deconstructors
		Line();
		Line(std::string);
		Line(std::string,int);
		~Line();
		
		//setters and getters
		void setStr(std::string);
		std::string getStr() const;
		void setWordcount(int);
		//no const on getWordCount because of the getter's dynamic nature + need to set wordcount
		int getWordcount();
		void setCharcount(int);
		int getCharcount() const;

		//functions
		//1-8
		vector<string> parseWords();
		//1-9
		vector<char> parseChar();
		//1-10
		vector<char> parseChar(string*, int);

		//a function to find the punctuation
		char getPunctuation();

	private:
		std::string str;
		int wordcount;
		int charcount;
};