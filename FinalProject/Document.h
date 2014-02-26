//1-3 Document class (header file)
#include <Line.h>
#include <string>
#include <vector>

using namespace std;

class Document{
	public:
		int id;
		//constructors and destructors
		Document(std::string);
		Document(std::string,int);
		//setters and getters
		int getLinecount() const;
		void setLinecount(int);
		int getWordcount() ;
		void setWordcount(int);
		vector<Line> getLineArray() const;
		void setLineArray(vector<Line>);
		void addToLineArray(Line);
		std::string getName() const;
		void setName(std::string);

		//functions
		//1-4 loadDocument functions
		int loadDocument(std::string);
		//1-7 outputDocument
		void outputDocument(string);
		//1-11 parseWords
		vector<string> parseWords();
		//1-12 parseChar
		vector<char> parseChar();

	private:
		int linecount;
		int wordcount;
		//array of lines on the heap using the vector class
		vector<Line> lineArray;
		std::string name;

};