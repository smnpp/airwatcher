// Cleaner.h
#ifndef CLEANER_H
#define CLEANER_H

#include "Date.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>


class Cleaner {
public:
    Cleaner(std::string id, double latitude, double longitude, Date startDate, Date endDate);

protected:
    std::string id;
    double latitude;
    double longitude;
    Date startDate;
    Date endDate;
};

#endif  // CLEANER_H