#include "TowerBlock.h"
#include "CityExceptions.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
TowerBlock::TowerBlock(string addr, int year, double area,
    int numFloors, int unitsPerFloor)
    : ResidentialBuilding(addr, year, area, numFloors,
        numFloors* unitsPerFloor * 2)
{
    // Validate
    if (numFloors < 5) {
        throw BuildingException(
            "TowerBlock must have at least 5 floors. "
            "Use Apartment for smaller buildings.");
    }
    if (unitsPerFloor < 2) {
        throw BuildingException("Tower must have at least 2 units per floor");
    }

    // Initialize attributes
    this->unitsPerFloor = unitsPerFloor;
    this->totalUnits = numFloors * unitsPerFloor;
    elevatorCount = max(2, numFloors / 10); 
    hasConcierge = false;
    hasRooftopPool = false;
    hasHelipPad = false;
    hasUndergroundParking = false;
    parkingLevels = 0;
    hasPenthouse = false;
    penthousePrice = 0.0;
    penthouseSizeMultiplier = 3.0;
    securityLevel = 3;    
    hasKeyCardAccess = true;   
    totalMonthlyRevenue = 0.0;

    floorResidents.resize(numFloors);   
    double basePrice = 800.0; 

    for (int floor = 1; floor <= numFloors; floor++) {
       
        double floorPrice = basePrice * (1.0 + (floor - 1) * 0.05);
        bool isPent = (floor == numFloors);
        if (isPent) {
            floorPrice = basePrice * 3.0;
            hasPenthouse = true;
            penthousePrice = floorPrice;
        }

        floorInfoList.push_back(
            FloorInfo(floor, unitsPerFloor, floorPrice, isPent)
        );
    }

    cout << "TowerBlock constructed at " << address
        << " | " << numFloors << " floors | "
        << totalUnits << " total units" << endl;
}

double TowerBlock::calculateMaintenanceCost()const {
    double cost = 0.0;

    cost += landArea * 5.0;
    cost += floors * floors * 100.0;   
    cost += elevatorCount * 10000.0;
    cost += floors * 500.0;        
    cost += securityLevel * 10000.0;  

  
    if (hasRooftopPool)         cost += 12000.0;
    if (hasConcierge)           cost += 60000.0;   
    if (hasHelipPad)            cost += 8000.0;
    if (hasUndergroundParking)  cost += parkingLevels * 5000.0;
    cost += totalUnits * 300.0;       

    // Age factor
    int age = getAge();
    if (age > 40) {
        cost *= 2.5;                  
    }
    else if (age > 20) {
        cost *= 1.8;
    }
    else if (age > 10) {
        cost *= 1.3;
    }

    return cost;
}
int TowerBlock::getDailyVisitors() {
    int visitors = 0;
    int occupiedCount = getTotalOccupiedUnits();
    visitors += static_cast<int>(occupiedCount * 1.5);
    if (hasConcierge)    visitors += 5;
    if (hasRooftopPool)  visitors += 10;

    return visitors;
}
string TowerBlock::getBuildingType() const {
    return "TowerBlock";
}
void TowerBlock::displayDetails() const {
    cout << "\n============ TOWER BLOCK ============" << endl;
    cout << "ID:        " << buildingID << endl;
    cout << "Address:   " << address << endl;
    cout << "Built:     " << buildYear
        << "  (Age: " << getAge() << " years)" << endl;
    cout << "Floors:    " << floors << endl;
    cout << "Land Area: " << landArea << " sqm" << endl;
    cout << "Value:     $" << fixed << setprecision(2)
        << buildingValue << endl;
    cout << "Condition: " << condition << "/100" << endl;

    cout << "\n--- Tower Features ---" << endl;
    cout << "Elevators:          " << elevatorCount << endl;
    cout << "Security Level:     " << securityLevel << "/5" << endl;
    cout << "Key Card Access:    " << (hasKeyCardAccess ? "Yes" : "No") << endl;
    cout << "Concierge:          " << (hasConcierge ? "Yes" : "No") << endl;
    cout << "Rooftop Pool:       " << (hasRooftopPool ? "Yes" : "No") << endl;
    cout << "Helipad:            " << (hasHelipPad ? "Yes" : "No") << endl;
    cout << "Underground Parking:"
        << (hasUndergroundParking
            ? " Yes (" + to_string(parkingLevels) + " levels)"
            : " No") << endl;

    if (hasPenthouse) {
        cout << "Penthouse:          Yes ($"
            << fixed << setprecision(0)
            << penthousePrice << "/month)" << endl;
    }

    cout << "\n--- Occupancy ---" << endl;
    cout << "Total Units:       " << totalUnits << endl;
    cout << "Occupied:          " << getTotalOccupiedUnits() << endl;
    cout << "Occupancy Rate:    "
        << fixed << setprecision(1)
        << getOverallOccupancyRate() << "%" << endl;

    cout << "\n--- Floor Summary ---" << endl;
    cout << left
        << setw(8) << "Floor"
        << setw(15) << "Name"
        << setw(12) << "Units"
        << setw(12) << "Occupied"
        << "Rent/unit" << endl;
    cout << string(55, '-') << endl;

    for (const FloorInfo& fi : floorInfoList) {
        cout << left
            << setw(8) << fi.floorNumber
            << setw(15) << fi.floorName
            << setw(12) << fi.maxUnitsOnFloor
            << setw(12) << fi.occupiedUnits
            << "$" << fixed << setprecision(0)
            << fi.pricePerUnit << endl;
    }

    cout << "\n--- Financial ---" << endl;
    cout << "Monthly Revenue:   $"
        << fixed << setprecision(2) << totalMonthlyRevenue << endl;
    cout << "Annual Maint:      $"
        << fixed << setprecision(2)
        << calculateMaintenanceCost() << endl;
    cout << "=====================================\n" << endl;
}

