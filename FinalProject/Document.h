//1-3 Document class (header file)
#include <Line.h>
#include <string>

class Document{
	public:
		int id;
		//constructors and destructors
		Document(std::string);
		Document(std::string,int);
		//setters and getters
		int getLinecount() const;
		void setLinecount(int);
		int getWordcount() const;
		void setWordcount(int);
		Line* getLineArray() const;
		void setLineArray(Line*);
		std::string getName() const;
		void setName(std::string);
	private:
		int linecount;
		int wordcount;
		//array of lines on the heap
		Line* lineArray;
		std::string name;

};