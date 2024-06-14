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
void analyzeSensorDataValidation(const std::unordered_map<std::string, Sensor> &sensors);
void viewAirQualityStatisticsValidation(const std::unordered_map<std::string, Sensor> &sensors);
void findNearbySensorsValidation(const std::unordered_map<std::string, Sensor> &sensors);
void calculateMeans(const Sensor &sensor, const Date &start, const Date &end);
void distanceValidation(const std::unordered_map<std::string, Sensor> &sensors, const string sensor);
void calculateweightedMeansValidation(const string sensor, const std::unordered_map<std::string, Sensor> &sensors, const Date &start, const Date &end);
int main()
{

    std::vector<Attribute> attributes;
    std::vector<Measurement> measurements;
    std::unordered_map<std::string, Sensor> sensors;

    int choice;

    std::cout << "Which Validation Test or Unit Test shall you run ?" << std::endl
              << "---------------------" << std::endl
              << " VALIDATION TESTS : " << std::endl
              << "1. Analyze Sensor Data" << std::endl
              << "2. View Air Quality Statistics" << std::endl
              << "---------------------" << std::endl
              << " UNIT TESTS : " << std::endl
              << "3. Nearby sensor" << std::endl
              << "4. Calculate Means" << std::endl
              << "5. Euclidian Distance " << std::endl
              << "6. Calculate Weighted Means " << std::endl
              << "7. Calculate Margin error " << std::endl;
    std::cin >> choice;
    std::cout << "---------------------" << std::endl;
    if (choice == 1)
    {
        loadAttributes("Data/dataset/attributes.csv", attributes);
        loadSensors("ValidationTests/SensorAnalysis/sensors1.csv", sensors);
        loadMeasurements("ValidationTests/SensorAnalysis/measurements1.csv", measurements, sensors);
        analyzeSensorDataValidation(sensors);
    }
    else if (choice == 2)
    {
        loadAttributes("Data/dataset/attributes.csv", attributes);
        loadSensors("ValidationTests/Statistics/sensors2.csv", sensors);
        loadMeasurements("ValidationTests/Statistics/measurements2.csv", measurements, sensors);
        viewAirQualityStatisticsValidation(sensors);
    }
    else if (choice == 3)
    {
        char choice2;
        cout << "a.Correct Test" << std::endl;
        cout << "b.Test with 4 sensor asked but there are only 3" << std::endl;
        cout << "c.Reference sensor doesn't exist" << std::endl;
        cout << "d.No other sensor than the reference in the csv" << std::endl;
        cout << "Enter your choice: ";
        cin >> choice2;
        if (choice2 == 'a')
        {
            loadAttributes("Data/dataset/attributes.csv", attributes);
            loadSensors("ValidationTests/FindNearbySensors/sensors1.csv", sensors);
            findNearbySensorsValidation(sensors);
        }
        else if (choice2 == 'b')
        {
            loadAttributes("Data/dataset/attributes.csv", attributes);
            loadSensors("ValidationTests/FindNearbySensors/sensors2.csv", sensors);
            findNearbySensorsValidation(sensors);
        }
        else if (choice2 == 'c')
        {
            loadAttributes("Data/dataset/attributes.csv", attributes);
            loadSensors("ValidationTests/FindNearbySensors/sensors3.csv", sensors);
            findNearbySensorsValidation(sensors);
        }
        else if (choice2 == 'd')
        {
            loadAttributes("Data/dataset/attributes.csv", attributes);
            loadSensors("ValidationTests/FindNearbySensors/sensors4.csv", sensors);
            findNearbySensorsValidation(sensors);
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    else if (choice == 4)
    {
        char choice2;
        cout << "a.Correct Test" << std::endl;
        cout << "b.Mean asked for a sensor not in the csv" << std::endl;
        cout << "c.Mean asked for a sensor with no measurements during the period" << std::endl;

        cout << "Enter your choice: ";
        cin >> choice2;
        if (choice2 == 'a')
        {
            loadSensors("ValidationTests/CalculateMeans/sensors1.csv", sensors);
            loadMeasurements("ValidationTests/CalculateMeans/measurements1.csv", measurements, sensors);

            Sensor sensor57; // Declare and initialize sensor57 variable
            Date start = Date::parse("2018-12-31 12:00:00");
            Date end = Date::parse("2019-02-02 12:00:00");
            for (const auto &sensor : sensors)
            {
                if (sensor.first == "Sensor57")
                {
                    sensor57 = sensor.second; // Assign sensor57 value
                }
            };
            std ::cout << "Sensor57 " << "We'll calculate means for Sensor57" << endl;
            std ::cout << "Sensor57 " << "We have set the measurements to 47, 50, 48, 49 so these values must be displayed " << endl;
            calculateMeans(sensor57, start, end);
        }
        else if (choice2 == 'b')
        {
            loadSensors("ValidationTests/CalculateMeans/sensors1.csv", sensors);
            loadMeasurements("ValidationTests/CalculateMeans/measurements1.csv", measurements, sensors);
            Sensor sensor0; // Declare and initialize sensor0 variable
            Date start = Date::parse("2018-12-31 12:00:00");
            Date end = Date::parse("2019-02-02 12:00:00");
            std ::cout << "Sensor0 " << "is not in the csv so means are null" << endl;
            calculateMeans(sensor0, start, end);
        }
        else if (choice2 == 'c')
        {
            loadSensors("ValidationTests/CalculateMeans/sensors1.csv", sensors);
            loadMeasurements("ValidationTests/CalculateMeans/measurements1.csv", measurements, sensors);
            Sensor sensor66; // Declare and initialize sensor57 variable
            Date start = Date::parse("2019-03-01 12:00:00");
            Date end = Date::parse("2019-04-01 12:00:00");
            for (const auto &sensor : sensors)
            {
                if (sensor.first == "Sensor66")
                {
                    sensor66 = sensor.second; // Assign sensor57 value
                }
            };
            cout << sensor66.getSensorID() << " has no measurement in the specified time period" << endl;
            calculateMeans(sensor66, start, end);
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    else if (choice == 5)
    {

        char choice2;
        cout << "a.Correct Test" << std::endl;

        cout << "Enter your choice: ";
        cin >> choice2;
        if (choice2 == 'a')
        {
            loadSensors("ValidationTests/Distance/sensors1.csv", sensors);
            distanceValidation(sensors, "Sensor66");
        }

        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    else if (choice == 6)
    {
        char choice2;
        cout << "a.Correct Test" << std::endl;
        cout << "b.The selectedSensor doesn’t have nearby sensors " << std::endl;
        cout << "c.There are no measurements during the period of time" << std::endl;

        cout << "Enter your choice: ";
        cin >> choice2;
        if (choice2 == 'a')
        {
            loadSensors("ValidationTests/CalculateWeightedMeans/sensors1.csv", sensors);
            loadMeasurements("ValidationTests/CalculateWeightedMeans/measurements1.csv", measurements, sensors);
            Date start = Date::parse("2018-12-31 12:00:00");
            Date end = Date::parse("2019-04-02 12:00:00");
            calculateweightedMeansValidation("Sensor57", sensors, start, end);
        }
        else if (choice2 == 'b')
        {
            loadSensors("ValidationTests/CalculateWeightedMeans/sensors2.csv", sensors);
            loadMeasurements("ValidationTests/CalculateWeightedMeans/measurements1.csv", measurements, sensors);
            Date start = Date::parse("2018-12-31 12:00:00");
            Date end = Date::parse("2019-04-02 12:00:00");
            calculateweightedMeansValidation("Sensor57", sensors, start, end);
        }
        else if (choice2 == 'c')
        {
            loadSensors("ValidationTests/CalculateWeightedMeans/sensors1.csv", sensors);
            loadMeasurements("ValidationTests/CalculateWeightedMeans/measurements1.csv", measurements, sensors);
            Date start = Date::parse("2019-04-02 12:00:00");
            Date end = Date::parse("2020-01-01 12:00:00");
            calculateweightedMeansValidation("Sensor57", sensors, start, end);
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }
    else if (choice == 7)
    {
        char choice2;
        cout << "a.Correct Test : we test the margin error of value 45 compared to 50 : it's 0.1" << std::endl;
        cout << "b.Margin error with a division by 0 : the result must return 0 instead of NaN" << std::endl;

        cout << "Enter your choice: ";
        cin >> choice2;
        if (choice2 == 'a')
        {
            double test = SensorManagementServices::calculateMarginError(45, 50);
            cout << test << endl;
        }
        else if (choice2 == 'b')
        {
            double test = SensorManagementServices::calculateMarginError(45, 0);

            cout << test << endl;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }

    else
    {
        cout << "Invalid choice." << endl;
    }
    return 0;
} // Add this closing brace to complete the main function declaration

void analyzeSensorDataValidation(const std::unordered_map<std::string, Sensor> &sensors)
{
    std::cout << "From 2019-01-01 to 2019-01-07 : All the sensors provide coherent data. They are declared reliable. Test this scenario through menus 1) then b.\n" << endl;
    std::cout << "From 2019-02-01 to 2019-02-07 : We changed Sensor 67 measurement of O3 to make it incoherent to the others sensors measurements of O3, so Sensor67 presents more than 20 percent of its measurements deviating." << endl;
    std::cout << "It is considered unreliable : test this scenario through menus 1) then a. and enter ID 67. Identically, if any other, or all measure is incoherent, the sensor will still be considered unreliable, so no need to set another data set for such a scenario.\n" << endl;
    std::cout << "From 2019-03-01 to 2019-03-07 : Sensor 67 is the only sensor which provides data : we have no measurements to compare it with and it is therefore considered reliable.\n" << endl;
    std::cout << "NB : As we have only set 5 sensors in the data set, deviation of Sensor67 could influence deviation of other sensors due to the method used to compute weighted means. We therefore neglect all other sensors while running second and third tests (use of analyseSensor service that only analyzes one sensor at a time)." << endl;

    std::cout << endl;

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

    if (choice == 'a')
    {
        std::string sensorID;
        std::cout << "Enter the sensor ID to analyze: ";
        std::cin >> sensorID;

        SensorManagementServices::SensorAnalyzeResult result = SensorManagementServices::analyzeSensor(sensors, sensorID, startDate, endDate);

        std::cout << "Is Reliable: " << (result.isReliable ? "Yes" : "No") << std::endl;
        std::cout << "Deviation Count: " << result.deviationCount << std::endl;
        std::cout << "Total Count: " << result.totalCount << std::endl;
        std::cout << "Deviation Rate: " << result.deviationRate * 100 << "%" << std::endl;
    }
    else if (choice == 'b')
    {

        SensorManagementServices::AllSensorsAnalyzeResult results = SensorManagementServices::analyzeAllSensors(sensors, startDate, endDate);

        std::cout << "\nReliable Sensors:\n";
        for (const auto &sensor : results.reliableSensors)
        {
            std::cout << "Sensor " << sensor.first << " with " << sensor.second << " deviations" << std::endl;
        }

        std::cout << "\nUnreliable Sensors:\n";
        for (const auto &sensor : results.unreliableSensors)
        {
            std::cout << "Sensor " << sensor.first << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid choice. Please try again.\n";
    }
}

void viewAirQualityStatisticsValidation(const std::unordered_map<std::string, Sensor> &sensors)
{
    std::cout << "The files contained in ValidationTests/Statistics contain 5 sensors that measured pollutants concentrations from 2019-01-01 to 2019-12-31. Let’s focus on the area centered around Sensor11, with a radius of 1000 km." << endl;
    std::cout << "The specified area therefore comprises sensors 11 , 12 , 13 , 21 , 22. The manually determined average concentration of pollutants is :" << endl;
    std::cout << "68.974 for NO2 –> NO2 ATMO Index = 3" << endl;
    std::cout << "65.255 for O3 –> O3 ATMO Index = 3" << endl;
    std::cout << "30.132 for PM10 –> PM10 ATMO Index = 5" << endl;
    std::cout << "88.936 for SO2 –> SO2 ATMO Index = 3" << endl;

    std::cout << endl;
    std::cout << "Therefore, for lat = 44 , long = 0 , radius = 1000, start date = 2019-01-01, end date = 2019-12-31, the global ATMO Index of the area must be 5." << endl;
    std::cout << "If there are no measurements in the specified time period : for lat = 44 , long = 0 , radius = 1000, start date = 2020-01-01, end date = 2020-12-31, the global ATMO Index of the area must also be null." << endl;
    std::cout << "If there are no sensors in the specified area : Let’s center the measures around a single point where no sensor is placed : for lat = 70, long = 70, radius = 0, start date and end end date don’t matter, the index must be null." << endl;

    std::cout << endl;

    double latitude, longitude, radius;
    std::cout << "Enter latitude: ";
    std::cin >> latitude;
    std::cout << "Enter longitude: ";
    std::cin >> longitude;
    std::cout << "Enter radius (default is 10): ";
    std::cin >> radius;

    if (radius <= 0)
    {
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

    if (airQualityIndex != -1)
    {
        std::cout << "Air Quality Index: " << airQualityIndex << std::endl;
    }
    else
    {
        std::cout << "No valid ATMO index could be determined for the specified area and period." << std::endl;
    }
}

void findNearbySensorsValidation(const std::unordered_map<std::string, Sensor> &sensors)
{
    std::cout << "The files contained in ValidationTests/FindNearbySensors initially contain 6 sensors : 57 , 66 , 67 , 68 , 77 and 100" << endl;
    std::cout << "Let's focus on Sensor 57" << endl;
    std::cout << "For test a : Sensor100 is chosen such as it is too far from Sensor57 : the other four sensors are therefore the nearby ones" << endl;
    std::cout << "For test b : we've removed three sensors : only 3 are left in the dataset. These two latter (66 and 67) are the two closest to 57 (can't display four sensors)  " << endl;
    std::cout << "For test c : we want to display the closest sensors to a sensor no set in the dataset. The computation can't be done." << endl;
    std::cout << "For test d : the only sensor in the dataset is Sensor57, so the computation can't be done" << endl;

    Sensor sensor57;

    for (const auto &sensor : sensors)
    {
        if (sensor.first == "Sensor57")
        {
            sensor57 = sensor.second; // Assign sensor57 value
        }
    };

    vector<Sensor> nearbySensors = SensorManagementServices::findNearbySensors(sensor57, sensors, 4); // Pass sensor57 as argument
    size_t taille = nearbySensors.size();
    std::cout << "The sensors nearby Sensor57 are : " << endl;
    for (size_t i = 0; i < taille; i++)
    {
        cout << nearbySensors[i].getSensorID() << endl;
    }
}
void calculateMeans(const Sensor &sensor, const Date &start, const Date &end)
{

    vector<double> resultat = SensorManagementServices::calculateMeans(sensor, start, end);
    for (size_t i = 0; i < resultat.size(); i++)
    {
        cout << resultat[i] << endl;
    }
}
void distanceValidation(const std::unordered_map<std::string, Sensor> &sensors, const string sensort)
{
    std::cout << "The files contained in ValidationTests/Distance initially contain 2 sensors : 57 (coordinates 46.0 ; 3.9) and 66 (coordinates 46.4 ; 3.2) " << endl;
    std::cout << "The distance between the two is 0.806226" << endl;
    Sensor sensor57;
    Sensor sensorTest;
    for (const auto &sensor : sensors)
    {
        if (sensor.first == "Sensor57")
        {
            sensor57 = sensor.second; // Assign sensor57 value
        }
        if (sensor.first == sensort)
        {
            sensorTest = sensor.second; // Assign sensor57 value
        }
    };

    double distance = SensorManagementServices::distance(sensor57, sensorTest);
    cout << "The distance is " << distance << endl;
}
void calculateweightedMeansValidation(const string sensort, const std::unordered_map<std::string, Sensor> &sensors, const Date &start, const Date &end)
{
    std::cout << "The files contained in ValidationTests/CalculateWeightedMeans initially contain 6 sensors : 57 , 66 , 67 , 68 , 77 and 100" << endl;
    std::cout << "Let's focus on Sensor 57" << endl;
    std::cout << "The closest sensors are Sensor66 , 67 , 68 , 77" << endl;
    std::cout << "The distances to these sensors are 0.806226 , 0.4 , 0.806226 , 0.8 respectively" << endl;
    std::cout << "The means vectors are 47 50 48 40 , 47 50 48 41, 47 50 48 42, 47 50 48 42 respectively" << endl;
    std::cout << "For test a : the three first values of the weighted means vector are 47 50 48" << endl;
    std::cout << "The fourth weighted mean is (40/0.806226 + 41/0.4 + 42/0.806226 + 42/0.8) / (1/0.806226 + 1/0.4 + 1/0.806226 + 1/0.8) = 41.2006" << endl;
    std::cout << "For tests b : there are no closest sensors so weighted means are means of Sensor 57" << endl;
    std::cout << "For tests c : there are no measurements during the period of time so weighted means are 0 0 0 0" << endl;
    Sensor sensorp;
    for (const auto &sensor : sensors)
    {
        if (sensor.first == sensort)
        {
            sensorp = sensor.second;
        }
    };
    vector<Sensor> nearbySensors = SensorManagementServices::findNearbySensors(sensorp, sensors, 4);
    vector<double> resultat = SensorManagementServices::calculateWeightedMeans(sensorp, nearbySensors, start, end);
    for (size_t i = 0; i < resultat.size(); i++)
    {
        cout << resultat[i] << endl;
    }
}

void loadAttributes(const string &filename, vector<Attribute> &attributes)
{
    ifstream file(filename);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            string attributeID, unit, description;
            getline(ss, attributeID, ';');
            getline(ss, unit, ';');
            getline(ss, description, ';');
            attributes.emplace_back(attributeID, unit, description);
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file: " + filename << endl;
    }
}

// Function to load measurements from a CSV file
void loadMeasurements(const string &filename, vector<Measurement> &measurements, unordered_map<string, Sensor> &sensors)
{
    ifstream file(filename);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
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
            if (sensors.find(sensorID) == sensors.end())
            {
                sensors[sensorID] = Sensor(sensorID, 0.0, 0.0);
            }
            sensors[sensorID].addMeasurement(newMeasurement);
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file: " + filename << endl;
    }
}

// Function to load sensors from a CSV file
void loadSensors(const string &filename, unordered_map<string, Sensor> &sensors)
{
    ifstream file(filename);
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
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
    }
    else
    {
        cerr << "Unable to open file: " + filename << endl;
    }
}
