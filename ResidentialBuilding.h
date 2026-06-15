#pragma once
#include "Building.h"
#include <vector>
using namespace std;
// Forward declaration (we'll create Citizen class later)
class Citizen;
class ResidentialBuilding:public Building
{
protected:
   
    int maxOccupants;              
    int currentOccupants;         
    vector<Citizen*> residents;    
 
    bool hasParking;               
    bool hasGarden;               
   
    double monthlyRent;            // Rent amount
    bool isRented;           
    double utilityBill; // Monthly utilities

public:
    ResidentialBuilding(string addr, int year, double area,int floors, int maxOcc);
    virtual double calculateMaintenanceCost()const = 0;
    virtual int getDailyVisitors() = 0;
    virtual void displayDetails() const = 0;
    virtual~ResidentialBuilding();
    string getBuildingType() const override;
    virtual double calculateRent() const;
    void addResident(Citizen* citizen);
    void removeResident(Citizen* citizen);
    vector<Citizen*> getResidents() const;
    bool hasVacancy() const;
    int getVacantSpots() const;
    int getMaxOccupants() const { return maxOccupants; }
    int getCurrentOccupants() const { return currentOccupants; }
    bool isRentedProperty() const { return isRented; }
    double getMonthlyRent() const { return monthlyRent; }
};