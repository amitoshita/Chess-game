#include "Q1functions.h"


/*This function creating and returning an array of possible locations that the knight can move to*/
chessPosArray*** validKnightMoves()
{
	chessPosArray*** res;
	int col, row, i, j, currSize;

	res = (chessPosArray***)malloc(sizeof(chessPosArray**) * ROWS);/*allocting the pointers array*/
	checkAllocation(res, "res");

	for (col = 0; col < ROWS; col++)
	{
		res[col] = (chessPosArray**)malloc(sizeof(chessPosArray*) * COLS);
		checkAllocation(res[col], "res[col]");
	}

	for (row = 0; row < ROWS; row++)
		for (col = 0; col < COLS; col++)
		{
			chessPosArray* validKnightMoves;
			validKnightMoves = (chessPosArray*)malloc(sizeof(chessPosArray));
			checkAllocation(validKnightMoves, "validKnightMoves");
			validKnightMoves->size = 8; /*the maximum number of locations the knight can go to*/
			validKnightMoves->positions = (chessPos*)malloc((validKnightMoves->size) * sizeof(chessPos));
			checkAllocation(validKnightMoves->positions, "validKnightMovesPos");
			currSize = 0;


			/*2 steps left and one down loation*/
			i = row + 1; j = col - 2;
			if (i >= 0 && i < ROWS && j >= 0 && j < COLS)
			{
				insertPosToValidMoves(validKnightMoves->positions, currSize, i, j);
				currSize++;
			}

			/*two steps down and 1 step left/ one step right*/
			i = row + 2;
			for (j = col - 1; j <= col + 1; j = j + 2)
				if (i >= 0 && i < ROWS && j >= 0 && j < COLS)
				{
					insertPosToValidMoves(validKnightMoves->positions, currSize, i, j);
					currSize++;
				}

			/*two steps right and one step up/down*/
			j = col + 2;
			for (i = row + 1; i >= row - 1; i = i - 2)
				if (i >= 0 && i < ROWS && j >= 0 && j < COLS)
				{
					insertPosToValidMoves(validKnightMoves->positions, currSize, i, j);
					currSize++;
				}

			/*two steps up and one step left/right*/
			i = row - 2;
			for (j = col + 1; j >= col - 1; j = j - 2)
				if (i >= 0 && i < ROWS && j >= 0 && j < COLS)
				{
					insertPosToValidMoves(validKnightMoves->positions, currSize, i, j);
					currSize++;
				}

			/*one step up two steps left*/
			i = row - 1; j = col - 2;
			if (i >= 0 && i < ROWS && j >= 0 && j < COLS)
			{
				insertPosToValidMoves(validKnightMoves->positions, currSize, i, j);
				currSize++;
			}

			validKnightMoves->positions = (chessPos*)realloc(validKnightMoves->positions, currSize * sizeof(chessPos)); /*reallocating the arr to it's new size*/
			checkAllocation(validKnightMoves->positions, "realloc of validKnightMoves");
			validKnightMoves->size = currSize; /*updating the size to the real size, we counted each step*/

			res[row][col] = validKnightMoves;
		}

	return res;
}

/*This function inserting the position it got (row,col) to the array of the positions*/
void insertPosToValidMoves(chessPos* position, int i, int row, int col)
{
	position[i][0] = 'A' + row; /*inserting row*/
	position[i][1] = '1' + col;/*inserting col*/
}

/*This function free the array we of the possible knight moves we created */
void freeKnightMovesArr(chessPosArray*** arr)
{
	int i, j, k;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			free(arr[i][j]->positions); /*free the position */
			free(arr[i][j]); /*free the cell that held the position*/
		}
	}

	for (i = 0; i < ROWS; i++)
	{
		free(arr[i]);
	}

	free(arr);
}

