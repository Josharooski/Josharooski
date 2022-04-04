#include <iostream>
#include <random> //for RNG engine/distribution
#include "Node.h"

const int ROWS = 8;
const int COLS = 8;
const int STARTER_COL = 0;
const double RANDOM_SD = 20.0; //Standard deviation for RNG
const double RANDOM_MEAN = 49.5; //Mean for RNG

std::mt19937 engine(std::random_device{}());
std::normal_distribution<double> norm(RANDOM_MEAN, RANDOM_SD);

void createBoolTable(bool boolTable[][COLS]);
void create_DLX_Matrix(bool boolTable[][COLS], Node Table[][COLS], Node*& headPtr);
void printBoolTable(bool boolTable[][COLS]);
void printTable(Node Table[][COLS], Node* headPtr);
void searchForExC(Node Table[][COLS], Node* headPtr, int currentColumn);
void cover(Node Table[][COLS], Node* headPtr, Node* coverMe);
void uncover(Node Table[][COLS], Node* headPtr, Node* uncoverMe);
Node* lowestNumNodes(Node Table[][COLS], Node* headPtr);



int main() {
	Node* headPtr = new Node();
	bool(*boolTable)[COLS] = new bool[ROWS][COLS];
	Node(*Table)[COLS] = new Node[ROWS][COLS];

	createBoolTable(boolTable);
	printBoolTable(boolTable);
	create_DLX_Matrix(boolTable, Table, headPtr);

	std::cout << std::endl;
	printTable(Table, headPtr);

	searchForExC(Table, headPtr, STARTER_COL);
}



void createBoolTable(bool boolTable[][COLS]) {
	bool hasValue = false;

	for (int row = 0; row <= ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			if (row == 0) {
				boolTable[row][col] = true;
			}
			else {
				int num = norm(engine);
				if (num < 0) {
					num *= -1;
				}
				if(num > 33){
					boolTable[row][col] = false;
				}
				else {
					boolTable[row][col] = true;
					hasValue = true;
				}
			}
		}
	}
}



void create_DLX_Matrix(bool boolTable[][COLS], Node Table[][COLS], Node*& headPtr) {

	for (int row = 0; row <= ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			if (boolTable[row][col]) {
				if (row) {
					Table[0][col].numNodes++;
				}
				
				Table[row][col].setColumn(&Table[0][col]);
				Table[row][col].inRow = row;
				Table[row][col].inCol = col;

				int rowCheck = row;
				int colCheck = col;
				do {
					colCheck = Table[row][colCheck].getLeftIndex(colCheck);
				} while (!boolTable[rowCheck][colCheck] && colCheck != col);
				Table[row][col].setLeft(&Table[row][colCheck]);

				rowCheck = row;
				colCheck = col;
				do {
					colCheck = Table[row][colCheck].getRightIndex(colCheck);
				} while (!boolTable[rowCheck][colCheck] && colCheck != col);
				Table[row][col].setRight(&Table[row][colCheck]);

				rowCheck = row;
				colCheck = col;
				do {
					rowCheck = Table[rowCheck][col].getUpIndex(rowCheck);
				} while (!boolTable[rowCheck][colCheck] && rowCheck != row);
				Table[row][col].setUp(&Table[rowCheck][col]);

				rowCheck = row;
				colCheck = col;
				do {
					rowCheck = Table[rowCheck][col].getDownIndex(rowCheck);
				} while (!boolTable[rowCheck][colCheck] && rowCheck != row);
				Table[row][col].setDown(&Table[rowCheck][col]);
			}
		}
	}

	headPtr->setRight(&Table[0][0]);
	headPtr->setLeft(&Table[0][COLS - 1]);

	Table[0][0].setLeft(headPtr);
	Table[0][COLS - 1].setRight(headPtr);

	Node* zeroCheck = headPtr->getRight();
	while(zeroCheck != headPtr) {
		if(zeroCheck->numNodes == 0) {
			int randRowIndex = norm(engine);
			randRowIndex = (randRowIndex % COLS) + COLS;
			Table[randRowIndex][zeroCheck->inCol];
			while()
		}
		zeroCheck = zeroCheck->getRight();
	}
}



