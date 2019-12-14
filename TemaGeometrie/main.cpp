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
	for (size_t i = 0; i < n; ++i) {
		if (orientation(Polygon[(i - 1) % n], Polygon[i], Polygon[(i + 1) % n]) < 0)
			Concaves.push_back(Polygon[i]);
	}
	for (auto point : Concaves)
		cout << point << ' ';
	Polygon.clear();
	return 0;
}