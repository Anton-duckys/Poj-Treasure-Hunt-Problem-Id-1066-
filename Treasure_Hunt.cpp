#include<vector>
#include<iostream>
#include<algorithm>

/*
The idea is to draw a line passing through the enclosing-wall point and the treasure point for each enclosing-wall point and calculate the number of crossings between these lines and inside walls. Then I choose the minimum number of crossings and include one enclosing-wall.
*/
using namespace std;
class point {
public:
	point(double x, double y) {
		this->x = x;
		this->y = y;
	}
	point() {

	}
	void show() {
		cout << this->x << " and " << this->y << endl;
	}

private:

	double x, y;
	friend class line;
	friend void count_walls(point treasure, vector<line> lines);
	friend bool  between(point t, point t1, point t2);
};
class line {
public:

	line(point p1, point p2) {
		this->p1 = p1;
		this->p2 = p2;
		if (p1.x == p2.x || p1.y == p2.y) {
			if (p2.x == p1.x)
			{
				this->koef_x = 1;
				this->koef_c = (int)-p1.x;
				this->koef_y = 0;
			}


			if (p2.y == p1.y)
			{
				this->koef_y = 1;
				this->koef_c = (int)-p1.y;
				this->koef_x = 0;

			}

		}
		else {
			koef_x = (double)1 / (p2.x - p1.x);
			koef_y = -(double)1 / (p2.y - p1.y);
			koef_c = (double)p1.y / (p2.y - p1.y) - (double)p1.x / (p2.x - p1.x);
		}


	}

private:
	double koef_x, koef_y, koef_c;
	point p1, p2;
	friend bool check_crossing(line l1, line l2);
	friend point find_cross(line l1, line l2);
	friend void count_walls(point treasure, vector<line> lines);
	friend bool  between(point t, point t1, point t2);
};

/*
This
*/
bool check_crossing(line l1, line l2) {

	return(abs((l1.koef_x * l2.koef_y) - (l1.koef_y * l2.koef_x)));
}
/*
Checking if the intersection point lies in rectangle with vertices at a point on the wall and treasure.
*/
bool between(point t, point t1, point t2) {
	return(t.x > min(t1.x, t2.x) && t.x < max(t1.x, t2.x) && t.y > min(t1.y, t2.y) && t.y < max(t1.y, t2.y));
}
/*
This function returns the intersection point of two lines
*/
point find_cross(line l1, line l2) {
	double tempx = -1 * (double)((double)((l1.koef_c * l2.koef_y) - (l2.koef_c * l1.koef_y)) / (double)((l1.koef_x * l2.koef_y) - (l2.koef_x * l1.koef_y)));
	double tempy = -1 * (double)((double)((l1.koef_x * l2.koef_c) - (l2.koef_x * l1.koef_c)) / (double)((l1.koef_x * l2.koef_y) - (l2.koef_x * l1.koef_y)));
	return point(tempx, tempy);
}

void count_walls(point treasure, vector<line> lines) {
	int count = lines.size();
	for (auto elem : lines) {
		int res = 0;
		line l(elem.p1, treasure);
		for (auto el : lines) {
			if (check_crossing(l, el)) {
				point pp = find_cross(l, el);
				if (between(pp, elem.p1, treasure))
					++res;
			}
		}
		count = min(count, res);
		res = 0;
		l = line(elem.p2, treasure);
		for (auto el : lines) {
			if (check_crossing(l, el)) {
				point pp = find_cross(l, el);
				if (between(pp, elem.p2, treasure))
					++res;
			}
		}
		count = min(count, res);

	}
	cout << "Number of walls = " << count + 1 << endl;
}
int main() {

	int number_of_walls;
	vector<line> lines;
	cout << "Enter number of walls" << endl;
	cin >> number_of_walls;
	for (int i = 0; i < number_of_walls; ++i) {
		cout << "Enter coordinates of the wall " << i + 1 << endl;
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		lines.emplace_back(point(x1, y1), point(x2, y2));
	}
	double treasure_x, treasure_y;
	cout << "Enter coordinates of the treasure " << endl;
	cin >> treasure_x >> treasure_y;
	count_walls(point(treasure_x, treasure_y), lines);
	system("pause");
	return 0;
}


