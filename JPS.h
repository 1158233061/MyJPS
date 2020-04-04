#pragma once
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <math.h>

using namespace std;

const int kCost1 = 10;
const int kCost2 = 14;

struct Point
{
	int x, y;
	int F, G, H;
	bool opened = false;
	bool closed = false;
	bool forced = false;
	Point* parent;
	Point(int _x, int _y) :x(_x), y(_y), F(0), G(9), H(0), parent(NULL)
	{
	}
	friend bool operator==(const Point& a, const Point& b)
	{
		if (a.x == b.x && a.y == b.y)
			return true;
		else return false;
	}
	friend bool operator<(const Point& a, const Point& b)
	{
		return a.f < b.F ? true : false;
	}
};
class JPS
{
public:
	JPS();
	void Init(vector<vector<int> >& maze);
	list<Point*> GetPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);
private:
	Point* findPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner);
	vector<Point*> getSurroundPoints(const Point* point, bool isIgnoreCorner);
	void expandSuccessors(Point* point);
	vector<Point*> findNeighbors(Point* point);
	bool isCanReach(int x, int y);
	bool isInOpen(Point* point);
	Point* getLeastF();
	int calculateG(Point* start, Point* point);
	int calculateH(Point* point, Point* end);
	int calculateF(Point* point);


private:
	Point startPoint;
	Point endPoint;
	vector<vector<int>> maze;
	priority_queue<Point, vector<Point*>, greater<Point> > openlist;
	unordered_set<Point*> openset;
	unordered_set<Point*> forceNeighbours;
};
