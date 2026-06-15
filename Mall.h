#pragma once
#include "CommercialBuilding.h"
#include "Shop.h"
#include <vector>
#include <string>
using namespace std;
class Mall : public CommercialBuilding {
public:
    struct StoreSpace {
        int storeNumber;
        double areaSquareMeters;
        bool isRented;
        Shop* tenant;
        double monthlyRent;
        string storeCategory;
        StoreSpace(int num, double area, double rent, string cat)
            : storeNumber(num), areaSquareMeters(area),
            isRented(false), tenant(nullptr),
            monthlyRent(rent), storeCategory(cat) {
        }
    };
private:
    string mallName;
    vector<StoreSpace> storeSpaces;
    bool hasFoodCourt;
    int foodCourtCapacity;
    bool hasCinema;
    int cinemaScreens;
    bool hasAmusementArea;
    int parkingLevels;
    int totalParkingSpots;
    double weekdayFootTraffic;
    double weekendFootTraffic;
    string managementCompany;
public:
    Mall(string addr, int year, double area, int floors, string mallName, int totalStores);
    double calculateMaintenanceCost()const override;
    int getDailyVisitors()override;
    string getBuildingType() const override;
    void displayDetails() const override;
    double calculateMonthlyRevenue() override;
    Shop* openStore(int storeNumber, string shopName, string category, int year);
    void closeStore(int storeNumber);
    int getOccupiedStores() const;
    int getAvailableStores() const;
    double getOccupancyRate() const;
    Shop* findStore(int storeNumber);
    void addFoodCourt(int capacity);
    void addCinema(int screens);
    void addAmusementArea();
    void addParkingLevel();
    string getMallName() const { return mallName; }
    int getTotalStores() const { return (int)storeSpaces.size(); }
    bool getHasCinema() const { return hasCinema; }
    bool getHasFoodCourt() const { return hasFoodCourt; }
    ~Mall();
};
