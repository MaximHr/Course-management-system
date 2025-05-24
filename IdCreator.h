#pragma once
#include "String.h"

struct IdCreator {
	unsigned idCounter;
	String tableName;
	IdCreator();
	void increment();
	void setIdCounter(unsigned value);
};