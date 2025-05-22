#include "FileHandler.h"
#include <iostream>

FileHandler::FileHandler(const String& str) {
	open(str);
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
	std::cout << str.c_str() << " opened" << '\n';
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

void FileHandler::write(const char* data, unsigned bytes) {
	if(data == nullptr) throw std::invalid_argument("Argument cannot be null pointer");
	if(!isOpen()) throw std::runtime_error("File can not be opened 37.");

	file.seekp(0, std::ios::end);
	file.write(data, bytes);
}

void FileHandler::read(char* data, unsigned bytes) {
	if(!isOpen()) throw std::runtime_error("File can not be opened 44.");
	file.read(data, bytes);
	if (file.gcount() != bytes) {
    std::cout << "Only read " << file.gcount() << " of " << bytes << " bytes.\n";
	}
	if(file.fail()) {
		std::cout << bytes <<  " Non-fatal I/O error (failbit is set).\n";
	}
}

void FileHandler::read(String& str) {
	if(!isOpen()) throw std::runtime_error("File can not be opened 49.");
	unsigned length;
	file.read((char*)&length, sizeof(unsigned));
	char buffer[length + 1];
	file.read((char*)buffer, length);
	buffer[length] = '\0';
	str = buffer;
	if (file.gcount() != length) {
    std::cout << "Only read " << file.gcount() << " of " << length << " bytes.\n";
	}
	if (file.fail()) {
		std::cout << str <<  "STRING Non-fatal I/O error (failbit is set).\n";
	}
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

void FileHandler::copyBytes(std::ofstream& ofs, int bytes) {
	file.seekg(-bytes, std::ios::cur);
	char buffer[bytes];
	read(buffer, bytes);
	ofs.write((const char*)buffer, bytes);
}

bool FileHandler::isOpen() const {
	return file.is_open();
}

void FileHandler::close() {
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
