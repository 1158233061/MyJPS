#include "JPS.h"

void JPS::Init(vector<vector<int>>& maze)
{
	this->maze = maze;
}

list<Point*> JPS::GetPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner)
{
	Point* result = findPath(startPoint, endPoint, isIgnoreCorner);
	list<Point*> path;
	while (result)
	{
		path.push_back(result);
		result = result->parent;
	}
	return list<Point*>();
}

Point* JPS::findPath(Point& startPoint, Point& endPoint, bool isIgnoreCorner)
{
	openlist.push(new Point(startPoint.x, startPoint.y));
	openset.insert(new Point(startPoint.x, startPoint.y));
	while (!openlist.empty())
	{
		Point* curPoint = getLeastF();
		curPoint->closed = true;
		if (*curPoint == endPoint) return curPoint;
		expandSuccessors(curPoint);
	}
	return nullptr;
}

void JPS::expandSuccessors(Point* point)
{
	vector<Point*> neighbors = findNeighbors(point);
	for (Point* neighbor : neighbors)
	{

	}
}

vector<Point*> JPS::findNeighbors(Point* point)
{
	vector<Point*> res;
	if (point->parent)
	{
		// 有父节点，要剪枝
		int dx = max(abs(point->x - point->parent->x), 1);
		int dy = max(abs(point->y - point->parent->y), 1);
		// 对角线
		if (dx != 0 && dy != 0)
		{
			// 轴向分量
			if (isCanReach(point->x, point->y + dy))
				res.push_back(new Point(point->x, point->y + dy));
			if (isCanReach(point->x + dx, point->y))
				res.push_back(new Point(point->x + dx, point->y));
			// 往前看
			if (isCanReach(point->x, point->y + dy) && isCanReach(point->x + dx, point->y) && isCanReach(point->x + dx, point->y + dy))
				res.push_back(new Point(point->x + dx, point->y + dy));
		}
		// 垂直分量
		else if (dx == 0)
		{
			// 向前看
			if (isCanReach(point->x, point->y + dy))
				res.push_back(new Point(point->x, point->y + dy));
			// 向左看
			if (!isCanReach(point->x - 1, point->y - dy) && isCanReach(point->x - 1, point->y))
			{
				forceNeighbours.insert(new Point(point->x - 1, point->y - dy));
			}
			// 向右看
		}
		return res;
	}
}

bool JPS::isCanReach(int x, int y)
{
	if (x<0 || y<0 || x>maze.size() - 1 || y>maze[0].size() - 1 || maze[x][y] == 1)
		return false;
	return true;
}

bool JPS::isInOpen(Point* point)
{
	if (openset.find(point) != openset.end())
		return true;
	return false;
}

Point* JPS::getLeastF()
{
	if (!openlist.empty()) {
		Point* curP = openlist.top();
		openlist.pop();
		return curP;
	}
	return nullptr;
}
int JPS::calculateG(Point* start, Point* point)
{
	int extraG, parentG;
	if (abs(point->x - start->x) + abs(point->y - start->y) == 1)
		extraG = kCost1;
	else
		extraG = kCost2;
	if (point->parent == NULL)
		parentG = 0;
	else
		parentG = point->parent->G;
	return parentG + extraG;
}

int JPS::calculateH(Point* point, Point* end)
{
	int dx = abs(point->x - end->x);
	int dy = abs(point->y - end->y);
	return dx + dy;
}

int JPS::calculateF(Point* point)
{
	return point->G + point->H;
}