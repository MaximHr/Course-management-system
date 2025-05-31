/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "../Utils/String.h"
#include "../FileHandlers/UserFileHandler.h"
#include <stdint.h>

enum class UserType:uint8_t {
	Admin,
	Teacher,
	Student
};

class User {
protected:
	String firstName;
	String lastName;
	String hashedPassword;
	unsigned id;
	friend User* UserFileHandler::readUser();

public:
	User() = default;
	User(const String& firstName, const String& lastName, const String& password, int idCounter);
	virtual ~User() = default;
	
	virtual UserType getRole() const = 0;
	virtual User* clone() const = 0;
	const String& getFirstName() const;
	const String& getLastName() const;
	const String& getHashedPassword() const;
	unsigned getId() const;
};
