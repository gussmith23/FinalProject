//1-2 creating class line (header file)
#include <string>
class Line{
	public:
		int id;
		//constructors and deconstructors
		Line();
		Line(std::string);
		Line(std::string,int);
		
		//setters and getters
		void setStr(std::string);
		std::string getStr() const;
		void setWordcount(int);
		int getWordcont() const;
		void setCharcount(int);
		int getCharcount() const;

	private:
		std::string str;
		int wordcount;
		int charcount;
};