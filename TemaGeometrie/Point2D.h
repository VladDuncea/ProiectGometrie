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

double orientation(const Point2D& A, const Point2D& B, const Point2D& C) {
	return abs((A.X * B.Y + B.X * C.Y + C.X * A.Y) - (A.Y * B.X + B.Y * C.X + C.Y * A.X));
}

bool isInside(const Point2D& A, const Point2D& B, const Point2D& C, const Point2D& P) {
	/* Calculate area of triangle ABC */
	double ABC = abs(orientation(A, B, C));

	// Calculate area of triangle PBC
	double PBC = abs(orientation(P, B, C));

	// Calculate area of triangle PAC 
	double APC = abs(orientation(A, P, C));

	// Calculate area of triangle PAB 
	double ABP = abs(orientation(A, B, P));

	// Check if sum of A1, A2and A3 is same as A
	return (ABC == PBC + APC + ABP);
}

