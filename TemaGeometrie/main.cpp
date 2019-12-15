#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include "Point2D.h" 

using namespace std;

vector<Triangle> triangulate(vector<Point2D> Polygon, vector<Point2D> Concaves) {
	vector<Triangle> Result;
	size_t n = Polygon.size();
	while (n > 2) {
		for (size_t i = 0; i < n; ++i) {
			//varf convex
			if (orientation(Polygon[(i - 1 + n) % n], Polygon[i], Polygon[(i + 1) % n]) > 0) {
				bool valid = true;
				//verificare nu contine varf concav
				for (Point2D point : Concaves)
					if (isInside(Polygon[(i - 1 + n) % n], Polygon[i], Polygon[(i + 1) % n], point)) {
						valid = false;
						break;
					}
				if (valid) {
					//avem nou triunghi
					Result.push_back({ Polygon[(i - 1 + n) % n], Polygon[i], Polygon[(i + 1) % n] });
					//TODO: desenam diagonala
					//verificare vecini daca sunt convexi
					auto it = find(Concaves.begin(), Concaves.end(), Polygon[(i - 1) % n]);
					if (it != Concaves.end() && orientation(Polygon[(i - 2 + n) % n], Polygon[(i - 1 + n) % n], Polygon[(i + 1) % n]) > 0)
						Concaves.erase(it);
					it = find(Concaves.begin(), Concaves.end(), Polygon[(i + 1) % n]);
					if (it != Concaves.end() && orientation(Polygon[(i - 1 + n) % n], Polygon[(i + 1) % n], Polygon[(i + 2) % n]) > 0)
						Concaves.erase(it);
					//sterge varf taiat
					Polygon.erase(Polygon.begin() + i);
					n--;
				}
			}
		}
	}
	return Result;
}

int main() {
	Point2D P;
	vector<Point2D> Polygon, Concaves;
	ifstream fin("date.in");
	size_t n;
	fin >> n;
	for (size_t i = 0; i < n; ++i) {
		Point2D newPoint;
		fin >> newPoint;
		Polygon.push_back(newPoint);
	}
	fin >> P;
	fin.close();
	for (size_t i = 0; i < n; ++i) {
		if (orientation(Polygon[(i - 1) % n], Polygon[i], Polygon[(i + 1) % n]) < 0)
			Concaves.push_back(Polygon[i]);
	}
	vector<Triangle> Triangulation = triangulate(Polygon, Concaves);
	for (auto t : Triangulation) {
		cout << t.A << ' ' << t.B << ' ' << t.C << "\n";
	}
	map<Triangle, vector<Triangle>> Adjacence;
	map<Triangle, bool> Visited;
	for (Triangle t1 : Triangulation) {
		Visited[t1] = false;
		for (Triangle t2 : Triangulation) {
			if (isAdjacent(t1, t2))
				Adjacence[t1].push_back(t2);
		}
	}
	queue<Triangle> tQueue;
	for (Triangle t : Triangulation) {
		if (isInside(t.A, t.B, t.C, P, true)) {
			tQueue.push(t);
			cout << "Triangle: " << t << '\n';
			Visited[t] = true;
			break;
		}
	}
	cout << "Observable:\n";
	while (!tQueue.empty()) {
		Triangle Front = tQueue.front();
		tQueue.pop();
		size_t count = 0;
		count += orientation(Front.A, Front.B, Front.C) * orientation(P, Front.B, Front.C) >= 0;
		count += orientation(Front.A, Front.B, Front.C) * orientation(Front.A, P, Front.C) >= 0;
		count += orientation(Front.A, Front.B, Front.C) * orientation(Front.A, Front.B, P) >= 0;
		if (count >= 2) {
			cout << Front << '\n';
			for (Triangle t : Adjacence[Front]) {
				if (!Visited[t]) {
					Visited[t] = true;
					tQueue.push(t);
				}
			}
		}
	}
	Polygon.clear();
	return 0;
}