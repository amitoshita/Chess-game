#ifndef __MAINFUNCTIONS_H
#define __MAINFUNCTIONS_H
#include "all_defines.h"
#include "Q1functions.h"
#include "Q2functions.h"
#include "Q3functions.h"
#include "Q4functions.h"
#include "Q5functions.h"
#include "Q6functions.h"

void print_menu();
void getPosFromUser(chessPos position);
void casesToChoose();
void checkAllocation(void* arr, char* msg);
void freeList(chessPosList* lst);
void checkFileOpen(FILE* fp, char* msg);
void checkIfTreeBuilt(bool* buildTree, chessPos* position, pathTree* tree);
void checkIfListBuilt(bool* listBuilt, pathTree* tree, chessPosList* list);
void checkUserChoice(int userChoice);
void checkIfListAndTreeBuilt(bool* treeBuild, bool* listBuild, chessPosList* list,
	chessPos* position, pathTree* tree);
void saveListToBinFileHelper(chessPosList* list);
void readAlistFromBinFile();

#endif