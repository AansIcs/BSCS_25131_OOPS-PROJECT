#include "Apartment.h"
#include "CityExceptions.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
Apartment::Apartment(string addr, int year, double area,  int numFloors, int unitsPerFloor)  : ResidentialBuilding(addr, year, area, numFloors,numFloors* unitsPerFloor * 2)
{
    
    if (numFloors < 1) {
        throw BuildingException("Apartment must have at least 1 floor");
    }
    if (unitsPerFloor < 1) {
        throw BuildingException("Must have at least 1 unit per floor");
    }

    // Initialize attributes
    totalUnits = numFloors * unitsPerFloor;
    occupiedUnits = 0;
    hasElevator = (numFloors > 3);  
    hasSecurityGuard = false;
    hasGym = false;
    hasSwimmingPool = false;
    hasRooftopTerrace = false;
    totalParkingSpots = totalUnits / 2;   
    availableParkingSpots = totalParkingSpots;
    totalMonthlyRevenue = 0.0;
    buildingManagerName = "Unassigned";
    int unitCounter = 0;
    for (int floor = 1; floor <= numFloors; floor++) {
        for (int unit = 1; unit <= unitsPerFloor; unit++) {
            unitCounter++;
            int unitNum = (floor * 100) + unit;  
            double size = 60.0 + (floor * 5.0);          
            double rent = 500.0 + (floor * 100.0);      
            string type = "Studio";
            if (size > 100) type = "2BR";
            else if (size > 75) type = "1BR";

            units.push_back(ApartmentUnit(unitNum, floor, size, rent, type));
        }
    }

    cout << "Apartment building constructed at " << address
        << " with " << totalUnits << " units" << endl;
}

double Apartment::calculateMaintenanceCost()const {
    double cost = 0.0;
    cost += landArea * 3.0;          
    cost += floors * 1000.0;         
    cost += totalUnits * 200.0;   
    if (hasElevator) {
        cost += 5000.0;
    }
    if (hasGym) {
        cost += 3000.0;
    }
    if (hasSwimmingPool) {
        cost += 8000.0;             
    }
    if (hasRooftopTerrace) {
        cost += 2000.0;
    }
    if (hasSecurityGuard) {
        cost += 30000.0;
    }
    cost += totalParkingSpots * 100.0; 
    int age = getAge();
    if (age > 50) {
        cost *= 2.0;
    }
    else if (age > 20) {
        cost *= 1.5;
    }
    if (condition < 50) {
        cost *= 1.4;
    }

    return cost;
}

int Apartment::getDailyVisitors() {
    int visitors = 0;
    visitors += occupiedUnits * 1;
    if (hasGym) {
        visitors += 10;
    }
    if (hasSwimmingPool) {
        visitors += 5;
    }

    return visitors;
}
string Apartment::getBuildingType() const {
    return "Apartment";
}

void Apartment::displayDetails() const {
    cout << "\n========== APARTMENT BUILDING ==========" << endl;
    cout << "ID:        " << buildingID << endl;
    cout << "Address:   " << address << endl;
    cout << "Built:     " << buildYear
        << "  (Age: " << getAge() << " years)" << endl;
    cout << "Floors:    " << floors << endl;
    cout << "Land Area: " << landArea << " sqm" << endl;
    cout << "Value:     $" << fixed << setprecision(2)
        << buildingValue << endl;
    cout << "Condition: " << condition << "/100" << endl;
    cout << "Status:    "
        << (isOperational ? "Operational" : "Non-Operational") << endl;

    cout << "\n--- Units ---" << endl;
    cout << "Total Units:    " << totalUnits << endl;
    cout << "Occupied:       " << occupiedUnits << endl;
    cout << "Vacant:         " << (totalUnits - occupiedUnits) << endl;
    cout << "Occupancy Rate: "
        << fixed << setprecision(1)
        << getOccupancyRate() << "%" << endl;

    cout << "\n--- Amenities ---" << endl;
    cout << "Elevator:        " << (hasElevator ? "Yes" : "No") << endl;
    cout << "Security Guard:  " << (hasSecurityGuard ? "Yes" : "No") << endl;
    cout << "Gym:             " << (hasGym ? "Yes" : "No") << endl;
    cout << "Swimming Pool:   " << (hasSwimmingPool ? "Yes" : "No") << endl;
    cout << "Rooftop Terrace: " << (hasRooftopTerrace ? "Yes" : "No") << endl;

    cout << "\n--- Parking ---" << endl;
    cout << "Total Spots:     " << totalParkingSpots << endl;
    cout << "Available:       " << availableParkingSpots << endl;

    cout << "\n--- Financial ---" << endl;
    cout << "Monthly Revenue: $"
        << fixed << setprecision(2) << getTotalRevenue() << endl;
    cout << "Annual Maint:   $"
        << fixed << setprecision(2)
        << calculateMaintenanceCost() << endl;

    cout << "\n--- Unit Breakdown ---" << endl;
    cout << left << setw(8) << "Unit" << setw(8) << "Floor" << setw(12) << "Size(sqm)" << setw(12) << "Rent/mo" << setw(10) << "Type" << "Status" << endl;
    cout << string(60, '-') << endl;

    for (const ApartmentUnit& unit : units) {
        cout << left << setw(8) << unit.unitNumber  << setw(8) << unit.floor  << setw(12) << unit.sizeSquareMeters  << setw(12) << ("$" + to_string((int)unit.monthlyRent))  << setw(10) << unit.unitType
            << (unit.isOccupied ? "Occupied" : "Vacant") << endl;
    }
    cout << "========================================\n" << endl;
}

