#include <Line.h> 

//sets id to random number
Line::Line(){
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
}
//sets id to random number and str to value
Line::Line(std::string strvalue){
	//we use a six-digit random number here
	id = rand() % (999999 - 100000 + 1) + 100000;
	str = strvalue; 
}
//sets id to value and str to value
Line::Line(std::string strvalue, int idval){
	id = idval;
	str = strvalue; 
}