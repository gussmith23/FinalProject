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

Document searchByName(string,vector<Document>);

int main(int argc, char* argv[]){
	//a set of loaded documents
	vector<Document> documents = vector<Document>();
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
	//the input for the load document option - filename, and user-given name
	string loadDocumentInput; string docName;
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
					cout<<"Please enter the filename of the document.\n";
					cin >> loadDocumentInput;
					cout<<"Give the file a name:\n";
					cin >> docName;
					//create a new document with the name given
					Document documentToLoad = Document(loadDocumentInput);
					//set the document name
					documentToLoad.setName(docName);
					//load the document and check if it passes
					if(documentToLoad.loadDocument(loadDocumentInput)){
						//if it passes...
						documents.push_back(documentToLoad);

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
					if(documents.size() < 1){
						cout<<"Please load a document first.\n";
						break;
					}

					string docToOutputName;
					cout<<"Please enter the name of the file you'd like to output.\n";
					cin >> docToOutputName;
					Document docToOutput = searchByName(docToOutputName,documents);
					//if we can't find the document
					if(docToOutput.getId() == -1){
						cout << "Please input a valid file." <<endl;
						break;
					}

					//now we take in the output file name.
					string outputDocumentInput;
					cout<<"Please enter the desired name of the output file.\n";
					cin >> outputDocumentInput;
					docToOutput.outputDocument(outputDocumentInput);
				}
			break;

			//parse document REMOVE
			case 1000: 
				{
				//first we check that the document is loaded...
				if(documents.size() < 1){
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
				if(documents.size() < 1){
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
					//histogram of all characters
					case 'd':
						{
							d.printAllChars();
						}
						break;
					//histogram of top k words
					case 'e':
						{
							cout<<"How many words?"<<endl;
							int k;
							cin>>k;
							d.printTopKWord(k);
						}
						break;
					//histogram of bottom k words
					case 'f':
						{
							cout<<"How many words?"<<endl;
							int k;
							cin>>k;
							d.printBottomKWord(k);
						}
						break;
					//word trace
					case 'g':
						{
							cout<<"How many words?"<<endl;
							int k;
							cin>>k;
							//now we'll collect the words...
							string* words = new string[k];
							for(int i = 0; i<k; i++){
								cout<<"Enter word #" << i+1 << ":"<<endl;
								cin>>words[i];
							}

							d.wordTraceK(words,k);

						}
						break;




					case 'i':
						{
							analyzeLoop = false;
						}
						break;
					}
					cout<<divider1<<d.getName()<<divider2;
				}while(analyzeLoop);
				}
			break;

			case 4:
				{
				//first we check that the document is loaded...
				if(documents.size() < 2){
					cout<<"Please load two documents first.\n";
					break;
				}

				//should we keep iterating?
				bool documentloop = true;
				//the two documents we'll compare
				Document doc1 = Document("",-1);Document doc2 = Document("",-1);

				do{
					
					cout << "a. Input document names\nb. Clear document names\nc. Compare different\nd. Go back\n";
					char analyzeInput = NULL;
					cin >> analyzeInput;
					switch(analyzeInput){
					//input doc names
					case 'a':
						{
							bool valid = false;
							
							while(!valid){
								cout<<"Input document 1's name:"<<endl;
								string doc1name;
								cin >> doc1name;
								doc1 = searchByName(doc1name, documents);
								if(doc1.getId() != -1) valid = true;
								else cout<<"Input a valid name."<<endl;
							}

							valid = false;

							while(!valid){
								cout<<"Input document 2's name:"<<endl;
								string doc2name;
								cin >> doc2name;
								doc2 = searchByName(doc2name, documents);
								if(doc2.getId() != -1) valid = true;
								else cout<<"Input a valid name."<<endl;
							}

						}
						break;
					//clear
					case 'b':
						{
							doc1 = Document("",-1);
							doc2 = Document("",-1);
							cout << "Documents cleared." << endl;
						}
						break;
					//compare
					case 'c':
						{
							doc1.reverseCompare(doc2);
						}
						break;
					//exit
					case 'd':
						{
							documentloop = false;
						}
						break;
					}
					//output the document names as a header
					cout<<divider1;
					for (int i = 0; i < documents.size(); i++)
					{
						cout<< " " << documents.at(i).getName() << " ";
					}
					cout<<divider2;
				}while(documentloop);
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
		//output the document names as a header
		cout<<divider1;
		for (int i = 0; i < documents.size(); i++)
		{
			cout<< " " << documents.at(i).getName() << " ";
		}
			cout<<divider2;
	}while(!exit);
	
	return 0;

}

Document searchByName(string docName,vector<Document> docs){
	//for every document...
	for(int i = 0; i<docs.size(); i++){
		if(docs.at(i).getName() == docName) return docs.at(i);
	}
	return Document("",-1);
}