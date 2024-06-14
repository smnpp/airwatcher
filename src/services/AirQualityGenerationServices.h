#ifndef AIR_QUALITY_GENERATION_SERVICE_H
#define AIR_QUALITY_GENERATION_SERVICE_H

#include "Sensor.h"
#include "Date.h"
#include <vector>
#include <unordered_map>

class AirQualityGenerationService {
public:
    // Function to generate air quality statistics
    static std::vector<Sensor> findSensorsInArea(const std::unordered_map<std::string, Sensor>& sensors,
                                                 double lat, double lon, double radius);
    static std::vector<double> calculateAverageConcentrations(const std::vector<Sensor>& sensors,
                                                              const Date& startDate, const Date& endDate);
    static int determineATMOIndex(const std::vector<double>& concentrations);

    static int analyzeAirQuality(const std::unordered_map<std::string, Sensor>& sensors, double latitude, double longitude, const Date& startAQ, const Date& endAQ, double radius = 10);

};

#endif // AIR_QUALITY_GENERATION_SERVICE_H
