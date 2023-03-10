#include "Q6functions.h"

/*This function creating a new list node that contains a position*/
chessPosCell* createNewListNode2(chessPos Pos, chessPosCell* next)
{
	chessPosCell* newNode;
	newNode = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkAllocation(newNode, "fail");

	newNode->position[0] = Pos[0];
	newNode->position[1] = Pos[1];
	newNode->next = next;
	return newNode;
}

/*This function getting a file name that contains position in it's shrinked representation, it creating a list that contain those position in it's regular 
un-shrinked representaion*/
int checkAndDisplayPathFromFile(char* fileName)
{
	FILE* file;
	chessPosList filePosList;
	chessPos currCell;
	makeEmptyList(&filePosList);
	if (checkIfFileExist(&file, fileName) == false) /*checking if the file is exists, in case it doesn't, return -1*/
		return -1;

	file = fopen(fileName, "rb");
	checkFileOpen(file, "Fail");
	BYTE curr, pos = 0;
	BYTE read = 0, mask;
	short int numOfPositions, size;
	int i = 0, j, counter = 0, numOrLetter = 0;;
	fread(&numOfPositions, sizeof(short int), 1, file); /*getting the number of position from the file*/
	while (i < numOfPositions) /*while we didn't got all positions*/
	{
		fread(&curr, sizeof(BYTE), 1, file); /*getting a byte*/
		mask = 0x80;  /*defining a mask of "1000 0000" in order to check each bit*/
		for (j = 0; j < BITS_IN_BYTE; j++)
		{
			pos = pos << 1;
			read = (mask & curr);

			if ((read) != 0) /*if the current bit is lightened*/
			{
				pos = (pos | 1); /*then we will light it as well in our pos byte*/
			}

			mask = mask >> 1; /*moving on to check the next bit*/
			counter++;
			if (counter == 3) /*if we read a letter/number*/
			{
				if (numOrLetter == 0) /*if the byte represents a letter*/
				{
					currCell[0] = pos + 'A';
					numOrLetter = 1;
				}
				else
				{
					currCell[1] = pos + '1';  /*if the byte represents a number*/
					numOrLetter = 0;
					insertDataToStartList(&filePosList, currCell); /*we got a location,so we add it to the list*/
					currCell[0] = currCell[1] = NULL;
					i++;
				}
				pos = 0;
				counter = 0;
			}
		}
	}
	fclose(file);
	if (isValid(&filePosList) == false) /*if the list is ilegal then return 1*/
		return 1;

	else
	{
		display(&filePosList);  /*delete locations which appear twice and print the board with the legal locations*/
		size = returnSize(&filePosList); /*checking the new size of the list*/
		if (size == (ROWS*COLS)) /*if the legal knight way covers the board return 2 */
			return 2;
		else
			return 3;
	}
}


/*This function getting a file and checking if the file exist*/
bool checkIfFileExist(FILE* fp, char* name)
{
	if (fp == NULL)
	{
		printf("File %s does not exist\n", name);
		return false; /* if the file doesn't exist, return false*/
	}
	else return true;
}


void insertDataToStartList(chessPosList* lst, chessPos data)//inserting DATA to the start of the list.
{
	chessPosCell* newHead;
	newHead = createNewListNode2(data, NULL);//in order to add data we must first to create a node.
	insertNodeToStartList(lst, newHead);//then, we add the node to the list.
}


/* inserting new NODE to the start of the list.*/
void insertNodeToStartList(chessPosList* lst, chessPosCell* curr)
{
	if ((lst->head == NULL) && (lst->tail == NULL))
	{
		lst->head = lst->tail = curr;
	}
	else
	{
		curr->next = lst->head;
		lst->head = curr;
	}
}


/*This function getting a list of positions of a knight, and checking if the road of the knight in the list is legal*/
bool isValid(chessPosList* list)
{
	chessPosCell* curr, * prev;
	prev = list->head;
	curr = list->head->next;
	while (curr != NULL)
	{

		/*if the position is one down and two to the right from the current position*/
		if (((prev->position[0] + 1) == (curr->position[0])) && (prev->position[1] + 2))
		{
			prev = prev->next;
			curr = curr->next;
		}
		/*if the position is one down and two to the left from the current position*/
		else if (((prev->position[0] + 1) == (curr->position[0])) && (prev->position[1] - 2))
		{
			prev = prev->next;
			curr = curr->next;
		}
		/*if the position is one up and two to the right from the current position*/
		else if (((prev->position[0] - 1) == (curr->position[0])) && (prev->position[1] + 2))
		{
			prev = prev->next;
			curr = curr->next;
		}
		/*if the position is one up and two to the left from the current position*/
		else if (((prev->position[0] - 1) == (curr->position[0])) && (prev->position[1] - 2))
		{
			prev = prev->next;
			curr = curr->next;
		}
		/*if the position is two down and one to the right from the current position*/
		else if (((prev->position[0] + 2) == (curr->position[0])) && (prev->position[1] + 1))
		{
			prev = prev->next;
			curr = curr->next;
		}
		/*if the position is two down and one to the left from the current position*/
		else if (((prev->position[0] + 2) == (curr->position[0])) && (prev->position[1] - 1))
		{
			prev = prev->next;
			curr = curr->next;
		}
		/*if the position is two up and one to the right from the current position*/
		else if (((prev->position[0] - 2) == (curr->position[0])) && (prev->position[1] + 1))
		{
			prev = prev->next;
			curr = curr->next;
		}
		/*if the position is two up and one to the left from the current position*/
		else if (((prev->position[0] - 2) == (curr->position[0])) && (prev->position[1] - 1))
		{
			prev = prev->next;
			curr = curr->next;
		}
		/*if the cell is out of board borders so return false*/
		else if (((curr->position[0] > ROWS) || (curr->position[0] <= 0)) || ((curr->position[1] > COLS) || (curr->position[1] <= 0)))
			return false;
		else  /*if it's not any of those cases than it is not a legal road*/
		{
			return false;
		}
	}
	return true;

}