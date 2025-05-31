/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "../Utils/String.h"
#include <fstream>
#include <exception>

class FileHandler {
public:
	std::fstream file;

	FileHandler() = default;
	FileHandler(const String& str);
	~FileHandler();

	void open(const String& str);
	void close();
	void write(const String& str);
	void read(String& str);
	void copyBytes(std::fstream& output, int bytes);
	void changeFile(const char* strFrom, const char* strTo);
	bool isOpen() const;
	int getFileSize();
	int setAtBeginning();
};