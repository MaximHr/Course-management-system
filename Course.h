#pragma once
#include "Teacher.h"
#include "Student.h"
#include "Assignment.h"
#include "String.h"

class Course {
	Teacher teacher;
	Student* students;
	String name;
	String hashedPassword;
	Assignment* assignments;
};