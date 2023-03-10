#ifndef __Q5_FUNCTIONS_H
#define __Q5_FUNCTIONS_H

#include "all_defines.h"
#include "MainFunctions.h"


void saveListToBinFile(char* fileName, chessPosList* pos_list);
short int returnSize(chessPosList* pos_list);
void insertNumToBYTE(unsigned char num, BYTE* write, int* counter, FILE* file);
void insertLetterToBYTE(unsigned char letter, BYTE* write, int* counter, FILE* file);

#endif