#include <typeinfo>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Metrics{
private:
	int id;
	/*
	PLEASE NOTE that the following two functions break if passed
	anything other than a char, int, or string.
	*/
	template<class T> bool lessThan(T item1,T item2){
		string type = typeid(T).name();
		if(type.compare("int")==0||type.compare("char")==0){
			return item1 < item2;
		}else{
			stringstream ss1;
			ss1 << item1;
			stringstream ss2;
			ss2 << item2;
			return ss1.str().compare(ss2.str())<0;
		}
	}
	template<class T> bool greaterThan(T item1,T item2){
		string type = typeid(T).name();
		if(type.compare("int")==0||type.compare("char")==0){
			return item1 > item2;
		}else{
			stringstream ss1;
			ss1 << item1;
			stringstream ss2;
			ss2 << item2;
			return ss1.str().compare(ss2.str())<0;
		}
	}
public:

	/*
	3-1 templated sorts for int, char, and string 
	*/
	template<class T>
	void selectionSort(T*,int,int);
	template<class T>
	void insertionSort(T*,int,int);
	template<class T> void mergeSort(T* vars, int leftIndex, int rightIndex){
	
		if(rightIndex - leftIndex + 1 <= 10){ //execute insertion sort
			insertionSort(vars,leftIndex, rightIndex);
			return;
		}

		//the midpoint
		int m = (leftIndex+rightIndex)/2;
		//sort the two halves
		mergeSort(vars,leftIndex,m);
		mergeSort(vars,m+1,rightIndex);

		//merge two halves together
		insertionSort(vars, leftIndex,rightIndex);
	}
};

template<class T>
void Metrics::selectionSort(T* vars, int leftIndex, int rightIndex){
	//for every index 
	for(int i = leftIndex; i <= rightIndex; i++){
		//the index of the current minimum
		int min = i;
		//for every index INCLUDING and AFTER the current outer index
		for(int j = i; j <= rightIndex; j++){
			//if the current inner index contains val less than current min...
			if(lessThan(vars[j],vars[min])) min = j;
		}
		//swap index with current min
		T temp = vars[i];
		vars[i] = vars[min];
		vars[min] = temp;
	}
}
template<class T>
void Metrics::insertionSort(T* vars, int leftIndex,int rightIndex){
	int min = leftIndex;
	//find the min
	for(int i = leftIndex; i <= rightIndex; i++){
		if(lessThan(vars[i],vars[min])) min = i;
	}
	//place the min in the first index
	T temp = vars[leftIndex];
	vars[leftIndex] = vars[min];
	vars[min] = temp;
	//for all indexes beginning with the third...
	for(int i = leftIndex + 2; i <= rightIndex; i++){
		//keeping track of item at the index
		T item = vars[i]; 
		int j = i;
		//we move backward until the item to the left is smaller than the current item 
		while(lessThan(item,vars[j-1])){
			//shifting the items over to the right
			vars[j] = vars[j-1];
			j--;
		}
		//assigning the item to the correct spot
		vars[j] = item;
	}
}


