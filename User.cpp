#include "User.h"

//for simplcity i am not hashing the password, but just reversing it
User::User(const String& firstName, const String& lastName, const String& password, int idCounter):
	firstName(firstName), lastName(lastName), hashedPassword(password.reverse()), id(idCounter)
	{
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
