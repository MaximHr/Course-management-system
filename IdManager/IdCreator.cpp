/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "IdCreator.h"

IdCreator::IdCreator() {
	idCounter = 100;
}

void IdCreator::increment() {
	idCounter++;
}

void IdCreator::setIdCounter(unsigned value) {
	idCounter = value;
}
