#ifndef SENSORMANAGEMENTSERVICES_H
#define SENSORMANAGEMENTSERVICES_H

#include <cmath>
#include <vector>
#include <unordered_map>  // Include this to recognize std::unordered_map
#include "Sensor.h"       // Ensure this includes all necessary declarations for Sensor

// Declare the SensorManagementServices class
class SensorManagementServices {
public:

    struct SensorAnalyzeResult {
        bool isReliable;
        int deviationCount;
        int totalCount;
        double deviationRate;
    };

    struct AllSensorsAnalyzeResult {
        std::vector<std::pair<std::string, int>> reliableSensors;
        std::vector<std::pair<std::string, int>> unreliableSensors;
    };

    static std::vector<double> calculateMeans(const Sensor &sensor, const Date& startDate, const Date& endDate);
    static std::vector<double> calculateWeightedMeans(const Sensor &selectedSensor, const std::vector<Sensor> &nearbySensors, const Date& startDate, const Date& endDate);
    static double distance(const Sensor& sensor1, const Sensor& sensor2);
    static double calculateMarginError(double concentration, double weightedConcentration);
    static Sensor closestSensor(const Sensor& sensorSelected, const std::vector<Sensor>& excludedSensors, const std::unordered_map<std::string, Sensor>& allSensors);
    static std::vector<Sensor> findNearbySensors(const Sensor& sensor, const std::unordered_map<std::string, Sensor>& allSensors, int count);
    static std::string getAttributeIDByIndex(size_t index);
    static SensorAnalyzeResult analyzeSensor(const std::unordered_map<std::string, Sensor> &sensors, std::string sensorID, const Date &startDate, const Date &endDate);
    static AllSensorsAnalyzeResult analyzeAllSensors(const std::unordered_map<std::string, Sensor>& sensors, const Date& startDate, const Date& endDate);
};

#endif