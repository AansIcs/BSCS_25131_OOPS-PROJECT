#include "House.h"
#include "Apartment.h"
#include "TowerBlock.h"
#include "CityExceptions.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    cout << "=== SMART CITY - DAY 3 TEST ===\n" << endl;

    // ── TEST 1: Apartment Creation ───────────────────────────
    cout << "--- Test 1: Apartment Creation ---" << endl;
    try {
        Apartment* apt = new Apartment("45 Downtown Ave", 2018, 1200, 5, 4); // 5 floors, 4 units/floor
        cout << "Type: " << apt->getBuildingType() << endl;
        cout << "Total units: " << apt->getTotalUnits() << endl;
        cout << "Has elevator: " << (apt->getHasElevator() ? "Yes" : "No") << endl;
        apt->displayDetails();
        delete apt;
    }
    catch (const CityException& e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
    }

    // ── TEST 2: Apartment Unit Renting ───────────────────────
    cout << "\n--- Test 2: Renting Apartment Units ---" << endl;
    try {
        Apartment* apt2 = new Apartment("22 Oak Street", 2015, 800, 3, 4);
        try {
            // Rent unit 101 (nullptr as citizen - Citizen class not built yet)
            apt2->rentUnit(101, nullptr);
            apt2->rentUnit(102, nullptr);
            apt2->rentUnit(201, nullptr);
            cout << "Occupied: " << apt2->getOccupiedUnits() << endl;
            cout << "Vacant: " << apt2->getAvailableUnits() << endl;
            cout << "Revenue: $" << apt2->getTotalRevenue() << endl;
            cout << "Occupancy: " << apt2->getOccupancyRate() << "%" << endl;

            // Try renting same unit twice
            apt2->rentUnit(101, nullptr); // Should throw exception!
        }
        catch (const BuildingException& e) {
            cout << "Caught expected: " << e.what() << endl;
        }
        delete apt2;
    }
    catch (const CityException& e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
    }

    // ── TEST 3: TowerBlock Creation ──────────────────────────
    cout << "\n--- Test 3: TowerBlock Creation ---" << endl;
    try {
        TowerBlock* tower = new TowerBlock("1 Sky High Blvd", 2022, 2000, 20, 8); // 20 floors, 8 units
        cout << "Type: " << tower->getBuildingType() << endl;
        cout << "Total units: " << tower->getTotalUnits() << endl;
        cout << "Floor 1 rent: $" << tower->getFloorRent(1) << endl;
        cout << "Floor 10 rent: $" << tower->getFloorRent(10) << endl;
        cout << "Floor 20 rent: $" << tower->getFloorRent(20) << endl;

        // Add luxury features
        tower->enableConcierge();
        tower->addUndergroundParking(2);
        tower->setSecurityLevel(5);
        tower->displayDetails();
        delete tower;
    }
    catch (const CityException& e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
    }

    // ── TEST 4: Floor Management in TowerBlock ───────────────
    cout << "\n--- Test 4: TowerBlock Floor Management ---" << endl;
    try {
        TowerBlock* tower2 = new TowerBlock("2 Luxury Lane", 2020, 1500, 10, 4); // 10 floors, 4 units
        try {
            // Assign residents to different floors
            tower2->assignToFloor(1, nullptr);
            tower2->assignToFloor(1, nullptr);
            tower2->assignToFloor(5, nullptr);
            tower2->assignToFloor(10, nullptr);
            cout << "Floor 1 occupied: " << tower2->getFloorInfo(1).occupiedUnits << endl;
            cout << "Floor 1 vacancy: " << tower2->getFloorVacancy(1) << endl;
            cout << "Floor 5 occupied: " << tower2->getFloorInfo(5).occupiedUnits << endl;
            cout << "Overall rate: " << tower2->getOverallOccupancyRate() << "%" << endl;

            // Try invalid floor
            tower2->assignToFloor(99, nullptr); // Should throw!
        }
        catch (const BuildingException& e) {
            cout << "Caught expected: " << e.what() << endl;
        }
        delete tower2;
    }
    catch (const CityException& e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
    }

    // ── TEST 5: Polymorphism with All 3 Types ────────────────
    cout << "\n--- Test 5: Polymorphism ---" << endl;
    try {
        vector<Building*> allBuildings;
        allBuildings.push_back(new House("1 Maple St", 2019, 400, 2, 3, 2));
        allBuildings.push_back(new Apartment("5 Center Rd", 2017, 900, 4, 3));
        allBuildings.push_back(new TowerBlock("10 High Rise", 2021, 1800, 15, 6));

        cout << "All building types:" << endl;
        for (Building* b : allBuildings) {
            cout << " Type: " << left << setw(12) << b->getBuildingType()
                << " Maintenance: $" << fixed << setprecision(0) << b->calculateMaintenanceCost() << endl;
        }

        // Cleanup
        for (Building* b : allBuildings) {
            delete b;
        }
        allBuildings.clear();
    }
    catch (const CityException& e) {
        cout << "Error: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
    }

    // ── TEST 6: Exception Handling ───────────────────────────
    cout << "\n--- Test 6: Exception Testing ---" << endl;
    // TowerBlock with too few floors
    try {
        TowerBlock* badTower = new TowerBlock("X", 2020, 500, 3, 4);
        delete badTower; // Delete if constructor surprisingly succeeds
    }
    catch (const BuildingException& e) {
        cout << "Caught: " << e.what() << endl;
    }
    catch (const CityException& e) {
        cout << "Caught unexpected CityException: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
    }

    // Apartment with 0 units per floor
    try {
        Apartment* badApt = new Apartment("Y", 2020, 300, 3, 0);
        delete badApt; // Delete if constructor surprisingly succeeds
    }
    catch (const BuildingException& e) {
        cout << "Caught: " << e.what() << endl;
    }
    catch (const CityException& e) {
        cout << "Caught unexpected CityException: " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown error occurred." << endl;
    }

    cout << "\n=== Day 3 Complete! ===" << endl;

    try {
        cout << "Total buildings ever created: " << Building::getBuildingCount() << endl;
    }
    catch (...) {
        cout << "Could not fetch total building count." << endl;
    }

    return 0;
}
