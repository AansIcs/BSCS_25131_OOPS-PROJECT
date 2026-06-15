#pragma once

#include "Building.h"
#include <vector>
#include <string>
using namespace std;
class Citizen;
class CityManager;
class CommercialBuilding : public Building {
friend class CityManager;
protected:
  
    string businessName;        
    string businessType;      
    string industry;            
    int  employeeCapacity; 
    vector<Citizen*>  employees;         
    bool   isOpen;              
    string openingTime;        
    string closingTime;     
    int    customerCapacity;    
    int    currentCustomers;     
    double monthlyRevenue;       
    double monthlyExpenses;      
    double monthlyProfit;     
    bool   hasCustomerParking;
    int    parkingSpaces;

public:
    CommercialBuilding(string addr, int year, double area,int numFloors, string bizName, string bizType);
    string getBuildingType() const;
    virtual double calculateMaintenanceCost()const = 0;
    virtual int    getDailyVisitors() = 0;
    virtual void   displayDetails()        const = 0;
    virtual double calculateMonthlyRevenue() = 0;
    virtual double calculatePropertyTax()  const override;
    void   openBusiness();
    void   closeBusiness();
    bool   isCurrentlyOpen()   const { return isOpen; }
    void   hireEmployee(Citizen* employee);
    void   fireEmployee(Citizen* employee);
    bool   isEmployee(Citizen* person) const;
    int    getEmployeeCount()  const { return (int)employees.size(); }
    vector<Citizen*> getEmployees() const { return employees; }
    bool   customerEnters();   
    void   customerLeaves();
    int    getCurrentCustomers() const { return currentCustomers; }
    bool   isAtCapacity()        const;
    double getMonthlyRevenue()   const { return monthlyRevenue; }
    double getMonthlyExpenses()  const { return monthlyExpenses; }
    double getMonthlyProfit()    const { return monthlyProfit; }
    void   processMonthlyFinancials();
    string getBusinessName()     const { return businessName; }
    string getBusinessType()     const { return businessType; }
    int    getEmployeeCapacity() const { return employeeCapacity; }
    CommercialBuilding(const CommercialBuilding&) = delete;
    CommercialBuilding& operator=(const CommercialBuilding&) = delete;
    virtual ~CommercialBuilding();
};
