#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <Document.h>

using namespace std;

int main(int argc, char* argv[]){

	int userArg = atoi(argv[1]);

	//1-1: main function switch
	switch(userArg){
		//load document
		case 0:
		break;

		//output document
		case 1: 
		break;

		//parse document
		case 2: 
		break;

		//analyze document
		case 3:
		break;

		//exit
		case 4:
		break;
	}


	//debug workspace
	Document doc("foo");
	doc.loadDocument("foo.txt");


	cout << "Press any key to exit...";
	getchar();
	return 0;

}