#ifndef __Q4_FUNCTIONS_H
#define __Q4_FUNCTIONS_H

#include "all_defines.h"
#include "MainFunctions.h"

chessPosList findKnightPathCoveringAllBoard(pathTree* path_tree);
chessPosList createListAndReturnSize(treeNode* root, int* size);
chessPosCell* createNewListNode(chessPos Pos, treeNode* next);
void makeEmptyList(chessPosList* list);
void insertNodeToEndList(chessPosList* lst, chessPosCell* newTail);
void insertDataToEndList(chessPosList* lst, chessPos position);

#endif