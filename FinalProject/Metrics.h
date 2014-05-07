/*
Gus Henry Smith

Metrics.h

The Metrics class contains just that - metrics tools. included are all 
sorts, used to sort both arrays and linked lists.
As it is a templated class, all functions must be defined in the header.

Metrics includes a heirarchy of sorts:
1. Sorts for arrays
	a. selectionSort
	b. insertionSort
2. Sorts for linked lists
	a. Sorts which sort by the Node's key
		i. insertionSortLinkedList
		ii. mergeSortLinkedListByCount	
	b. Sorts which sort by the Node's "count" field
		(used to order a list of nodes by the frequency of the nodes)
		i. insertionSortLinkedListByCount
		ii. mergeSortLinkedListByCount

Metrics also includes some helper functions:
*sortRecursion/sortRecursionByCount: The recursive portion of the merge sort functions.
*lessThan/equals: general functions which are able to compare ints, chars, and strings 

*/

#include <typeinfo>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class Metrics{
private:
	int id;
	/*
	THIS FUNCTION MUST BE DEFINED HERE, OTHERWISE THE PROGRAM THROWS LINKER ERRORS.
	
	lessThan: A generalized function for comparing objects. Can compare strings, chars, and ints.
	PLEASE NOTE that the following function breaks if passed
	anything other than a char, int, or string.
	*/
	template<class T> bool lessThan(T item1,T item2){
		string type = typeid(T).name();
		if(type.compare("int")==0||type.compare("char")==0){
			return item1 < item2;
		}else{
			//we get the strings.
			stringstream ss1;
			ss1 << item1;
			string string1 = ss1.str();
			//convert to lowercase...
			for(int i = 0; i < string1.length(); i++) string1[i] = tolower(string1[i]);
			stringstream ss2;
			string string2 = ss2.str();
			//convert to lowercase...
			for(int i = 0; i < string2.length(); i++) string2[i] = tolower(string2[i]);
			//return comparison of their lowercase.
			return string1.compare(string2)<0;
		}
	}
