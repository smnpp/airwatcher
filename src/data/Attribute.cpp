#include "Attribute.h"

// Default constructor
Attribute::Attribute() : attributeID(""), unit(""), description("") {
}

// Parameterized constructor
Attribute::Attribute(std::string id, std::string unit, std::string description) : attributeID(id), unit(unit), description(description) {
}

// Getter for attributeID
std::string Attribute::getAttributeID() const {
    return attributeID;
}

// Setter for attributeID
void Attribute::setAttributeID(std::string id) {
    attributeID = id;
}

// Getter for unit
std::string Attribute::getUnit() const {
    return unit;
}

// Setter for unit
void Attribute::setUnit(std::string unit) {
    this->unit = unit;
}

// Getter for description
std::string Attribute::getDescription() const {
    return description;
}

// Setter for description
void Attribute::setDescription(std::string description) {
    this->description = description;
}
