/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "../Users/User.h"

class SystemVerifier {
private:
	User*& currentUser;
public:
	SystemVerifier(User*& user);
	void requireLogged() const;
	void requireLoggedOut() const;
	void requireAdmin() const;
	void requireTeacher() const;
	void requireStudent() const;
	void requireClient() const;
};