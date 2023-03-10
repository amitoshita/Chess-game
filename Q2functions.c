#include "Q2functions.h"

/*Check given list, if there are double cells, it delets them. At the End, it prints the board*/
void display(chessPosList* lst)
{
	chessPos mainBoard[ROWS][COLS];
	bool booleanArr[ROWS][COLS]; /*Boolean array which marks cells that already existed*/
	chessPosCell* curr = lst->head;
	chessPosCell* prev = NULL;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			booleanArr[ROWS][COLS] = false; /*First, we make all cell in the array to "false"*/
		}
	}

	while (curr != NULL) {

		if (booleanArr[curr->position[0] - 'A'][curr->position[1] - '1'] == true) {
			deletDoubleCells(lst, prev);
			curr = prev->next;
		}

		else {
			booleanArr[curr->position[0] - 'A'][curr->position[1]] = true; /*Marks "true" cells that already existed*/
			prev = curr;
			curr = curr->next;
		}

	}
	putNums(mainBoard, lst); 
	printBoard(mainBoard);
	Sleep(6000);
}

/*Function that deletes double cells*/
void deletDoubleCells(chessPosList* list, chessPosCell* prev) {

	if (prev->next == list->tail) {
		deletFromEndList(list, prev);
	}
	else if (prev->next != list->tail)
		deletFromInnerList(prev);
}

/*Deletes cells from the end of list*/
void deletFromEndList(chessPosList* list, chessPosCell* prev) {

	free(prev->next);
	list->tail = prev;
	prev->next = NULL;
}

/*Deletes cells in inner list*/
void deletFromInnerList(chessPosCell* prev) {

	chessPosCell* tempcell = prev->next;

	prev->next = tempcell->next;
	free(tempcell);
}

/*Print the given board*/
void printBoard(chessPos board[][COLS])
{
	int i, j;
	printf("  ");
	for (int i = 1; i <= COLS; i++)
		printf("%4d", i);
	printf("\n");
	for (int i = 0; i < COLS * 7 - 5; i++)
		printf("_");
	printf("\n");
	for (int i = 0; i < ROWS; i++)
	{
		printf("%4c|", i + 'A');
		for (int j = 0; j < COLS; j++)
		{
			printf("%c%c | ", (board[i][j])[0], (board[i][j])[1]);
		}
		printf("\n");
	}
}

/*This function puts the num of index in list in every array's cell*/
void putNums(chessPos board[][COLS], chessPosList* list) {

	chessPosCell* curr = list->head;

	int row, col;
	int index = 1;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			(board[i][j])[0] = ' ';
			(board[i][j])[1] = ' ';
		}
	}
	while (curr)
	{
		row = curr->position[0] - 'A';
		col = curr->position[1] - '1';

		if (index <= 9) {
			(board[row][col])[0] = index + '0';
		}
		else {
			(board[row][col])[0] = (index / 10) + '0';
			(board[row][col])[1] = (index % 10) + '0';

		}

		index++;
		curr = curr->next;
	}
}