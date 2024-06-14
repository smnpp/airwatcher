#ifndef PRIVATEINDIVIDUAL_H
#define PRIVATEINDIVIDUAL_H

#include "Sensor.h"
#include "User.h"

#include <iostream>
#include <vector>


class PrivateIndividual : public User {
public:
    PrivateIndividual(std::string id, std::string lastName, std::string firstName, std::string mail, std::string address, std::string password);
    void setBan(bool ban);
    void addSensor(const Sensor &sensor);
    const std::vector<Sensor> &getSensors() const;

protected:
    std::vector<Sensor> sensors;
    bool isBan = 0;
};
#endif