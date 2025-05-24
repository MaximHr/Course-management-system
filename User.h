#pragma once
#include "String.h"
#include <stdint.h>
#include "UserFileHandler.h"

enum class UserType:uint8_t {
	Admin,
	Teacher,
	Student
};

class User {
private:
protected:
	String firstName;
	String lastName;
	String hashedPassword;
	unsigned id;

public:
	friend User* UserFileHandler::readUser();
	virtual UserType getRole() const = 0;
	virtual User* clone() const = 0;
	const String& getFirstName() const;
	const String& getLastName() const;
	unsigned getId() const;
	const String& getHashedPassword() const;
	User() = default;
	User(const String& firstName, const String& lastName, const String& password, int idCounter);
	virtual ~User() = default;
};
