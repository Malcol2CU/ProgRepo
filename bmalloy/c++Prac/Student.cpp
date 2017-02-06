#include "Student.h"

Student::Student(){
	std::cout << "Default" << std::endl;
}

Student::Student(string fName, string lName): firstName(fName), lastName(lName), wholeName(fName+" "+lName){
}

Student::Student(const Student& student){
	firstName = student.firstName;
	lastName = student.lastName;
	wholeName = student.wholeName;
	email = student.email;
}
void Student::setEmail(string E){
	email = E;
}
