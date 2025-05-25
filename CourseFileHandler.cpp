#include "CourseFileHandler.h"
#include "Course.h"

CourseFileHandler::CourseFileHandler(const String& str):FileHandler(str, false) {}

//saves course without student ids
void CourseFileHandler::saveCourse(const Course& course, FileHandler& fs) {
	unsigned ownerId = course.getOwnerId();
	unsigned courseId = course.getId();
	unsigned studentsCount = course.getStudentsCount();
	
	fs.file.write((const char*)& ownerId, sizeof(ownerId));
	fs.file.write((const char*)& courseId, sizeof(courseId));
	fs.write(course.getName());
	fs.write(course.getHashedPassword());
	fs.file.write((const char*)& studentsCount, sizeof(studentsCount));
}

Course* CourseFileHandler::readCourse() {
	Course* course = new Course();

	file.read((char *)& course->ownerId, sizeof(course->ownerId));
	file.read((char *)& course->id, sizeof(course->id));
	read(course->name);
	read(course->hashedPassword);
	file.read((char *)& course->studentsCount, sizeof(course->studentsCount));
	file.seekg(course->getStudentsCount() * sizeof(unsigned), std::ios::cur); // skips all student ids


	return course;
}

Course* CourseFileHandler::readCourse(int& sizeInBytes) {
	int start = file.tellg();
	Course* course = readCourse();
	sizeInBytes = (int)file.tellg() - start;

	return course;
}

void CourseFileHandler::addStudentId(Course& course, unsigned studentId) {
	FileHandler fs(Config::fileNames(6).c_str(), false);
	if(!fs.isOpen()) throw std::runtime_error("Failed to open temporary file for writing");

	int index = file.tellg();
	file.seekg(0);
	int bytes = 0;
	Course* tempCourse = readCourse(bytes);

	while(file) {
		if(tempCourse->getId() != course.getId()) {
			copyBytes(fs.file, bytes);
		} else {
			course.incrementStudentsCount();
			saveCourse(course, fs);
			copyBytes(fs.file, (course.getStudentsCount() - 1) * sizeof(unsigned));
			fs.file.write((const char*)& studentId, sizeof(unsigned));
		}
		delete tempCourse;
		tempCourse = readCourse(bytes);
	}

	fs.close();
	changeFile(Config::fileNames(6).c_str(), Config::fileNames(3).c_str());
	file.seekg(index);

	delete tempCourse;
}

Course* CourseFileHandler::getCourse(unsigned id) {
	int pos = findCourse(id);
	if(pos == -1) throw std::runtime_error("Course with that id was not found");

	int current = file.tellg();
	file.seekg(pos);
	Course* course = readCourse();
	file.seekg(current);
	return course;
}

Course* CourseFileHandler::getCourse(unsigned id, const String& hashedPassword) {
	int pos = findCourseWithPassword(id, hashedPassword);
	if(pos == -1) throw std::runtime_error("Course was not found");

	int current = file.tellg();
	file.seekg(pos);
	Course* course = readCourse();
	file.seekg(current);
	return course;
}

bool CourseFileHandler::findStudentId(unsigned courseId, unsigned studentId, unsigned studentsCount) {
	if(studentsCount == 0) return 0;
	int index = file.tellg();
	file.seekg(0);

	int pos = findCourse(courseId);
	if(pos == -1) throw std::runtime_error("Course with that id was not found");
	file.seekg(pos);

	//goes to the end of the course and then back to where studentIds are saved
	Course* course = readCourse();
	delete course;
	file.seekg(-sizeof(studentId) * studentsCount, std::ios::cur);

	for(int i = 0;i < studentsCount;i++) {
		unsigned savedId;
		file.read((char *)& savedId, sizeof(studentId));
		if(savedId == studentId) {
			return 1;
		}
	}

	file.seekg(index);
	return 0;
}

int CourseFileHandler::findCourse(unsigned id) {
	return findCourseMatcher(id, "", false);
}

int CourseFileHandler::findCourseWithPassword(unsigned id, const String& hashedPassword) {
	return findCourseMatcher(id, hashedPassword, true);
}

int CourseFileHandler::findCourseMatcher(unsigned id, const String& hashedPassword, bool shouldCheckPassword) {
	if(!isOpen()) throw std::runtime_error("file cannot be opened");
	if(getFileSize() == 0) return -1;

	int index = file.tellg();
	file.clear();
	file.seekg(0);
	Course* course = readCourse();
	int result = 0;

	while(
		(!shouldCheckPassword && course->getId() != id) || 
		(shouldCheckPassword && (course->getId() != id || course->getHashedPassword() != hashedPassword))
	) {
		if(!file) {
			file.clear();
			delete course;
			return -1;
		}
		result = file.tellg();
		delete course;
		course = readCourse();
	}

	file.clear();
	file.seekg(index);
	delete course;
	return result;
}