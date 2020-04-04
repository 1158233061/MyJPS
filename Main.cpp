#include "JPS.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main()
{
	vector<vector<int>> maze = {
		{1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,1,0,0},
		{1,1,1,0,1,0,1,0,1},
		{1,0,0,0,1,0,0,0,1},
		{1,0,1,0,1,0,1,0,1},
		{1,0,1,0,0,0,1,0,1},
		{1,0,1,0,1,0,1,0,1},
		{0,0,1,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1}
	};
	JPS jps;
	jps.Init(maze);

	//设置起始和结束点 
	Point start(7, 0);
	Point end(1, 8);
	//A*算法找寻路径 
	list<Point*> path = jps.GetPath(start, end, false);
	//打印 
	for (auto& p : path)
		maze[p->x][p->y] = 2;
		//cout << '(' << p->x << ',' << p->y << ')' << endl;

	for (int i = 0; i < maze.size(); ++i)
	{
		for (int j = 0; j < maze[0].size(); ++j)
		{
			if (maze[i][j] == 1) printf("@ ");
			else if (maze[i][j] == 0) printf("  ");
			else printf("* ");
		}
		printf("\n");
	}


	
	return 0;
}


