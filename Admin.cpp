#include "Admin.h"

Admin::Admin():User("admin", "_", "0000", 0) { }

UserType Admin::getRole() const {
	return UserType::Admin;
}

User* Admin::clone() const {
	return new Admin(*this);
}