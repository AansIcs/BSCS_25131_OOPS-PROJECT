#include "Restaurant.h"
#include "CityExceptions.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <numeric>
using namespace std;
Restaurant::Restaurant(string addr, int year, double area,
    int floors, string name, string cuisine,
    int numTables, int seatsPerTable)
    : CommercialBuilding(addr, year, area, floors, name, "Food Service")
{
    if (numTables < 1) {
        throw BuildingException("Restaurant must have at least 1 table");
    }
    if (seatsPerTable < 1) {
        throw BuildingException("Tables must have at least 1 seat");
    }
    cuisineType = cuisine;
    currentDiners = 0;
    chefCount = 1;
    waiterCount = numTables / 3 + 1;
    foodQualityRating = 0.0;
    serviceRating = 0.0;
    ambianceRating = 0.0;
    totalReviews = 0;
    coversToday = 0;
    revenueToday = 0.0;

    totalSeatingCapacity = 0;
    for (int i = 1; i <= numTables; i++) {
        tables.push_back(Table(i, seatsPerTable));
        totalSeatingCapacity += seatsPerTable;
    }

    customerCapacity = totalSeatingCapacity;

    cout << "Restaurant '" << businessName << "' (" << cuisineType << ")"
        << " opened with " << numTables << " tables ("
        << totalSeatingCapacity << " seats)" << endl;
}

double Restaurant::calculateMaintenanceCost()const {
    double cost = 0.0;
    cost += landArea * 5.0;
    cost += tables.size() * 500.0;
    cost += chefCount * 2000.0;
    cost += 3000.0;
    cost += 1000.0;

    if (getOverallRating() > 4.0) {
        cost *= 1.3;
    }

    int age = getAge();
    if (age > 15) cost *= 1.5;
    else if (age > 8) cost *= 1.2;

    return cost;
}

int Restaurant::getDailyVisitors() {
    double turnover = 2.0;

    if (getOverallRating() > 4.5) turnover = 3.0;
    else if (getOverallRating() > 4.0) turnover = 2.5;

    return static_cast<int>(totalSeatingCapacity * turnover);
}

string Restaurant::getBuildingType() const {
    return "Restaurant";
}

void Restaurant::displayDetails() const {
    cout << "\n======== RESTAURANT ========" << endl;
    cout << "Name:     " << businessName << endl;
    cout << "Cuisine:  " << cuisineType << endl;
    cout << "ID:       " << buildingID << endl;
    cout << "Address:  " << address << endl;
    cout << "Status:   " << (isOpen ? "OPEN" : "CLOSED") << endl;

    cout << "\n--- Seating ---" << endl;
    cout << "Tables:          " << tables.size() << endl;
    cout << "Total Seats:     " << totalSeatingCapacity << endl;
    cout << "Current Diners:  " << currentDiners << endl;
    cout << "Available Seats: " << getAvailableSeats() << endl;

    cout << "\n--- Staff ---" << endl;
    cout << "Chefs:     " << chefCount << endl;
    cout << "Waiters:   " << waiterCount << endl;
    cout << "Employees: " << employees.size() << endl;

    cout << "\n--- Ratings ---" << endl;
    if (totalReviews > 0) {
        cout << fixed << setprecision(1);
        cout << "Food:     " << foodQualityRating << "/5.0" << endl;
        cout << "Service:  " << serviceRating << "/5.0" << endl;
        cout << "Ambiance: " << ambianceRating << "/5.0" << endl;
        cout << "Overall:  " << getOverallRating() << "/5.0 ("
            << totalReviews << " reviews)" << endl;
    }
    else {
        cout << "No reviews yet" << endl;
    }

    cout << "\n--- Menu Sample ---" << endl;
    cout << "Total Items: " << menu.size() << endl;

    cout << "\n--- Financials ---" << endl;
    cout << "Monthly Revenue:  $" << fixed << setprecision(2)
        << monthlyRevenue << endl;
    cout << "Annual Maint:     $" << fixed << setprecision(2)  << calculateMaintenanceCost() << endl;
    cout << "============================\n" << endl;
}

double Restaurant::calculateMonthlyRevenue() {
    if (menu.empty()) return 0.0;

    double totalMenuPrice = 0.0;
    int    availableItems = 0;
    for (const MenuItem& item : menu) {
        if (item.isAvailable) {
            totalMenuPrice += item.sellingPrice;
            availableItems++;
        }
    }

    if (availableItems == 0) return 0.0;

    double avgMealPrice = (totalMenuPrice / availableItems) * 2.0;

    double dailyRevenue = getDailyVisitors() * avgMealPrice;
    double monthly = dailyRevenue * 30;

    if (getOverallRating() > 4.0) {
        monthly *= 1.2;
    }

    return monthly;
}

