#include "House.h"
#include"CityExceptions.h"
#include <iostream>
using namespace std;
int main02() {
    cout << "=== SMART CITY - DAY 2 TEST ===" << endl;
    cout << "\n--- Test 1: Creating a House ---" << endl;
    try {
        House* house = new House("123 Main Street", 2020, 500, 2, 3, 2);
        cout << " House created successfully!" << endl;
        cout << "Building ID: " << house->getBuildingID() << endl;
        cout << "Type: " << house->getBuildingType() << endl;
        cout << "Age: " << house->getAge() << " years" << endl;

        delete house;
    }
    catch (BuildingException& e) {
        cout << " Error: " << e.what() << endl;
    }
    cout << "\n--- Test 2: Invalid House (Exception Test) ---" << endl;
    try {
        House* badHouse = new House("456 Oak", 2020, 300, 1, 0, 1);  // 0 bedrooms!
        cout << " Should have thrown exception!" << endl;
    }
    catch (BuildingException& e) {
        cout << " Caught exception: " << e.what() << endl;
    }
    cout << "\n--- Test 3: Polymorphism Test ---" << endl;
    Building* b = new House("789 Pine Ave", 2015, 600, 2, 4, 3);
    cout << "Building Type (via Building*): " << b->getBuildingType() << endl;
    cout << "Maintenance Cost: $" << b->calculateMaintenanceCost() << endl;
    delete b;
    cout << "\n--- Test 4: Adding Features ---" << endl;
    House* myHouse = new House("321 Elm St", 2018, 700, 2, 3, 2);
    cout << "Initial value: $" << myHouse->getValue() << endl;

    myHouse->addGarage(2);
    cout << "After garage: $" << myHouse->getValue() << endl;

    myHouse->addBasement();
    cout << "After basement: $" << myHouse->getValue() << endl;

    myHouse->expandGarden(150);
    cout << "After garden: $" << myHouse->getValue() << endl;
    cout << "\n--- Test 5: Full Details ---" << endl;
    myHouse->displayDetails();
    cout << "\n--- Test 6: Maintenance & Deterioration ---" << endl;
    cout << "Initial condition: " << myHouse->getCondition() << endl;

    myHouse->deteriorate();
    cout << "After deterioration: " << myHouse->getCondition() << endl;

    myHouse->performMaintenance();
    cout << "After maintenance: " << myHouse->getCondition() << endl;
    cout << "\n--- Test 7: Rent Calculation ---" << endl;
    cout << "Monthly rent: $" << myHouse->calculateRent() << endl;

    // Cleanup
    delete myHouse;

    cout << "\n Day 2 Complete!" << endl;
    cout << "Buildings created: " << Building::getBuildingCount() << endl;

    return 0;
}