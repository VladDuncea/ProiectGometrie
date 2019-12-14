#include "Point2D.h"

Point2D::Point2D(double X, double Y): X(X), Y(Y) {}

Point2D Point2D::operator=(const Point2D& Obj) {
	if (this == &Obj)
		return *this;
	X = Obj.X;
	Y = Obj.Y;
	return *this;
}

bool Point2D::operator==(const Point2D& Obj)
{
	return (Obj.X == X && Obj.Y == Y);
}

istream& operator>>(istream& in, Point2D& Obj) {
	in >> Obj.X >> Obj.Y;
	return in;
}

ostream& operator<<(ostream& out, const Point2D& Obj) {
	out << '(' << Obj.X << ", " << Obj.Y << ')';
	return out;
}

double orientation(const Point2D& A, const Point2D& B, const Point2D& C) {
	return (A.X * B.Y + B.X * C.Y + C.X * A.Y) - (A.Y * B.X + B.Y * C.X + C.Y * A.X);
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

	//check if point is on edges
	if (ABP == 0 || APC == 0 || PBC == 0)
		return false;

	// Check if sum of A1, A2and A3 is same as A
	return (ABC == PBC + APC + ABP);
}
