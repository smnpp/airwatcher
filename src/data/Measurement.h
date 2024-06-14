#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include "Date.h"  // Include the Date class header

#include <string>

class Measurement {
private:
    Date date;                // Use Date class for the measurement's date
    std::string attributeID;  // ID for the type of measurement (e.g., O3 for ozone)
    double value;             // Numeric value of the measurement

public:
    // Constructors
    Measurement();
    Measurement(const Date& dt, std::string attrID, double val);

    // Getter for date
    Date getDate() const;
    // Setter for date
    void setDate(const Date& dt);

    // Getter for attribute ID
    std::string getAttributeID() const;
    // Setter for attribute ID
    void setAttributeID(std::string attrID);

    // Getter for value
    double getValue() const;
    // Setter for value
    void setValue(double val);
    
};

#endif  // MEASUREMENT_H
