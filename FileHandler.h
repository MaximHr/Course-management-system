#pragma once
#include "String.h"
#include <fstream>
#include <exception>

class FileHandler {
public:
	std::fstream file;

	FileHandler()=default;

	FileHandler(const String& str, bool truncMode);
	void open(const String& str);
	void open(const String& str, bool truncMode);
	bool isOpen() const;
	void close();
	~FileHandler();
	void write(const String& str);
	void write(const char* data, unsigned bytes);
	void read(String& str);
	int getFileSize();
	void copyBytes(std::ofstream& ofs, int bytes);
	void changeFile(const char* strFrom, const char* strTo);
};