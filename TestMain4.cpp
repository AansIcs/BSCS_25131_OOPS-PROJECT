#include "House.h"
#include "Apartment.h"
#include "TowerBlock.h"
#include "Shop.h"
#include "Restaurant.h"
#include "Office.h"
#include "Mall.h"
#include "CityExceptions.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int main() {
    cout << "=== SMART CITY - DAY 4 TEST ===\n" << endl;

    cout << "--- Test 1: Shop ---" << endl;
    Shop* grocery = new Shop("10 Market St", 2019, 300, 1,
        "Fresh Mart", "Grocery");

    grocery->addProduct("P001", "Rice 5kg", "Food", 2.0, 5.0, 100);
    grocery->addProduct("P002", "Milk 1L", "Food", 0.8, 1.5, 200);
    grocery->addProduct("P003", "Bread Loaf", "Food", 1.0, 2.0, 150);
    grocery->addProduct("P004", "Laptop", "Electronics", 500.0, 750.0, 10);

    grocery->enableOnlineStore(20.0);
    grocery->displayInventory();

    grocery->sellProduct("P001", 5);
    grocery->sellProduct("P002", 20);

    grocery->displayDetails();
    delete grocery;

    cout << "\n--- Test 2: Restaurant ---" << endl;
    Restaurant* resto = new Restaurant("25 Food Lane", 2021, 250, 1,
        "La Bella Italia", "Italian",
        10, 4);

    resto->addMenuItem("M001", "Bruschetta", "Starter", 2.0, 8.0, 10);
    resto->addMenuItem("M002", "Pasta Carbonara", "Main", 5.0, 18.0, 20);
    resto->addMenuItem("M003", "Pizza Margherita", "Main", 4.0, 15.0, 15);
    resto->addMenuItem("M004", "Tiramisu", "Dessert", 2.5, 8.0, 5);
    resto->addMenuItem("M005", "Wine Glass", "Drink", 3.0, 12.0, 2);

    try {
        resto->hireChef();
        resto->hireWaiter();

        resto->seatDiners(1, 4);
        resto->seatDiners(2, 2);
        resto->seatDiners(3, 4);

        cout << "Available tables: " << resto->getAvailableTables() << endl;
        cout << "Available seats:  " << resto->getAvailableSeats() << endl;

        resto->receiveReview(4.5, 4.0, 4.8);
        resto->receiveReview(5.0, 4.5, 4.2);
        resto->receiveReview(4.0, 3.5, 4.5);

        resto->clearTable(2);

        resto->displayDetails();
    }
    catch (CityException& e) {
        cout << "Error: " << e.what() << endl;
    }
    delete resto;

    cout << "\n--- Test 3: Office ---" << endl;
    Office* techOffice = new Office("50 Tech Park", 2022, 800, 3,
        "TechCorp HQ", "Technology");

    try {
        techOffice->addConferenceRoom();
        techOffice->addCafeteria();
        techOffice->enable24HourAccess();

        techOffice->leaseSpace(101, nullptr, "Engineering");
        techOffice->leaseSpace(102, nullptr, "Design");
        techOffice->leaseSpace(201, nullptr, "HR");
        techOffice->leaseSpace(202, nullptr, "Finance");

        cout << "Available spaces: " << techOffice->getAvailableSpaces() << endl;
        cout << "Occupancy rate:   "
            << techOffice->getOccupancyRate() << "%" << endl;

        techOffice->displayDetails();
    }
    catch (CityException& e) {
        cout << "Error: " << e.what() << endl;
    }
    delete techOffice;

    cout << "\n--- Test 4: Mall + Composition ---" << endl;
    Mall* cityMall = new Mall("1 Mall Road", 2020, 5000, 3,
        "City Shopping Centre", 30);

    try {
        cityMall->addFoodCourt(200);
        cityMall->addCinema(5);
        cityMall->addAmusementArea();
        cityMall->addParkingLevel();

        Shop* clothingShop = cityMall->openStore(101, "Fashion Hub",
            "Clothing", 2020);
        Shop* electronics = cityMall->openStore(102, "TechZone",
            "Electronics", 2020);
        Shop* foodStore = cityMall->openStore(201, "Gourmet Grocer",
            "Grocery", 2020);

        clothingShop->addProduct("C001", "T-Shirt", "Clothing", 5.0, 20.0, 50);
        clothingShop->addProduct("C002", "Jeans", "Clothing", 15.0, 60.0, 30);
        electronics->addProduct("E001", "Headphones", "Electronics", 20.0, 80.0, 25);
        foodStore->addProduct("F001", "Cheese", "Food", 3.0, 8.0, 40);

        cout << "\nMall Stats:" << endl;
        cout << "Occupied stores: " << cityMall->getOccupiedStores() << endl;
        cout << "Available:        " << cityMall->getAvailableStores() << endl;
        cout << "Occupancy rate:  "
            << fixed << setprecision(1)
            << cityMall->getOccupancyRate() << "%" << endl;

        cityMall->displayDetails();

        cout << "\nClosing store 101..." << endl;
        cityMall->closeStore(101);
        clothingShop = nullptr;

        cout << "Occupied stores after close: "
            << cityMall->getOccupiedStores() << endl;

    }
    catch (CityException& e) {
        cout << "Error: " << e.what() << endl;
    }

    delete cityMall;

    cout << "\n--- Test 5: Full Polymorphism Test ---" << endl;
    vector<Building*> allBuildings;

    allBuildings.push_back(new House("1 Maple", 2019, 400, 2, 3, 2));
    allBuildings.push_back(new Apartment("2 Oak", 2018, 900, 4, 3));
    allBuildings.push_back(new Shop("3 Pine", 2020, 300, 1,
        "Corner Shop", "Grocery"));
    allBuildings.push_back(new Restaurant("4 Elm", 2021, 250, 1,
        "Diner", "American", 8, 4));
    allBuildings.push_back(new Office("5 Cedar", 2022, 600, 3,
        "Biz Hub", "Finance"));

    cout << left << setw(16) << "Type"
        << setw(14) << "Maintenance"
        << setw(12) << "Visitors"
        << "Property Tax" << endl;
    cout << string(56, '-') << endl;

    for (Building* b : allBuildings) {
        cout << left
            << setw(16) << b->getBuildingType()
            << setw(14) << ("$" + to_string((int)b->calculateMaintenanceCost()))
            << setw(12) << b->getDailyVisitors()
            << "$" << fixed << setprecision(0)
            << b->calculatePropertyTax() << endl;
    }

    for (Building* b : allBuildings) {
        delete b;
    }
    allBuildings.clear();

    cout << "\n--- Test 6: Exception Tests ---" << endl;

    Shop* testShop = new Shop("X St", 2020, 200, 1, "Test", "General");
    testShop->addProduct("P1", "Item", "General", 5.0, 10.0, 20);

    try {
        testShop->sellProduct("P1", 100);
    }
    catch (BuildingException& e) {
        cout << "Caught: " << e.what() << endl;
    }

    try {
        testShop->sellProduct("NOTEXIST", 1);
    }
    catch (BuildingException& e) {
        cout << "Caught: " << e.what() << endl;
    }

    delete testShop;

    cout << "\n=== Day 4 Complete! ===" << endl;
    cout << "Total buildings tracked: "
        << Building::getBuildingCount() << endl;

    return 0;
}