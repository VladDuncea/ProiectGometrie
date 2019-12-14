#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Point2D.h" 

using namespace std;

struct triunghi
{
	Point2D a, b, c;
};


vector<triunghi> triangulate(vector<Point2D> Polygon, vector<Point2D> Concaves)
{
	vector<triunghi> rez;

	int n = Polygon.size();

	while (Polygon.size() > 3)
	{
		for (size_t i = 0; i < n; ++i) {
			//varf convex
			if (orientation(Polygon[(i - 1) % n], Polygon[i], Polygon[(i + 1) % n]) > 0)
			{
				bool valid = true;
				//verificare nu contine varf concav
				for (Point2D point : Concaves)
					if (isInside(Polygon[(i - 1) % n], Polygon[i], Polygon[(i + 1) % n], point))
					{
						valid = false;
						break;
					}

				if (valid)
				{
					//avem nou triunghi
					rez.push_back({ Polygon[(i - 1) % n], Polygon[i], Polygon[(i + 1) % n] });
					//TODO: desenam diagonala

					//verificare vecini daca sunt convexi
					auto it = find(Concaves.begin(), Concaves.end(), Polygon[(i - 1) % n]);
					if (it != Concaves.end() && orientation(Polygon[(i - 2) % n], Polygon[(i - 1) % n], Polygon[(i + 1) % n]) > 0)
					{
							Concaves.erase(it);
					}

					it = find(Concaves.begin(), Concaves.end(), Polygon[(i + 1) % n]);
					if (it != Concaves.end() && orientation(Polygon[(i - 1) % n], Polygon[(i + 1) % n], Polygon[(i + 2) % n]) > 0)
					{
							Concaves.erase(it);
					}

					//sterge varf taiat
					Polygon.erase(Polygon.begin() + i);
					n--;
				}
			}
		}

		//elimin
	}

	rez.push_back({ Polygon[0], Polygon[1], Polygon[2] });

	return rez;
}

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
	vector<triunghi> rezultat = triangulate(Polygon, Concaves);

	for (auto t : rezultat)
	{
		cout << t.a << ' ' << t.b << ' ' << t.c << "\n";
	}
		
	Polygon.clear();
	return 0;
}