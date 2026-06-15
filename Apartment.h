#pragma once
#include "ResidentialBuilding.h"
#include <vector>
#include <string>
using namespace std;
// Forward declaration
class Citizen;
class Apartment : public ResidentialBuilding {

public:
    struct ApartmentUnit {
        int    unitNumber;      
        int    floor;           
        double sizeSquareMeters; 
        double monthlyRent;      
        bool   isOccupied;     
        Citizen* tenant;      
        string unitType;       
        ApartmentUnit()
            : unitNumber(0), floor(0), sizeSquareMeters(0.0),
            monthlyRent(0.0), isOccupied(false), tenant(nullptr),
            unitType("1BR") {
        }
        ApartmentUnit(int num, int flr, double size,
            double rent, string type)
            : unitNumber(num), floor(flr), sizeSquareMeters(size),
            monthlyRent(rent), isOccupied(false), tenant(nullptr),
            unitType(type) {
        }
    };

private:
   
    int  totalUnits;           
    int  occupiedUnits;       
    vector<ApartmentUnit> units; 
    bool   hasElevator;
    bool   hasSecurityGuard;
    bool   hasGym;
    bool   hasSwimmingPool;
    bool   hasRooftopTerrace;
    int   totalParkingSpots;
    int  availableParkingSpots;
    double totalMonthlyRevenue; 
    string buildingManagerName;

public:
    Apartment(string addr, int year, double area, int numFloors, int unitsPerFloor);
    double calculateMaintenanceCost()const override;
    int    getDailyVisitors()         override;
    string getBuildingType()    const override;
    void   displayDetails()     const override;
    double calculateRent() const override;
    void   addUnit(int unitNum, int floor, double size,double rent, string type);
    bool   rentUnit(int unitNumber, Citizen* tenant);
    bool   vacateUnit(int unitNumber);
    ApartmentUnit* findUnit(int unitNumber);
    int    getAvailableUnits()    const;
    double getOccupancyRate()     const;
    double getTotalRevenue()      const;
    vector<ApartmentUnit> getVacantUnits() const;
    void setHasElevator(bool val) { hasElevator = val; }
    void setHasSecurity(bool val) { hasSecurityGuard = val; }
    void setHasGym(bool val) { hasGym = val; }
    void setHasPool(bool val) { hasSwimmingPool = val; }
    int    getTotalUnits()      const { return totalUnits; }
    int    getOccupiedUnits()   const { return occupiedUnits; }
    bool   getHasElevator()     const { return hasElevator; }
    bool   getHasGym()          const { return hasGym; }
    Apartment(const Apartment&) = delete;
    Apartment& operator=(const Apartment&) = delete;
    ~Apartment();
};

