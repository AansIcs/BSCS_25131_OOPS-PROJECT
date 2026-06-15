#include "ResidentialBuilding.h"
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
ResidentialBuilding::ResidentialBuilding(string addr, int year,double area, int floors,int maxOcc): Building(addr, year, area, floors)  
{
    if (maxOcc <= 0) {
        throw BuildingException("Max occupants must be positive");
    }
    maxOccupants = maxOcc;
    currentOccupants = 0;
    hasParking = false;
    hasGarden = false;
    monthlyRent = 0.0;
    isRented = false;
    utilityBill = 0.0;
}
string ResidentialBuilding::getBuildingType() const {
    return "Residential";
}
double ResidentialBuilding::calculateRent() const 
{
    double baseRent = landArea * 10.0;  
    double floorBonus = floors * 200.0; 
    double amenityBonus = 0.0;
    if (hasParking) {
        amenityBonus += 100.0;
    }
    if (hasGarden) {
        amenityBonus += 150.0; 
    }
    double totalRent = baseRent + floorBonus + amenityBonus;
    if (!isOperational) {
        return 0.0;
    }

    return totalRent;
}
void ResidentialBuilding::addResident(Citizen* citizen) {
    if (citizen == nullptr) {
        throw CitizenException("Cannot add null citizen to building");
    }

    if (currentOccupants >= maxOccupants) {
        throw BuildingException("Building is at maximum capacity");
    }

    if (!isOperational) {
        throw BuildingException("Cannot move into non-operational building");
    }
    for (Citizen* resident : residents) {
        if (resident == citizen) {
            throw CitizenException("Citizen is already a resident");
        }
    }
    residents.push_back(citizen);
    currentOccupants++;
    cout << "Resident added to " << buildingID << endl;
}

void ResidentialBuilding::removeResident(Citizen* citizen) 
{
    if (citizen == nullptr) {
        throw CitizenException("Cannot remove null citizen");
    }
    auto it = find(residents.begin(), residents.end(), citizen);
    if (it == residents.end()) {
        throw CitizenException("Citizen is not a resident of this building");
    }
    residents.erase(it);
    currentOccupants--;
    cout << "Resident removed from " << buildingID << endl;
}
bool ResidentialBuilding::hasVacancy() const {
    return currentOccupants < maxOccupants;
}

int ResidentialBuilding::getVacantSpots() const {
    return maxOccupants - currentOccupants;
}

vector<Citizen*> ResidentialBuilding::getResidents() const {
    return residents;
}
ResidentialBuilding::~ResidentialBuilding() 
{
    residents.clear();
    cout << "ResidentialBuilding at " << address << " demolished" << endl;
}
