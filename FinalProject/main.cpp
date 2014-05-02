/*
Current status: 
fix sorts(3-1) implement node not array
check updated hash (3-2) (i think it's done)
*/

#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <Document.h>
#include <Plot.h>
#include <Metrics.h>

using namespace std;

int main(int argc, char* argv[]){

	//the user's input
	int userArg = NULL;
	//to exit the program, this needs to be switched
	bool exit = false;
	//the welcome statement
	cout << "Welcome!\n";
	//the document loaded - begins as a dummy
	Document d =  Document("No Document Loaded",-1);
	//the exit bool for the parse submenu
	bool doParseLoop = true;
	//the input for the load document option
	string loadDocumentInput;
	//the divider used to separate the console
	string divider2 = "-------------------------\n";
	string divider1 = "-------------------------";

	//1-1: main function switch
	do{
		//menu selection
		cout << "Please make a selection:\n1. Load document\n2. Output document\n3. Analyze document\n5. Exit\n";
		//resetting....
		userArg = NULL;
		cin >> userArg;

		switch(userArg){
			//load document
			case 1:
				{
					cout<<"Please enter the name of the document.\n";
					cin >> loadDocumentInput;
					//create a new document with the name given
					Document documentToLoad = Document(loadDocumentInput);
					//load the document and check if it passes
					if(documentToLoad.loadDocument(loadDocumentInput)){
						//if it passes...
						d = documentToLoad;

						//YOU CAN PUT DEBUG STUFF HERE
												
					}
					else{
						cout << "Document load failed.\n";
					}

				}
			break;

			//output document
			case 2: 
				{
					//to output the document, we first must check if we have a document loaded.
					if(d.id == -1){
						cout<<"Please load a document first.\n";
						break;
					}

					//now we take in the output file name.
					string outputDocumentInput;
					cout<<"Please enter the desired name of the output file.\n";
					cin >> outputDocumentInput;
					d.outputDocument(outputDocumentInput);
				}
			break;

			//parse document REMOVE
			case 1000: 
				{
				//first we check that the document is loaded...
				if(d.id == -1){
					cout<<"Please load a document first.\n";
					break;
				}

				//creating a submenu for parse
				do{
					cout << "a. Parse characters\nb. Parse words\nc. Get word count\nd. Get line count\ne. Go back\n";
					char parseInput = NULL;
					cin >> parseInput;
					switch(parseInput){
					//parsechar
					case 'a':
						{
							cout << "Number of letters: " << d.getAlphaCharArray().size() << endl;
							cout << "Total number of characters: " << d.getCharArray().size() << endl;
						}
						break;
					//parse words
					case 'b':
						{
							vector<string> vec = d.parseWords();
							cout << "Array of strings returned.\nLength: " << vec.size() << endl;
						}
						break;
					//wordcount
					case 'c':
						{
							cout<< "Wordcount: " << d.getWordcount() << endl;
						}
						break;
					//linecount
					case 'd':
						{
							cout<<"Linecount: " << d.getLinecount() << endl;
						}
						break;
					//exit
					case 'e':
						doParseLoop = false;
						break;
					default:
						cout<<"Please make a valid selection\n";
						break;
					}

					cout<<divider1<<d.getName()<<divider2;
				}while(doParseLoop);

				doParseLoop = true;
				
				}
			break;

			//analyze document
			case 3:
				{
				//first we check that the document is loaded...
				if(d.id == -1){
					cout<<"Please load a document first.\n";
					break;
				}

				//should we keep iterating?
				bool analyzeLoop = true;

				do{
					cout << "a. Print character count\nb. Print word count\nc. Print sentence count\nd. Go back\n";
					char analyzeInput = NULL;
					cin >> analyzeInput;
					Plot p = Plot();
					switch(analyzeInput){
					case 'a':
						{
							cout << "Number of letters: " << d.getAlphaCharArray().size() << endl;
							cout << "Total number of characters: " << d.getCharArray().size() << endl;
						}
						break;
					case'b':
						{
							cout<< "Word count: " << d.getWordcount() << endl;
						}
						break;
					case'c':
						{
							cout<<"Sentence count: " << d.getLinecount() << endl;
							
						}
						break;
					case 'd':
						{
							analyzeLoop = false;
						}
						break;
					}
					cout<<divider1<<d.getName()<<divider2;
				}while(analyzeLoop);
				}
			break;

			//exit
			case 5:
				exit = true;
			break;

			default:
				cout << "Please make a valid selection.\n";
			break;
		}
		cout<<divider1<<d.getName()<<divider2;
	}while(!exit);
	
	return 0;

}