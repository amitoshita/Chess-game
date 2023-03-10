#include "MainFunctions.h"

/*Print the chess menu*/
void print_menu()
{
	printf("~ Please choose: ~\n\n");
	printf("1. Enter a knight's starting position\n\n");
	printf("2. Create all possible knight paths\n\n");
	printf("3. Find a knight path covering all board\n\n");
	printf("4. Save knight path covering all board\n\n");
	printf("5. Load and display path from file\n\n");
	printf("6. Exit\n");
}

/*The actions of the menu*/
void casesToChoose() {

	int UserChoice;
	bool insertPos = false, EXIT = false, treeBuild = false, listBuild = false;
	pathTree tree;
	chessPosList list;
	chessPos position;
	while (!EXIT) {
		system("cls");
		print_menu();
		scanf("%d", &UserChoice);
		checkUserChoice(&UserChoice);
		if (UserChoice == 1) {
			getPosFromUser(position);
			insertPos = true;
		}
		if (UserChoice == 2) {
			if (insertPos == true) {
				checkIfTreeBuilt(&treeBuild, &position, &tree);
			}
		}
		if (UserChoice == 3) {
			if (insertPos == true) {
				checkIfListAndTreeBuilt(&treeBuild, &listBuild, &list, &position, &tree);
			}
		}
		if (UserChoice == 4) {
			if (insertPos == true) {
				checkIfListAndTreeBuilt(&treeBuild, &listBuild, &list, &position, &tree);
				saveListToBinFileHelper(&list);
			}
		}
		if (UserChoice == 5){
			if (insertPos == true) {
				checkIfListAndTreeBuilt(&treeBuild, &listBuild, &list, position, &tree);
				readAlistFromBinFile();
			}
		}
		if (UserChoice == 6) {
			EXIT = true;
		}
	}
	ClearTree(&tree); /*Free tree*/
	freeList(&list);/*Free list*/
}

/*Get position from the user and check it's validity*/
void getPosFromUser(chessPos position) {

	system("cls");
	bool right = false;
	position[0] = position[1] = NULL;
	printf("Please Enter Position:\n\n");
	while (right == false) {
		getchar();
		scanf("%c", &(position)[0]);
		scanf("%c", &(position)[1]);
		if ((position[0] >= 'A' && position[0] <= 'H') && (position[1] >= '1' && position[1] <= '8'))
		{
			right = true;
		}
		else {
			printf("Invalid position. Please insert a valid position again.\n");
		}
	}
	
}

/*Check memory allocation*/
void checkAllocation(void* arr, char* msg)
{
	if (!arr)
	{
		fprintf(stderr, "Allocation failure: %s\n", msg);
		exit(1);
	}
}


/*This function check if the tree was already built, and if not- function builds it*/
void checkIfTreeBuilt(bool* buildTree, chessPos* position, pathTree* tree) {

	if (*buildTree == false) {
		*tree = findAllPossibleKnightPaths(position);
		*buildTree = true;
	}
}

/*This function check if the list was already created, and if not- function creates it*/
void checkIfListBuilt(bool* listBuilt, pathTree* tree, chessPosList* list) {

	if (*listBuilt == false)
	{
		*list = findKnightPathCoveringAllBoard(tree);
		*listBuilt = true;
	}
}

/*The function that operates the functions from Q5*/
void readAlistFromBinFile() {

	char fileName[100];
	int checkListFromFile;
	printf("Please enter a name of file.\n");
	getchar();
	scanf("%s", fileName);
	checkListFromFile = checkAndDisplayPathFromFile(fileName);
	printf("%d", checkListFromFile);

}

/*This function check user's menu choice and requests a valid choice */
void checkUserChoice(int *userChoice) {

	bool check = false;
	if ((*userChoice < 1) || (*userChoice > 6)) {
		while (check == false) {
			printf("Please Enter a valid choice from menu\n\n");
			scanf("%d", userChoice);
			if ((*userChoice >= 1) && (*userChoice <= 6)){
				check = true;
		}
		}
	}
}

/*This function operates the function from Q6*/
void saveListToBinFileHelper(chessPosList* list) {

	char fileName[100];
	printf("Please enter a name of file.\n");
	getchar();
	scanf("%s", fileName);
	if (list->head != NULL) {
		saveListToBinFile(fileName, list);
	}
}

/*Helper function that operates the listCheck and treeCheck functions.*/
void checkIfListAndTreeBuilt(bool* treeBuild, bool* listBuild, chessPosList* list, 
	chessPos* position, pathTree* tree) {
	checkIfTreeBuilt(treeBuild, position, tree);
	checkIfListBuilt(listBuild, tree, list);
}

/*Free the list*/
void freeList(chessPosList* lst)
{
	chessPosCell* curr;
	chessPosCell* temp;
	curr = lst->head;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
}

/*Check if file opened or not, if not- returns a messege.*/
void checkFileOpen(FILE* fp, char* msg)
{
	if (!fp)
	{
		fprintf(stderr, "Error opening file: %s\n", msg);
		exit(FILE_OPENING_ERROR);
	}
}


