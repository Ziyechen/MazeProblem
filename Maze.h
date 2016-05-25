#pragma once

#include <iostream>
using namespace std;

#include <stack>
#include <assert.h>

//得到节点的行和列
struct Maze_Node
{
	Maze_Node(int row = 0, int col = 0)
	:_row(row)
	, _col(col)
	{}

	int _row;
	int _col;
};

//得到迷宫
int * GetMazeMap(FILE *fp)
{
	int row = 0, col = 0;
	char c;

	while ((c = fgetc(fp)) != ' ')
	{
		row = row * 10 + c - '0';
	}
	while ((c = fgetc(fp)) != '\n')
	{
		col = col * 10 + c - '0';
	}

	int *array = new int[row * col];
	int i = 0, j = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			char c;
			while (1)
			{
				c = fgetc(fp);
				if (c == '1' || c == '0')
				{
					array[i * row + j] = c - '0';
					break;
				}
			}
		}
	}

	fclose(fp);

	return array;
}

void Print(int *array, int row, int col)
{
	int i = 0, j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			cout << array[i * row + j] << " ";
		}
		cout << endl;
	}
}

bool IsOutTheRange(Maze_Node pos, int row, int col)
{
	if (pos._col > col || pos._col < 0)
		return true;

	if (pos._row > row || pos._row < 0)
		return true;

	return false;
}

bool SearchMazePath(int *array, int row, int col, Maze_Node enrty, stack<Maze_Node> pos)
{
	assert(array);

	pos.push(enrty);
	while (!pos.empty())
	{
		Maze_Node cur = pos.top();
		array[cur._row * row + cur._col] = 2;
		//判断是否找到出口
		if (cur._row == (row - 1))
		{
			return true;
		}

		Maze_Node tmp = cur;
		//找路
		cur._col--;
		if (!IsOutTheRange(cur, row, col))
		{
			if (array[cur._row * row + cur._col] == 0)
			{
				pos.push(cur);
				continue;
			}
		}

		cur = tmp;
		cur._col++;
		if (!IsOutTheRange(cur, row, col))
		{
			if (array[cur._row * row + cur._col] == 0)
			{
				pos.push(cur);
				continue;
			}
		}

		cur = tmp;
		cur._row--;
		if (!IsOutTheRange(cur, row, col))
		{
			if (array[cur._row * row + cur._col] == 0)
			{
				pos.push(cur);
				continue;
			}
		}

		cur = tmp;
		cur._row++;
		if (!IsOutTheRange(cur, row, col))
		{
			if (array[cur._row * row + cur._col] == 0)
			{
				pos.push(cur);
				continue;
			}
		}

		//回溯
		pos.pop();
	}
	return false;
}
