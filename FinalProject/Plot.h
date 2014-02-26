/*1-13 Create a Class called Plot. Private: int id, array of string xlabel, 
array of string ylabels, int numPoints. Make the correct setters and getters.*/
#include <vector>
#include <string>

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

	private:
		int id;
		vector<string> xlabel;
		vector<string> ylabel;
		int numPoints;
};