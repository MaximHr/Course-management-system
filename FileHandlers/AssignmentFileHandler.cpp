#include "AssignmentFileHandler.h"
#include "../Components/Assignment/Assignment.h"

AssignmentFileHandler::AssignmentFileHandler(const String& str) : FileHandler(str) {}

Assignment* AssignmentFileHandler::readAssignment() {
	if(!isOpen()) throw std::runtime_error("file can not be opened");
	Assignment* assignment = new Assignment();
	
	file.read((char *)& assignment->id, sizeof(assignment->id));
	file.read((char *)& assignment->courseId, sizeof(assignment->courseId));
	read(assignment->name);

	return assignment;
}

void AssignmentFileHandler::saveAssignment(const Assignment& assignment) {
	if(!isOpen()) throw std::runtime_error("file can not be opened");

	unsigned assignmentId = assignment.getId();
	unsigned courseId = assignment.getCourseId();
	
	file.write((const char*)& assignmentId, sizeof(assignmentId));
	file.write((const char*)& courseId, sizeof(courseId));
	write(assignment.getName());
	file.flush();
}

Assignment* AssignmentFileHandler::getAssignment(unsigned id) {
	int pos = findAssignment(id);
	if(pos == -1)  {
		throw std::runtime_error("Assignment with that id was not found");
	}

	int current = file.tellg();
	file.seekg(pos);
	Assignment* assignment = readAssignment();
	file.seekg(current);

	return assignment;
}

int AssignmentFileHandler::findAssignment(unsigned id) {
	if(!isOpen()) throw std::runtime_error("file cannot be opened");
	if(getFileSize() == 0) return -1;

	int index = setAtBeginning();
	Assignment* assignment = readAssignment();
	int result = 0;

	while(assignment->getId() != id) {
		if(!file) {
			file.clear();
			delete assignment;
			return -1;
		}
		result = file.tellg();
		delete assignment;
		assignment = readAssignment();
	}

	file.clear();
	file.seekg(index);
	delete assignment;

	return result;
}