void printBoolTable(bool boolTable[][COLS]) {
	std::cout << "Bool Table:" << std::endl;
	for (int row = 0; row <= ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
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



void printTable(Node Table[][COLS], Node* headPtr) {
	std::cout << "Node Coordinates: " << std::endl;

	Node* rowPtr;
	Node* colPtr;
	Node* ptrInPlace;
	rowPtr = headPtr->getRight();
	colPtr = rowPtr->getDown();
	ptrInPlace = rowPtr;

	do { 
		do {
			if(colPtr->inRow){
				std::cout << '[' << colPtr->inCol + 1 << ',';
				std::cout << colPtr->inRow << "] ";
			}
			colPtr = colPtr->getDown();
		} while (colPtr != ptrInPlace);
		std::cout << std::endl;
		rowPtr = rowPtr->getRight();
		colPtr = rowPtr->getDown();
		ptrInPlace = rowPtr;
	} while (rowPtr != headPtr);
	std::cout << std::endl;

	rowPtr = nullptr;
	colPtr = nullptr;
	ptrInPlace = nullptr;
}



void searchForExC(Node Table[][COLS], Node* headPtr, int currentColumn) {
	Node* col = nullptr;
	Node* downCheck = nullptr;
	Node* rightCheck = nullptr;
	Node* obj = nullptr;

	if(headPtr->getLeft() == headPtr){
		std::cout << "All done?" << std::endl;
	}
	else{
		col = lowestNumNodes(Table, headPtr);
		cover(Table, headPtr, col);
		downCheck = col->getDown();
		while(downCheck != col){
			obj = downCheck;

			while(rightCheck != downCheck){
				cover(Table, headPtr, rightCheck->getColumn());
				rightCheck = rightCheck->getRight();
			}

			//REMOVE
			printTable(Table, headPtr);
			//
			searchForExC(Table, headPtr, currentColumn + 1);

			downCheck = obj;
			col = downCheck->getColumn();
			while(rightCheck != downCheck){
				uncover(Table, headPtr, rightCheck->getLeft());
			}
			downCheck = downCheck->getDown();
		}
		uncover(Table, headPtr, col);
	}
}



void cover(Node Table[][COLS], Node* headPtr, Node* coverMe) {
	Node* downPtr = nullptr;
	Node* rightPtr = nullptr;
	downPtr = coverMe->getDown();
	rightPtr = downPtr->getRight();

	*coverMe->getRight()->getLeft() = *coverMe->getLeft();
	*coverMe->getLeft()->getRight() = *coverMe->getRight();
	while(downPtr != coverMe){
		while(rightPtr != downPtr){
			*rightPtr->getDown()->getUp() = *rightPtr->getUp();
			*rightPtr->getUp()->getDown() = *rightPtr->getDown();
			rightPtr->getColumn()->numNodes--;
			rightPtr = rightPtr->getRight();
		}
		downPtr = downPtr->getDown();
	}
}



void uncover(Node Table[][COLS], Node* headPtr, Node* uncoverMe) {
	Node* upPtr = nullptr;
	Node* leftPtr = nullptr;
	upPtr = uncoverMe->getUp();
	leftPtr = upPtr->getLeft();

	while(upPtr != uncoverMe){
		while(leftPtr != upPtr){
			leftPtr->getColumn()->numNodes++;
			*leftPtr->getDown()->getUp() = *leftPtr;
			*leftPtr->getUp()->getDown() = *leftPtr;
			leftPtr = leftPtr->getLeft();
		}
		upPtr = upPtr->getUp();
	}
	*uncoverMe->getRight()->getLeft() = *uncoverMe;
	*uncoverMe->getLeft()->getRight() = *uncoverMe;
}



Node* lowestNumNodes(Node Table[][COLS], Node* headPtr) {
	int tracker = headPtr->getRight()->numNodes;
	Node* ptr = headPtr->getRight();
	Node* returnPtr = ptr;

	while(ptr != headPtr){
		if(tracker > ptr->numNodes){
			tracker = ptr->numNodes;
			returnPtr = ptr;
		}
		ptr = ptr->getRight();
	}
	returnPtr = ptr;

	return returnPtr;
}