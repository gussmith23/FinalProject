#include <Plot.h>
#include <cmath>
#include <iostream>

using namespace std;

Plot::Plot(){
	//setting heightBuffer
	heightBuffer = 3;

	updateCsbi();
}
void Plot::plotSinglePoint(double x, double y){

	string xLabel = "x-axis";
	string yLabel = "y-axis";
	
	//info on CSBI class from stackoverflow and MSDN
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
	//getting the height and the width of the screen.
	//subtracting from the height because that's just how the size works out for me right now. not an exact science...or it is, but i don't want to bother.
	int height = abs(csbi.srWindow.Top-csbi.srWindow.Bottom) - 3;
	int width = abs(csbi.srWindow.Left-csbi.srWindow.Right);

	//return if the coordinates are out of range.
	if((y>height-2)||(x>width-2)){
		cout<< "Your coordinates are out of the plottable range.\n";
		return;
	}

	//so we need to plot this point.
	/* the structure is as follows: the leftmost column is blank, reserved for the y axis label. 
	the bottom row is also blank, reserved for the x axis label. axes borders defined by _ and |.*/

	//we have one string for each line.
	string* screen = new string[height];
	
	
	//we initialize each string
	for(int i = 0; i < height; i++){
		screen[i] = "";
		for(int j = 0; j < width; j++){
			screen[i] = screen[i] + " ";
		}
	}
	//we build the vertical axis.
	for(int i = 0; i < height-1; i++){
		screen[i][1] = '|';
	}
	//we build the horizontal axis.
	for(int i = 1; i < width; i++){
		screen[height-2][i] = '-';
	}
	//we label the x axis.
	for(size_t i = 0; i < xLabel.size(); i++){
		screen[height-1][i+2] = xLabel[i];
	}
	//we label the y axis.
	for(size_t i = 0; i < yLabel.size(); i++){
		screen[i+2][0] = yLabel[i];
	}
	
	//we number the x-axis
	for(int i = 0; 5*i + 1< width; i++){
		int xActual = 5*i + 1;
		//if 5*i is greater than 10, we'll need 2 spots.
		if(5*i>=10){
			char* c = new char[2];
			itoa((5*i),c,10);
			screen[height-2][xActual] = c[1];
			screen[height-2][xActual-1] = c[0];
		}
		else{
			char* c = new char[1];
			itoa(5*i,c,10);
			screen[height-2][xActual] = c[0];
		}
	}
	//we number the y-axis
	for(int i = 0; 5*i + 1< height; i++){
		int yActual = height - 2 - 5*i;
		//if 5*i is greater than 10, we'll need 2 spots.
		if(5*i>=10){
			char* c = new char[2];
			itoa((5*i),c,10);
			screen[yActual-1][1] = c[0];
			screen[yActual][1] = c[1];
		}
		else{
			char* c = new char[1];
			itoa(5*i,c,10);
			screen[yActual][1] = c[0];
		}
	}

	//we plot the point. we have to consider how this actually works, now.
	/*coordinate systems measure up and to the right as positive, while this string system measures down
	and to the right as positive. thus our (0,0) is technically at (1,height-2). we can translate our 
	coordinates as follows - xActual = xGiven + 1, yActual = (height-2) - yGiven*/
	//to plot the point, we find the right string and the right char.
	int xActual = x+1;
	int yActual = (height - 2) - y;
	screen[yActual][xActual]='*';

	//we output everything.
	for(int i = 0; i< height; i++){
		cout << screen[i] <<endl;
	}
}
void Plot::plot2D(double* x, double* y, int length){
	string xLabel = "x-axis";
	string yLabel = "y-axis";
	
	//info on CSBI class from stackoverflow and MSDN
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);
	//getting the height and the width of the screen.
	//subtracting from the height because that's just how the size works out for me right now. not an exact science...or it is, but i don't want to bother.
	int height = abs(csbi.srWindow.Top-csbi.srWindow.Bottom) - 3;
	int width = abs(csbi.srWindow.Left-csbi.srWindow.Right);

	//so we need to plot this point.
	/* the structure is as follows: the leftmost column is blank, reserved for the y axis label. 
	the bottom row is also blank, reserved for the x axis label. axes borders defined by _ and |.*/

	//we have one string for each line.
	string* screen = new string[height];
	
	
	//we initialize each string
	for(int i = 0; i < height; i++){
		screen[i] = "";
		for(int j = 0; j < width; j++){
			screen[i] = screen[i] + " ";
		}
	}
	//we build the vertical axis.
	for(int i = 0; i < height-1; i++){
		screen[i][1] = '|';
	}
	//we build the horizontal axis.
	for(int i = 1; i < width; i++){
		screen[height-2][i] = '-';
	}
	//we label the x axis.
	for(size_t i = 0; i < xLabel.size(); i++){
		screen[height-1][i+2] = xLabel[i];
	}
	//we label the y axis.
	for(size_t i = 0; i < yLabel.size(); i++){
		screen[i+2][0] = yLabel[i];
	}
	
	//we number the x-axis
	for(int i = 0; 5*i + 1< width; i++){
		int xActual = 5*i + 1;
		//if 5*i is greater than 10, we'll need 2 spots.
		if(5*i>=10){
			char* c = new char[2];
			itoa((5*i),c,10);
			screen[height-2][xActual] = c[1];
			screen[height-2][xActual-1] = c[0];
		}
		else{
			char* c = new char[1];
			itoa(5*i,c,10);
			screen[height-2][xActual] = c[0];
		}
	}
	//we number the y-axis
	for(int i = 0; 5*i + 1< height; i++){
		int yActual = height - 2 - 5*i;
		//if 5*i is greater than 10, we'll need 2 spots.
		if(5*i>=10){
			char* c = new char[2];
			itoa((5*i),c,10);
			screen[yActual-1][1] = c[0];
			screen[yActual][1] = c[1];
		}
		else{
			char* c = new char[1];
			itoa(5*i,c,10);
			screen[yActual][1] = c[0];
		}
	}

	//we plot the point. we have to consider how this actually works, now.
	/*coordinate systems measure up and to the right as positive, while this string system measures down
	and to the right as positive. thus our (0,0) is technically at (1,height-2). we can translate our 
	coordinates as follows - xActual = xGiven + 1, yActual = (height-2) - yGiven*/
	
	
	//to plot the point, we find the right string and the right char.
	//we have to iterate through each point and plot them individually.
	for(int i = 0; i < length;i++){

		//continuing if the coordinates are out of range.
		if((y[i]>height-2)||(x[i]>width-2)){
			continue;
		}

		int xActual = x[i]+1;
		int yActual = (height - 2) - y[i];
		screen[yActual][xActual]='*';
	}

	//we output everything.
	for(int i = 0; i< height; i++){
		cout << screen[i] <<endl;
	}
}
/*
2-1
A scaling plot function.
As we can use drawAxis to draw the axis on-screen, all this function needs to do is number the axes and then 
draw the points accordingly.
Current status:
numberAxes
*/
void Plot::plot2DScale(double* x, double* y, int length){
	
	//variables
	//the max X and maxY
	double maxX,maxY;

	updateCsbi();

	//we draw the axis, passing the console window so that we know it draws correctly.
	createAxis();

	//we find the max X and max Y
	maxX = findMax(x,length);
	maxY = findMax(y,length);

	//now we use the maxes to set the graph's max values
	setGraphMaxValues(maxX,maxY);

	numberAxes();

	for(int i = 0;i < length;i++){
		plotPoint(x[i],y[i]);
	}
	
	rulehoriz(2,width-1,3);
	rulevert(0,height-3,3);

	redraw();
}
/*
a function that creates the axis. note: you must use redraw() to actually draw the axis.
*/
void Plot::createAxis(){
	string xLabel = "x-axis";
	string yLabel = "y-axis";

	
	//getting the height and the width of the screen.
	//subtracting from the height because that's just how the size works out for me right now. not an exact science...or it is, but i don't want to bother.
	height = abs(csbi.srWindow.Top-csbi.srWindow.Bottom) - heightBuffer;
	width = abs(csbi.srWindow.Left-csbi.srWindow.Right);
	//setting the working area of the graph.
	graphHeight = height-1;
	graphWidth = width-1;

	//so we need to plot this point.
	/* the structure is as follows: the leftmost column is blank, reserved for the y axis label. 
	the bottom row is also blank, reserved for the x axis label. axes borders defined by _ and |.*/

	//we have one string for each line.
	screen = new string[height];
	
	//we initialize each string
	for(int i = 0; i < height; i++){
		screen[i] = "";
		for(int j = 0; j < width; j++){
			screen[i] = screen[i] + " ";
		}
	}
	//we build the vertical axis.
	for(int i = 0; i < height-1; i++){
		screen[i][1] = '|';
	}
	//we build the horizontal axis.
	for(int i = 1; i < width; i++){
		screen[height-2][i] = '-';
	}
	//we label the x axis.
	for(size_t i = 0; i < xLabel.size(); i++){
		screen[height-1][i+2] = xLabel[i];
	}
	//we label the y axis.
	for(size_t i = 0; i < yLabel.size(); i++){
		screen[i+2][0] = yLabel[i];
	}
}
/*
the function which numbers the axes.

we start at increment, and increase by increment as long as we're less than or equal to the graph's max 
val, which is a multiple of increment. for each iteration of the loop, we put the numbers on 
the graph using the translate functions and insertion into the screen array.
*/
void Plot::numberAxes(){
	
	numberXAxis();
	numberYAxis();
	
	/*
	//x axis
	for(int i = xincrement; i < graphMaxX; i = i + xincrement){

		//we need to figure out how long the number actually is
		char* holder = new char[10];
		itoa(i,holder,10);
		int digits = ((string)holder).length();

		//we put the initial digit on the graph
		int loc = translateX(i);
		screen[height-2][loc+1] = holder[0];

		//now we place the rest of the number on the plot
		for(int j = 1; j < digits; j++){
			screen[height-2][loc+1+j] = holder[j];
		}

	}
	//y axis
	for(int i = yincrement; i < graphMaxY; i = i + yincrement){
		
		

		//we need to figure out how long the number actually is
		char* holder = new char[10];
		itoa(i,holder,10);
		int digits = ((string)holder).length();

		//we put the initial digit on the graph
		int loc = translateY(i);
		screen[height-1-loc][1] = holder[0];

		
		//now we place the rest of the number on the plot
		for(int j = 1; j < digits; j++){
			screen[height-1-loc+j][1] = holder[j];
		}
		
		
	}
	*/

}
/*
a function which simply outputs everything to the screen.
*/
void Plot::redraw(){
	//we output everything.
	for(int i = 0; i< height; i++){
		cout << screen[i] <<endl;
	}
}
/*
a simple max function
*/
double Plot::findMax(double* values, int length){
	double max = 0.0;
	//linear search. may implement binary/other type later.
	for(int i = 0; i < length; i++){
		if(values[i]>max) max = values[i];
	}
	return max;
}
/*
update the object which represents the console window. this should be run liberally.
*/
void Plot::updateCsbi(){
	GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &(Plot::csbi));
}
/*
takes a double, and returns at what position RELATIVE TO THE AXIS the item should be placed, given 
current state of Plot values. note: this doesn't give the absolute position in the screen array.

so we have the graphHeight/Width and the graphMaxX/Y. so (inputX/graphMaxX)*graphWidth
should give the right distance along the x axis. 

*/
int Plot::translateX(double x){
	return floor((x/graphMaxX)*graphWidth);
}
int Plot::translateY(double y){
	return floor((y/graphMaxY)*graphHeight);
}
/*
this function takes the max values in the set, and uses that information in combination
with the current state of the Plot object to determine the max values present on the graph.

basically what will happen is this:
we will ceiling the double. then we'll run a while loop on it, incrementing it until it is
evenly divisible by increment. the number it increments to is the graph's max val.
*/
void Plot::setGraphMaxValues(double maxX,double maxY){
	xincrement = 10;
	yincrement = 5;

	//for the x
	int x = ceil(maxX);
	while(!((x)%xincrement==0)){
		x++;
	}
	graphMaxX = x+xincrement;

	//for the y
	int y = ceil(maxY);
	while(!((y)%yincrement==0)){
		y++;
	}
	graphMaxY = y+yincrement;
	
}
/*
*/
void Plot::plotPoint(double x, double y){
	screen[height - translateY(y) - 1 - 1][translateX(x)+1] = '*';
}
/*
the following functions build the ruler on the screen.
*/
void Plot::rulehoriz(int l, int r, int h){
	//this is simply a recursion which divides the screen into sections, indicating each time
	//with marks
	int m = (l+r)/2;
	if(h>0){
		rulehoriz(l,m,h-1);
		markhoriz(m,h);
		rulehoriz(m,r,h-1);
	}
}
void Plot::markhoriz(int loc, int h){
	
	for(int i = 0; i<h; i++){
		screen[height-1-1-1-i][loc+1] = '|';
	}

}
void Plot::rulevert(int l, int r, int h){
	int m = (l+r)/2;
	if(h>0){
		rulevert(l,m,h-1);
		markvert(m,h);
		rulevert(m,r,h-1);
	}
}
void Plot::markvert(int loc, int h){
	
	for(int i = 0; i<h; i++){
		screen[height-2-loc][i+2] = '-';
	}

}
/*
2-4 histogram:
Create a function in Plot class called histogram. This function should create a histogram
based on a given array of frequencies.
the way this function works is as follows:
1. axes created.
2. max frequency found -> y axis numbered.
3. x-axis labeled.
4. vertical bars drawn
*/
void Plot::histogram(double* frequencies,int length){



}
/*
in the next two functions, we're simply separating the numberAxes function
*/
void Plot::numberXAxis(){
	//x axis
	for(int i = xincrement; i < graphMaxX; i = i + xincrement){

		//we need to figure out how long the number actually is
		char* holder = new char[10];
		itoa(i,holder,10);
		int digits = ((string)holder).length();

		//we put the initial digit on the graph
		int loc = translateX(i);
		screen[height-2][loc+1] = holder[0];

		//now we place the rest of the number on the plot
		for(int j = 1; j < digits; j++){
			screen[height-2][loc+1+j] = holder[j];
		}

	}
}
void Plot::numberYAxis(){
	//y axis
	for(int i = yincrement; i < graphMaxY; i = i + yincrement){
		
		

		//we need to figure out how long the number actually is
		char* holder = new char[10];
		itoa(i,holder,10);
		int digits = ((string)holder).length();

		//we put the initial digit on the graph
		int loc = translateY(i);
		screen[height-1-loc][1] = holder[0];

		
		//now we place the rest of the number on the plot
		for(int j = 1; j < digits; j++){
			screen[height-1-loc+j][1] = holder[j];
		}
		
		
	}
}