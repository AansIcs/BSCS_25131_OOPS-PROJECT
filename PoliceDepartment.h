#pragma once
#include "EmergencyService.h"
using namespace std;
class CrimeIncident;
class PoliceDepartment :public EmergencyService {
	friend class CityManager;
private:
	int arrestsMade;
	int casesSolved;
	double clearanceRate;
public:
	PoliceDepartment(string cityName);
	void respondToIncident(Incident* incident)override;
	bool canHandle(Incident* incident)const override;
	string getServiceType()const override;
	void displayInfo()const override;
	void investigateCrime(CrimeIncident* crime);
	int getArrestsMade()const { return arrestsMade; }
	int getCasesSolved()const { return casesSolved; }
	double getClearanceRate()const { return clearanceRate; }
	~PoliceDepartment();
};