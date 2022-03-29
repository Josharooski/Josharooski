#ifndef NODE_
#define NODE_

class Node {
private:
	Node* left;
	Node* right;
	Node* up;
	Node* down;
	Node* column;
public:
	int numNodes, inRow, inCol;

	Node();
	Node(const Node& copyMe);
	~Node();

	//Mutators

	void setLeft(Node* newPtr);
	void setRight(Node* newPtr);
	void setUp(Node* newPtr);
	void setDown(Node* newPtr);
	void setColumn(Node* newPtr);

	//Acessors

	Node* getLeft() const;
	Node* getRight() const;
	Node* getUp() const;
	Node* getDown() const;
	Node* getColumn() const;

	int getLeftIndex(int ogIndex) const;
	int getRightIndex(int ogIndex) const;
	int getUpIndex(int ogIndex) const;
	int getDownIndex(int ogIndex) const;
};

#endif