#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>

#include "../Data/Attribute.h"
#include "../Data/Date.h"
#include "../Data/Measurement.h"
#include "../Data/Sensor.h"

#include "../Services/SensorManagementServices.h"
#include "../Services/AirQualityGenerationServices.h"

using namespace std;

// Function prototypes for loading data from CSV files
void loadAttributes(const std::string &filename, std::vector<Attribute> &attributes);
void loadMeasurements(const std::string &filename, std::vector<Measurement> &measurements, std::unordered_map<std::string, Sensor> &sensors);
void loadSensors(const std::string &filename, std::unordered_map<std::string, Sensor> &sensors);

// Function prototypes for menu options
void analyzeSensorData(const std::unordered_map<std::string, Sensor>& sensors);
void viewAirQualityStatistics(const std::unordered_map<std::string, Sensor>& sensors);
void agencyMenu(const std::unordered_map<std::string, Sensor>& sensors);

int main() {
    std::vector<Attribute> attributes;
    std::vector<Measurement> measurements;
    std::unordered_map<std::string, Sensor> sensors;
    
    // Load data from CSV files for main use
    loadAttributes("Data/dataset/attributes.csv", attributes);
    loadSensors("Data/dataset/sensors.csv", sensors);
    loadMeasurements("Data/dataset/measurements.csv", measurements, sensors);

    std::string role;
    std::cout << "Enter your role (Agency/Provider/Private Individual): ";
    std::cin >> role;

    if (role != "Agency") {
        std::cout << "Role not implemented yet." << std::endl;
        return 0;
    }

    std::string username, password;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (username == "admin" && password == "admin") {
        agencyMenu(sensors);
    } else {
        std::cout << "Authentication failed." << std::endl;
    }

    return 0;
}

void agencyMenu(const std::unordered_map<std::string, Sensor>& sensors) {
    while (true) {
        std::cout << "\nAGENCY MENU\n";
        std::cout << "1. Analyze Sensor Data\n";
        std::cout << "2. View Air Quality Statistics\n";
        std::cout << "3. Ranking sensors compared to the one selected\n";
        std::cout << "4. Observe Cleaner Impact\n"; // not implemented
        std::cout << "5. Manage User Points and Classifications System Settings\n"; // not implemented
        std::cout << "6. Log Out\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                analyzeSensorData(sensors);
                break;
            case 2:
                viewAirQualityStatistics(sensors);
                break;
            case 3:
                std::cout << "Ranking sensors is not implemented yet.\n";
                break;
            case 4:
                std::cout << "Observe Cleaner Impact is not implemented yet.\n";
                break;
            case 5:
                std::cout << "Manage User Points and Classifications System Settings is not implemented yet.\n";
                break;
            case 6:
                std::cout << "Logging out...\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void analyzeSensorData(const std::unordered_map<std::string, Sensor>& sensors) {
    std::cout << "a. Analyze one sensor\n";
    std::cout << "b. Analyze all sensors\n";
    std::cout << "Enter your choice: ";
    char choice;
    std::cin >> choice;

    std::string start, end;
    cout << "Enter the start date (YYYY-MM-DD): ";
    cin >> start;
    cout << "Enter the end date (YYYY-MM-DD): ";
    cin >> end;

    Date startDate = Date::parse(start + " 00:00:00");
    Date endDate = Date::parse(end + " 23:59:59");

    if (choice == 'a') {
        std::string sensorID;
        std::cout << "Enter the sensor ID to analyze: ";
        std::cin >> sensorID;

        SensorManagementServices::SensorAnalyzeResult result = SensorManagementServices::analyzeSensor(sensors, sensorID, startDate, endDate);

        std::cout << "Is Reliable: " << (result.isReliable ? "Yes" : "No") << std::endl;
        std::cout << "Deviation Count: " << result.deviationCount << std::endl;
        std::cout << "Total Count: " << result.totalCount << std::endl;
        std::cout << "Deviation Rate: " << result.deviationRate*100 << "%" << std::endl;
    } else if (choice == 'b') {

        std::cout << "Analyzing all sensors (this might take a few moments...)"<<endl ;
        
        SensorManagementServices::AllSensorsAnalyzeResult results = SensorManagementServices::analyzeAllSensors(sensors, startDate, endDate);

        std::cout << "\nReliable Sensors:\n";
        for (const auto& sensor : results.reliableSensors) {
        std::cout << "Sensor " << sensor.first << " with " << sensor.second << " deviations" << std::endl;
    }

        std::cout << "\nUnreliable Sensors:\n";
        for (const auto& sensor : results.unreliableSensors) {
        std::cout << "Sensor " << sensor.first << " with " << sensor.second << " deviations" << std::endl;
    }
    
    } else {
        std::cout << "Invalid choice. Please try again.\n";
    }
}

void viewAirQualityStatistics(const std::unordered_map<std::string, Sensor>& sensors) {
    double latitude, longitude, radius;
    std::cout << "Enter latitude: ";
    std::cin >> latitude;
    std::cout << "Enter longitude: ";
    std::cin >> longitude;
    std::cout << "Enter radius (default is 10): ";
    std::cin >> radius;
    
    if (radius <= 0) {
        radius = 10;
    }

    std::string startAQ, endAQ;
    std::cout << "Enter the start date (YYYY-MM-DD): ";
    std::cin >> startAQ;
    std::cout << "Enter the end date (YYYY-MM-DD): ";
    std::cin >> endAQ;

    Date startDateAQ = Date::parse(startAQ + " 00:00:00");
    Date endDateAQ = Date::parse(endAQ + " 23:59:59");

    int airQualityIndex = AirQualityGenerationService::analyzeAirQuality(sensors, latitude, longitude, startDateAQ, endDateAQ, radius);

    if (airQualityIndex != -1) {
        std::cout << "Air Quality Index: " << airQualityIndex << std::endl;
    } else {
        std::cout << "No valid ATMO index could be determined for the specified area and period." << std::endl;
    }
}

// Function to load attributes from a CSV file
void loadAttributes(const string &filename, vector<Attribute> &attributes) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string attributeID, unit, description;
            getline(ss, attributeID, ';');
            getline(ss, unit, ';');
            getline(ss, description, ';');
            attributes.emplace_back(attributeID, unit, description);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}

// Function to load measurements from a CSV file
void loadMeasurements(const string &filename, vector<Measurement> &measurements, unordered_map<string, Sensor> &sensors) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string timestampStr, sensorID, attributeID, valueStr;
            double value;
            Date timestamp;
            getline(ss, timestampStr, ';');
            getline(ss, sensorID, ';');
            getline(ss, attributeID, ';');
            getline(ss, valueStr, ';');
            value = stod(valueStr);
            timestamp = Date::parse(timestampStr);
            Measurement newMeasurement(timestamp, attributeID, value);
            measurements.push_back(newMeasurement);
            if (sensors.find(sensorID) == sensors.end()) {
                sensors[sensorID] = Sensor(sensorID, 0.0, 0.0);
            }
            sensors[sensorID].addMeasurement(newMeasurement);
        }
        file.close();
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}

// Function to load sensors from a CSV file
void loadSensors(const string &filename, unordered_map<string, Sensor> &sensors) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string sensorID;
            double latitude, longitude;
            getline(ss, sensorID, ';');
            ss >> latitude;
            ss.ignore();
            ss >> longitude;
            sensors.emplace(sensorID, Sensor(sensorID, latitude, longitude));
        }
        file.close();
    } else {
        cerr << "Unable to open file: " + filename << endl;
    }
}
