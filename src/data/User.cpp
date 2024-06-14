#include "User.h"

#include <iostream>
#include <string>

User::User(std::string id, std::string lastName, std::string firstName, std::string mail, std::string address, std::string password)
    : id(id), lastName(lastName), firstName(firstName), mail(mail), address(address), password(password) {
}
std::string User::getId() {
    return this->id;
}
std::string User::getPassword() {
    return this->password;
}
void User::setPassword(std::string password) {
    this->password = password;
}
void User::setMail(std::string mail) {
    this->mail = mail;
}
void User::setId(std::string id) {
    this->id = id;
}
