/*
Gus Henry Smith

main.cpp

The main file for the program. Contains all of the code to display the main
menu and submenus. 
The only significant functions/data handled in this file relate to the array
of Document objects which the program keeps track of. In the vector called
"documents", we keep a list of documents which either the user has loaded, or
the program has created (after encrypting/decrypting). There is also a funct-
ion searchByName which searches through this array of documents for a document
matching the name given. This is used when the user inputs what document they
are trying to output/analyze/encrypt/decrypt/compare.
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
	//the document loaded - begins as a dummy
	Document d =  Document("No Document Loaded",-1);
	//the exit bool for the parse submenu
	bool doParseLoop = true;
	//the input for the load document option - filename, and user-given name
	string loadDocumentInput; string docName;
	//the divider used to separate the console
	string divider2 = "<-------\n";
	string divider1 = "\n------->";
	//the welcome statement
	cout << "Welcome!\n";
	
	//1-1: main function switch
	do{
		//The list of available options
		cout << "Please make a selection:\n1. Load document\n2. Output document\n3. Analyze document\n4. Compare two documents\n5. Encrypt\n6. Decrypt\n7. Exit\n";
		
		//resetting the inputted arg
		userArg = NULL;
		cin >> userArg;

		switch(userArg){
			//load document
			case 1:
				{
					//getting user input...
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
						//if it passes, add it to the list of active documents
						documents.push_back(documentToLoad);												
					}
					else{
						//else, the document failed
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
					//getting user info...
					string docToOutputName;
					cout<<"Please enter the name of the file you'd like to output.\n";
					cin >> docToOutputName;
					Document docToOutput = searchByName(docToOutputName,documents);
					//if we can't find the document
					if(docToOutput.getId() == -1){
						cout << "Please input a valid file." <<endl;
						break;
					}
					//now that we know there's a valid document to output, we take in the desired output file name.
					string outputDocumentInput;
					cout<<"Please enter the desired name of the output file.\n";
					cin >> outputDocumentInput;
					//call the output function
					docToOutput.outputDocument(outputDocumentInput);
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

				/*
				Here, we ask them for the document that they want to analyze BEFORE they choose
				an item from the submenu. It is simply more effective to run this section this way.
				*/

				//get the document they want to use
				string docToAnalyzeName;
				cout << "Which document would you like to analyze?"<<endl;
				cin >> docToAnalyzeName;
				Document docToAnalyze = searchByName(docToAnalyzeName,documents);
				//if we can't find the document
				if(docToAnalyze.getId() == -1){
					cout << "Please input a valid file." <<endl;
					break;
				}

				//should we keep iterating?
				bool analyzeLoop = true;

				do{
					//display the submenu, which is pretty long for the analyze option
					cout << "a. Print character counts\nb. Print word count\nc. Print sentence count\nd. Print histogram of all chars\ne. Print histogram of all chars, offset\nf. Print histogram of top k words\ng. Print histogram of bottom k words (with top word included for reference)\nh. Print word trace\ni. Go back\n";
					char analyzeInput = NULL;
					cin >> analyzeInput;
					Plot p = Plot();
					switch(analyzeInput){
					//character counts
					case 'a':
						{
							//output number of alpha chars
							cout << "Number of letters: " << docToAnalyze.getAlphaCharArray().size() << endl;
							//output number of chars total
							cout << "Total number of characters: " << docToAnalyze.getCharArray().size() << endl;
						}
						break;
					//wordcount
					case'b':
						{
							cout<< "Word count: " << docToAnalyze.getWordcount() << endl;
						}
						break;
					//line/sentence count
					case'c':
						{
							cout<<"Sentence count: " << docToAnalyze.getLinecount() << endl;
							
						}
						break;
					//histogram of all characters
					case 'd':
						{
							docToAnalyze.printAllChars();
						}
						break;

					//histogram with offset
					case 'e':
						{
							cout<<"Enter character offset:"<<endl;
							int offset;
							cin>>offset;
							docToAnalyze.printAllCharsOffset(offset);
						}
						break;
					//histogram of top k words
					case 'f':
						{
							cout<<"How many words?"<<endl;
							int k;
							cin>>k;
							docToAnalyze.printTopKWord(k);
						}
						break;
					//histogram of bottom k words
					case 'g':
						{
							cout<<"How many words?"<<endl;
							int k;
							cin>>k;
							docToAnalyze.printBottomKWord(k);
						}
						break;
					//word trace
					case 'h':
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

							docToAnalyze.wordTraceK(words,k);

						}
						break;
					//exit
					case 'i':
						{
							analyzeLoop = false;
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
				}while(analyzeLoop);
				}
			break;
			//compare two documents
			case 4:
				{
				//first we check that two documents are loaded...
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
							//until we get a valid document
							while(!valid){
								cout<<"Input document 1's name:"<<endl;
								string doc1name;
								cin >> doc1name;
								doc1 = searchByName(doc1name, documents);
								if(doc1.getId() != -1) valid = true;
								else cout<<"Input a valid name."<<endl;
							}

							valid = false;

							//until we get a valid document
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
							//simply reset both documents
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

			//encrypt
			case 5:
				{
				//check that the document is loaded...
				if(documents.size() < 1){
					cout<<"Please load two documents first.\n";
					break;
				}

				//should we keep iterating?
				bool encryptloop = true;

				do{
					//encrypting options
					cout << "a. Caesar cipher\nb. Vigenere cipher\nc. Go back\n";
					char analyzeInput = NULL;
					cin >> analyzeInput;
					switch(analyzeInput){
					//caesar cipher
					case 'a':
						{
							//get the document
							cout<<"Which document would you like to encrypt?"<<endl;
							string docToEncryptName;
							cin >> docToEncryptName;
							Document docToEncrypt = searchByName(docToEncryptName,documents);
							//if we can't find it, return;
							if(docToEncrypt.getId()==-1){
								cout<<"Please choose a valid file."<<endl;
								break;
							}
							//else, get the offset...
							cout<<"What offset do you want to use?"<<endl;
							int offset;
							cin>>offset;
							//we get the set of encrypted lines...
							vector<Line> encryptedLines = docToEncrypt.caesar(offset);
							//we create a new "encrypted" document...
							Document encryptedDoc = Document(docToEncryptName + "_c_en");
							//set the line array of encrypted document to the encrypted lines
							encryptedDoc.setLineArray(encryptedLines);
							//so we can analyze the document later, we run all of our analysis functions on the newly created encrypted doc
							encryptedDoc.runInitialFunctions();
							//put the doc in the list of viewable docs
							documents.push_back(encryptedDoc);
							cout<<"Encrypted."<<endl;
						break;
						}
					//vigenere cipher
					case 'b':
						{
							//get the document
							cout<<"Which document would you like to encrypt?"<<endl;
							string docToEncryptName;
							cin >> docToEncryptName;
							Document docToEncrypt = searchByName(docToEncryptName,documents);
							//if we can't find it, return;
							if(docToEncrypt.getId()==-1){
								cout<<"Please choose a valid file."<<endl;
								break;
							}
							//else, get the keyword...
							cout<<"What keyword do you want to use?"<<endl;
							string key;
							cin>>key;
							//we get the set of encrypted lines...
							vector<Line> encryptedLines = docToEncrypt.vigenere(key);
							//we create a new "encrypted" document...
							Document encryptedDoc = Document(docToEncryptName + "_v_en");
							//set the line array of encrypted document to the encrypted lines
							encryptedDoc.setLineArray(encryptedLines);
							//get data from the new lines so we can then analyze them
							encryptedDoc.runInitialFunctions();
							//put the doc in the list of viewable docs
							documents.push_back(encryptedDoc);
							cout<<"Encrypted."<<endl;
						break;
						}
					case 'c':
						{
							encryptloop=false;
						break;
						}
					}//close switch
					//output the document names as a header
					cout<<divider1;
					for (int i = 0; i < documents.size(); i++)
					{
						cout<< " " << documents.at(i).getName() << " ";
					}
					cout<<divider2;
					
				}while(encryptloop);
				}
				
			break;

			//decrypt
			case 6:
				{
				//check that the document is loaded...
				if(documents.size() < 1){
					cout<<"Please load two documents first.\n";
					break;
				}

				//should we keep iterating?
				bool decryptloop = true;

				do{
					cout << "a. Caesar decipher\nb. Vigenere decipher\nc. Go back\n";
					char analyzeInput = NULL;
					cin >> analyzeInput;
					switch(analyzeInput){
					//caesar decipher
					case 'a':
						{
							//get the document
							cout<<"Which document would you like to decrypt?"<<endl;
							string docToDecryptName;
							cin >> docToDecryptName;
							Document docToDecrypt = searchByName(docToDecryptName,documents);
							//if we can't find it, return;
							if(docToDecrypt.getId()==-1){
								cout<<"Please choose a valid file."<<endl;
								break;
							}
							//else, get the offset...
							cout<<"What offset do you want to use?"<<endl;
							int offset;
							cin>>offset;
							//we get the set of decrypted lines...
							vector<Line> decryptedLines = docToDecrypt.caesar_d(offset);
							//we create a new "decrypted" document...
							Document decryptedDoc = Document(docToDecryptName + "_c_de");
							//set the line array of decrypted document to the decrypted lines
							decryptedDoc.setLineArray(decryptedLines);
							//get data from the new lines so we can then analyze them
							decryptedDoc.runInitialFunctions();
							//put the doc in the list of viewable docs
							documents.push_back(decryptedDoc);
							cout<<"Decrypted."<<endl;
						break;
						}
					//vigenere decipher
					case 'b':
						{
							//get the document
							cout<<"Which document would you like to decrypt?"<<endl;
							string docToDecryptName;
							cin >> docToDecryptName;
							Document docToDecrypt = searchByName(docToDecryptName,documents);
							//if we can't find it, return;
							if(docToDecrypt.getId()==-1){
								cout<<"Please choose a valid file."<<endl;
								break;
							}
							//else, get the offset...
							cout<<"What key do you want to use?"<<endl;
							string key;
							cin>>key;
							//we get the set of decrypted lines...
							vector<Line> decryptedLines = docToDecrypt.vigenere_d(key);
							//we create a new "decrypted" document...
							Document decryptedDoc = Document(docToDecryptName + "_v_de");
							//set the line array of decrypted document to the decrypted lines
							decryptedDoc.setLineArray(decryptedLines);
							//get data from the new lines so we can then analyze them
							decryptedDoc.runInitialFunctions();
							//put the doc in the list of viewable docs
							documents.push_back(decryptedDoc);
							cout<<"Decrypted."<<endl;
						break;
						}
					case 'c':
						{
							decryptloop=false;
						break;
						}
					}//close switch
					//output the document names as a header
					cout<<divider1;
					for (int i = 0; i < documents.size(); i++)
					{
						cout<< " " << documents.at(i).getName() << " ";
					}
					cout<<divider2;
					
				}while(decryptloop);
				}
				
			break;

			//exit
			case 7:
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


/*
searchByName simply does a linear search through the vector of documents
to find the document specified. If no document is found, a document with
ID -1 is returned (which the program can then check for).
A linear search is justified, because the list of documents will never be
exceedingly long.
*/
Document searchByName(string docName,vector<Document> docs){
	//for every document...
	for(int i = 0; i<docs.size(); i++){
		if(docs.at(i).getName() == docName) return docs.at(i);
	}
	return Document("",-1);
}