/*1-13 Create a Class called Plot. Private: int id, array of string xlabel, 
array of string ylabels, int numPoints. Make the correct setters and getters.*/
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
		//1-14
		void plot2D(double*,double*,int);
		void plotSinglePoint(double,double);
		//2-1 scaling plot function
		void plot2DScale(double*,double*,int);

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
		int graphMaxX; int graphMaxY;
		//the amount the axes are incremented by
		int xincrement; int yincrement;

		void setGraphMaxValues(double,double);
		
		//redraw the plot
		void redraw();
		//find max of a set
		double findMax(double*,int);
		//number the axes
		void numberAxes();
		//plot a single point on the graph
		void plotPoint(double,double);

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