void Restaurant::addMenuItem(string id, string name, string cat,
    double cost, double price, int prep) {
    if (price <= 0) {
        throw BuildingException("Menu item price must be positive");
    }
    if (price < cost) {
        throw BuildingException("Selling price cannot be less than cost");
    }

    for (const MenuItem& m : menu) {
        if (m.itemID == id) {
            throw BuildingException("Menu item ID " + id + " already exists");
        }
    }

    menu.push_back(MenuItem(id, name, cat, cost, price, prep));
    cout << "Menu item '" << name << "' added ($" << price << ")" << endl;
}

void Restaurant::removeMenuItem(string itemID) {
    auto it = find_if(menu.begin(), menu.end(),
        [&](const MenuItem& m) {
            return m.itemID == itemID;
        });

    if (it == menu.end()) {
        throw BuildingException("Menu item not found: " + itemID);
    }

    cout << "Menu item '" << it->itemName << "' removed" << endl;
    menu.erase(it);
}

void Restaurant::setAvailability(string itemID, bool available) {
    for (MenuItem& m : menu) {
        if (m.itemID == itemID) {
            m.isAvailable = available;
            cout << m.itemName << (available ? " is now available" : " is now unavailable") << endl;
            return;
        }
    }
    throw BuildingException("Menu item not found: " + itemID);
}

Restaurant::MenuItem Restaurant::findMenuItem(string itemID) const {
    for (const MenuItem& m : menu) {
        if (m.itemID == itemID) return m;
    }
    throw BuildingException("Menu item not found: " + itemID);
}

bool Restaurant::seatDiners(int tableNum, int count) {
    if (!isOpen) {
        throw BuildingException("Restaurant is not open");
    }

    for (Table& t : tables) {
        if (t.tableNumber == tableNum) {
            if (t.isOccupied) {
                throw BuildingException("Table " + to_string(tableNum)  + " is already occupied");
            }
            if (count > t.capacity) {
                throw BuildingException("Party of " + to_string(count)  + " too large for table "  + to_string(tableNum)  + " (capacity: "  + to_string(t.capacity) + ")");
            }

            t.isOccupied = true;
            t.currentDiners = count;
            currentDiners += count;
            coversToday += count;

            cout << count << " diners seated at table " << tableNum << endl;
            return true;
        }
    }
    throw BuildingException("Table " + to_string(tableNum) + " not found");
}

bool Restaurant::clearTable(int tableNum) {
    for (Table& t : tables) {
        if (t.tableNumber == tableNum) {
            if (!t.isOccupied) {
                throw BuildingException("Table " + to_string(tableNum)   + " is already empty");
            }
            currentDiners -= t.currentDiners;
            t.isOccupied = false;
            t.currentDiners = 0;
            cout << "Table " << tableNum << " cleared" << endl;
            return true;
        }
    }
    throw BuildingException("Table " + to_string(tableNum) + " not found");
}

int Restaurant::getAvailableTables() const {
    int count = 0;
    for (const Table& t : tables) {
        if (!t.isOccupied) count++;
    }
    return count;
}

int Restaurant::getAvailableSeats() const {
    int seats = 0;
    for (const Table& t : tables) {
        if (!t.isOccupied) seats += t.capacity;
    }
    return seats;
}

void Restaurant::hireChef() {
    chefCount++;
    cout << "Chef hired at " << businessName
        << " (Total chefs: " << chefCount << ")" << endl;
}

void Restaurant::hireWaiter() {
    waiterCount++;
    cout << "Waiter hired at " << businessName
        << " (Total waiters: " << waiterCount << ")" << endl;
}

void Restaurant::receiveReview(double food, double service, double ambiance) {
    auto clamp = [](double val) { return max(1.0, min(5.0, val)); };
    food = clamp(food);
    service = clamp(service);
    ambiance = clamp(ambiance);

    int n = totalReviews;
    foodQualityRating = (foodQualityRating * n + food) / (n + 1);
    serviceRating = (serviceRating * n + service) / (n + 1);
    ambianceRating = (ambianceRating * n + ambiance) / (n + 1);

    totalReviews++;
    cout << "Review received. Overall rating: "
        << fixed << setprecision(2) << getOverallRating() << "/5.0" << endl;
}

double Restaurant::getOverallRating() const {
    if (totalReviews == 0) return 0.0;
    return (foodQualityRating + serviceRating + ambianceRating) / 3.0;
}

Restaurant::~Restaurant() {
    menu.clear();
    tables.clear();
    cout << "Restaurant '" << businessName << "' closed permanently" << endl;
}