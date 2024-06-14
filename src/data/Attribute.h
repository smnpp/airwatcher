#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

class Attribute {
private:
    std::string attributeID;  // Identifiant unique pour le type de mesure
    std::string unit;         // Unité de mesure (par exemple, µg/m3)
    std::string description;  // Description du type de mesure

public:
    // Constructors
    Attribute();
    Attribute(std::string id, std::string unit, std::string description);

    // Getter for attributeID
    std::string getAttributeID() const;
    // Setter for attributeID
    void setAttributeID(std::string id);

    // Getter for unit
    std::string getUnit() const;
    // Setter for unit
    void setUnit(std::string unit);

    // Getter for description
    std::string getDescription() const;
    // Setter for description
    void setDescription(std::string description);
};

#endif  // ATTRIBUTE_H
