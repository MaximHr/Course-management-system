#pragma once
#include "User.h"
#include "Config.h"
#include <iostream>

class Admin: public User {
public:
	Admin();
	UserType getRole() const override;
	User* clone() const override;
};