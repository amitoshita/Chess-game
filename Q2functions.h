#ifndef __Q2_FUNCTIONS_H
#define __Q2_FUNCTIONS_H

#include "all_defines.h"
#include "MainFunctions.h"

void display(chessPosList* lst);
void deletDoubleCells(chessPosList* list, chessPosCell* prev);
void deletFromEndList(chessPosList* list, chessPosCell* prev);
void deletFromInnerList(chessPosCell* prev);
void putNums(chessPos board[][COLS], chessPosList* list);
void printBoard(chessPos board[][COLS]);

#endif