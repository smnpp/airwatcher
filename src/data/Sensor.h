#ifndef SENSOR_H
#define SENSOR_H

#include "Measurement.h"

#include <string>
#include <vector>

// Declare the Sensor class
class Sensor
{
private:                                   // The following members are private and can only be accessed from within the class
    std::string sensorID;                  // Declare a string to store the sensor ID
    double latitude;                       // Declare a double to store the latitude of the sensor
    double longitude;                      // Declare a double to store the longitude of the sensor
    std::vector<Measurement> measurements; // Declare a vector to store the measurements associated with the sensor

public: // The following members are public and can be accessed from outside the class
    // Declare constructors
    Sensor();                                              // Default constructor
    Sensor(const std::string &id, double lat, double lon); // Parameterized constructor

    // Declare getter and setter for sensorID
    std::string getSensorID() const;         // Getter for sensorID
    void setSensorID(const std::string &id); // Setter for sensorID

    // Declare getter and setter for latitude
    double getLatitude() const;   // Getter for latitude
    void setLatitude(double lat); // Setter for latitude

    // Declare getter and setter for longitude
    double getLongitude() const;   // Getter for longitude
    void setLongitude(double lon); // Setter for longitude

       // Declare methods to manage measurements
    void addMeasurement(const Measurement &measurement);                                                 // Method to add a measurement to the vector of measurements
    std::vector<Measurement> getMeasurements() const;                                                    // Method to get all measurements
    std::vector<Measurement> getMeasurementsForPeriod(const Date &startDate, const Date &endDate) const; // Method to get measurements for a specific period
    void displayDetails() const;                                                                         // Method to display the details of the sensor
};

#endif