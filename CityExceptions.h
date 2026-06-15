#pragma once
#include <exception>
#include <string>
using namespace std;
class CityException : public exception {
protected:
    string message;
    string errorCode;

public:
    CityException(const string& msg, const string& code = "CITY_ERROR")
        : message(msg), errorCode(code) {
    }

    // Override what() from std::exception
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
    string getErrorCode() const {
        return errorCode;
    }
    virtual ~CityException() {}
};
class BuildingException : public CityException {
public:
    BuildingException(const string& msg): CityException(msg, "BUILDING_ERROR") {
    }
};
class CitizenException : public CityException {
public:
    CitizenException(const string& msg): CityException(msg, "CITIZEN_ERROR") {
    }
};

class VehicleException : public CityException {
public:
    VehicleException(const string& msg): CityException(msg, "VEHICLE_ERROR") {
    }
};
class BudgetException : public CityException {
public:
    BudgetException(const string& msg) : CityException(msg, "BUDGET_ERROR") {
    }
};
class UtilityException : public CityException {
public:
    UtilityException(const string& msg): CityException(msg, "UTILITY_ERROR") {
    }
};
