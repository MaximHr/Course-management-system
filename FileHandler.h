#pragma once
#include "String.h"
#include <fstream>
#include <exception>

struct FileHandler {
	std::fstream file;

	FileHandler()=default;
	FileHandler(const String& str);
	void open(const String& str);
	bool isOpen() const;
	void close();
	~FileHandler();
	void write(const String& str);
	void write(const char* data, unsigned bytes);
	void read(String& str);
	void read(char* data, unsigned bytes);
	int getFileSize();
	void copyBytes(std::ofstream& ofs, int bytes);
	void changeFile(const char* strFrom, const char* strTo);
};