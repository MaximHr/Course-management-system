#pragma once
#include "../Utils/String.h"

struct IdCreator {
	unsigned idCounter;
	String tableName;
	IdCreator();
	void increment();
	void setIdCounter(unsigned value);
};