/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "String.h"

namespace {
	const unsigned defaultCapacity = 8;
	unsigned resizeFactor = 2;

	unsigned calculateStringCapacity(unsigned n) {
		int res = defaultCapacity;
		while(res <= n) {
			res *= resizeFactor;
		}
		return res;
	}

	char toLowercase(char ch) {
		if(ch >= 'A' && ch <= 'Z') {
			return ch + ('a' - 'A');
		}
		return ch;
	}

	char toUppercase(char ch) {
		if(ch >= 'a' && ch <= 'z') {
			return ch - ('a' - 'A');
		}
		return ch;
	}

	bool isMatch(const char* str1, const char* str2, int index, int strLen) {
		if(str1 == nullptr || str2 == nullptr) {
			throw std::invalid_argument("argument is nullpointer");
		}
	
		for(int i = 0; i < strLen; i++) {
			if(str1[index + i] != str2[i]) {
				return false;
			}
		}
		return true;
	}
}


void String::free() {
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = defaultCapacity;
}

void String::resize(unsigned newCapacity) {
	if(newCapacity == 0) {
		throw std::invalid_argument("capacity can not be 0");
	}
	if(capacity == newCapacity) return;

	char* tempData = new char[newCapacity];
	if(size >= newCapacity) {
		size = newCapacity - 1;
	}

	for(int i = 0;i < size;i++) {
		tempData[i] = data[i];
	}
	tempData[size] = '\0';

	delete[] data;
	data = tempData;
	capacity = newCapacity;
}

void String::copyFrom(const String& other) {
	if(other.capacity == 0) {
		throw std::invalid_argument("Capacity can not be 0");
	}
	if(data == nullptr) {
		data = new char[other.capacity];
	}
	if(other.capacity != capacity) {
		resize(other.capacity);
	}
	for(int i = 0;i < other.size;i++) {
		data[i] = other.data[i];
	}
	size = other.size;
	data[size] = '\0';
}

String::String() {
	data = new char[defaultCapacity];
	data[0] = '\0';
	size = 0;
	capacity = defaultCapacity;
}

String::~String() {
	free();
}

String::String(const String& other):capacity(defaultCapacity), data(nullptr) {
	copyFrom(other);
}

String::String(const char* str, unsigned size, unsigned capacity) {
	if(str == nullptr || size >= capacity) {
		throw std::invalid_argument("Invalid argument");
	}
	this->size = size;
	this->capacity = capacity;
	data = new char[capacity];
	strcpy(data, str);
}

String::String(const char* str) {
	if(str == nullptr) {
		throw std::invalid_argument("argument is nullpointer");
	}
	size = strlen(str);
	capacity = calculateStringCapacity(size);
	data = new char[capacity];
	strcpy(data, str);
}

