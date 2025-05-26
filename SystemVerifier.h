#pragma once
#include "User.h"

class SystemVerifier {
private:
	const User*& currentUser;
public:
	SystemVerifier(const User*& user);
	bool isLogged() const;
	bool isAdmin() const;
	bool isTeacher() const;
	bool isStudent() const;
};