double Apartment::calculateRent() const {
    if (units.empty()) return 0.0;

    double total = 0.0;
    for (const ApartmentUnit& unit : units) {
        total += unit.monthlyRent;
    }

    return total / units.size();  // Average rent
}
void Apartment::addUnit(int unitNum, int floor, double size, double rent, string type) {
    // Validate
    if (size <= 0) {
        throw BuildingException("Unit size must be positive");
    }
    if (rent < 0) {
        throw BuildingException("Unit rent cannot be negative");
    }
    if (floor < 1 || floor > floors) {
        throw BuildingException("Invalid floor number: " + to_string(floor));
    }
    for (const ApartmentUnit& u : units) {
        if (u.unitNumber == unitNum) {
            throw BuildingException("Unit " + to_string(unitNum)
                + " already exists");
        }
    }
    units.push_back(ApartmentUnit(unitNum, floor, size, rent, type));
    totalUnits++;

    cout << "Unit " << unitNum << " added to " << buildingID << endl;
}

bool Apartment::rentUnit(int unitNumber, Citizen* tenant) {
    // Find unit
    ApartmentUnit* unit = findUnit(unitNumber);

    if (unit == nullptr) {
        throw BuildingException("Unit " + to_string(unitNumber) + " not found");
    }

    if (unit->isOccupied) {
        throw BuildingException("Unit " + to_string(unitNumber)  + " is already occupied");
    }

    if (!isOperational) {
        throw BuildingException("Building is not operational");
    }

    // Assign tenant
    unit->isOccupied = true;
    unit->tenant = tenant;
    occupiedUnits++;
    currentOccupants++;

    // Also add to parent's residents vector
    if (tenant != nullptr) {
        residents.push_back(tenant);
    }

    // Update revenue
    totalMonthlyRevenue += unit->monthlyRent;

    cout << "Unit " << unitNumber << " rented successfully" << endl;
    return true;
}

bool Apartment::vacateUnit(int unitNumber) {
    ApartmentUnit* unit = findUnit(unitNumber);

    if (unit == nullptr) {
        throw BuildingException("Unit " + to_string(unitNumber) + " not found");
    }

    if (!unit->isOccupied) {
        throw BuildingException("Unit " + to_string(unitNumber)  + " is already vacant");
    }

    // Remove from parent's residents vector
    if (unit->tenant != nullptr) {
        auto it = find(residents.begin(), residents.end(), unit->tenant);
        if (it != residents.end()) {
            residents.erase(it);
        }
    }

    // Update revenue
    totalMonthlyRevenue -= unit->monthlyRent;

    // Clear unit
    unit->isOccupied = false;
    unit->tenant = nullptr;
    occupiedUnits--;
    currentOccupants--;

    cout << "Unit " << unitNumber << " vacated" << endl;
    return true;
}

Apartment::ApartmentUnit* Apartment::findUnit(int unitNumber) {
    for (ApartmentUnit& unit : units) {
        if (unit.unitNumber == unitNumber) {
            return &unit;   // Address of element in vector
        }
    }
    return nullptr;         
}
int Apartment::getAvailableUnits() const {
    return totalUnits - occupiedUnits;
}
double Apartment::getOccupancyRate() const {
    if (totalUnits == 0) return 0.0;
    return (static_cast<double>(occupiedUnits) / totalUnits) * 100.0;
}
double Apartment::getTotalRevenue() const {
    double revenue = 0.0;
    for (const ApartmentUnit& unit : units) {
        if (unit.isOccupied) {
            revenue += unit.monthlyRent;
        }
    }
    return revenue;
}
vector<Apartment::ApartmentUnit> Apartment::getVacantUnits() const {
    vector<ApartmentUnit> vacant;

    for (const ApartmentUnit& unit : units) {
        if (!unit.isOccupied) {
            vacant.push_back(unit);
        }
    }

    return vacant;
}
Apartment::~Apartment() {
    units.clear();
    cout << "Apartment building at " << address << " demolished" << endl;
}