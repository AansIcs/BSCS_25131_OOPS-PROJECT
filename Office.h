#pragma once
#include "CommercialBuilding.h"
#include <vector>
#include <string>
using namespace std;
class Citizen;
class Office : public CommercialBuilding {
public:
    struct OfficeSpace {
        int spaceNumber;
        int floor;
        double areaSquareMeters;
        bool isOccupied;
        Citizen* occupant;
        string department;
        double monthlyLeaseCost;
        OfficeSpace(int num, int flr, double area, double lease)
            : spaceNumber(num), floor(flr), areaSquareMeters(area),
            isOccupied(false), occupant(nullptr),
            department("General"), monthlyLeaseCost(lease) {
        }
    };
private:
    string companyName;
    string industryType;
    vector<OfficeSpace> spaces;
    int conferenceRooms;
    int occupiedConferenceRooms;
    bool hasReception;
    bool hasCafeteria;
    bool hasPrinterRoom;
    bool has24HourAccess;
    double rentPerSquareMeter;
    int totalOccupiedSpaces;
public:
    Office(string addr, int year, double area, int floors, string officeName, string industry);
    double calculateMaintenanceCost() const override;
    int getDailyVisitors() override;
    string getBuildingType() const override;
    void displayDetails() const override;
    double calculateMonthlyRevenue() override;
    void addOfficeSpace(int spaceNum, int floor, double area, double lease);
    bool leaseSpace(int spaceNumber, Citizen* occupant, string department);
    bool vacateSpace(int spaceNumber);
    int getAvailableSpaces() const;
    double getOccupancyRate() const;
    void addConferenceRoom();
    void addCafeteria();
    void enable24HourAccess();
    string getIndustryType() const { return industryType; }
    int getTotalSpaces() const { return (int)spaces.size(); }
    int getConferenceRooms() const { return conferenceRooms; }
    ~Office();
};
