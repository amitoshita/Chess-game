#include "Q4functions.h"
#include "MainFunctions.h"


/*This function checking if there is a track from the path it got of the knight possible moves that covers the whole board,
it creating a list of the track and returning it*/
chessPosList findKnightPathCoveringAllBoard(pathTree* path_tree) {

	chessPosList list;
	makeEmptyList(&list);
	int size = -1;
	list = createListAndReturnSize(path_tree->root, &size);

	if (size == (COLS * ROWS)) /*if the knight track covers the whole board*/
		return list;
	else
	{
		freeList(&list);
		makeEmptyList(&list);
		return list;
	}
}


/*This function helping to find a way on the knight that covers the whole board,it is returning a list of the longest road of the knight  */
chessPosList createListAndReturnSize(treeNode* root, int* size)
{
	int maxSize = 0, currSize;
	chessPosList maxList, currList;
	makeEmptyList(&maxList);
	treeNodeListCell* curr;
	if (root == NULL) /*if we reached the end of the current way of the knight return the max list we found so far*/
	{
		makeEmptyList(&maxList);
		*size = 0;
		return maxList;

	}
	else
	{
		curr = root->next_possible_positions;
		while (curr != NULL)
		{
			currList = createListAndReturnSize(curr->node, &currSize);
			if (currSize > maxSize) /*if the current road is longer the the max road we found*/
			{
				maxSize = currSize; /*then update the max road to be the current road*/
				freeList(&maxList); /*free the old max road*/
				maxList = currList;
			}
			else {

				freeList(&currList);
			}
			curr = curr->next;
		}
	}

	insertDataToEndList(&maxList, root->position);  /*insert the node to the max list*/
	maxSize++;

	*size = maxSize;
	return maxList;
}

/*This function getting a list and a list node and inserting the node to the end of the list it got*/
void insertNodeToEndList(chessPosList* lst, chessPosCell* newTail)
{
	if (lst->head == NULL) /*if the list is empty*/
	{
		lst->head = newTail;
		lst->tail = newTail;
	}
	else
	{
		lst->tail->next = newTail;
		lst->tail = newTail;
	}
}

/*This function getting a list of chess positions and a position and inserting the position to the end of the list*/
void insertDataToEndList(chessPosList* lst, chessPos position)
{
	chessPosCell* newTail;
	newTail = createNewListNode(position, NULL);
	insertNodeToEndList(lst, newTail);
}

/*This function creating and returning new tree node that contains the position it got*/
chessPosCell* createNewListNode(chessPos Pos, treeNode* next)
{
	chessPosCell* newNode;
	newNode = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkAllocation(newNode, "fail");

	newNode->position[0] = Pos[0];
	newNode->position[1] = Pos[1];
	newNode->next = next;
	return newNode;
}

/*This function getting a list and updating it to be an empty list*/
void makeEmptyList(chessPosList* list) {

	list->head = list->tail = NULL;
}