public:
	
	/*
	THIS FUNCTION MUST BE DEFINED HERE, OTHERWISE THE PROGRAM THROWS LINKER ERRORS.

	equals: a generalized equality function for strings, ints and chars. this function
	covers cases when strings are equivalent, but their cases are not.
	*/
	template<class T> static bool equals(T item1,T item2){
		string type = typeid(T).name();
		if(type.compare("int")==0||type.compare("char")==0){
			return item1 == item2;
		}else{
			//we get the strings.
			stringstream ss1;
			ss1 << item1;
			string string1 = ss1.str();
			//convert to lowercase...
			for(int i = 0; i < string1.length(); i++) string1[i] = tolower(string1[i]);
			stringstream ss2;
			ss2 << item2;
			string string2 = ss2.str();
			//convert to lowercase...
			for(int i = 0; i < string2.length(); i++) string2[i] = tolower(string2[i]);
			//return comparison of their lowercase.
			return string1.compare(string2)==0;
		}
	}


	/*
	3-1 templated sorts for int, char, and string. I have sorts for both arrays and linked lists.
	*/

	/* 
	SORTS FOR ARRAYS:
	Includes a selection insertion, and merge sort, which take the array of vars (int, char, or string)
	and a left/right index.
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
	/*END SORTS FOR ARRAYS*/
	

	/*SORTS FOR LINKED LISTS*/
	/*
	insertionSortLinkedList: insertion sort for linked lists
	*/
	template<class T>
	Node<T>* insertionSortLinkedList(Node<T>* head);
	/*
	insertionSortLinkedListByCount: sorts by the "count" field, instead of by
	the Node's key.
	*/
	template<class T>
	Node<T>* insertionSortLinkedListByCount(Node<T>* head);
	/*
	THE NEXT GIANT SECTION IS FOR THE MERGE SORT FOR NODES. I KNOW IT'S FAR FROM
	IDEAL TO DEFINE THESE HERE, BUT IF THEY'RE TO BE TEMPLATED, THIS IS THE ONLY
	WAY.
	*/
	/*
	mergeSortLinkedList:
	A merge sort for linked lists.
	we will sort recursively, meaning we will begin with a sub-list of size m,
	and then split that into a sub-list of size m/2.
	this first function simply finds the length of the list, and then calculates
	the maximum sub-list size m from that. it then calls the recursive function,
	passing it the maximum sub-list size and the head of the list.
	*/
	template<class T>
	Node<T>* mergeSortLinkedList(Node<T>* head){

		if(head == nullptr) return nullptr;
	
		//finding a length for the list
		int length = 1;
		Node<T>* trace = head;
		while(trace->getNext() != nullptr){
			trace = trace->getNext();
			length++;
		}
		//the max grouping size we should be getting. 
		int maxM = pow(2,ceil(log10(length)/log10(2)));
	
		return sortRecursion(maxM,head);
	}
	/*
	sortRecursion: the recursion section for the merge sort.
	the recursive sort works in this way:
	it first recurses down, breaking down the sub-list size until
	we are simply looking at single nodes. when we have the single
	node by itself, we disconnect it from the chain by setting its
	next val to nullptr, and simply return it back up. one level up,
	the function is handling TWO nodes (the two nodes that were just
	returned as described, one on the left hand and one on the right).
	these nodes are then run through linearly and placed on a mas-
	ter list, on which, the nodes are in ascending order. this list
	is then returned. one level up, the function is handling
	FOUR nodes: two each, from the master lists returned by both the
	right and the left side. these are again compiled into a master 
	list and returned, until the master list returned is simply
	the original list, sorted.
	*/
	template<class T>
	Node<T>* sortRecursion(int groupSize, Node<T>* head){
		
		if(head == nullptr) return nullptr;
		
		//return if we were passed a single node
		if(groupSize==0){
			Node<T>* val = head;
			//'unlink' the node from the original linked list first
			val->setNext(nullptr);
			return val;
		}

		
		//if the groups are smaller than 10...
		if(groupSize <= 10){

			/*
			here, we find the end of the list.
			it's either the node at groupsize-1, or somewhere before that.
			*/
			int i = 1;
			Node<T>* index = head;
			while(i<groupSize&&index->getNext()!=nullptr){
				i++;
				index = index->getNext();
			}
			//now we set the last node's "next" to null, to disconnect it from the main chain.
			index->setNext(nullptr);
			//additionally, we set the head's "prev" to null, to disconnect it on the other side.
			head->setPrev(nullptr);

			//now we run insertion sort on the linked list.
			head = insertionSortLinkedList(head);

			//once again we find the end...
			i = 0;
			index = head;
			while(i<groupSize&&index->getNext()!=nullptr){
				i++;
				index = index->getNext();
			}

			//and again we set the values...
			index->setNext(nullptr);
			head->setPrev(nullptr);
			
			//now we run insertion sort on this small list and return it.
			return insertionSortLinkedList(head);

		}

		//recurse on the right and left sides
		//this value just indicates where in the middle of the list does our second sub-list start
		Node<T>* right = Node<T>::get(groupSize/2,head);
		//this is the merged list for the left side...
		Node<T>* traceLeft = sortRecursion(groupSize/2,head);
		//this is the merged list for the right side...
		Node<T>* traceRight = sortRecursion(groupSize/2,right);

		//our merged list
		Node<T>* mergedListHead = new Node<T>();
		Node<T>* mergedList = mergedListHead;

		/*
		now we basically "pop" nodes off of the two sub-lists (traceLeft and traceRight)
		comparing them each time and chaining them in order.
		*/
		//while at least one of the lists has items left
		while(traceLeft!=nullptr||traceRight!=nullptr){

			//the smallest node, which will be added to the list
			Node<T>* val;
			//if the left list is empty...
			if(traceLeft == nullptr){
				val = traceRight;
				traceRight = traceRight->getNext();
			}
			//if the right list is empty...
			else if(traceRight == nullptr){
				val = traceLeft;
				traceLeft = traceLeft->getNext();
			}
			//if the right item is smaller than the left...
			else if(lessThan(traceRight->getKey(),traceLeft->getKey())){
				val = traceRight;
				traceRight = traceRight->getNext();
			}
			//if the left item is smaller (or equal) to the right..
			else{
				val = traceLeft;
				traceLeft = traceLeft->getNext();
			}
		
			//add the smaller item to the list...
			mergedList->setNext(val);
			mergedList = mergedList->getNext();
		}

		//return the entire now-merged list (excluding the first node, which was a dummy)
		return mergedListHead->getNext();
	}
	/*
	mergeSortLinkedListByCount/sortRecursionByCount:
	Same merge/insertion sort as above, but using the count field.
	*/
	template<class T>
	Node<T>* mergeSortLinkedListByCount(Node<T>* head){

		if(head == nullptr) return nullptr;
	
		//finding a length for the list
		int length = 1;
		Node<T>* trace = head;
		while(trace->getNext() != nullptr){
			trace = trace->getNext();
			length++;
		}
		//the max grouping size we should be getting. 
		int maxM = pow(2,ceil(log10(length)/log10(2)));
	
		return sortRecursionByCount(maxM,head);
	}
	template<class T>
	Node<T>* sortRecursionByCount(int groupSize, Node<T>* head){
		
		if(head == nullptr) return nullptr;
		
		//return if we were passed a single node
		if(groupSize==0){
			Node<T>* val = head;
			//'unlink' the node from the original linked list first
			val->setNext(nullptr);
			return val;
		}

		
		//if the groups are smaller than 10...
		if(groupSize <= 10){

			/*
			here, we find the end of the list.
			it's either the node at groupsize-1, or somewhere before that.
			*/
			int i = 1;
			Node<T>* index = head;
			while(i<groupSize&&index->getNext()!=nullptr){
				i++;
				index = index->getNext();
			}
			//now we set the last node's "next" to null, to disconnect it from the main chain.
			index->setNext(nullptr);
			//additionally, we set the head's "prev" to null, to disconnect it on the other side.
			head->setPrev(nullptr);

			//now we run insertion sort on the linked list.
			head = insertionSortLinkedListByCount(head);

			//once again we find the end...
			i = 0;
			index = head;
			while(i<groupSize&&index->getNext()!=nullptr){
				i++;
				index = index->getNext();
			}

			//and again we set the values...
			index->setNext(nullptr);
			head->setPrev(nullptr);
			
			return head;

		}

		//recurse on the right and left sides
		//this value just indicates where in the middle of the list does our second sub-list start
		Node<T>* right = Node<T>::get(groupSize/2,head);
		//this is the merged list for the left side...
		Node<T>* traceLeft = sortRecursionByCount(groupSize/2,head);
		//this is the merged list for the right side...
		Node<T>* traceRight = sortRecursionByCount(groupSize/2,right);

		//our merged list
		Node<T>* mergedListHead = new Node<T>();
		Node<T>* mergedList = mergedListHead;

		/*
		now we basically "pop" nodes off of the two sub-lists (traceLeft and traceRight)
		comparing them each time and chaining them in order.
		*/
		//while at least one of the lists has items left
		while(traceLeft!=nullptr||traceRight!=nullptr){

			//the smallest node, which will be added to the list
			Node<T>* val;
			//if the left list is empty...
			if(traceLeft == nullptr){
				val = traceRight;
				traceRight = traceRight->getNext();
			}
			//if the right list is empty...
			else if(traceRight == nullptr){
				val = traceLeft;
				traceLeft = traceLeft->getNext();
			}
			//if the right item is smaller than the left...
			else if(traceRight->getCount()<traceLeft->getCount()){
				val = traceRight;
				traceRight = traceRight->getNext();
			}
			//if the left item is smaller (or equal) to the right..
			else{
				val = traceLeft;
				traceLeft = traceLeft->getNext();
			}
		
			//add the smaller item to the list...
			mergedList->setNext(val);
			mergedList = mergedList->getNext();
		}

		//return the entire now-merged list (excluding the first node, which was a dummy)
		return mergedListHead->getNext();
	}
	/*
	END SORTS FOR LINKED LISTS
	*/
};//END CLASS DEFINITION

