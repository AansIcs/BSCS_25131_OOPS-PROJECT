
#define _CRT_SECURE_NO_WARNINGS
#include "Building.h"
#include <ctime>
#include <sstream>
#include <iomanip>

int Building::buildingCounter = 0;

Building::Building(string addr, int year, double area, int numFloors) 
{
    if (year < 1800 || year > 2025) {
        throw BuildingException("Invalid build year: " + to_string(year));
    }

    if (area <= 0) {
        throw BuildingException("Land area must be positive");
    }

    if (numFloors < 1) {
        throw BuildingException("Building must have at least 1 floor");
    }

  
    buildingID = generateBuildingID();
    address = addr;
    buildYear = year;
    landArea = area;
    floors = numFloors;

    // New buildings start in good condition
    condition = 100;
    isOperational = true;

    // Calculate initial value based on land area and floors
    buildingValue = landArea * 500 + floors * 50000; 
    maintenanceCost = 0.0;  
    buildingCounter++;
}

string Building::generateBuildingID() {
   
    time_t now = time(0);
    tm* ltm = localtime(&now); // Current Time

    stringstream ss;
    ss << "BLD-" << (1900 + ltm->tm_year) << setfill('0') << setw(2) << (1 + ltm->tm_mon)<< setfill('0') << setw(2) << ltm->tm_mday << "-" << setfill('0') << setw(4) << buildingCounter;

    return ss.str();
}


int Building::getAge() const { // Building Age
    time_t now = time(0);
    tm* ltm = localtime(&now);
    int currentYear = 1900 + ltm->tm_year;
    return currentYear - buildYear;
}

bool Building::needsMaintenance() const {  // Need Maintenance
    if (condition < 70) {
        return true;
    }

    int age = getAge();
    if (age > 20 && condition < 85) {
        return true;
    }
    return false;
}

void Building::performMaintenance() {
    if (!isOperational) {
        throw BuildingException("Cannot maintain non-operational building: " + buildingID);
    }

    // Restore condition (but not above 95 - can't make it "new" again)
    int oldCondition = condition;
    condition = min(95, condition + 20);
    maintenanceCost = calculateMaintenanceCost();

    cout << "Maintained " << buildingID << ": Condition " << oldCondition << " -> " << condition << endl;
}

void Building::deteriorate() {  // Detoriorate Checking
    int age = getAge();
    int deterioration = 1;

    // Older buildings deteriorate faster
    if (age > 50) {
        deterioration = 3;
    }
    else if (age > 30) {
        deterioration = 2;
    }
    condition -= deterioration;
    if (condition < 0) {
        condition = 0;
    }

    // Building becomes non-operational if too damaged
    if (condition < 30) {
        isOperational = false;
        cout << "WARNING: Building " << buildingID<< " is no longer operational (condition: "<< condition << ")" << endl;
    }
}

void Building::upgrade() {   // Upgrade Building
    if (!isOperational) {
        throw BuildingException("Cannot upgrade non-operational building");
    }

    // Improve condition
    condition = min(100, condition + 15);

    buildingValue *= 1.10;

    cout << "Upgraded " << buildingID << endl;
}

double Building::calculatePropertyTax() const {
    return buildingValue * 0.01;  // 1% property tax
}


void Building::setValue(double value) {
    if (value < 0) {
        throw BuildingException("Building value cannot be negative");
    }
    buildingValue = value;
}

void Building::setCondition(int cond) {
    if (cond < 0 || cond > 100) {
        throw BuildingException("Condition must be between 0 and 100");
    }
    condition = cond;
}

void Building::setOperational(bool status) {
    isOperational = status;
}

Building::~Building() {
    buildingCounter--;
    cout << "Building " << buildingID << " demolished" << endl;
}