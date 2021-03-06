/*
Gus Henry Smith

Plot.h

The Plot class contains numerous utilities used in plotting data. 
For more information on the specific functions, look in Plot.cpp.

The functioning of the Plot class depends on the CONSOLE_SCREEN_BUFFER_INFO
object, which is a Windows-only construct. This object represents 
the console, and is used to determine placement of points, the si-
ze of the graph, etc.
*/
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class Plot{
	public:

		Plot();

		//getters and setters
		int getId() const;
		void setId(int);

		vector<string> getXLabel()const;
		void setXLabel(vector<string>);
		void addXLabel(string);

		vector<string> getYLabel()const;
		void setYLabel(vector<string>);
		void addYLabel(string);

		int getNumPoints() const;
		void setNumPoints(int);

		//functions
		//2-1 scaling plot function
		void plot2DScale(double*,double*,char*,int);
		//2-4 histogram - takes array of frequencies and length of array
		void histogram(double*,char*,int);
		//override to handle strings
		void histogram(double*,string*,int);

		void numberXAxis(char*,int);
		//find max of a set
		static double findMax(double*,int);

	private:
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		int id;
		vector<string> xlabel;
		vector<string> ylabel;
		int numPoints;
		//function used to create the axis
		void createAxis();
		//an array of strings which represents the screen.
		string* screen;
		//this value is changed depending on how much space needs to be reserved below the graph
		int heightBuffer;
		
		//the height and width of the screen
		int height; int width;
		//the height and witdth of the graph area
		int graphHeight; int graphWidth;
		//the max x and y represented on the graph.
		double graphMaxX; double graphMaxY;
		//the amount the axes are incremented by
		double xincrement; double yincrement;
		//takes the greatest X and Y values present, and the desired values to increment the x and y axes by.
		void setGraphMaxValues(double,double,int,int);
		
		//redraw the plot
		void redraw();
		//number the axes
		void numberAxes();
		//plot a single point on the graph
		void plotPoint(double,double,char);
		//separating the numberAxes()  function
		void numberXAxis(); void numberYAxis();

		//update csbi
		void updateCsbi();
		//the translation functions
		int translateX(double); int translateY(double);

		//2-2 ruling functions
		void markhoriz(int,int);
		void rulehoriz(int,int,int);
		void markvert(int,int);
		void rulevert(int,int,int);
};