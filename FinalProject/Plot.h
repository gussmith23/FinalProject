/*1-13 Create a Class called Plot. Private: int id, array of string xlabel, 
array of string ylabels, int numPoints. Make the correct setters and getters.*/
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class Plot{
	public:

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
		int id;
		vector<string> xlabel;
		vector<string> ylabel;
		int numPoints;
		//function used to draw the axis
		void drawAxis(CONSOLE_SCREEN_BUFFER_INFO);
};