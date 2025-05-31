/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "IdCreator.h"
#include <iostream>
#include "../FileHandlers/FileHandler.h"
#include "../Utils/Config.h"

class IdContainer {
	FileHandler fileHandler;
	IdCreator* idCreators;
	int length;
	void copyFrom(const IdContainer& other);
	void free();
	int findByName(const String& name) const;
	void loadLargestIds();
	void saveIdCounters();
public:
	IdContainer() = delete;
	IdContainer(const String& fileName, const String* names, int length);
	IdContainer(const IdContainer& other);
	IdContainer& operator=(const IdContainer& other);
	~IdContainer();

	void increment(const String& name);
	void setIdCounter(const String& name, unsigned value);
	unsigned getId(const String& name) const;
};