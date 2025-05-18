#pragma once
#include <cstring>
#include <fstream>
#include <exception>

class String {
	char* data;
	unsigned size;
	unsigned capacity;

	void free();
	void copyFrom(const String& other);
	void resize(unsigned newCapacity);

public:
	String();
	~String();
	String(const String& other);
	String(const char* str);
	String(const char* str, unsigned size, unsigned capcaity);

	String& operator=(const String& other);
	char& operator[](int index);
	const char& operator[](int index) const;
	String& operator+=(const String& other);

	String& remove(unsigned index, unsigned length);
	String& insert(unsigned index, const char* str);
	void clear();
	void shrinkToFit();
	void pop();
	void pop(unsigned length);

	String substr(unsigned startIndex, unsigned len) const;
	String trimStart() const; //Removes spaces from the beginning
	String trimEnd() const; //Removes spaces from the end
	String trim() const; //Removes space from both sides
	String toLower() const;
	String toUpper() const;
	String reverse() const;
	String replace(char oldChar, char newChar) const; //replaces first occurance of oldChar
	String replace(const char* oldString, const char* newString) const;
	String replaceAll(char oldChar, char newChar) const; //replaces all occurances of oldChar
	String replaceAll(const char* oldString, const char* newString) const;
	unsigned getSize() const;
	unsigned getCapacity() const;
	const char* c_str() const;
	bool isEmpty() const;
	int find(char letter) const; // returns the index of the letter, or -1 if the letter was not found
	int find(const char* str) const;

	friend std::istream& operator>>(std::istream& input, String& str);

};

std::istream& operator>>(std::istream& input, String& str);
std::ostream& operator<<(std::ostream& output, const String& str);

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);