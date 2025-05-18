#include "UserFactory.h"

User* UserFactory::createUser(UserType type){
	switch(type) {
		case UserType::Admin:
			return new Admin();
		case UserType::Teacher:
			return new Teacher();
		case UserType::Student:
			return new Student();	
		default:
			throw std::runtime_error("Can not create user");
	}
}

User* UserFactory::createUser(UserType type, const String& firstName, const String& lastName, const String& password){
	switch(type) {
		case UserType::Teacher:
			return new Teacher(firstName, lastName, password);
		case UserType::Student:
			return new Student(firstName, lastName, password);	
		default:
			throw std::runtime_error("Can not create user");
	}
}