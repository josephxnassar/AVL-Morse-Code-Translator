#include "Node.h"

Node::Node(Data const& newData)
{
	this->mHeight = 1;
	this->mData = newData;
	this->mpLeft = nullptr;
	this->mpRight = nullptr;
}

Node::~Node()
{
	//cout << "Inside Node destructor!" << endl;
}

int Node::getHeight() const
{
	return this->mHeight;
}

Data Node::getData() const
{
	return this->mData;
}

Node* Node::getLeftPtr() const
{
	return this->mpLeft;
}

Node* Node::getRightPtr() const
{
	return this->mpRight;
}

void Node::setHeight(int newHeight)
{
	this->mHeight = newHeight;
}

void Node::setData(Data newData)
{
	this->mData = newData;
}

void Node::setLeftPtr(Node* newLeftPtr)
{
	this->mpLeft = newLeftPtr;
}

void Node::setRightPtr(Node* newRightPtr)
{
	this->mpRight = newRightPtr;
}