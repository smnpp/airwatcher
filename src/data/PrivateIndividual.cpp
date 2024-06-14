#include "PrivateIndividual.h"

#include <iostream>
#include <string>

PrivateIndividual::PrivateIndividual(std::string id, std::string lastName, std::string firstName, std::string mail, std::string address, std::string password)
    : User(id, lastName, firstName, mail, address, password) {
}

void PrivateIndividual::setBan(bool ban) {
    isBan = ban;
}
void PrivateIndividual::addSensor(const Sensor &sensor) {
    sensors.push_back(sensor);
}
const std::vector<Sensor> &PrivateIndividual::getSensors() const {
    return sensors;
}