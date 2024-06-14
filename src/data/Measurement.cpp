#include "Measurement.h"

// Default constructor
Measurement::Measurement() : attributeID(""), value(0.0) {
    // The Date class should have its default constructor set the date to some default value
}

// Parameterized constructor
Measurement::Measurement(const Date& dt, std::string attrID, double val) : date(dt), attributeID(attrID), value(val) {
}

// Getter for date
Date Measurement::getDate() const {
    return date;
}

// Setter for date
void Measurement::setDate(const Date& dt) {
    date = dt;
}

// Getter for attribute ID
std::string Measurement::getAttributeID() const {
    return attributeID;
}

// Setter for attribute ID
void Measurement::setAttributeID(std::string attrID) {
    attributeID = attrID;
}

// Getter for value
double Measurement::getValue() const {
    return value;
}

// Setter for value
void Measurement::setValue(double val) {
    value = val;
}
