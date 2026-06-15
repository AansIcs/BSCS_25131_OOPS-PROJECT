#include "Mall.h"
#include "CityExceptions.h"
#include"Shop.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
Mall::Mall(string addr, int year, double area,int floors, string name, int totalStores): CommercialBuilding(addr, year, area, floors, name, "Mixed Retail")
{
    if (totalStores < 1) {
        throw BuildingException("Mall must have at least 1 store space");
    }

    mallName = name;
    hasFoodCourt = false;
    foodCourtCapacity = 0;
    hasCinema = false;
    cinemaScreens = 0;
    hasAmusementArea = false;
    parkingLevels = 1;
    totalParkingSpots = totalStores * 10;
    weekdayFootTraffic = totalStores * 50;
    weekendFootTraffic = totalStores * 120;
    managementCompany = "Self-Managed";

    int storesPerFloor = totalStores / floors;
    if (storesPerFloor < 1) storesPerFloor = 1;

    int storeCount = 0;
    for (int f = 1; f <= floors && storeCount < totalStores; f++) {
        for (int s = 1; s <= storesPerFloor && storeCount < totalStores; s++) {
            int storeNum = f * 100 + s;
            double storeArea = (area / floors) / storesPerFloor;
            double rent = storeArea * 50.0 / f;

            string cat = "General";
            if (s <= storesPerFloor / 3) cat = "Food";
            else if (s <= storesPerFloor * 2 / 3) cat = "Clothing";
            else cat = "Electronics";

            storeSpaces.push_back(StoreSpace(storeNum, storeArea, rent, cat));
            storeCount++;
        }
    }

    cout << "Mall '" << mallName << "' built with "
        << storeSpaces.size() << " store spaces" << endl;
}

double Mall::calculateMaintenanceCost()const {
    double cost = 0.0;

    cost += landArea * 8.0;
    cost += storeSpaces.size() * 1000.0;
    cost += floors * 2000.0;
    cost += totalParkingSpots * 50.0;

    if (hasFoodCourt) cost += foodCourtCapacity * 20.0;
    if (hasCinema) cost += cinemaScreens * 5000.0;
    if (hasAmusementArea) cost += 10000.0;

    cost += storeSpaces.size() * 500.0;

    int age = getAge();
    if (age > 20) cost *= 2.0;
    else if (age > 10) cost *= 1.5;

    return cost;
}

int Mall::getDailyVisitors() {
    double avgDaily = (weekdayFootTraffic * 5 + weekendFootTraffic * 2) / 7.0;

    if (hasCinema) avgDaily += cinemaScreens * 200;
    if (hasFoodCourt) avgDaily += foodCourtCapacity * 0.5;

    return static_cast<int>(avgDaily);
}

string Mall::getBuildingType() const {
    return "Mall";
}

void Mall::displayDetails() const {
    cout << "\n============ MALL ============" << endl;
    cout << "Name:     " << mallName << endl;
    cout << "ID:       " << buildingID << endl;
    cout << "Address:  " << address << endl;
    cout << "Floors:   " << floors << endl;
    cout << "Status:   " << (isOpen ? "OPEN" : "CLOSED") << endl;

    cout << "\n--- Stores ---" << endl;
    cout << "Total Spaces:  " << storeSpaces.size() << endl;
    cout << "Occupied:      " << getOccupiedStores() << endl;
    cout << "Available:     " << getAvailableStores() << endl;
    cout << "Occupancy:     "
        << fixed << setprecision(1) << getOccupancyRate() << "%" << endl;

    cout << "\n--- Facilities ---" << endl;
    if (hasFoodCourt) {
        cout << "Food Court:    Yes (" << foodCourtCapacity << " seats)" << endl;
    }
    if (hasCinema) {
        cout << "Cinema:        Yes (" << cinemaScreens << " screens)" << endl;
    }
    cout << "Amusement:     " << (hasAmusementArea ? "Yes" : "No") << endl;
    cout << "Parking:       " << parkingLevels << " level(s), "
        << totalParkingSpots << " spots" << endl;

    cout << "\n--- Traffic ---" << endl;
    cout << "Weekday avg:   " << (int)weekdayFootTraffic << " visitors" << endl;
    cout << "Weekend avg:   " << (int)weekendFootTraffic << " visitors" << endl;
    cout << "\n--- Financials ---" << endl;
    cout << "Monthly Revenue: $"
        << fixed << setprecision(2) << monthlyRevenue << endl;
    cout << "Annual Maint:    $"
        << fixed << setprecision(2) << calculateMaintenanceCost() << endl;
    cout << "==============================\n" << endl;
}