/*
DEFINITION OF FUNCTIONS
*/
/*
selectionSort/insertionSort:
Simple sorts, taking in an array of chars, strings, or ints, and a left and
right index. The functions do not return; they simply alter the given list.
*/
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
/*
insertionSortLinkedList/insertionSortLinkedListByCount:
A linked list insertion sort, taking the head of the list, and either sorting
the values by the key or by the count field.
*/
template<class T>
Node<T>* Metrics::insertionSortLinkedList(Node<T>* head){
	//find the minimum. if there are multiple, then the leftmost one should be moved.
	Node<T>* index = head;
	Node<T>* min = head;
	while(index != nullptr){
		//if we found a new minimum
		if(lessThan(index->getKey(),min->getKey())) min = index;
		//progress through
		index = index->getNext();
	}
	//insert the minimum at the beginning and set new head
	head = min->moveTo(0,head);

	//we begin at the third item
	int i = 2;
	index = Node<T>::get(i, head);
	//now we interate through and sort. this is the outer loop.
	while(index != nullptr){
		//the current index, which we will now move backwards through.
		int j = i;
		//now we loop and shift node until the node hits a node smaller than it.
		while(lessThan(index->getKey(),index->getPrev()->getKey())){
			//we move it back in the list
			index->moveTo(j-1, head);
			//decrement
			j--;
		}
		//increase index
		i++;
		//set new node
		index = Node<T>::get(i,head);
	}

	return head;
}
template<class T>
Node<T>* Metrics::insertionSortLinkedListByCount(Node<T>* head){
	//find the minimum. if there are multiple, then the leftmost one should be moved.
	Node<T>* index = head;
	Node<T>* min = head;
	while(index != nullptr){
		//if we found a new minimum
		if(index->getCount()<min->getCount()) min = index;
		//progress through
		index = index->getNext();
	}
	//insert the minimum at the beginning and set new head
	head = min->moveTo(0,head);

	//we begin at the third item
	int i = 2;
	index = Node<T>::get(i, head);
	//now we interate through and sort. this is the outer loop.
	while(index != nullptr){
		//the current index, which we will now move backwards through.
		int j = i;
		//now we loop and shift node until the node hits a node smaller than it.
		while(index->getCount()<index->getPrev()->getCount()){
			//we move it back in the list
			index->moveTo(j-1, head);
			//decrement
			j--;
		}
		//increase index
		i++;
		//set new node
		index = Node<T>::get(i,head);
	}

	return head;
}




