#include "User.h"

//TODO: read from file which is the lastId and set idCounter properly:
unsigned User::idCounter = 99;

User::User() {
	id = idCounter;
	idCounter++;
};

//for simplcity i am not hashing the password, but just reversing it
User::User(const String& firstName, const String& lastName, const String& password):
	firstName(firstName), lastName(lastName), hashedPassword(password.reverse())
{
	id = idCounter;
	idCounter++;
};

const String& User::getFirstName() const {
	return firstName;
}

const String& User::getLastName() const {
	return lastName;
}

unsigned User::getId() const {
	return id;
}

const String& User::getHashedPassword() const {
	return hashedPassword;
}
