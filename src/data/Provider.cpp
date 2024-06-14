#include "Provider.h"

#include <iostream>
#include <string>

Provider::Provider(std::string id, std::string lastName, std::string firstName, std::string mail, std::string address, std::string password) : User(id, lastName, firstName, mail, address, password) {
}