double Mall::calculateMonthlyRevenue() {
    double revenue = 0.0;

    for (const StoreSpace& space : storeSpaces) {
        if (space.isRented) {
            revenue += space.monthlyRent;
        }
    }

    if (hasCinema) {
        revenue += cinemaScreens * 20000.0;
    }

    if (hasFoodCourt) {
        revenue += foodCourtCapacity * 30.0;
    }
    revenue += totalParkingSpots * getDailyVisitors() * 0.01 * 30;

    return revenue;
}

Shop* Mall::openStore(int storeNumber, string shopName,
    string category, int year) {
    for (StoreSpace& space : storeSpaces) {
        if (space.storeNumber == storeNumber) {
            if (space.isRented) {
                throw BuildingException("Store space " + to_string(storeNumber)
                    + " is already occupied");
            }

            Shop* newShop = new Shop(address + " #" + to_string(storeNumber),year,space.areaSquareMeters,1,shopName,category);

            space.isRented = true;
            space.tenant = newShop;

            cout << "Store '" << shopName << "' opened in space "
                << storeNumber << endl;
            return newShop;
        }
    }
    throw BuildingException("Store space " + to_string(storeNumber)
        + " not found");
}

void Mall::closeStore(int storeNumber) {
    for (StoreSpace& space : storeSpaces) {
        if (space.storeNumber == storeNumber) {
            if (!space.isRented) {
                throw BuildingException("Store space "
                    + to_string(storeNumber)
                    + " is already empty");
            }

            delete space.tenant;
            space.tenant = nullptr;
            space.isRented = false;

            cout << "Store in space " << storeNumber << " closed" << endl;
            return;
        }
    }
    throw BuildingException("Store space not found: " + to_string(storeNumber));
}

int Mall::getOccupiedStores() const {
    int count = 0;
    for (const StoreSpace& s : storeSpaces) {
        if (s.isRented) count++;
    }
    return count;
}

int Mall::getAvailableStores() const {
    return (int)storeSpaces.size() - getOccupiedStores();
}

double Mall::getOccupancyRate() const {
    if (storeSpaces.empty()) return 0.0;
    return (static_cast<double>(getOccupiedStores()) / storeSpaces.size()) * 100.0;
}

Shop* Mall::findStore(int storeNumber) {
    for (StoreSpace& s : storeSpaces) {
        if (s.storeNumber == storeNumber && s.isRented) {
            return s.tenant;
        }
    }
    return nullptr;
}

void Mall::addFoodCourt(int capacity) {
    if (capacity < 1) {
        throw BuildingException("Food court capacity must be positive");
    }
    hasFoodCourt = true;
    foodCourtCapacity = capacity;
    buildingValue += capacity * 500.0;
    cout << "Food court added (" << capacity << " seats)" << endl;
}

void Mall::addCinema(int screens) {
    if (screens < 1) {
        throw BuildingException("Cinema must have at least 1 screen");
    }
    hasCinema = true;
    cinemaScreens = screens;
    buildingValue += screens * 500000.0;
    cout << "Cinema added (" << screens << " screens)" << endl;
}

void Mall::addAmusementArea() {
    hasAmusementArea = true;
    buildingValue *= 1.05;
    cout << "Amusement area added to " << mallName << endl;
}

void Mall::addParkingLevel() {
    parkingLevels++;
    int newSpots = (int)(landArea / 15);
    totalParkingSpots += newSpots;
    buildingValue += newSpots * 10000.0;
    cout << "Parking level added (+" << newSpots << " spots)" << endl;
}

Mall::~Mall() {
    cout << "Demolishing mall '" << mallName << "'..." << endl;

    for (StoreSpace& space : storeSpaces) {
        if (space.isRented && space.tenant != nullptr) {
            delete space.tenant;
            space.tenant = nullptr;
        }
    }
    storeSpaces.clear();

    cout << "Mall '" << mallName << "' demolished" << endl;
}