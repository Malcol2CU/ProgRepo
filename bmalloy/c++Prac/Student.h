#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using std::string;


class Student{
public:
	Student(); // Default constructor
	Student(string, string); //convert constructor
	Student(const Student&); //copy constructor

	const string& getName() const { return wholeName;};

	void setEmail(string);
	const string& getEmail() const { return email;};


	int getAge() const {return age;};

private: 
	string firstName, lastName, wholeName, email;
	int age;
};
#endif 
