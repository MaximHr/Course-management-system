#include "SystemVerifier.h"

SystemVerifier::SystemVerifier(const User*& user) : currentUser(user) { }

bool SystemVerifier::isLogged() const {
	return (currentUser != nullptr);
}

bool SystemVerifier::isAdmin() const {
	return (currentUser->getRole() == UserType::Admin);
}

bool SystemVerifier::isTeacher() const {
	return (currentUser->getRole() == UserType::Teacher);

}

bool SystemVerifier::isStudent() const {
	return (currentUser->getRole() == UserType::Student);
}