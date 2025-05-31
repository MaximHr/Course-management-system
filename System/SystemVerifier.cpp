/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "SystemVerifier.h"

SystemVerifier::SystemVerifier(User*& user) : currentUser(user) { }

void SystemVerifier::requireLogged() const {
	if(currentUser == nullptr) {
		throw std::runtime_error("Access denied: user not logged in.");
	}
}

void SystemVerifier::requireLoggedOut() const {
	if(currentUser != nullptr) {
		throw std::runtime_error("You must logout first, in order to log in.");
	}
}

void SystemVerifier::requireAdmin() const {
	requireLogged();
	if(currentUser->getRole() != UserType::Admin) {
		throw std::runtime_error("Access denied: requires Admin role.");
	}
}

void SystemVerifier::requireTeacher() const {
	requireLogged();
	if(currentUser->getRole() != UserType::Teacher) {
		throw std::runtime_error("Access denied: requires Teacher role.");
	}
}

void SystemVerifier::requireStudent() const {
	requireLogged(); 
	if(currentUser->getRole() != UserType::Student) {
		throw std::runtime_error("Access denied: requires Student role.");
	}
}

void SystemVerifier::requireClient() const {
	requireLogged();
	if(currentUser->getRole() != UserType::Student && currentUser->getRole() != UserType::Teacher) {
		throw std::runtime_error("Access denied: requires Student or Teacher role.");
	}
}