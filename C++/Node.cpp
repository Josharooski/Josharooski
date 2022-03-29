#include "Node.h"

const int ROWS = 8;
const int COLS = 8;

Node::Node() {
	left = nullptr;
	right = nullptr;
	up = nullptr;
	down = nullptr;
	column = nullptr;
	numNodes = 0;
	inRow = 0;
	inCol = 0;
}

Node::Node(const Node& copyMe) {
	left = copyMe.left;
	right = copyMe.right;
	up = copyMe.up;
	down = copyMe.down;
	column = copyMe.column;
	numNodes = copyMe.numNodes;
	inRow = copyMe.inRow;
	inCol = copyMe.inCol;
}

Node::~Node() {
	delete left;
	delete right;
	delete up;
	delete down;
	delete column;
	left = nullptr;
	right = nullptr;
	up = nullptr;
	down = nullptr;
	column = nullptr;
}

void Node::setLeft(Node* newPtr) {
	left = newPtr;
}

void Node::setRight(Node* newPtr) {
	right = newPtr;
}

void Node::setDown(Node* newPtr) {
	down = newPtr;
}

void Node::setUp(Node* newPtr) {
	up = newPtr;
}

void Node::setColumn(Node* newPtr) {
	column = newPtr;
}

Node* Node::getLeft() const {
	return left;
}

Node* Node::getRight() const {
	return right;
}

Node* Node::getUp() const {
	return up;
}

Node* Node::getDown() const {
	return down;
}

Node* Node::getColumn() const {
	return column;
}

int Node::getRightIndex(int ogIndex) const{
	return (ogIndex + 1) % COLS;
}

int Node::getLeftIndex(int ogIndex) const{
	int newIndex;

	if (ogIndex - 1 < 0) {
		newIndex = COLS - 1;
	}
	else {
		newIndex = ogIndex - 1;
	}

	return newIndex;
}

int Node::getUpIndex(int ogIndex) const {
	int newIndex;

	if (ogIndex - 1 < 0) {
		newIndex = ROWS;
	}
	else {
		newIndex = ogIndex - 1;
	}

	return newIndex;
}

int Node::getDownIndex(int ogIndex) const {
	return (ogIndex + 1) % (ROWS + 1);
}