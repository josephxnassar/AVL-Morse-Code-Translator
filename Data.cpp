#include "Data.h"

Data::Data()
{
	this->mCharacter = '\0';
	this->mString = "";
}

Data::Data(char character, std::string str)
{
	this->mCharacter = character;
	this->mString = str;
}


Data::Data(Data const& copy)
{
	this->mCharacter = copy.getCharacter();
	this->mString = copy.getString();
}

Data::~Data()
{
	//cout << "Inside Data Destructor!" << endl;
}

char Data::getCharacter() const
{
	return this->mCharacter;
}

std::string Data::getString() const
{
	return this->mString;
}

void Data::setCharacter(char newCharacter)
{
	this->mCharacter = newCharacter;
}

void Data::setString(std::string newString)
{
	this->mString = newString;
}