#pragma once
#include <iostream>

using namespace std;

class Point2D {
public:
	double X, Y;
	Point2D(double X = 0, double Y = 0);
	Point2D operator=(const Point2D& Obj);
	friend istream& operator>>(istream& in, Point2D& Obj);
	friend ostream& operator<<(ostream& out, const Point2D& Obj);
};

double orientation(const Point2D& A, const Point2D& B, const Point2D& C);

bool isInside(const Point2D& A, const Point2D& B, const Point2D& C, const Point2D& P);