String& String::operator=(const String& other) {
	if(this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

unsigned String::getSize() const {
	return size;
}

unsigned String::getCapacity() const {
	return capacity;
}

bool String::isEmpty() const {
	return (size == 0);
}

std::istream& operator>>(std::istream& input, String& str) {
	char buffer[1024];
	input.getline(buffer, 1024);
	str = String(buffer);
	str = str.trim();
	
	return input;
}

std::ostream& operator<<(std::ostream& output, const String& str) {
	for(int i = 0;i < str.getSize();i++) {
		output << str.c_str()[i];
	}
	return output;
}

const char* String::c_str() const {
	return data;
}

String String::substr(unsigned startIndex, unsigned len) const {
	if(startIndex + len > size) {
		throw std::logic_error("Substring does not exist");
	}
	char* substring = new char[len + 1];
	for(int i = 0;i < len;i++) {
		substring[i] = data[startIndex + i];
	}
	substring[len] = '\0';

	String str(substring, len, calculateStringCapacity(len));
	delete[] substring;

	return str;

}

char& String::operator[](int index) {
	if(index < 0 || index >= size) {
		throw std::out_of_range("Out of range");
	}
	return data[index];
}

const char& String::operator[](int index) const {
	if(index < 0 || index >= size) {
		throw std::out_of_range("Out of range");
	}
	return data[index];
}

String& String::operator+=(const String& other) {
	int newSize = size + other.size;
	resize(calculateStringCapacity(newSize));
	for(int i = size;i < newSize;i++) {
		data[i] = other.data[i - size];
	}
	data[newSize] = '\0';
	size = newSize;

	return *this;
}

bool operator==(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator>=(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator<=(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator<(const String& lhs, const String& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

int String::find(char letter) const {
	for(int i = 0;i < size;i++) {
		if(data[i] == letter) {
			return i;
		}
	}
	return -1;
}

int String::find(const char* str) const {
	if(str == nullptr) return -1;// or throw error

	int strLen = strlen(str);
	if(size < strLen) {
		return -1;
	}
	for(int i = 0;i <= size - strLen;i++) {
		if(isMatch(data, str, i, strLen)) {
			return i;
		}
	}

	return -1;
}

void String::clear() {
	free();
	data = new char[defaultCapacity];
	data[0] = '\0';
}

void String::shrinkToFit() {
	resize(size);
}

void String::pop() {
	if(size == 0) {
		throw std::logic_error("Can not call pop() when the string is empty");
	}
	size--;
}

void String::pop(unsigned length) {
	if(size < length) {
		throw std::logic_error("Cannot remove more elements than currently exist in the string.");
	}
	size -= length;
}

String String::trimStart() const {
	char* str = new char[capacity];
	unsigned updatedSize = size, index = 0;
	bool areTrimmed = false;

	for(int i = 0;i < size;i++) {
		if(areTrimmed) {
			str[index] = data[i];
			index++;
		} else if(data[i] != ' ') {
			str[index] = data[i];
			index++;
			areTrimmed = true;
		} else {
			updatedSize--;
		}
	}

	return String(str, updatedSize, capacity);
}

String String::trimEnd() const {
	String s1(*this);
	bool isTrimmed = false;

	for(int i = size - 1;i >= 0;i--) {
		if(data[i] == ' ') {
			s1.size --;
		} else {
			break;
		}
	}
	
	return s1;
}

String String::trim() const {
	String s1(*this);
	s1 = s1.trimStart().trimEnd();

	return s1;
}

String String::toLower() const {
	String s1(*this);
	for(int i = 0;i < size;i++) {
		s1[i] = toLowercase(s1[i]);
	}
	return s1;
}

String String::toUpper() const {
	String s1(*this);
	for(int i = 0;i < size;i++) {
		s1[i] = toUppercase(s1[i]);
	}
	return s1;
}

String String::reverse() const {
	String s1(*this);
	int updatedSize = size / 2;
	char temp;

	for(int i = 0;i < updatedSize;i++) {
		temp = s1[i];
		s1[i] = s1[size - i - 1];
		s1[size - i - 1] = temp;
	}

	return s1;
}

String String::replace(char oldChar, char newChar) const {
	String s1(*this);
	for(int i = 0;i < size;i++) {
		if(s1[i] == oldChar) {
			s1[i] = newChar;
			return s1;
		}
	}
	return s1;
}

String& String::remove(unsigned index, unsigned length) {
	if(index >= size) {
		throw std::out_of_range("Out of range");
	}
	if(index + length > size) {
		length = size - index; 
	}

	String before = substr(0, index);
	String after = substr(index + length, size - (index + length));

	*this = before;
	*this += after;
	return *this;
}

String& String::insert(unsigned index, const char* str) {
	if(index > size) {
		throw std::out_of_range("Out of range");
	}

	String before = substr(0, index);
	String after = substr(index, size - index);
	String toInsert(str);

	*this = before;
	*this += toInsert;
	*this += after;
	return *this;
}

String String::replace(const char* oldString, const char* newString) const {
	if(oldString == nullptr || newString == nullptr) {
		throw std::invalid_argument("Argument is nullpointer");
	}

	String s1(*this);
	int index = s1.find(oldString);
	if(index != -1) {
 		s1.remove(index, strlen(oldString)).insert(index, newString);
	}
	return s1;
}

String String::replaceAll(const char* oldString, const char* newString) const {
	if(oldString == nullptr || newString == nullptr) {
		throw std::invalid_argument("argument is nullpointer");
	}

	String s1(*this);
	int index = s1.find(oldString);
	while(index != -1) {
		s1.remove(index, strlen(oldString)).insert(index, newString);
		index = s1.find(oldString);
	} 

	return s1;
}

String String::replaceAll(char oldChar, char newChar) const {
	String s1(*this);
	for(int i = 0;i < size;i++) {
		if(s1[i] == oldChar) {
			s1[i] = newChar;
		}
	}
	return s1;
}