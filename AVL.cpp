#include "AVL.h"

std::ostream& operator<<(std::ostream& lhs, Data const& rhs)
{
	lhs << "Character: " << rhs.getCharacter() << " Morse Code : " << rhs.getString() << std::endl;
	return lhs;
}

/*** CONSTRUCTOR ***/

AVL::AVL(char* filename)
{
	this->mpRoot = nullptr;

	std::ifstream input;

	auto start = std::chrono::high_resolution_clock::now();

	input.open(filename); // couldn't find translations for ~ } | { ` ^ ] \ [ > < * # so I made them up

	while (!input.eof())
	{
		char line[20];
		input.getline(line, 20);

		char c = *strtok(line, "\t");

		this->insert(Data(c, strtok(nullptr, "\n"))); // can't do strtok's in this line cuz of reading violation
		this->setItems(this->getItems() + 1);
	}

	input.close();

	auto end = std::chrono::high_resolution_clock::now();

	this->setInsertionTime(end - start);
}

/*** DECONSTRUCTOR ***/

AVL::~AVL()
{
	//std::cout << "Inside AVL destructor"" << endl;
}

/*** PUBLIC MEMBER FUNCTIONS ***/

void AVL::insert(Data const& newData)
{
	this->mpRoot = this->insert(this->getRootPtr(), newData);
}

Data AVL::search(char newSearch)
{
	return this->search(this->getRootPtr(), toupper(newSearch));
}

void AVL::convert(char* f1, char* f2)
{
	std::ifstream input;
	std::ofstream output;

	auto start = std::chrono::high_resolution_clock::now();

	input.open(f1);
	output.open(f2);

	while (!input.eof())
	{
		char line[1000];
		input.getline(line, 1000);
		output << this->convert(this->getRootPtr(), line) << std::endl;
	}

	input.close();
	output.close();

	auto end = std::chrono::high_resolution_clock::now();

	this->setTranslationTime(end - start);
}

void AVL::print()
{
	this->print(this->getRootPtr());
}

void  AVL::print2D()
{
	print2D(this->mpRoot, 0);
}

void AVL::destroyTree()
{
	this->destroyTree(this->getRootPtr());
}

void AVL::printStats()
{
	std::cout << "Insertion time: " << this->getInsertionTime().count() << " Conversion time: " << this->getTranslationTime().count() << std::endl;
}

/*** GETTERs / SETTERSs ***/

Node* AVL::getRootPtr() const
{
	return this->mpRoot;
}

void AVL::setRootPtr(Node* newRootPtr)
{
	this->mpRoot = newRootPtr;
}

std::chrono::duration<double> AVL::getInsertionTime() const
{
	return this->tInsertion;
}

void AVL::setInsertionTime(std::chrono::duration<double> time)
{
	this->tInsertion = time;
}

std::chrono::duration<double> AVL::getTranslationTime() const
{
	return this->tTranslation;
}

void AVL::setTranslationTime(std::chrono::duration<double> time)
{
	this->tTranslation = time;
}

int AVL::getItems() const
{
	return this->mItems;
}

void AVL::setItems(int newItems)
{
	this->mItems = newItems;
}

/*** PRIVATE MEMBER FUNCTIONS ***/

int AVL::getHeight(Node* pTree)
{
	if (pTree != nullptr)
		return pTree->getHeight();
	else
		return 0;
}

//void AVL::insert(Node* pTree, Data const& newData) // OLD CODE (BST & backwards height)
//{
//	if (pTree != nullptr)
//	{
//		if (newData.getCharacter() > pTree->getData().getCharacter())
//		{
//			if (pTree->getRightPtr() != nullptr)
//			{
//				this->insert(pTree->getRightPtr(), newData);
//			}
//			else
//			{
//				pTree->setRightPtr(new Node(newData));
//				this->setItems(this->getItems() + 1);
//			}
//
//			pTree->getRightPtr()->setHeight(pTree->getHeight() + 1);
//		}
//		else if (newData.getCharacter() < pTree->getData().getCharacter())
//		{
//			if (pTree->getLeftPtr() != nullptr)
//			{
//				this->insert(pTree->getLeftPtr(), newData);
//			}
//			else
//			{
//				pTree->setLeftPtr(new Node(newData));
//				this->setItems(this->getItems() + 1);
//			}
//
//			pTree->getLeftPtr()->setHeight(pTree->getHeight() + 1);
//		}
//		else
//		{
//			std::cout << "Duplicates" << std::endl;
//		}
//	}
//	else
//	{
//		this->setItems(this->getItems() + 1);
//		this->mpRoot = new Node(newData); // base case 
//	}
//}