double TowerBlock::calculateRent() const {
    if (floorInfoList.empty()) return 0.0;

    double total = 0.0;
    for (const FloorInfo& fi : floorInfoList) {
        total += fi.pricePerUnit * fi.maxUnitsOnFloor;
    }
    return total / totalUnits; 
}


bool TowerBlock::assignToFloor(int floorNumber, Citizen* resident) {
    if (floorNumber < 1 || floorNumber > floors) {
        throw BuildingException("Invalid floor: " + to_string(floorNumber)
            + ". Tower has " + to_string(floors) + " floors");
    }

    if (resident == nullptr) {
        throw CitizenException("Cannot assign null resident");
    }

    if (!isOperational) {
        throw BuildingException("Building is not operational");
    }
    int floorIndex = floorNumber - 1;
    FloorInfo& fi = floorInfoList[floorIndex];
    if (fi.occupiedUnits >= fi.maxUnitsOnFloor) {
        throw BuildingException("Floor " + to_string(floorNumber) + " is full");
    }
    floorResidents[floorIndex].push_back(resident);
    fi.occupiedUnits++;
    residents.push_back(resident);
    currentOccupants++;
    totalMonthlyRevenue += fi.pricePerUnit;

    cout << "Resident assigned to floor " << floorNumber
        << " of tower " << buildingID << endl;
    return true;
}

