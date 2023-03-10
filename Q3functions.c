#include "Q3functions.h"


/*This function getting the position where the knight currently stands and creating and returning a tree that it's root is the knight strting position,
 and every tree node kids contain it's possible next positions*/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition) {

	chessPosArray*** res;
	pathTree tree;
	bool existPos[ROWS][COLS];
	res = validKnightMoves();
	checkAllocation(res, "fail in Q3");
	/*creating a boolean array of positions , and Initiates every cell to false */
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
			existPos[i][j] = false;
	}


	tree.root = findAllPossibleHelper(startingPosition, res, existPos);
	freeKnightMovesArr(res);
	return tree;
}


/*This function helping us to build the tree of the possible knight positions it can go from it's starting position*/
treeNode* findAllPossibleHelper(chessPos* startingPosition, chessPosArray*** res, bool existPos[][COLS]) {

	treeNode* root, * temp;
	int i = (startingPosition[0][0] - 'A');
	int j = (startingPosition[0][1] - '1');
	int m, row, col;
	int n = 0;
	int size;
	int count = 0;

	for ((res[i][j])->positions[n]; n < (res[i][j])->size; n++)
	{ /*if we have been at that position that count it*/
		if (existPos[res[i][j]->positions[n][0] - 'A'][res[i][j]->positions[n][1] - '1'] == true) {
			count++;
		}
	}
	/*if we have been at all the possible positions we finished to build the tree, return the current root*/
	if (count == (res[i][j])->size) {
		root = createNewNode(startingPosition);
		return root;
	}

	else {
		/*else, create list node that contains that position*/
		root = createNewNode(startingPosition);

		/*update that position in the boolean arr to be true, because now we are at that position (in order to prevent a situation of the knight going in circles*/
		existPos[i][j] = true;

		size = (res[i][j])->size; /*the number of the current tree node kids is the number of the next possible position from that position*/
		for (m = 0; m < size; m++)
		{
			row = res[i][j]->positions[m][0] - 'A';
			col = res[i][j]->positions[m][1] - '1';
			if (existPos[row][col] == false) /*if we haven't been at that position*/
			{
				temp = findAllPossibleHelper(res[i][j]->positions[m], res, existPos); /*then we need to add it to the tree as well*/
				insertNodeToStartTreeList(temp, root);/*insert the kid to the list of the tree*/
			}
		}

		existPos[i][j] = false;/*after we finished that path, update the position to be false for another path of the tree*/
	}
	return root;
}


/*This function creating new tree node and returning it*/
treeNode* createNewNode(chessPos* position) {

	treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
	checkAllocation(newNode, "fail in cell allocate");
	newNode->position[0] = position[0][0];
	newNode->position[1] = position[0][1];

	newNode->next_possible_positions = NULL;
	return newNode;

}

/*This function inserting a tree node it got to another tree node list it got*/
void insertNodeToStartTreeList(treeNode* temp, treeNode* root) {

	treeNodeListCell* cell = createListCell(temp); /*creating new list node*/

	if (root->next_possible_positions == NULL) /*if the root is the tail*/
	{

		root->next_possible_positions = cell;
		cell->next = NULL;
	}
	else {
		cell->next = root->next_possible_positions;
		root->next_possible_positions = cell;
	}

}

/*This function creating and returning new list cell that in a tree node*/
treeNodeListCell* createListCell(treeNode* temp) {

	treeNodeListCell* cell;
	cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	checkAllocation(cell, "fail in cell allocation");
	cell->node = temp;
	cell->next = NULL;

	return cell;
}

/*this function clear the tree byy free every tree node*/
void ClearTree(pathTree* tree)
{
	if (tree->root) /*if the node is not null*/
	{
		ClearTreeAux(tree->root);
		tree->root = NULL;
	}
}

/*This function helping to clear the tree*/
void ClearTreeAux(treeNode* root)
{
	treeNodeListCell* curr;
	if (root) {
		curr = root->next_possible_positions;
		while (curr != NULL) {
			ClearTreeAux(curr->node);
			curr = curr->next;
		}
	}
	free(root);
}