#include "./Components/CommandHandler/CommandHandler.h"

//TODO:
//allow users to change their passwords
//add message_all
//add message_course
//add comments on each file

//make the filehandlers singletons and use them with ::
//change message to cout sender
//change the printing of homeworks(grades for students only) to show which course and assignment they are
//make systemVerifier better

int main() {
	CommandHandler c;
	c.start();

	return 0;
}