bool TowerBlock::removeFromFloor(int floorNumber, Citizen* resident) {
    if (floorNumber < 1 || floorNumber > floors) {
        throw BuildingException("Invalid floor number");
    }
    if (resident == nullptr) {
        throw CitizenException("Cannot remove null resident");
    }

    int floorIndex = floorNumber - 1;
    auto& floorVec = floorResidents[floorIndex];
    auto it = find(floorVec.begin(), floorVec.end(), resident);

    if (it == floorVec.end()) {
        throw CitizenException("Resident not found on floor "
            + to_string(floorNumber));
    }
    floorVec.erase(it);
    floorInfoList[floorIndex].occupiedUnits--;
    auto pit = find(residents.begin(), residents.end(), resident);
    if (pit != residents.end()) {
        residents.erase(pit);
    }
    currentOccupants--;
    totalMonthlyRevenue -= floorInfoList[floorIndex].pricePerUnit;

    cout << "Resident removed from floor " << floorNumber << endl;
    return true;
}
vector<Citizen*> TowerBlock::getFloorResidents(int floorNumber) const {
    if (floorNumber < 1 || floorNumber > floors) {
        throw BuildingException("Invalid floor number");
    }

    return floorResidents[floorNumber - 1];  
}
bool TowerBlock::isFloorFull(int floorNumber) const {
    if (floorNumber < 1 || floorNumber > floors) {
        throw BuildingException("Invalid floor number");
    }

    const FloorInfo& fi = floorInfoList[floorNumber - 1];
    return fi.occupiedUnits >= fi.maxUnitsOnFloor;
}
int TowerBlock::getFloorVacancy(int floorNumber) const {
    if (floorNumber < 1 || floorNumber > floors) {
        throw BuildingException("Invalid floor number");
    }

    const FloorInfo& fi = floorInfoList[floorNumber - 1];
    return fi.maxUnitsOnFloor - fi.occupiedUnits;
}
double TowerBlock::getFloorRent(int floorNumber) const {
    if (floorNumber < 1 || floorNumber > floors) {
        throw BuildingException("Invalid floor number");
    }
    return floorInfoList[floorNumber - 1].pricePerUnit;
}

void TowerBlock::addPenthouse(double price) {
    if (price <= 0) {
        throw BuildingException("Penthouse price must be positive");
    }

    hasPenthouse = true;
    penthousePrice = price;
    floorInfoList.back().isPenthouse = true;
    floorInfoList.back().pricePerUnit = price;
    floorInfoList.back().floorName = "Penthouse";
    buildingValue += price * 12; 

    cout << "Penthouse added at $" << price << "/month" << endl;
}

void TowerBlock::setElevatorCount(int count) {
    if (count < 1) {
        throw BuildingException("Must have at least 1 elevator");
    }
    elevatorCount = count;
    cout << "Elevator count updated to " << count << endl;
}

void TowerBlock::addUndergroundParking(int levels) {
    if (levels < 1) {
        throw BuildingException("Must have at least 1 parking level");
    }
    hasUndergroundParking = true;
    parkingLevels = levels;
    buildingValue += levels * 500000;  
    cout << "Underground parking: " << levels << " levels added" << endl;
}

void TowerBlock::enableConcierge() {
    hasConcierge = true;
    buildingValue *= 1.05; 
    cout << "24/7 Concierge service enabled" << endl;
}

void TowerBlock::setSecurityLevel(int level) {
    if (level < 1 || level > 5) {
        throw BuildingException("Security level must be 1-5");
    }
    securityLevel = level;
    cout << "Security level set to " << level << "/5" << endl;
}
int TowerBlock::getTotalOccupiedUnits() const {
    int count = 0;
    for (const FloorInfo& fi : floorInfoList) {
        count += fi.occupiedUnits;
    }
    return count;
}

double TowerBlock::getOverallOccupancyRate() const {
    if (totalUnits == 0) return 0.0;
    return (static_cast<double>(getTotalOccupiedUnits()) / totalUnits) * 100.0;
}

TowerBlock::FloorInfo TowerBlock::getFloorInfo(int floorNumber) const {
    if (floorNumber < 1 || floorNumber > floors) {
        throw BuildingException("Invalid floor number");
    }
    return floorInfoList[floorNumber - 1];
}
TowerBlock::~TowerBlock() {
    for (auto& floorVec : floorResidents) {
        floorVec.clear();
    }
    floorResidents.clear();
    floorInfoList.clear();
    cout << "TowerBlock at " << address << " demolished" << endl;
}