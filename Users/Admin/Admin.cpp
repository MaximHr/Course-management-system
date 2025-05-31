/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "Admin.h"

Admin::Admin() : User("admin", "_", Config::adminPassword(), Config::adminId) { }

UserType Admin::getRole() const {
	return UserType::Admin;
}

User* Admin::clone() const {
	return new Admin(*this);
}