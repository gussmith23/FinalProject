#include <Windows.h>
#include <Plot.h>
#include <cmath>
#include <iostream>

using namespace std;

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
	string* lines = new string[height];
	
	
	//we initialize each string
	for(int i = 0; i < height; i++){
		lines[i] = "";
		for(int j = 0; j < width; j++){
			lines[i] = lines[i] + " ";
		}
	}
	//we build the vertical axis.
	for(int i = 0; i < height-1; i++){
		lines[i][1] = '|';
	}
	//we build the horizontal axis.
	for(int i = 1; i < width; i++){
		lines[height-2][i] = '-';
	}
	//we label the x axis.
	for(size_t i = 0; i < xLabel.size(); i++){
		lines[height-1][i+2] = xLabel[i];
	}
	//we label the y axis.
	for(size_t i = 0; i < yLabel.size(); i++){
		lines[i+2][0] = yLabel[i];
	}
	
	//we number the x-axis
	for(int i = 0; 5*i + 1< width; i++){
		int xActual = 5*i + 1;
		//if 5*i is greater than 10, we'll need 2 spots.
		if(5*i>=10){
			char* c = new char[2];
			itoa((5*i),c,10);
			lines[height-2][xActual] = c[1];
			lines[height-2][xActual-1] = c[0];
		}
		else{
			char* c = new char[1];
			itoa(5*i,c,10);
			lines[height-2][xActual] = c[0];
		}
	}
	//we number the y-axis
	for(int i = 0; 5*i + 1< height; i++){
		int yActual = height - 2 - 5*i;
		//if 5*i is greater than 10, we'll need 2 spots.
		if(5*i>=10){
			char* c = new char[2];
			itoa((5*i),c,10);
			lines[yActual-1][1] = c[0];
			lines[yActual][1] = c[1];
		}
		else{
			char* c = new char[1];
			itoa(5*i,c,10);
			lines[yActual][1] = c[0];
		}
	}

	//we plot the point. we have to consider how this actually works, now.
	/*coordinate systems measure up and to the right as positive, while this string system measures down
	and to the right as positive. thus our (0,0) is technically at (1,height-2). we can translate our 
	coordinates as follows - xActual = xGiven + 1, yActual = (height-2) - yGiven*/
	//to plot the point, we find the right string and the right char.
	int xActual = x+1;
	int yActual = (height - 2) - y;
	lines[yActual][xActual]='*';

	//we output everything.
	for(int i = 0; i< height; i++){
		cout << lines[i] <<endl;
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
	string* lines = new string[height];
	
	
	//we initialize each string
	for(int i = 0; i < height; i++){
		lines[i] = "";
		for(int j = 0; j < width; j++){
			lines[i] = lines[i] + " ";
		}
	}
	//we build the vertical axis.
	for(int i = 0; i < height-1; i++){
		lines[i][1] = '|';
	}
	//we build the horizontal axis.
	for(int i = 1; i < width; i++){
		lines[height-2][i] = '-';
	}
	//we label the x axis.
	for(size_t i = 0; i < xLabel.size(); i++){
		lines[height-1][i+2] = xLabel[i];
	}
	//we label the y axis.
	for(size_t i = 0; i < yLabel.size(); i++){
		lines[i+2][0] = yLabel[i];
	}
	
	//we number the x-axis
	for(int i = 0; 5*i + 1< width; i++){
		int xActual = 5*i + 1;
		//if 5*i is greater than 10, we'll need 2 spots.
		if(5*i>=10){
			char* c = new char[2];
			itoa((5*i),c,10);
			lines[height-2][xActual] = c[1];
			lines[height-2][xActual-1] = c[0];
		}
		else{
			char* c = new char[1];
			itoa(5*i,c,10);
			lines[height-2][xActual] = c[0];
		}
	}
	//we number the y-axis
	for(int i = 0; 5*i + 1< height; i++){
		int yActual = height - 2 - 5*i;
		//if 5*i is greater than 10, we'll need 2 spots.
		if(5*i>=10){
			char* c = new char[2];
			itoa((5*i),c,10);
			lines[yActual-1][1] = c[0];
			lines[yActual][1] = c[1];
		}
		else{
			char* c = new char[1];
			itoa(5*i,c,10);
			lines[yActual][1] = c[0];
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
		lines[yActual][xActual]='*';
	}

	//we output everything.
	for(int i = 0; i< height; i++){
		cout << lines[i] <<endl;
	}
}