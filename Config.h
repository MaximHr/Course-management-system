#pragma once
#include "String.h"

class Config {
public:
    static const unsigned adminId = 0;
    static const String& adminPassword() {
			static String password = "0000";
			return password;
    }

    static const int numberOfFiles = 7;
    const static String* fileNames() {
			static String names[numberOfFiles] = {
				"users.dat",
				"ids.dat",
				"homeworks.dat",
				"courses.dat",
				"assignments.dat",
				"messages.dat",
				"temp.dat"
			};
			return names;
    }
    static const String fileNames(unsigned i) {
			if(i >= numberOfFiles) {
				throw std::invalid_argument("invalid index");
			}
			static String names[numberOfFiles] = {
				"users.dat",
				"ids.dat",
				"homeworks.dat",
				"courses.dat",
				"assignments.dat",
				"messages.dat",
				"temp.dat"
			};
			return names[i];
    }
};