Node* AVL::rRotate(Node* pTree)
{
	Node* newNode = pTree->getLeftPtr();
	pTree->setLeftPtr(newNode->getRightPtr());
	newNode->setRightPtr(pTree);

	pTree->setHeight(1 + std::max(this->getHeight(pTree->getLeftPtr()), this->getHeight(pTree->getRightPtr())));
	newNode->setHeight(1 + std::max(this->getHeight(newNode->getLeftPtr()), this->getHeight(newNode->getRightPtr())));

	return newNode;
}

Node* AVL::lRotate(Node* pTree)
{
	Node* newNode = pTree->getRightPtr();
	pTree->setRightPtr(newNode->getLeftPtr());
	newNode->setLeftPtr(pTree);

	pTree->setHeight(1 + std::max(this->getHeight(pTree->getLeftPtr()), this->getHeight(pTree->getRightPtr())));
	newNode->setHeight(1 + std::max(this->getHeight(newNode->getLeftPtr()), this->getHeight(newNode->getRightPtr())));

	return newNode;
}

Node* AVL::insert(Node* pTree, Data const& newData)
{
	if (pTree == nullptr)
		return new Node(newData);

	if (newData.getCharacter() < pTree->getData().getCharacter())
		pTree->setLeftPtr(insert(pTree->getLeftPtr(), newData));
	else if (newData.getCharacter() > pTree->getData().getCharacter())
		pTree->setRightPtr(insert(pTree->getRightPtr(), newData));
	pTree->setHeight(1 + std::max(this->getHeight(pTree->getLeftPtr()), this->getHeight(pTree->getRightPtr())));

	int treeBalance = this->getHeight(pTree->getLeftPtr()) - this->getHeight(pTree->getRightPtr());
	if (treeBalance > 1) // left heavy
	{
		if (newData.getCharacter() < pTree->getLeftPtr()->getData().getCharacter())
			return rRotate(pTree);
		else
		{
			pTree->setLeftPtr(lRotate(pTree->getLeftPtr()));
			return rRotate(pTree);
		}
	}
	else if (treeBalance < -1) // right heavy
	{
		if (newData.getCharacter() > pTree->getRightPtr()->getData().getCharacter())
			return lRotate(pTree);
		else
		{
			pTree->setRightPtr(rRotate(pTree->getRightPtr()));
			return lRotate(pTree);
		}
	}

	return pTree;
}

Data AVL::search(Node* pTree, char newSearch)
{
	if (pTree != nullptr)
	{
		if (newSearch < pTree->getData().getCharacter())
			return this->search(pTree->getLeftPtr(), newSearch);
		else if (newSearch > pTree->getData().getCharacter())
			return this->search(pTree->getRightPtr(), newSearch);

		return Data(pTree->getData()); // found ==
	}
}

std::string AVL::convert(Node* pTree, std::string str)
{
	std::string convertedString;

	for (int i = 0; i < str.size(); i++)
	{
		Data searchData = this->search(str[i]); // returns (character, morse) pair

		searchData.getString() == "" ? convertedString += "   " : convertedString += searchData.getString() + " ";
	}

	return convertedString;
}

void AVL::print(Node* pTree)
{
	if (pTree != nullptr) // in order traversal
	{
		this->print(pTree->getLeftPtr());
		std::cout << "Character: " << pTree->getData().getCharacter() << " Morse translation: " << pTree->getData().getString() << " Tree Height: " << pTree->getHeight() << "\n" << std::endl;
		this->print(pTree->getRightPtr());
	}
}

void AVL::print2D(Node* pTree, int space)
{
	if (pTree != NULL)
	{
		space += 3;

		print2D(pTree->getRightPtr(), space);

		for (int i = 3; i < space; i++)
			std::cout << " ";
		std::cout << pTree->getData().getCharacter() << std::endl;

		print2D(pTree->getLeftPtr(), space);
	}
}

void AVL::destroyTree(Node* pTree)
{
	if (pTree != nullptr) // post order
	{
		this->destroyTree(pTree->getLeftPtr());
		this->destroyTree(pTree->getRightPtr());
		delete(pTree);
	}
}
