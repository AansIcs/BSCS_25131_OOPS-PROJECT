#pragma once
#include <string>
#include <iostream>
#include "CityExceptions.h"
using namespace std;
// Forward declaration (we'll use these classes later)
class CityManager;

class Building 
{
    // Friend class - CityManager can access private members
    friend class CityManager;

protected:
   
    string buildingID;       
    string address;            
    int buildYear;               
    double landArea;           
    double buildingValue;        
    int condition;         
    bool isOperational;     
    int floors;               
    double maintenanceCost;   

private:
    static int buildingCounter;  // For generating unique IDs

    // Private helper method
    string generateBuildingID();

public:
    
    Building(string addr, int year, double area, int numFloors);
    virtual double calculateMaintenanceCost()const = 0;
    virtual int getDailyVisitors() = 0;
    virtual string getBuildingType() const = 0;
    virtual void displayDetails() const = 0;
    virtual void upgrade();
    virtual void deteriorate();
    virtual double calculatePropertyTax() const;
    int getAge() const;
    bool needsMaintenance() const;
    void performMaintenance();
    string getBuildingID() const { return buildingID; }
    string getAddress() const { return address; }
    double getValue() const { return buildingValue; }
    int getCondition() const { return condition; }
    int getFloors() const { return floors; }
    double getLandArea() const { return landArea; }
    bool isOperating() const { return isOperational; }
    void setValue(double value);
    void setCondition(int cond);
    void setOperational(bool status);

    // Static method - called on class, not object
    static int getBuildingCount() { return buildingCounter; }

    // Virtual destructor - important for polymorphism!
    virtual ~Building();
};
