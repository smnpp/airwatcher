#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <ctime>
#include <string>
#include <functional> // Pour std::hash

class Date {
private:
    int year, month, day, hour, minute, second;

public:
    Date(); // Default constructor
    Date(int y, int m, int d, int h, int min, int s); // Parameterized constructor

    static Date parse(const std::string& dateString); // Parses date from string
    time_t to_time_t() const; // Converts Date to time_t

    Date addDays(int days) const; // Adds days to the date

    bool operator>=(const Date& other) const; // Comparison operator
    bool operator<=(const Date& other) const; // Comparison operator
    bool operator==(const Date& other) const; // Equality operator


    friend std::ostream& operator<<(std::ostream& os, const Date& dt); // Output stream overload

    int daysTo(const Date& other) const; // Returns the number of days between two dates 

    // Fonction de hachage pour la classe Date
    struct HashFunction {
        std::size_t operator()(const Date& date) const {
            std::size_t h1 = std::hash<int>()(date.year);
            std::size_t h2 = std::hash<int>()(date.month);
            std::size_t h3 = std::hash<int>()(date.day);
            std::size_t h4 = std::hash<int>()(date.hour);
            std::size_t h5 = std::hash<int>()(date.minute);
            std::size_t h6 = std::hash<int>()(date.second);
            return h1 ^ h2 ^ h3 ^ h4 ^ h5 ^ h6; // Combine les hachages
        }
    };
};

#endif // DATE_H
