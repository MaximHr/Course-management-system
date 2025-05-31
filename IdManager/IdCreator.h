/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "../Utils/String.h"

struct IdCreator {
	unsigned idCounter;
	String tableName;
	IdCreator();
	void increment();
	void setIdCounter(unsigned value);
};