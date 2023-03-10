#ifndef __Q6_FUNCTIONS_H
#define __Q6_FUNCTIONS_H

#include "all_defines.h"
#include "MainFunctions.h"
#include "Q5functions.h"

bool isValid(chessPosList* list);
chessPosCell* createNewListNode2(chessPos Pos, chessPosCell* next);
int checkAndDisplayPathFromFile(char* fileName);
void insertDataToStartList(chessPosList* lst, chessPos data);
bool checkIfFileExist(FILE* fp, char* name);
void insertNodeToStartList(chessPosList* lst, chessPosCell* curr);

#endif