/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "FileHandler.h"
class Course;

class CourseFileHandler: public FileHandler {
private:
	Course* getCourseMatcher(unsigned id, const String& hashedPassword, bool shouldCheckPassword);
	int findCourseMatcher(unsigned id, const String& hashedPassword, bool shouldCheckPassword);
public:
	CourseFileHandler() = default;
	CourseFileHandler(const String& str);

	void saveCourse(const Course& course, FileHandler& fs);
	void addStudentId(Course& course, unsigned studentId);
	Course* readCourse();
	Course* readCourse(int& sizeInBytes);
	Course* getCourse(unsigned id);
	bool findStudentId(unsigned courseId, unsigned studentId, unsigned studentsCount);
	Course* getCourse(unsigned id, const String& hashedPassword);
	int findCourse(unsigned id);
	int findCourseWithPassword(unsigned id, const String& hashedPassword);
};