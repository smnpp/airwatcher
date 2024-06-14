// Include necessary header files from the Data directory
#include "../Data/Attribute.h"
#include "../Data/Date.h"
#include "../Data/Measurement.h"
#include "../Data/Sensor.h"

// Include services from the Services directory
#include "SensorManagementServices.h"
#include "AirQualityGenerationServices.h"


#include <cmath>
#include <algorithm>
#include <unordered_map>


// Function to find sensors within a specified radius
std::vector<Sensor> AirQualityGenerationService::findSensorsInArea(const std::unordered_map<std::string, Sensor>& sensors,
                                                                   double lat, double lon, double radius) {
    std::vector<Sensor> localSensors;
    for (const auto& sensorPair : sensors) {
        const Sensor& sensor = sensorPair.second;
        double distance = std::sqrt(std::pow(sensor.getLatitude() - lat, 2) + std::pow(sensor.getLongitude() - lon, 2));
        if (distance <= radius) {
            localSensors.push_back(sensor);
        }
    }
    return localSensors;
}


// Function to calculate average concentrations of pollutants
std::vector<double> AirQualityGenerationService::calculateAverageConcentrations(const std::vector<Sensor>& sensors,
                                                                                const Date& startDate, const Date& endDate) {
    std::vector<double> averages(4, 0.0); // Assuming 4 pollutants: O3, SO2, NO2, PM10
    if (sensors.empty()) return averages;

    std::vector<double> sums(4, 0.0);
    std::vector<int> counts(4, 0);

    // Use SensorManagementServices to calculate means for each sensor in the specified area and period
    for (const Sensor& sensor : sensors) {
        std::vector<double> means = SensorManagementServices::calculateMeans(sensor, startDate, endDate);
        for (size_t i = 0; i < means.size(); i++) {
            if (means[i] > 0) { // Only add to sums if there were measurements
                sums[i] += means[i];
                counts[i]++;
            }
        }
    }

    // Calculate the average from the sums and counts
    for (size_t i = 0; i < averages.size(); i++) {
        if (counts[i] > 0) {
            averages[i] = sums[i] / counts[i];
        }
    }

    return averages;
}


// Function to determine the ATMO index based on the calculated averages
int AirQualityGenerationService::determineATMOIndex(const std::vector<double>& concentrations) {
    std::vector<int> atmoIndexes(4, 0);

    // Check O3 concentrations
    if (concentrations[0] >= 0 && concentrations[0] <= 29) {
        atmoIndexes[0] = 1;
    } else if (concentrations[0] <= 54) {
        atmoIndexes[0] = 2;
    } else if (concentrations[0] <= 79) {
        atmoIndexes[0] = 3;
    } else if (concentrations[0] <= 104) {
        atmoIndexes[0] = 4;
    } else if (concentrations[0] <= 129) {
        atmoIndexes[0] = 5;
    } else if (concentrations[0] <= 149) {
        atmoIndexes[0] = 6;
    } else if (concentrations[0] <= 179) {
        atmoIndexes[0] = 7;
    } else if (concentrations[0] <= 209) {
        atmoIndexes[0] = 8;
    } else if (concentrations[0] <= 239) {
        atmoIndexes[0] = 9;
    } else if (concentrations[0] >= 240) {
        atmoIndexes[0] = 10;
    }

    // Check SO2 concentrations
    if (concentrations[1] <= 39) {
        atmoIndexes[1] = 1;
    } else if (concentrations[1] <= 79) {
        atmoIndexes[1] = 2;
    } else if (concentrations[1] <= 119) {
        atmoIndexes[1] = 3;
    } else if (concentrations[1] <= 159) {
        atmoIndexes[1] = 4;
    } else if (concentrations[1] <= 199) {
        atmoIndexes[1] = 5;
    } else if (concentrations[1] <= 249) {
        atmoIndexes[1] = 6;
    } else if (concentrations[1] <= 299) {
        atmoIndexes[1] = 7;
    } else if (concentrations[1] <= 399) {
        atmoIndexes[1] = 8;
    } else if (concentrations[1] <= 499) {
        atmoIndexes[1] = 9;
    } else if (concentrations[1] >= 500) {
        atmoIndexes[1] = 10;
    }

    // Check NO2 concentrations
    if (concentrations[2] <= 29) {
        atmoIndexes[2] = 1;
    } else if (concentrations[2] <= 54) {
        atmoIndexes[2] = 2;
    } else if (concentrations[2] <= 84) {
        atmoIndexes[2] = 3;
    } else if (concentrations[2] <= 109) {
        atmoIndexes[2] = 4;
    } else if (concentrations[2] <= 134) {
        atmoIndexes[2] = 5;
    } else if (concentrations[2] <= 164) {
        atmoIndexes[2] = 6;
    } else if (concentrations[2] <= 199) {
        atmoIndexes[2] = 7;
    } else if (concentrations[2] <= 274) {
        atmoIndexes[2] = 8;
    } else if (concentrations[2] <= 399) {
        atmoIndexes[2] = 9;
    } else if (concentrations[2] >= 400) {
        atmoIndexes[2] = 10;
    }

    // Check PM10 concentrations
    if (concentrations[3] <= 6) {
        atmoIndexes[3] = 1;
    } else if (concentrations[3] <= 13) {
        atmoIndexes[3] = 2;
    } else if (concentrations[3] <= 20) {
        atmoIndexes[3] = 3;
    } else if (concentrations[3] <= 27) {
        atmoIndexes[3] = 4;
    } else if (concentrations[3] <= 34) {
        atmoIndexes[3] = 5;
    } else if (concentrations[3] <= 41) {
        atmoIndexes[3] = 6;
    } else if (concentrations[3] <= 49) {
        atmoIndexes[3] = 7;
    } else if (concentrations[3] <= 64) {
        atmoIndexes[3] = 8;
    } else if (concentrations[3] <= 79) {
        atmoIndexes[3] = 9;
    } else if (concentrations[3] >= 80) {
        atmoIndexes[3] = 10;
    }

    // Determine the highest index from all pollutants
    int highestIndex = *std::max_element(atmoIndexes.begin(), atmoIndexes.end());
    return highestIndex;
}

    int AirQualityGenerationService::analyzeAirQuality(const std::unordered_map<std::string, Sensor>& sensors, double latitude, double longitude, const Date& startAQ, const Date& endAQ, double radius) 
    {
    int ATMOIndex = -1; // Default value for ATMO index

    std::vector<Sensor> areaSensors = AirQualityGenerationService::findSensorsInArea(sensors, latitude, longitude, radius);
    if (!areaSensors.empty()&& calculateAverageConcentrations(areaSensors,startAQ, endAQ) != std::vector<double>{0.0,0.0,0.0,0.0})
    {
    std::vector<double> averageConcentrations = AirQualityGenerationService::calculateAverageConcentrations(areaSensors,startAQ, endAQ);
    ATMOIndex = AirQualityGenerationService::determineATMOIndex(averageConcentrations);
    }
    return ATMOIndex;
    }