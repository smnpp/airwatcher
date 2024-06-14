
#if !defined(USER_H)
#define USER_H

#include <iostream>
#include <unordered_map>
#include <vector>

class User {
public:
    virtual void FonctionPure() const = 0;
    User(std::string id, std::string lastName, std::string firstName, std::string mail, std::string address, std::string password);
    std::string getId();
    std::string getPassword();
    void setPassword(std::string password);
    void setMail(std::string mail);
    void setId(std::string id);

protected:
    std::string id;
    std::string lastName;
    std::string firstName;
    std::string mail;
    std::string address;
    std::string password;
};

#endif