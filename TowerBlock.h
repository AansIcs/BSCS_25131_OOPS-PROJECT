#pragma once
#include "ResidentialBuilding.h"
#include <vector>
#include <string>
using namespace std;
class Citizen;
class TowerBlock : public ResidentialBuilding {

public:
   
    struct FloorInfo {
        int    floorNumber;       
        int    maxUnitsOnFloor;   
        int    occupiedUnits;   
        double pricePerUnit;     
        bool   isPenthouse;        
        string floorName;       
        FloorInfo()
            : floorNumber(0), maxUnitsOnFloor(0), occupiedUnits(0),
            pricePerUnit(0.0), isPenthouse(false), floorName("") {
        }
        FloorInfo(int num, int maxUnits, double price, bool pent = false)
            : floorNumber(num), maxUnitsOnFloor(maxUnits),
            occupiedUnits(0), pricePerUnit(price),
            isPenthouse(pent), floorName("") {
            if (pent) {
                floorName = "Penthouse";
            }
            else if (num == 1) {
                floorName = "Ground Floor";
            }
            else {
                floorName = to_string(num) + "th Floor";
            }
        }
    };

private:
 
    int    unitsPerFloor;        
    int    totalUnits;            
    vector<vector<Citizen*>> floorResidents;
    vector<FloorInfo> floorInfoList;

    // Tower features
    int    elevatorCount;          
    bool   hasConcierge;         
    bool   hasRooftopPool;
    bool   hasHelipPad;          
    bool   hasUndergroundParking;
    int    parkingLevels;

    // Penthouse
    bool   hasPenthouse;
    double penthousePrice;         
    double penthouseSizeMultiplier;

    // Security
    int    securityLevel;        
    bool   hasKeyCardAccess;

    // Financial
    double totalMonthlyRevenue;

public:

    TowerBlock(string addr, int year, double area,
        int numFloors, int unitsPerFloor);
    double calculateMaintenanceCost()const override;
    int    getDailyVisitors()         override;
    string getBuildingType()    const override;
    void   displayDetails()     const override;
    double calculateRent() const override;
    bool   assignToFloor(int floorNumber, Citizen* resident);
    bool   removeFromFloor(int floorNumber, Citizen* resident);
    vector<Citizen*> getFloorResidents(int floorNumber) const;
    bool   isFloorFull(int floorNumber) const;
    int    getFloorVacancy(int floorNumber) const;
    double getFloorRent(int floorNumber) const;


    void   addPenthouse(double price);
    void   setElevatorCount(int count);
    void   addUndergroundParking(int levels);
    void   enableConcierge();
    void   setSecurityLevel(int level);
    int    getTotalOccupiedUnits()  const;
    double getOverallOccupancyRate() const;
    FloorInfo getFloorInfo(int floorNumber) const;
    int    getTotalUnits()          const { return totalUnits; }
    TowerBlock(const TowerBlock&) = delete;
    TowerBlock& operator=(const TowerBlock&) = delete;
    ~TowerBlock();
};
