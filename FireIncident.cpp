#include "FireIncident.h"
#include "Building.h"
#include <iostream>
#include <algorithm>
using namespace std;
FireIncident::FireIncident(Building* loc, string type, int alarm)
	:Incident("Fire", loc, min(alarm * 2, 10))
{
	fireType = type;
	alarmLevel = alarm;
	isContained = false;
	burnedAreaSqm = 0.0;
	peopleTrapped = 0;
	peopleRescued = 0;
	totalLoss = false;
}
void FireIncident::describe()const {
	cout << "\n=== FIRE INCIDENT ===" << endl;
	cout << "ID:          " << incidentID << endl;
	cout << "Type:        " << fireType << endl;
	cout << "Alarm Level: " << alarmLevel << "/5" << endl;
	cout << "Status:      " << status << endl;
	cout << "Contained:   " << (isContained ? "Yes" : "No") << endl;
	cout << "Burned Area: " << burnedAreaSqm << " sqm" << endl;
	cout << "Trapped:     " << peopleTrapped << endl;
	cout << "Rescued:     " << peopleRescued << endl;
	cout << "Total Loss:  " << (totalLoss ? "YES" : "No") << endl;
	if (location)cout << "Location:    " << location->getAddress() << endl;
	cout << "Damage:      $" << calculateDamage() << endl;
	cout << "=====================\n" << endl;
}
double FireIncident::calculateDamage()const {
	double damage = 0.0;
	if (location) {
		if (totalLoss) {
			damage = location->getValue();
		}
		else {
			damage = location->getValue() * (burnedAreaSqm / 100.0) * 0.5;
		}
	}
	damage += injuredCount * 10000.0;
	damage += fatalityCount * 500000.0;
	return damage;
}
string FireIncident::getIncidentCategory()const {
	return "Fire";
}
void FireIncident::containFire() {
	isContained = true;
	cout << incidentID << " - Fire CONTAINED" << endl;
}
void FireIncident::rescuePerson() {
	if (peopleTrapped > 0) {
		peopleTrapped--;
		peopleRescued++;
		cout << "Person rescued! Remaining trapped: " << peopleTrapped << endl;
	}
}
void FireIncident::setBurnedArea(double sqm) {
	burnedAreaSqm = sqm;
	propertyDamage = calculateDamage();
}
void FireIncident::setTotalLoss(bool loss) {
	totalLoss = loss;
	if (loss) {
		cout << incidentID << " - Building is a TOTAL LOSS" << endl;
	}
}
FireIncident::~FireIncident() {}