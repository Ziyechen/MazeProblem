#define _CRT_SECURE_NO_WARNINGS 1

#include "Maze.h"
#include <stdlib.h>

void test1()
{
	FILE *fp = fopen("D:\\新建文件夹\\VS\\MazeProblem\\MazeProblem\\MazeMap.txt", "r");
	assert(fp);
	int *array = GetMazeMap(fp);

	Print(array, 10, 10);

	Maze_Node enrty(2, 0);
	stack<Maze_Node> pos;

	cout << SearchMazePath(array, 10, 10, enrty, pos) << endl;
	Print(array, 10, 10);
}

int main()
{
	test1();

	system("pause");
	return 0;
}
