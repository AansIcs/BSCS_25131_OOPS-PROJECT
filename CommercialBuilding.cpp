#include "CommercialBuilding.h"
#include "CityExceptions.h"
#include <iostream>
#include <algorithm>
using namespace std;
CommercialBuilding::CommercialBuilding(string addr, int year, double area,
    int numFloors, string bizName,
    string bizType)
    : Building(addr, year, area, numFloors)
{
    if (bizName.empty()) {
        throw BuildingException("Business name cannot be empty");
    }

    businessName = bizName;
    businessType = bizType;
    industry = "General";
    employeeCapacity = floors * 20;    // 20 employees per floor default
    isOpen = false;           // Starts closed
    openingTime = "09:00";
    closingTime = "18:00";
    customerCapacity = (int)(area / 5); // 1 customer per 5 sqm
    currentCustomers = 0;
    monthlyRevenue = 0.0;
    monthlyExpenses = 0.0;
    monthlyProfit = 0.0;
    hasCustomerParking = false;
    parkingSpaces = 0;
}

string CommercialBuilding::getBuildingType()const {
    return "Commercial";
}

double CommercialBuilding::calculatePropertyTax() const {
    return buildingValue * 0.02; 
}
void CommercialBuilding::openBusiness() {
    if (!isOperational) {
        throw BuildingException("Cannot open: building not operational");
    }
    if (employees.empty()) {
        throw BuildingException("Cannot open: no employees hired yet");
    }
    if (isOpen) {
        throw BuildingException("Business is already open");
    }

    isOpen = true;
    cout << businessName << " is now OPEN" << endl;
}
void CommercialBuilding::closeBusiness() {
    if (!isOpen) {
        throw BuildingException("Business is already closed");
    }

    isOpen = false;
    currentCustomers = 0;

    cout << businessName << " is now CLOSED" << endl;
}
void CommercialBuilding::hireEmployee(Citizen* employee) {
    if (employee == nullptr) {
        throw CitizenException("Cannot hire null employee");
    }
    if ((int)employees.size() >= employeeCapacity) {
        throw BuildingException("Cannot hire: at maximum employee capacity ("
            + to_string(employeeCapacity) + ")");
    }
    if (isEmployee(employee)) {
        throw CitizenException("This person is already an employee here");
    }

    employees.push_back(employee);
    cout << "Employee hired at " << businessName << endl;
}
void CommercialBuilding::fireEmployee(Citizen* employee) {
    if (employee == nullptr) {
        throw CitizenException("Cannot fire null employee");
    }

    auto it = find(employees.begin(), employees.end(), employee);

    if (it == employees.end()) {
        throw CitizenException("This person is not an employee here");
    }

    employees.erase(it);
    cout << "Employee removed from " << businessName << endl;
}
bool CommercialBuilding::isEmployee(Citizen* person) const {
    if (person == nullptr) return false;
    auto it = find(employees.begin(), employees.end(), person);
    return it != employees.end();
}
bool CommercialBuilding::customerEnters() {
    if (!isOpen) {
        return false;  
    }
    if (isAtCapacity()) {
        return false; 
    }

    currentCustomers++;
    return true;
}
void CommercialBuilding::customerLeaves() {
    if (currentCustomers > 0) {
        currentCustomers--;
    }
}
bool CommercialBuilding::isAtCapacity() const {
    return currentCustomers >= customerCapacity;
}
void CommercialBuilding::processMonthlyFinancials() {
    monthlyRevenue = calculateMonthlyRevenue();
    monthlyExpenses = 0.0;
    monthlyExpenses += floors * 500.0;             
    monthlyExpenses += (int)employees.size() * 2000.0; 
    monthlyExpenses += customerCapacity * 10.0;    
    monthlyExpenses += calculateMaintenanceCost() / 12.0; 
    monthlyProfit = monthlyRevenue - monthlyExpenses;
}
CommercialBuilding::~CommercialBuilding() {
    employees.clear();
    cout << businessName << " commercial building demolished" << endl;
}