#include <iostream>
#include "Student.h"

using std::string;

int main(){
	string fn, ln, email;

	std::cout << "First Name: "; std::cin >> fn;
	std::cout << "Last Name: "; std::cin >> ln;
	std::cout << "Email: "; std::cin >> email;
		
	Student me(fn, ln);
	me.setEmail(email);

	std::cout << me.getEmail() << std::endl;
	Student copy(me);
	std::cout << copy.getName() << std::endl;
}
