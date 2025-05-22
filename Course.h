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

//файл с курсове: учителя, ид на студенти, парола, име
//файл с асайнменти: текст, 
//файл с юзъри: не го променяме