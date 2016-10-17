/**
* @file		Sudoku_solve.c
* @brief	输入一个数独题目并进行求解,同时将结果输出到屏幕
* @author	zdz
* @date		2016.10.17
* @version	1.1
* @par		history:
*			v1.0: zdz, 2016.10.10, Initial Version\n
*			v1.1: zdz, 2016.10.17, Modify comment format\n
*/


#include "stdio.h"

#define FALSE 0      
#define TRUE 1      

typedef int BOOL;

int gl_answer_num = 0;

/*
* @brief	判断填入的数是否符合规则
* @arg		row		:int型，表示当前行
* @arg		column	:int型，表示当前列
* @arg		cells	:int[9][9]型，当前整个数独盘面
* @retval	BOOL
* @return	TRUE(1) OR FALSE(0)
*/
BOOL judge(int row, int column, int cells[9][9])
{
	int r = 0, c = 0;
	// 检查一行是否有重复的
	for (r = row, c = 0; c < 9; c++)
	{
		if (c != column && cells[r][c] == cells[row][column])
		{
			return 0;
		}
	}
	// 检查一列是否有重复的
	for (c = column, r = 0; r < 9; r++)
	{
		if (r != row && cells[r][c] == cells[row][column])
		{
			return 0;
		}
	}
	// 检查一九宫格是否有重复的
	for (r = (row / 3) * 3; r < (row / 3 + 1) * 3; r++)
	{
		for (c = (column / 3) * 3; c < (column / 3 + 1) * 3; c++)
		{
			if ((r != row || c != column) && cells[r][c] == cells[row][column])
			{
				return 0;
			}
		}
	}
	return 1;
}

/*
* @brief	打印结果
* @arg		cells	:int[9][9]型，当前整个数独盘面
* @retval	void
*/
void printCells(int cells[9][9])
{
	int r = 0, c = 0;      // r表行，c表列
	for (r = 0; r < 9; r++)
	{
	
		if (!(r%3))        // 画九宫格外边框横线
		{
			printf("———————————————————\n");
		}
		for (c = 0; c < 9; c++)
		{
			if (!(c%3))    // 画九宫格外边框竖线 
			{
				printf("|");
			}
			else           // 画九宫格内边框(空格)
			{
				printf(" ");
			}
			printf("%d", cells[r][c]);
		}
		printf("|\n");
	}
	printf("———————————————————\n");
}

/*
* @brief	暴力搜索，递归
* @arg		r	:int型，表示当前行
* @arg		c	:int型，表示当前列
* @arg		cells	:int[9][9]型，当前整个数独盘面
* @retval	void
*/
void try(int r, int c, int cells[9][9])
{
	int i = 0;
	// 全部确定完，打印答案
	if (9 == r)
	{
		printf("第%d种解法：\n", ++gl_answer_num);
		printCells(cells);
	}
	// 当前值未确定
	else if (0 == cells[r][c])
	{
		for (i = 1; i < 10; i++)
		{
			cells[r][c] = i;
			try(r, c, cells);
		}
		cells[r][c] = 0;
	}
	// 当前值已确定
	else if (!judge(r, c, cells))  // 当前值不符合
	{
		cells[r][c] = 0;
	}
	else if (8 == c)               // 一行到头了
	{
		try(r + 1, 0, cells);
	}
	else
	{
		try(r, c + 1, cells);
	}
}

/*
* @brief	main
* @retval	int
*/
int main(void)
{

	int cells[9][9] = {{0,0,2,  0,7,0,  0,6,8},
					   {0,0,4,  0,0,9,  0,2,0},
					   {1,0,5,  4,2,0,  0,0,7},

					   {0,2,0,  6,0,0,  0,3,9},
					   {0,0,9,  7,0,5,  2,0,0},
					   {5,3,0,  0,0,4,  0,7,0},

					   {6,0,0,  0,4,2,  9,0,3},
					   {0,4,0,  8,0,0,  6,0,0},
					   {2,5,0,  0,6,0,  7,0,0}};
	printf("题目：\n");
	printCells(cells);
	try(0, 0, cells);      // 从cells[0][0]开始试
	printf("\n共%d种解法\n", gl_answer_num);
	return 0;
}
