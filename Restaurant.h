#pragma once
#include "CommercialBuilding.h"
#include <vector>
#include <string>
using namespace std;
class Restaurant : public CommercialBuilding {
public:
    struct MenuItem {
        string itemID;
        string itemName;
        string category;
        double costToMake;
        double sellingPrice;
        int    prepTimeMinutes;
        bool   isAvailable;
        MenuItem()
            : itemID(""), itemName(""), category(""),
            costToMake(0.0), sellingPrice(0.0),
            prepTimeMinutes(15), isAvailable(true) {
        }

        MenuItem(string id, string name, string cat,
            double cost, double price, int prep)
            : itemID(id), itemName(name), category(cat),
            costToMake(cost), sellingPrice(price),
            prepTimeMinutes(prep), isAvailable(true) {
        }
    };

    struct Table {
        int  tableNumber;
        int  capacity;
        bool isOccupied;
        int  currentDiners;

        Table(int num, int cap)
            : tableNumber(num), capacity(cap),
            isOccupied(false), currentDiners(0) {
        }
    };

private:
    string cuisineType;
    vector<MenuItem> menu;
    vector<Table>    tables;

    int    totalSeatingCapacity;
    int    currentDiners;

    int    chefCount;
    int    waiterCount;

    double foodQualityRating;
    double serviceRating;
    double ambianceRating;
    int    totalReviews;

    int    coversToday;
    double revenueToday;

public:
    Restaurant(string addr, int year, double area,
        int floors, string name, string cuisine,
        int numTables, int seatsPerTable);

    double calculateMaintenanceCost()const override;
    int    getDailyVisitors()         override;
    string getBuildingType()    const override;
    void   displayDetails()     const override;
    double calculateMonthlyRevenue()  override;

    void     addMenuItem(string id, string name, string cat,
        double cost, double price, int prep);
    void     removeMenuItem(string itemID);
    void     setAvailability(string itemID, bool available);
    MenuItem findMenuItem(string itemID) const;

    bool     seatDiners(int tableNum, int count);
    bool     clearTable(int tableNum);
    int      getAvailableTables() const;
    int  getAvailableSeats()  const;

    void hireChef();
    void hireWaiter();

    void     receiveReview(double food, double service, double ambiance);
    double   getOverallRating() const;

    string   getCuisineType()    const { return cuisineType; }
    int  getMenuItemCount()  const { return (int)menu.size(); }
    int getCurrentDiners()  const { return currentDiners; }

    ~Restaurant();
};


