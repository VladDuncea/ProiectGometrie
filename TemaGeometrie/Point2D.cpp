#include "Point2D.h"

Point2D::Point2D(double X, double Y): X(X), Y(Y) {}

Point2D Point2D::operator=(const Point2D& Obj) {
	if (this == &Obj)
		return *this;
	X = Obj.X;
	Y = Obj.Y;
	return *this;
}

istream& operator>>(istream& in, Point2D& Obj) {
	in >> Obj.X >> Obj.Y;
	return in;
}

ostream& operator<<(ostream& out, const Point2D& Obj) {
	out << '(' << Obj.X << ", " << Obj.Y << ')';
	return out;
}
