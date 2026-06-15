#include "Building.h"
#include "CityExceptions.h"
#include <iostream>
using namespace std;
// Temporary concrete class JUST for testing
class TestBuilding : public Building {
public:
    TestBuilding(string addr, int year, double area, int floors)
        : Building(addr, year, area, floors) {
    }

    // Implement ALL pure virtuals with simple versions
    double calculateMaintenanceCost() const override {
        return 1000.0;  // Simple fixed cost
    }

    int getDailyVisitors() override {
        return 10;  // Fixed number
    }

    string getBuildingType() const override {
        return "TestBuilding";
    }

    void displayDetails() const override {
        cout << "Test Building at " << getAddress() << endl;
    }
};

int main01() {
    cout << "=== Smart City - Day 1 Test ===" << endl;

    // Test 1: Exception handling - invalid year
    cout << "\nTest 1: Invalid Year Exception" << endl;
    try {
        Building* b = new TestBuilding("123 Main", 1700, 500, 2);
    }
    catch (BuildingException& e) {
        cout << " Caught Exception: " << e.what() << endl;
        cout << "Error Code: " << e.getErrorCode() << endl;
    }

    // Test 2: Valid building creation
    cout << "\nTest 2: Valid Building Creation" << endl;
    try {
        Building* b = new TestBuilding("456 Oak St", 2020, 500, 2);
        cout << " Building created: " << b->getBuildingID() << endl;
        cout << "Age: " << b->getAge() << " years" << endl;
        cout << "Type: " << b->getBuildingType() << endl;
        delete b;
    }
    catch (BuildingException& e) {
        cout << " Unexpected exception: " << e.what() << endl;
    }

    // Test 3: Test deterioration
    cout << "\nTest 3: Building Deterioration" << endl;
    Building* b = new TestBuilding("789 Pine Ave", 1970, 300, 1);
    cout << "Initial condition: " << b->getCondition() << endl;
    b->deteriorate();
    cout << "After deterioration: " << b->getCondition() << endl;
    delete b;

    cout << "\n Day 1 Complete!" << endl;

    return 0;
}