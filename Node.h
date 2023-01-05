#pragma once

#include "Data.h"

class Node
{
public:
	Node(Data const &newData);
	~Node();

	int getHeight() const;
	Data getData() const;
	Node *getLeftPtr() const;
	Node *getRightPtr() const;

	void setHeight(int newHeight);
	void setData(Data newData);
	void setLeftPtr(Node *newLeftPtr);
	void setRightPtr(Node *newRightPtr);
private:
	int mHeight;
	Data mData;
	Node *mpLeft;
	Node *mpRight;
};