#ifndef __Q1_FUNCTIONS_H
#define __Q1_FUNCTIONS_H

#include "all_defines.h"
#include "MainFunctions.h"

chessPosArray*** validKnightMoves();
void insertPosToValidMoves(chessPos* position, int i, int row, int col);
void freeKnightMovesArr(chessPosArray*** arr);

#endif