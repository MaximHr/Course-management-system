#include "Submission.h"

Submission::Submission() : grade(-1) {};

Submission::Submission(unsigned id, unsigned studentId, unsigned assignmentId, const String& answer) : 
	id(id), 
	studentId(studentId), 
	assignmentId(assignmentId), 
	answer(answer),
	grade(-1)
{ }

double Submission::getId() const {
	return id;
}

bool Submission::isGraded() const {
	return grade != -1;
}

double Submission::getGrade() const {
	return grade;
}

double Submission::getStudentId() const {
	return studentId;
}

double Submission::getAssignmentId() const {
	return assignmentId;
}

const String& Submission::getAnswer() const {
	return answer;
}

void Submission::setGrade(double grade) {
	if(grade < 2 || grade > 6 ) {
		throw std::invalid_argument("Grade must be between 2 and 6");
	} else {
		int res = (grade * 100);
		this->grade = res / 100.0;
	}
}