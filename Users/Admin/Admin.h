/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "../User.h"
#include "../../Utils/Config.h"
#include <iostream>

class Admin: public User {
public:
	Admin();
	UserType getRole() const override;
	User* clone() const override;
};