#include <iostream>
#include "Node.h"

const int NUM_ROWS = 8;
const int NUM_COLS = 8;

void createBoolTable(bool boolTable[][NUM_COLS]);
void create_DLX_Matrix(bool boolTable[][NUM_COLS], Node Table[][NUM_COLS], Node* headPtr);
void printBoolTable(bool boolTable[][NUM_COLS]);
void printTable(Node Table[][NUM_COLS], Node* headPtr);

int main() {
	Node* headPtr = new Node();
	bool(*boolTable)[NUM_COLS] = new bool[NUM_ROWS][NUM_COLS];
	Node(*Table)[NUM_COLS] = new Node[NUM_ROWS][NUM_COLS];

	createBoolTable(boolTable);
	create_DLX_Matrix(boolTable, Table, headPtr);

	printBoolTable(boolTable);
	std::cout << std::endl;
	printTable(Table, headPtr);
}

void createBoolTable(bool boolTable[][NUM_COLS]) {
	for (int row = 0; row <= NUM_ROWS; row++) {
		for (int col = 0; col < NUM_COLS; col++) {
			if (row == 0) {
				boolTable[row][col] = true;
			}
			else {
				boolTable[row][col] = false;
			}
		}
	}

	boolTable[1][0] = true;
	boolTable[1][3] = true;
	boolTable[1][6] = true;
	boolTable[2][0] = true;
	boolTable[2][3] = true;
	boolTable[3][3] = true;
	boolTable[3][4] = true;
	boolTable[3][6] = true;
	boolTable[4][2] = true;
	boolTable[4][4] = true;
	boolTable[4][5] = true;
	boolTable[5][1] = true;
	boolTable[5][2] = true;
	boolTable[5][5] = true;
	boolTable[5][6] = true;
	boolTable[6][1] = true;
	boolTable[6][6] = true;
	boolTable[7][0] = true;
	boolTable[7][3] = true;
}

void create_DLX_Matrix(bool boolTable[][NUM_COLS], Node Table[][NUM_COLS], Node* headPtr) {

	for (int row = 0; row <= NUM_ROWS; row++) {
		for (int col = 0; col < NUM_COLS; col++) {
			if (boolTable[row][col]) {
				if (row) {
					Table[0][col].numNodes++;
				}
				
				Table[row][col].setColumn(&Table[0][col]);
				Table[row][col].inRow = row;
				Table[row][col].inCol = col;

				int rowCheck = row;
				int colCheck = col;
				while (!boolTable[rowCheck][colCheck] && colCheck != col) {
					colCheck = Table[row][colCheck].getLeftIndex(colCheck);
				}
				Table[row][col].setLeft(&Table[row][colCheck]);

				rowCheck = row;
				colCheck = col;
				while (!boolTable[rowCheck][colCheck] && colCheck != col) {
					colCheck = Table[row][colCheck].getRightIndex(colCheck);
				}
				Table[row][col].setRight(&Table[row][colCheck]);

				rowCheck = row;
				colCheck = col;
				while (!boolTable[rowCheck][colCheck] && rowCheck != row) {
					rowCheck = Table[rowCheck][col].getUpIndex(rowCheck);
				}
				Table[row][col].setUp(&Table[rowCheck][col]);

				rowCheck = row;
				colCheck = col;
				while (!boolTable[rowCheck][colCheck] && rowCheck != row) {
					rowCheck = Table[rowCheck][col].getDownIndex(rowCheck);
				}
				Table[row][col].setDown(&Table[rowCheck][col]);
			}
		}
	}

	headPtr->setRight(&Table[0][0]);
	headPtr->setLeft(&Table[0][NUM_COLS - 1]);

	Table[0][0].setLeft(headPtr);
	Table[0][NUM_COLS - 1].setRight(headPtr);
}

void printBoolTable(bool boolTable[][NUM_COLS]) {
	std::cout << "Bool Table:" << std::endl;
	for (int row = 0; row <= NUM_ROWS; row++) {
		for (int col = 0; col < NUM_COLS; col++) {
			if (boolTable[row][col]) {
				std::cout << "1 ";
			}
			else {
				std::cout << "0 ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void printTable(Node Table[][NUM_COLS], Node* headPtr) {
	std::cout << "Node Coordinates: " << std::endl;

	Node* rowPtr;
	Node* colPtr;
	rowPtr = headPtr->getRight();
	colPtr = rowPtr->getDown();

	while (rowPtr != headPtr) {
		while (colPtr != &Table[rowPtr->inRow][0]) {
			std::cout << '[' << colPtr->inRow << ',';
			std::cout << colPtr->inCol << "] ";
			colPtr = colPtr->getDown();
		}
		std::cout << std::endl;
		rowPtr = rowPtr->getRight();
	}
	std::cout << std::endl;
}
