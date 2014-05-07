/*
Gus Henry Smith

Plot.cpp

The Plot class definition includes many complex functions:
*updateCsbi: updates the object representing the console window which we print to.
*plot2DScale: a scaling plot function.
*histogram: creates a histogram from a set of data.
*plotPoint: plots a point using a custom symbol.
*createAxis, numberAxes, setGraphMaxValues, ruling and marking functions, numberX/YAxis:
	Functions that create the axis which we will plot upon.
*translateX/Y: translates a value to a coordinate value relative to the graph we've created
	inside the console window.
*/

#include <Plot.h>
#include <cmath>
#include <iostream>

using namespace std;

/*
CONSTRUCTORS AND DECONSTRUCTORS
*/
Plot::Plot(){
	//setting heightBuffer
	heightBuffer = 6;

	updateCsbi();
}

/*
FUNCTIONS
*/
/*
plot2DScale:
A scaling plot function.
As we can use drawAxis to draw the axis on-screen, all this function needs to do is number the axes and then 
draw the points accordingly.
*/
void Plot::plot2DScale(double* x, double* y, char* symbols, int length){
	
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
	setGraphMaxValues(maxX,maxY,maxX/10+1,maxY/10+1);

	//we DON'T number the axes. for all purposes in large files, the line numbers will be far too high to indicate easily.
	//numberAxes();

	for(int i = 0;i < length;i++){
		plotPoint(x[i],y[i],symbols[i]);
	}
	
	rulehoriz(2,width-1,3);
	rulevert(0,height-3,3);

	redraw();
}
/*
createAxis: a function that creates the axis. note: you must use redraw() to actually draw the axis.
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
numberAxes: the function which numbers the axes.

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
redraw: a function which simply outputs everything to the screen. 
*/
void Plot::redraw(){
	//we output everything.
	for(int i = 0; i< height; i++){
		cout << screen[i] <<endl;
	}
}
/*
findmax: a simple linear max function which we use to find the maximum values
in any given set of data.
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
updateCsbi:
This function updates the object which represents the console window. THIS IS WINDOWS-BASED ONLY.
This function should be run liberally, as we want to keep an up-to-date measurement of the window
in case the window was resized.
*/
void Plot::updateCsbi(){
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &(Plot::csbi));
}
/*
translateX/translateY:
takes a double, and returns at what position RELATIVE TO THE AXIS the item should be placed, given 
current state of Plot values. note: this doesn't give the absolute position in the screen array.

We have the graphHeight/Width and the graphMaxX/Y. so (inputX/graphMaxX)*graphWidth
should give the right distance along the x axis, for example.
*/
int Plot::translateX(double x){
	return floor((x/graphMaxX)*graphWidth);
}
int Plot::translateY(double y){
	return floor((y/graphMaxY)*graphHeight);
}
/*
setGraphMaxValues:
This function takes the max values in the set, and uses that information in combination
with the current state of the CSBI object to determine the max values present on the graph.

Basically what will happen is this:
We will ceiling the double. then we'll run a while loop on it, incrementing it until it is
evenly divisible by the x or y increment. The number it increments to is the graph's max value.
*/
void Plot::setGraphMaxValues(double maxX,double maxY,int xincrement,int yincrement){
	Plot::xincrement = xincrement;
	Plot::yincrement = yincrement;

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
plotPoint:
Plots a single point on the graph using the inputted char to represent the point.
*/
void Plot::plotPoint(double x, double y,char symbol){
	screen[height - translateY(y) - 1 - 1][translateX(x)+1] = symbol;
}
/*
rulehoriz/markhoriz/rulevert/markvert:
These recursive functions build a ruler on the plot, on both the x and y axes.
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
histogram:
Creates a histogram based on a given array of frequencies.
the way this function works is as follows:
1. axes created.
2. max frequency found -> set graph max values
3. y axis numbered.
4. x-axis labeled.
5. vertical bars drawn
*/
void Plot::histogram(double* frequencies,char* symbols,int length){
	
	//always important to do.
	updateCsbi();
	//create the basic axis.
	createAxis();
	//find max frequency
	int max = findMax(frequencies,length);
	/*
	set the max value for y. we choose 1 for the increment on the x axis so that each bar will
	be evenly spaced, and there will be no extra space for other bars.
	*/
	setGraphMaxValues(length,1,1,1);
	//number the axes
	numberYAxis();
	numberXAxis(symbols,length);
	/*
	now we plot the bars. we do this by simply plotting the original point, and then plotting
	at that same x position while decreasing the y value by 1. we do this over and over until 
	we hit the x axis; at that point we'll have a bar.
	note: we might need to decrement by smaller than 1 each time to get a solid bar. probably
	not though.
	*/
	//for each frequency
	for(int i = 0; i < length; i++){
		//the frequency we're dealing with
		double freq = frequencies[i]/max;
		/*
		we plot over and over
		we use j>.5 to make sure that the bar doesn't plot over the number on the x axis.
		*/
		for(double j = freq; j >= .15; j = j-.001){
			//we plot at x=the correct column for the frequency and y=freq-num iterations
			plotPoint(i+1,j,'*');
		}
	}
	//finally, draw 
	redraw();
}
/*
histogram:
This histogram function plots frequencies, but then prints the corresponding string above the column.
Used for the topK/bottomKWord functions.
*/
void Plot::histogram(double* frequencies,string* words,int length){
	
	//always important to do.
	updateCsbi();
	//create the basic axis.
	createAxis();
	//find max frequency
	int max = findMax(frequencies,length);
	/*
	set the max value for y. we choose 1 for the increment on the x axis so that each bar will
	be evenly spaced, and there will be no extra space for other bars.
	*/
	setGraphMaxValues(length,1,1,1);
	//number the y axis
	numberYAxis();
	/*
	now we plot the bars. we do this by simply plotting the original point, and then plotting
	at that same x position while decreasing the y value by a small amount. we do this over and over until 
	we hit the x axis; at that point we'll have a bar.
	additionally, in this overridden function, at the end of each iteration we then print the word above
	the bar.
	*/
	//for each frequency
	for(int i = 0; i < length; i++){
		//the frequency we're dealing with
		double freq = frequencies[i]/max;
		//the word we're printing
		string word = words[i];
		//the x-position of the word(moved over to the right by one)
		int xPos = translateX(i+1)+1;
		/*
		we plot over and over
		we use j>.5 to make sure that the bar doesn't plot over the number on the x axis.
		*/
		for(double j = freq; j >= .1; j = j-.01){
			//we plot at x=the correct column for the frequency and y=freq-num iterations
			plotPoint(i+1,j,'*');
		}

		//we print the word above the column.
		//for each char of the word...
		for(int j = 0; j<word.length()&& j<Plot::graphHeight; j++){
			screen[j][xPos] = word[j];
		}

	}
	//finally, draw 
	redraw();
}
/*
numberX/YAxis:
The next functions number their respective axes. The override of numberXAxis
uses symbols from the array given instead of numbers.
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
void Plot::numberXAxis(char* symbols, int length){
	for(int i = 1; i <= length; i++){

		//we put the initial symbol on the graph
		int loc = translateX(i*xincrement);
		screen[height-2][loc+1] = symbols[i-1];

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