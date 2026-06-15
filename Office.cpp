#include "Office.h"
#include "CityExceptions.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
Office::Office(string addr, int year, double area,int floors, string officeName, string industry) : CommercialBuilding(addr, year, area, floors, officeName, "Office")
{
    companyName = officeName;
    industryType = industry;
    conferenceRooms = floors;
    occupiedConferenceRooms = 0;
    hasReception = true;
    hasCafeteria = false;
    hasPrinterRoom = true;
    has24HourAccess = false;
    rentPerSquareMeter = 25.0;
    totalOccupiedSpaces = 0;

    int spacesPerFloor = 5;
    for (int f = 1; f <= floors; f++) {
        for (int s = 1; s <= spacesPerFloor; s++) {
            int spaceNum = f * 100 + s;
            double spaceArea = (area / floors) / spacesPerFloor;
            double lease = spaceArea * rentPerSquareMeter;
            spaces.push_back(OfficeSpace(spaceNum, f, spaceArea, lease));
        }
    }

    cout << "Office '" << businessName << "' (" << industryType << ")"
        << " ready with " << spaces.size() << " spaces" << endl;
}

double Office::calculateMaintenanceCost() const {
    double cost = 0.0;
    cost += landArea * 6.0;
    cost += conferenceRooms * 1000.0;
    if (hasCafeteria) cost += 5000.0;
    if (has24HourAccess) cost += 3000.0;
    cost += spaces.size() * 200.0;

    int age = getAge();
    if (age > 15) cost *= 1.4;
    else if (age > 8) cost *= 1.2;

    return cost;
}

int Office::getDailyVisitors() {
    return totalOccupiedSpaces * 5 + conferenceRooms * 3;
}

string Office::getBuildingType() const {
    return "Office";
}

void Office::displayDetails() const {
    cout << "\n======== OFFICE BUILDING ========" << endl;
    cout << "Company:    " << companyName << endl;
    cout << "Industry:   " << industryType << endl;
    cout << "ID:         " << buildingID << endl;
    cout << "Address:    " << address << endl;
    cout << "Floors:     " << floors << endl;
    cout << "Status:     " << (isOpen ? "OPEN" : "CLOSED") << endl;

    cout << "\n--- Spaces ---" << endl;
    cout << "Total Spaces:     " << spaces.size() << endl;
    cout << "Occupied:         " << totalOccupiedSpaces << endl;
    cout << "Available:        " << getAvailableSpaces() << endl;
    cout << "Occupancy Rate:   "
        << fixed << setprecision(1) << getOccupancyRate() << "%" << endl;

    cout << "\n--- Amenities ---" << endl;
    cout << "Conference Rooms: " << conferenceRooms << endl;
    cout << "Reception:        " << (hasReception ? "Yes" : "No") << endl;
    cout << "Cafeteria:        " << (hasCafeteria ? "Yes" : "No") << endl;
    cout << "24hr Access:      " << (has24HourAccess ? "Yes" : "No") << endl;

    cout << "\n--- Financials ---" << endl;
    cout << "Rate/sqm:         $" << rentPerSquareMeter << "/mo" << endl;
    cout << "Monthly Revenue:  $"
        << fixed << setprecision(2) << monthlyRevenue << endl;
    cout << "=================================\n" << endl;
}

double Office::calculateMonthlyRevenue() {
    double revenue = 0.0;
    for (const OfficeSpace& space : spaces) {
        if (space.isOccupied) {
            revenue += space.monthlyLeaseCost;
        }
    }
    return revenue;
}

void Office::addOfficeSpace(int spaceNum, int floor,
    double area, double lease) {
    if (area <= 0) {
        throw BuildingException("Space area must be positive");
    }
    for (const OfficeSpace& s : spaces) {
        if (s.spaceNumber == spaceNum) {
            throw BuildingException("Space number already exists");
        }
    }
    spaces.push_back(OfficeSpace(spaceNum, floor, area, lease));
    cout << "Office space " << spaceNum << " added" << endl;
}

bool Office::leaseSpace(int spaceNumber, Citizen* occupant, string dept) {
    for (OfficeSpace& s : spaces) {
        if (s.spaceNumber == spaceNumber) {
            if (s.isOccupied) {
                throw BuildingException("Space " + to_string(spaceNumber)+ " is already occupied");
            }
            s.isOccupied = true;
            s.occupant = occupant;
            s.department = dept;
            totalOccupiedSpaces++;
            cout << "Space " << spaceNumber << " leased to dept: " << dept << endl;
            return true;
        }
    }
    throw BuildingException("Space not found: " + to_string(spaceNumber));
}

bool Office::vacateSpace(int spaceNumber) {
    for (OfficeSpace& s : spaces) {
        if (s.spaceNumber == spaceNumber) {
            if (!s.isOccupied) {
                throw BuildingException("Space is already vacant");
            }
            s.isOccupied = false;
            s.occupant = nullptr;
            s.department = "General";
            totalOccupiedSpaces--;
            cout << "Space " << spaceNumber << " vacated" << endl;
            return true;
        }
    }
    throw BuildingException("Space not found: " + to_string(spaceNumber));
}

int Office::getAvailableSpaces() const {
    return (int)spaces.size() - totalOccupiedSpaces;
}

double Office::getOccupancyRate() const {
    if (spaces.empty()) return 0.0;
    return (static_cast<double>(totalOccupiedSpaces) / spaces.size()) * 100.0;
}

void Office::addConferenceRoom() {
    conferenceRooms++;
    buildingValue += 20000.0;
    cout << "Conference room added (Total: " << conferenceRooms << ")" << endl;
}

void Office::addCafeteria() {
    hasCafeteria = true;
    buildingValue *= 1.03;
    cout << "Cafeteria added to " << businessName << endl;
}

void Office::enable24HourAccess() {
    has24HourAccess = true;
    cout << "24-hour access enabled at " << businessName << endl;
}

Office::~Office() {
    spaces.clear();
    cout << "Office '" << businessName << "' vacated" << endl;
}