#include "Q5functions.h"


/*This function getting a binary file name and a list of position , it inserting the position to the file in a way that each position represented by 6 bits ,
3 for the row and 3 for the column*/
void saveListToBinFile(char* fileName, chessPosList* pos_list) {

	FILE* file = fopen(fileName, "wb+");
	checkFileOpen(file, "Cant open file in option 4");
	BYTE write = 0;
	chessPosCell* curr = pos_list->head;
	short int size = returnSize(pos_list); /*getting the number of positions the list contains*/
	unsigned char letter, num;
	fwrite(&size, sizeof(short int), 1, file); /*writing the number of the positions we got*/
	BYTE mask;
	int counter = 0;


	while (curr != NULL)  /*while we didn't reach the end of the list*/
	{

		letter = curr->position[0] - 'A';
		num = curr->position[1] - '1';
		mask = 4;
		insertLetterToBYTE(letter, &write, &counter, file); /*shrinking the binary represtation of the letter to 3 bits*/
		mask = 4;
		insertNumToBYTE(num, &write, &counter, file); /*shrinking the binary represtation of the number to 3 bits*/
		curr = curr->next;
	}
	if (counter != 0)
	{
		write = write << (8 - counter); /*move the bits to the left*/
		fwrite(&write, sizeof(BYTE), 1, file); /*writing the BYTE in the file*/
	}
	fclose(file);

}


/*This function counts and returning the number of position there are in the chessPos list it got*/
short int returnSize(chessPosList* pos_list) {

	chessPosCell* curr = pos_list->head;
	short int counter = 0;
	while (curr) {
		counter++;
		curr = curr->next;
	}
	return counter;
}

/*This function getting a letter and shrinking it to binary representaion of 3 bits*/
void insertLetterToBYTE(unsigned char letter, BYTE* write, int* counter, FILE* file) {
	int i;
	BYTE mask = 4;
	for (i = 0; i < 3; i++)
	{
		*write = *write << 1; /*move write 1 to the left in order to put our new bit in the right place*/
		if ((letter & mask) != 0) /*if the bit we got is 1 */
		{
			*write = *write | 1; /*than light the right place of write*/
		}
		mask = mask >> 1; /*moving on to check the next bit*/
		counter++;
		if (counter == BITS_IN_BYTE) /*if we reached to 8 bits*/
		{
			fwrite(&write, sizeof(BYTE), 1, file); /*then write it in the file*/
			fflush(file);
			*write = 0; /*creating new byte*/
			*counter = 0;
		}
	}
}

/*This function getting a number and shrinking it to binary representaion of 3 bits*/
void insertNumToBYTE(unsigned char num, BYTE* write, int* counter, FILE* file) {

	int i;
	BYTE mask = 4;
	for (i = 0; i < 3; i++) {
		*write = *write << 1;  /*move write 1 to the left in order to put our new bit in the right place*/
		if ((num & mask) != 0) /*if the bit we got is 1 */
		{
			*write = *write | 1;   /*than light the right place of write*/
		}
		mask = mask >> 1;   /*moving on to check the next bit*/
		counter++;
		if (counter == BITS_IN_BYTE)   /*if we reached to 8 bits*/
		{
			fwrite(&write, sizeof(BYTE), 1, file); /*then write it in the file*/
			fflush(file);
			*write = 0;  /*creating new byte*/
			*counter = 0;
		}
	}
}