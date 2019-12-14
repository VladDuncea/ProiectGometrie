#include <iostream>
#include <fstream>
#include <vector>
#include "Point2D.h" 
using namespace std;

int main() {
	vector<Point2D> Polygon, Concaves;
	ifstream fin("date.in");
	size_t n;
	fin >> n;
	for (size_t i = 0; i < n; ++i) {
		Point2D newPoint;
		fin >> newPoint;
		Polygon.push_back(newPoint);
	}
	fin.close();
	if (orientation(Polygon[n - 1], Polygon[0], Polygon[1]) < 0)
		Concaves.push_back(Polygon[0]);
	for (size_t i = 1; i < n - 1; ++i) {
		if (orientation(Polygon[i - 1], Polygon[i], Polygon[i + 1]) < 0)
			Concaves.push_back(Polygon[i]);
	}
	if (orientation(Polygon[n - 2], Polygon[n - 1], Polygon[0]) < 0)
		Concaves.push_back(Polygon[n - 1]);
	for (auto point : Concaves)
		cout << point << ' ';
	Polygon.clear();
	return 0;
}