#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <string.h>

class Data
{
public:
	Data();
	Data(char character, std::string str);
	Data(Data const &copy);
	~Data();

	char getCharacter() const;
	std::string getString() const;

	void setCharacter(char newCharacter);
	void setString(std::string newString);
private:
	char mCharacter;
	std::string mString;
};
