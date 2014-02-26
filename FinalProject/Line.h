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

	private:
		std::string str;
		int wordcount;
		int charcount;
};