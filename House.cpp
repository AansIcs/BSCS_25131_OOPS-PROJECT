#include "House.h"
#include <iostream>
House::House(string addr, int year, double area, int numFloors,int bedrooms, int bathrooms): ResidentialBuilding(addr, year, area, numFloors, bedrooms + 1)
{
      if (bedrooms < 1) {
        throw BuildingException("House must have at least 1 bedroom");
    }
    if (bathrooms < 1) {
        throw BuildingException("House must have at least 1 bathroom");
    }
    numBedrooms = bedrooms;
    numBathrooms = bathrooms;
    hasGarage = false;
    garageCapacity = 0;
    hasBasement = false;
    hasAttic = false;
    architectureStyle = "Modern";
    gardenArea = 0.0;
    cout << "House constructed at " << address << endl;
}
double House::calculateMaintenanceCost() const{
    double cost = 0.0;
    cost += landArea * 2.0;  
    cost += floors * 500.0;  
    cost += currentOccupants * 100.0;  
    cost += numBedrooms * 500.0;      
    cost += numBathrooms * 300.0;     

    if (hasGarage) {
        cost += garageCapacity * 200.0;  
    }

    if (hasBasement) {
        cost += 1000.0; 
    }

    if (hasAttic) {
        cost += 500.0;
    }

    if (hasGarden) {
        cost += gardenArea * 5.0;  
    }
    int age = getAge();
    double ageFactor = 1.0;

    if (age > 50) {
        ageFactor = 2.0;  
    }
    else if (age > 20) {
        ageFactor = 1.5;   
    }
    cost *= ageFactor;
    // Poor condition increases costs
    if (condition < 50) {
        cost *= 1.3;  
    }
    return cost;
}
int House::getDailyVisitors() 
{ 
    double visitors = currentOccupants * 0.5;
    visitors += numBedrooms * 0.2;
    if (hasGarden) {
        visitors += 2.0;
    }
    // Round to integer
    return static_cast<int>(visitors);
}
void House::displayDetails() const {
    cout << "\n--------------------- HOUSE DETAILS --------------------------" << endl;
    cout << "ID: " << buildingID << endl;
    cout << "Address: " << address << endl;
    cout << "Type: House (" << architectureStyle << ")" << endl;
    cout << "Built: " << buildYear << " (Age: " << getAge() << " years)" << endl;
    cout << "Land Area: " << landArea << " sqm" << endl;
    cout << "Floors: " << floors << endl;
    cout << "Value: $" << buildingValue << endl;
    cout << "Condition: " << condition << "/100" << endl;
    cout << "Operational: " << (isOperational ? "Yes" : "No") << endl;

    cout << "\n---------------------- Residential Info -----------------------" << endl;
    cout << "Bedrooms: " << numBedrooms << endl;
    cout << "Bathrooms: " << numBathrooms << endl;
    cout << "Occupants: " << currentOccupants << "/" << maxOccupants << endl;

    if (hasGarage) {
        cout << "Garage: Yes (" << garageCapacity << " cars)" << endl;
    }
    if (hasBasement) {
        cout << "Basement: Yes" << endl;
    }
    if (hasGarden) {
        cout << "Garden: " << gardenArea << " sqm" << endl;
    }

    cout << "\n--------------- Financial ---------------------" << endl;
    if (isRented) {
        cout << "Status: Rented" << endl;
        cout << "Monthly Rent: $" << monthlyRent << endl;
    }
    else {
        cout << "Status: Owner-Occupied" << endl;
    }
    cout << "Annual Maintenance: $" << calculateMaintenanceCost() << endl;
    cout << "Property Tax: $" << calculatePropertyTax() << endl;

    cout << "--------------------------------------------------------------------------\n" << endl;
}
string House::getBuildingType() const {
    return "House";
}
double House::calculateRent() const {
    double rent = ResidentialBuilding::calculateRent();
    rent += numBedrooms * 200.0;  
    rent += numBathrooms * 100.0; 
    if (hasGarage) {
        rent += garageCapacity * 150.0;  
    }
    if (hasBasement) {
        rent += 300.0;
    }
    return rent;
}
void House::addGarage(int capacity) {
    if (capacity < 1) {
        throw BuildingException("Garage capacity must be at least 1");
    }

    if (hasGarage) {
        cout << "Warning: Garage already exists. Expanding capacity." << endl;
        garageCapacity += capacity;
    }
    else {
        hasGarage = true;
        garageCapacity = capacity;
    }
    buildingValue += capacity * 15000;
    cout << "Garage added to house at " << address << endl;
}

void House::renovateKitchen() {
    condition = min(100, condition + 10);
    buildingValue *= 1.05;  

    cout << "Kitchen renovated at " << address << endl;
}

void House::addBasement() {
    if (hasBasement) {
        throw BuildingException("House already has a basement");
    }

    hasBasement = true;
    buildingValue += 30000;  
    cout << "Basement added to house at " << address << endl;
}

void House::expandGarden(double additionalArea) {
    if (additionalArea <= 0) {
        throw BuildingException("Additional area must be positive");
    }

    hasGarden = true;
    gardenArea += additionalArea;
    buildingValue += additionalArea * 100;  
    cout << "Garden expanded by " << additionalArea << " sqm" << endl;
}
House::~House() {
    cout << "House at " << address << " demolished" << endl;
}