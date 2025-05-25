#include "Config.h"
#include "FileHandler.h"
#include <iostream>

FileHandler::FileHandler(const String& str, bool truncMode) {
	open(str, truncMode);
}

void FileHandler::open(const String& str, bool truncMode) {
	if(truncMode == true) {
		if(!isOpen()) {
			file.open(str.c_str(), std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
		}
		
		if(!isOpen()) {
			throw std::runtime_error("File can not be opened 14.");
		}
	} else {
		open(str);
	}
}

void FileHandler::open(const String& str) {
	if(!isOpen()) {
		file.open(str.c_str(), std::ios::binary | std::ios::in | std::ios::out);
	}
	if(!isOpen()) {
		file.clear();
		file.open(str.c_str(), std::ios::out | std::ios::binary); // Creates the file
		file.close();
		file.open(str.c_str(), std::ios::in | std::ios::out | std::ios::binary);
	}
	if(!isOpen()) {
		throw std::runtime_error("File can not be opened 21.");
	}
}

void FileHandler::write(const String& str) {
	if(!isOpen()) {
		throw std::runtime_error("File can not be opened 27.");
	}
	file.seekp(0, std::ios::end);
	unsigned length = str.getSize();
	file.write((const char*)& length, sizeof(unsigned));
	file.write((const char*) str.c_str(), length);
}

void FileHandler::read(String& str) {
	if(!isOpen()) throw std::runtime_error("File can not be opened 49.");
	unsigned length;
	file.read((char*)&length, sizeof(unsigned));
	char buffer[length + 1];
	file.read((char*)buffer, length);
	buffer[length] = '\0';
	str = buffer;
}

void FileHandler::copyBytes(std::fstream& output, int bytes) {
	if(bytes == 0) return;
	file.seekg(-bytes, std::ios::cur);
	char buffer[bytes];
	file.read(buffer, bytes);
	output.write((const char*)buffer, bytes);
}

void FileHandler::changeFile(const char* strFrom, const char* strTo) {
	if(strFrom == nullptr || strTo == nullptr) {
		throw std::invalid_argument("File name is nullptr");
	}
	file.clear();
	file.close();
	file.flush();
	file.clear();
	remove(strTo);
  std::rename(strFrom, strTo);
	open(strTo);
}

bool FileHandler::isOpen() const {
	return file.is_open();
}

void FileHandler::close() {
	file.flush();
	file.close();
}

FileHandler::~FileHandler() {
	close();
}

int FileHandler::getFileSize() {
	if(!isOpen()) throw std::runtime_error("File can not be opened. 85");
	int currentPos = file.tellg();

	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	
	file.seekg(currentPos, std::ios::beg);

	return fileSize;
}
