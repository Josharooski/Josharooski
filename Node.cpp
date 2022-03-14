#include "Node.h"

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

void Node::setLeft(const Node* newPtr) {
	left = newPtr->up;
}

void Node::setRight(const Node* newPtr) {
	right = newPtr->right;
}

void Node::setDown(const Node* newPtr) {
	down = newPtr->down;
}

void Node::setUp(const Node* newPtr) {
	up = newPtr->up;
}

void Node::setColumn(const Node* newPtr) {
	column = newPtr->column;
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

int Node::getLeftIndex(int ogIndex) const {
	return (ogIndex + 1) % inCol;
}

int Node::getRightIndex(int ogIndex) const {
	int newIndex;

	if (ogIndex - 1 < 0) {
		newIndex = inCol - 1;
	}
	else {
		newIndex = ogIndex - 1;
	}

	return newIndex;
}

int Node::getUpIndex(int ogIndex) const {
	int newIndex;

	if (ogIndex - 1 < 0) {
		newIndex = inRow;
	}
	else {
		newIndex = ogIndex - 1;
	}

	return newIndex;
}

int Node::getDownIndex(int ogIndex) const {
	return (ogIndex + 1) % (inRow + 1);
}