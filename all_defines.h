#ifndef __DEFINEFUNCTIONS_H
#define __DEFINEFUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
#define FILE_OPENING_ERROR -1
#define BITS_IN_BYTE	8
#define ROWS 5
#define COLS 5

typedef unsigned char BYTE;
typedef char chessPos[2];
typedef struct _treeNodeListCell treeNodeListCell;
typedef struct _treeNode treeNode;

typedef struct _chessPosCell
{
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {

	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;

typedef struct _chessPosArray
{
	unsigned int size;
	chessPos* positions;
} chessPosArray;


typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;


typedef struct _pathTree {
	treeNode* root;
}pathTree;

#endif