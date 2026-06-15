#pragma once
#include "ResidentialBuilding.h"
using namespace std;
class House :public ResidentialBuilding
{
private:
    int numBedrooms;
    int numBathrooms;
    bool hasGarage;
    int garageCapacity;
    bool hasBasement;
    bool hasAttic;
    string architectureStyle;
    double gardenArea;
public:
    House(string addr, int year, double area, int numFloors, int bedrooms, int bathrooms);
    double calculateMaintenanceCost()const override;
    void displayDetails() const override;
    string getBuildingType() const override;
    double calculateRent() const override;
    int getDailyVisitors() override;
    void addGarage(int capacity);
    void renovateKitchen();
    void addBasement();
    void expandGarden(double additionalArea);
    int getNumBedrooms() const {
        return numBedrooms; 
    }
    int getNumBathrooms() const {
        return numBathrooms; 
    }
    bool hasGarageSpace() const {
        return hasGarage; 
    }
    int getGarageCapacity() const {
        return garageCapacity; 
    }
    string getArchitectureStyle() const {
        return architectureStyle; 
    }
    House(const House&) = delete;
    House& operator=(const House&) = delete;
    ~House();
};

