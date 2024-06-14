#include "Date.h"

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <tuple>

Date::Date() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

Date::Date(int y, int m, int d, int h, int min, int s)
    : year(y), month(m), day(d), hour(h), minute(min), second(s) {}

Date Date::parse(const std::string& dateString) {
    std::tm tm = {};
    std::istringstream ss(dateString);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        throw std::runtime_error("Failed to parse date string: " + dateString);
    }
    return Date(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

time_t Date::to_time_t() const {
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;
    return std::mktime(&tm);
}

Date Date::addDays(int days) const {
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day + days;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;
    time_t t = std::mktime(&tm);
    std::tm* new_tm = std::localtime(&t);
    return Date(new_tm->tm_year + 1900, new_tm->tm_mon + 1, new_tm->tm_mday, new_tm->tm_hour, new_tm->tm_min, new_tm->tm_sec);
}

bool Date::operator>=(const Date& other) const {
    return std::tie(year, month, day, hour, minute, second) >= std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
}

bool Date::operator<=(const Date& other) const {
    return std::tie(year, month, day, hour, minute, second) <= std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
}

bool Date::operator==(const Date& other) const {
    return std::tie(year, month, day, hour, minute, second) == std::tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
}

std::ostream& operator<<(std::ostream& os, const Date& dt) {
    os << std::setw(4) << std::setfill('0') << dt.year << '-'
       << std::setw(2) << std::setfill('0') << dt.month << '-'
       << std::setw(2) << std::setfill('0') << dt.day << ' '
       << std::setw(2) << std::setfill('0') << dt.hour << ':'
       << std::setw(2) << std::setfill('0') << dt.minute << ':'
       << std::setw(2) << std::setfill('0') << dt.second;
    return os;
}

int Date::daysTo(const Date& other) const {
    std::tm tm1 = {};
    tm1.tm_year = year - 1900;
    tm1.tm_mon = month - 1;
    tm1.tm_mday = day;
    tm1.tm_hour = hour;
    tm1.tm_min = minute;
    tm1.tm_sec = second;

    std::tm tm2 = {};
    tm2.tm_year = other.year - 1900;
    tm2.tm_mon = other.month - 1;
    tm2.tm_mday = other.day;
    tm2.tm_hour = other.hour;
    tm2.tm_min = other.minute;
    tm2.tm_sec = other.second;

    time_t t1 = std::mktime(&tm1);
    time_t t2 = std::mktime(&tm2);

    double difference = difftime(t2, t1);
    return difference / (60 * 60 * 24);
}