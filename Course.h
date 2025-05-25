#pragma once
#include "Teacher.h"
#include "Student.h"
#include "Assignment.h"
#include "String.h"
#include "CourseFileHandler.h"

class Course {
	String name;
	String hashedPassword;
	unsigned ownerId;
	unsigned id;
	unsigned studentsCount;

public:
	friend Course* CourseFileHandler::readCourse();
	Course() = default;
	Course(const String& name, const String& password, unsigned ownerId, unsigned id);
	void incrementStudentsCount();
	unsigned getStudentsCount() const;
	unsigned getId() const;
	const String& getName() const;
	const String& getHashedPassword() const;
	unsigned getOwnerId() const;
};