#include "Sensor.h" 

#include <chrono> 
#include <vector> 

// Default constructor
Sensor::Sensor() : sensorID(""), latitude(0.0), longitude(0.0) {
    // Initialize sensorID to an empty string and latitude and longitude to 0.0
}

// Parameterized constructor
Sensor::Sensor(const std::string& id, double lat, double lon) : sensorID(id), latitude(lat), longitude(lon) {
    // Initialize sensorID, latitude, and longitude with the provided values
}

// Getter for sensorID
std::string Sensor::getSensorID() const {
    return sensorID; // Return the sensorID
}

// Setter for sensorID
void Sensor::setSensorID(const std::string& id) {
    sensorID = id; // Set the sensorID to the provided value
}

// Getter for latitude
double Sensor::getLatitude() const {
    return latitude; // Return the latitude
}

// Setter for latitude
void Sensor::setLatitude(double lat) {
    latitude = lat; // Set the latitude to the provided value
}

// Getter for longitude
double Sensor::getLongitude() const {
    return longitude; // Return the longitude
}

// Setter for longitude
void Sensor::setLongitude(double lon) {
    longitude = lon; // Set the longitude to the provided value
}

// Method to add a measurement to the sensor
void Sensor::addMeasurement(const Measurement& measurement) {
    measurements.push_back(measurement); // Add the provided measurement to the measurements vector
}

// Method to get all measurements
std::vector<Measurement> Sensor::getMeasurements() const {
    return measurements; // Return the measurements vector
}

// Method to filter measurements by period
std::vector<Measurement> Sensor::getMeasurementsForPeriod(const Date &startDate, const Date &endDate) const {
    std::vector<Measurement> filteredMeasurements;
    for (const auto &measurement : measurements) {
        if (measurement.getDate() >= startDate && measurement.getDate() <= endDate) {
            filteredMeasurements.push_back(measurement);
        }
    }
    return filteredMeasurements;
}

// Method to display sensor details
void Sensor::displayDetails() const {
    // Print the sensor details
    std::cout << "Sensor ID: " << sensorID << std::endl;
    std::cout << "Latitude: " << latitude << std::endl;
    std::cout << "Longitude: " << longitude << std::endl;
    std::cout << "Measurements:" << std::endl;
    // Loop through all measurements and print their details
    for (const Measurement& measurement : measurements) {
        std::cout << "  Date: " << measurement.getDate() << std::endl;
        std::cout << "  Attribute ID: " << measurement.getAttributeID() << std::endl;
        std::cout << "  Value: " << measurement.getValue() << std::endl;
    }
}


