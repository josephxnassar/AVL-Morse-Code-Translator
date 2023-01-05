#pragma once

#include "Node.h"

class AVL
{
public:
	AVL(char* filename);
	~AVL();

	void insert(Data const& newData);
	Data search(char newSearch);
	void convert(char* f1, char* f2);
	void print();
	void print2D();
	void destroyTree();

	void printStats();

	Node* getRootPtr() const;
	int getItems() const;
	std::chrono::duration<double> getInsertionTime() const;
	std::chrono::duration<double> getTranslationTime() const;

	void setRootPtr(Node* newRootPtr);
	void setItems(int newItems);
	void setInsertionTime(std::chrono::duration<double> time);
	void setTranslationTime(std::chrono::duration<double> time);
private:
	Node* mpRoot;
	int mItems;
	std::chrono::duration<double> tInsertion;
	std::chrono::duration<double> tTranslation;

	int getHeight(Node* pTree);
	Node* rRotate(Node* pTree);
	Node* lRotate(Node* pTree);
	Node* insert(Node* pTree, Data const& newData);
	Data search(Node* pTree, char newSearch);
	std::string convert(Node* pTree, std::string str);
	void print(Node* pTree);
	void print2D(Node* pTree, int space);
	void destroyTree(Node* pTree);
};