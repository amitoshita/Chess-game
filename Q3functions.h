#ifndef __Q3_FUNCTIONS_H
#define __Q3_FUNCTIONS_H

#include "all_defines.h"
#include "Q1functions.h"
#include "MainFunctions.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* findAllPossibleHelper(chessPos* startingPosition, chessPosArray*** res, bool existPos[][COLS]);
treeNode* createNewNode(chessPos* position);
void insertNodeToStartTreeList(treeNode* temp, treeNode* root);
treeNodeListCell* createListCell(treeNode* temp);
void ClearTreeAux(treeNode* root);
void ClearTree(pathTree* tree);


#endif