#include "PoliceDepartment.h"
#include "CrimeIncident.h"
#include "PoliceStation.h"
#include <iostream>
#include <algorithm>
using namespace std;
PoliceDepartment::PoliceDepartment(string cityName)
	:EmergencyService(cityName + " Police Department", "Police")
{
	arrestsMade = 0;
	casesSolved = 0;
	clearanceRate = 0.0;
}
bool PoliceDepartment::canHandle(Incident* incident)const {
	return (incident->getIncidentCategory() == "Crime");
}
void PoliceDepartment::respondToIncident(Incident* incident) {
	if (!isOperational) {
		cout << serviceName << " cannot respond: not operational" << endl;
		return;
	}
	CrimeIncident* crime = dynamic_cast<CrimeIncident*>(incident);
	if (crime == nullptr)return;
	incident->markResponding();
	crime->assignOfficer();
	cout << serviceName << " responding to crime " << crime->getIncidentID() << endl;
	incident->markOnScene();
	investigateCrime(crime);
}
void PoliceDepartment::investigateCrime(CrimeIncident* crime) {
	for (PublicServiceBuilding* station : stations) {
		PoliceStation* ps = dynamic_cast<PoliceStation*>(station);
		if (ps != nullptr && ps->hasCarAvailable()) {
			ps->dispatchCar();
			ps->recordCrime();
			break;
		}
	}
	crime->apprehendSuspect();
	arrestsMade++;
	crime->solveCase();
	casesSolved++;
	if (totalIncidentsHandled > 0) {
		clearanceRate = (static_cast<double>(casesSolved) / totalIncidentsHandled) * 100.0;
	}
	cout << serviceName << " solved crime " << crime->getIncidentID() << " | Clearance: " << clearanceRate << "%" << endl;
}
string PoliceDepartment::getServiceType()const {
	return "Police";
}
void PoliceDepartment::displayInfo()const {
	cout << "\n=== POLICE DEPARTMENT ===" << endl;
	cout << "Name:        " << serviceName << endl;
	cout << "Stations:    " << stations.size() << endl;
	cout << "Vehicles:    " << vehicles.size() << endl;
	cout << "Staff:       " << staff.size() << endl;
	cout << "Arrests:     " << arrestsMade << endl;
	cout << "Solved:      " << casesSolved << endl;
	cout << "Clearance:  " << clearanceRate << "%" << endl;
	cout << "Budget:      $" << annualBudget << endl;
	cout << "=========================\n" << endl;
}
PoliceDepartment::~PoliceDepartment() {
	cout << serviceName << " disbanded" << endl;
}