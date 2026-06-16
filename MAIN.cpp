#include "CityManager.h"
#include "House.h"
#include "Apartment.h"
#include "TowerBlock.h"
#include "Shop.h"
#include "Restaurant.h"
#include "Office.h"
#include "Mall.h"
#include "School.h"
#include "Hospital.h"
#include "FireStation.h"
#include "PoliceStation.h"
#include "Citizen.h"
#include "Student.h"
#include "Retiree.h"
#include "Household.h"
#include "PrivateCar.h"
#include "Bus.h"
#include "Taxi.h"
#include "Road.h"
#include"Ambulance.h"
#include"FireTruck.h"
#include "TrafficLight.h"
#include "PowerService.h"
#include "WaterService.h"
#include "CityBudget.h"
#include "TaxSystem.h"
#include "RetailBusiness.h"
#include "IndustrailBusiness.h"
#include "FireDepartment.h"
#include "PoliceDepartment.h"
#include "MedicalService.h"
#include "CityExceptions.h"
#define NOMINMAX 
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#define CLEAR() system("cls")
#else
#include <unistd.h>
#define SLEEP(ms) usleep((ms) * 1000)
#define CLEAR() system("clear")
#endif

using namespace std;

// ============================================================
// HELPER FUNCTIONS
// ============================================================

void pressEnter() {
    cout << endl;
    cout << "Press Enter to continue...";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    cin.get();
}

void printLine(int width = 50) {
    cout << string(width, '-') << endl;
}

void printHeader(string title) {
    cout << endl;
    printLine();
    cout << "   " << title << endl;
    printLine();
    cout << endl;
}

void printLoading(string message) {
    cout << message;
    for (int i = 0; i < 5; i++) {
        cout << "." << flush;
        SLEEP(200);
    }
    cout << " Done!" << endl;
}

void clearAndHeader(string title) {
    CLEAR();
    printHeader(title);
}

int getIntInput(string prompt, int min, int max) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= min && val <= max) {
            cin.ignore();
            return val;
        }
        cout << "Invalid input. Enter a number between "
            << min << " and " << max << ": ";
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
}

double getDoubleInput(string prompt, double min) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= min) {
            cin.ignore();
            return val;
        }
        cout << "Invalid. Enter a number >= " << min << ": ";
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
}

string getStringInput(string prompt) {
    string val;
    cout << prompt;
    getline(cin, val);
    return val;
}

// ============================================================
// DEMO CITY SETUP
// ============================================================

void setupDemoCity(CityManager* city) {
    clearAndHeader("SETTING UP DEMO CITY");

    cout << "Building city infrastructure..." << endl << endl;

    // BUILDINGS
    printLoading("Adding residential buildings");

    House* house1 = city->addHouse(
        "123 Maple Street", 2018, 400, 2, 3, 2);
    house1->addGarage(2);
    house1->expandGarden(100);

    House* house2 = city->addHouse(
        "456 Oak Avenue", 2015, 350, 1, 2, 1);

    Apartment* apt1 = city->addApartment(
        "45 Downtown Avenue", 2015, 1200, 6, 4);
    apt1->setHasElevator(true);
    apt1->setHasGym(true);

    printLoading("Adding commercial buildings");

    Shop* grocery = city->addShop(
        "10 Market Street", 2019, 300, 1,
        "City Fresh Mart", "Grocery");
    grocery->addProduct("P001", "Rice 5kg", "Food", 2.0, 5.0, 100);
    grocery->addProduct("P002", "Milk 1L", "Food", 0.8, 1.5, 200);
    grocery->addProduct("P003", "Bread", "Food", 1.0, 2.5, 150);
    grocery->addProduct("P004", "Laptop", "Electronics", 450.0, 700.0, 8);
    grocery->addProduct("P005", "T-Shirt", "Clothing", 5.0, 20.0, 50);

    Restaurant* resto = city->addRestaurant(
        "25 Food Lane", 2020, 250, 1,
        "La Bella Italia", "Italian", 10, 4);
    resto->addMenuItem("M001", "Bruschetta", "Starter", 2.0, 8.0, 10);
    resto->addMenuItem("M002", "Pasta Carbonara", "Main", 5.0, 18.0, 20);
    resto->addMenuItem("M003", "Pizza Margherita", "Main", 4.0, 15.0, 15);
    resto->addMenuItem("M004", "Tiramisu", "Dessert", 2.5, 8.0, 5);
    resto->addMenuItem("M005", "Red Wine", "Drink", 4.0, 14.0, 2);
    resto->hireChef();
    resto->hireWaiter();
    resto->hireWaiter();

    Office* techOffice = city->addOffice(
        "50 Tech Park", 2022, 800, 3,
        "TechCorp HQ", "Technology");
    techOffice->addConferenceRoom();
    techOffice->addCafeteria();
    techOffice->enable24HourAccess();

    Mall* cityMall = city->addMall(
        "1 Mall Road", 2020, 5000, 3,
        "City Grand Mall", 20);
    cityMall->addFoodCourt(200);
    cityMall->addCinema(4);
    cityMall->addParkingLevel();

    printLoading("Adding public service buildings");

    School* elemSchool = city->addSchool(
        "5 Education Boulevard", 2010, 500, 2, "Elementary");
    elemSchool->hireTeacher();
    elemSchool->hireTeacher();
    elemSchool->hireTeacher();
    elemSchool->addLibrary();

    School* highSchool = city->addSchool(
        "8 Academy Road", 2005, 800, 3, "High");
    highSchool->hireTeacher();
    highSchool->hireTeacher();
    highSchool->hireTeacher();
    highSchool->hireTeacher();
    highSchool->addLibrary();
    highSchool->addLaboratory();

    Hospital* cityHospital = city->addHospital(
        "100 Health Avenue", 2012, 2000, 5, 200);
    cityHospital->hireDoctor();
    cityHospital->hireDoctor();
    cityHospital->hireDoctor();
    cityHospital->hireNurse();
    cityHospital->hireNurse();
    cityHospital->hireNurse();
    cityHospital->allocateBudget(500000.0);

    FireStation* fireStation = city->addFireStation(
        "30 Safety Street", 2015, 500);
    fireStation->hireFirefighter();
    fireStation->hireFirefighter();
    fireStation->hireFirefighter();
    fireStation->hireFirefighter();
    fireStation->addFireTruck();
    fireStation->addFireTruck();

    PoliceStation* policeStation = city->addPoliceStation(
        "40 Justice Avenue", 2014, 400);
    policeStation->hireOfficer();
    policeStation->hireOfficer();
    policeStation->hireOfficer();
    policeStation->hireOfficer();
    policeStation->addPatrolCar();
    policeStation->addPatrolCar();
    policeStation->addPatrolCar();

    // CITIZENS
    printLoading("Adding citizens");

    Citizen* john = city->addCitizen(
        "John", "Smith", 35, "Male",
        "Software Engineer", 75000.0);
    john->setHome(house1);
    house1->addResident(john);

    Citizen* sarah = city->addCitizen(
        "Sarah", "Johnson", 32, "Female",
        "Doctor", 95000.0);

    Citizen* mike = city->addCitizen(
        "Mike", "Williams", 45, "Male",
        "Business Owner", 120000.0);

    Citizen* emma = city->addCitizen(
        "Emma", "Davis", 28, "Female",
        "Teacher", 45000.0);

    Citizen* david = city->addCitizen(
        "David", "Brown", 40, "Male",
        "Accountant", 60000.0);

    Student* tommy = city->addStudent(
        "Tommy", "Smith", 10, "Male",
        elemSchool, "Elementary");

    Student* lisa = city->addStudent(
        "Lisa", "Brown", 16, "Female",
        highSchool, "High");
    lisa->getPartTimeJob(500.0);

    Student* alex = city->addStudent(
        "Alex", "Johnson", 14, "Male",
        highSchool, "High");

    Retiree* george = city->addRetiree(
        "George", "Wilson", 68, "Male",
        "Civil Engineer", 2500.0);
    george->setPreferredHospital(cityHospital);
    george->addHobby("Gardening");
    george->addHobby("Chess");

    Retiree* martha = city->addRetiree(
        "Martha", "Wilson", 65, "Female",
        "School Principal", 2200.0);
    martha->setPreferredHospital(cityHospital);
    martha->addHobby("Painting");

    // HOUSEHOLDS
    printLoading("Creating households");

    Household* smithFamily = city->createHousehold(john, house1);
    smithFamily->addMember(sarah);

    Household* wilsonFamily = city->createHousehold(david, house2);

    // VEHICLES
    printLoading("Adding vehicles");

    PrivateCar* johnsCar = city->addPrivateCar(
        "Toyota", "Camry", 2021, "Petrol", 5, john, 25000.0);

    PrivateCar* sarahsCar = city->addPrivateCar(
        "Honda", "Civic", 2022, "Petrol", 5, sarah, 22000.0);

    PrivateCar* mikesCar = city->addPrivateCar(
        "BMW", "X5", 2023, "Petrol", 7, mike, 60000.0);

    Bus* bus42 = city->addBus("42", 2020, false);
    bus42->addStop("City Center");
    bus42->addStop("Shopping Mall");
    bus42->addStop("Hospital");
    bus42->addStop("University");
    bus42->addStop("Train Station");
    bus42->startService();

    Bus* bus15 = city->addBus("15", 2021, true);
    bus15->addStop("North District");
    bus15->addStop("City Center");
    bus15->addStop("South District");
    bus15->startService();

    Taxi* taxi1 = city->addTaxi("CityTaxi Co", 2021, 3.0, 1.5);
    Taxi* taxi2 = city->addTaxi("CityTaxi Co", 2020, 3.0, 1.5);
    Taxi* taxi3 = city->addTaxi("FastRide", 2022, 2.5, 1.8);

    Ambulance* amb1 = city->addAmbulance(2022);
    Ambulance* amb2 = city->addAmbulance(2021);

    FireTruck* ft1 = city->addFireTruck(2019, 2000.0);
    FireTruck* ft2 = city->addFireTruck(2021, 2500.0);

    // ROADS
    printLoading("Building road network");

    Road* mainStreet = city->addRoad(
        "Main Street", house1, grocery, 4, 50, "Avenue");
    Road* cityHighway = city->addRoad(
        "City Highway", cityHospital, cityMall, 6, 100, "Highway");
    Road* parkRoad = city->addRoad(
        "Park Road", elemSchool, highSchool, 2, 40, "Street");

    // ECONOMY
    printLoading("Setting up economy");

    RetailBusiness* techStore = city->addRetailBusiness(
        "TechZone Electronics", "Electronics",
        mike, techOffice, 500000.0);
    techStore->enableOnlineStore();
    techStore->hireEmployee(david);

    IndustrialBusiness* factory = city->addIndustrialBusiness(
        "City Manufacturing Co", "Manufacturing",
        mike, nullptr, 1000000.0);
    factory->installWasteManagement();

    // Initial finances
    city->collectAllTaxes();
    city->allocateDepartmentBudgets();

    cout << endl;
    cout << "Demo city setup complete!" << endl;
    cout << endl;
    cout << "Summary:" << endl;
    cout << "  Buildings  : " << city->getBuildingCount() << endl;
    cout << "  Citizens   : " << city->getCitizenCount() << endl;
    cout << "  Vehicles   : " << city->getVehicleCount() << endl;
    cout << "  Businesses : " << city->getBusinessCount() << endl;

    SLEEP(1000);
    pressEnter();
}

// ============================================================
// BUILDING MENU
// ============================================================

void buildingMenu(CityManager* city) {
    int choice = -1;
    while (choice != 0) {
        clearAndHeader("BUILDING MANAGEMENT");

        cout << " 1.  Add House" << endl;
        cout << " 2.  Add Apartment" << endl;
        cout << " 3.  Add Shop" << endl;
        cout << " 4.  Add Restaurant" << endl;
        cout << " 5.  Add Office" << endl;
        cout << " 6.  Add Mall" << endl;
        cout << " 7.  Add School" << endl;
        cout << " 8.  Add Hospital" << endl;
        cout << " 9.  Add Fire Station" << endl;
        cout << " 10. Add Police Station" << endl;
        cout << " 11. List All Buildings" << endl;
        cout << " 0.  Back to Main Menu" << endl;
        printLine();

        choice = getIntInput("Enter choice: ", 0, 11);

        try {
            if (choice == 1) {
                clearAndHeader("ADD HOUSE");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built (1900-2025): ", 1900, 2025);
                double area = getDoubleInput("Land Area in sqm: ", 1.0);
                int floors = getIntInput("Number of Floors: ", 1, 50);
                int beds = getIntInput("Bedrooms: ", 1, 20);
                int baths = getIntInput("Bathrooms: ", 1, 20);

                House* h = city->addHouse(addr, year, area, floors, beds, baths);
                cout << endl << "House added successfully!" << endl;
                h->displayDetails();
                pressEnter();

            }
            else if (choice == 2) {
                clearAndHeader("ADD APARTMENT");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built: ", 1900, 2025);
                double area = getDoubleInput("Land Area in sqm: ", 1.0);
                int floors = getIntInput("Number of Floors: ", 1, 100);
                int uph = getIntInput("Units Per Floor: ", 1, 50);

                Apartment* a = city->addApartment(addr, year, area, floors, uph);
                cout << endl << "Apartment added successfully!" << endl;
                a->displayDetails();
                pressEnter();

            }
            else if (choice == 3) {
                clearAndHeader("ADD SHOP");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built: ", 1900, 2025);
                double area = getDoubleInput("Area in sqm: ", 1.0);
                int floors = getIntInput("Floors: ", 1, 10);
                string name = getStringInput("Shop Name: ");
                string cat = getStringInput("Category (Grocery/Clothing/Electronics/General): ");

                Shop* s = city->addShop(addr, year, area, floors, name, cat);
                cout << endl << "Shop added successfully!" << endl;
                s->displayDetails();
                pressEnter();

            }
            else if (choice == 4) {
                clearAndHeader("ADD RESTAURANT");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built: ", 1900, 2025);
                double area = getDoubleInput("Area in sqm: ", 1.0);
                int floors = getIntInput("Floors: ", 1, 10);
                string name = getStringInput("Restaurant Name: ");
                string cuisine = getStringInput("Cuisine Type (Italian/Chinese/American/etc): ");
                int tables = getIntInput("Number of Tables: ", 1, 200);
                int seats = getIntInput("Seats Per Table: ", 1, 20);

                Restaurant* r = city->addRestaurant(
                    addr, year, area, floors, name, cuisine, tables, seats);
                cout << endl << "Restaurant added successfully!" << endl;
                r->displayDetails();
                pressEnter();

            }
            else if (choice == 5) {
                clearAndHeader("ADD OFFICE");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built: ", 1900, 2025);
                double area = getDoubleInput("Area in sqm: ", 1.0);
                int floors = getIntInput("Floors: ", 1, 100);
                string name = getStringInput("Company Name: ");
                string industry = getStringInput("Industry (Tech/Finance/Legal/General): ");

                Office* o = city->addOffice(
                    addr, year, area, floors, name, industry);
                cout << endl << "Office added successfully!" << endl;
                o->displayDetails();
                pressEnter();

            }
            else if (choice == 6) {
                clearAndHeader("ADD MALL");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built: ", 1900, 2025);
                double area = getDoubleInput("Area in sqm: ", 1.0);
                int floors = getIntInput("Floors: ", 1, 20);
                string name = getStringInput("Mall Name: ");
                int stores = getIntInput("Number of Store Spaces: ", 1, 500);

                Mall* m = city->addMall(addr, year, area, floors, name, stores);
                cout << endl << "Mall added successfully!" << endl;
                m->displayDetails();
                pressEnter();

            }
            else if (choice == 7) {
                clearAndHeader("ADD SCHOOL");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built: ", 1900, 2025);
                double area = getDoubleInput("Area in sqm: ", 1.0);
                int floors = getIntInput("Floors: ", 1, 10);
                string level = getStringInput("Level (Elementary/Middle/High/University): ");

                School* s = city->addSchool(addr, year, area, floors, level);
                s->hireTeacher();
                s->hireTeacher();
                cout << endl << "School added (2 teachers hired)!" << endl;
                s->displayDetails();
                pressEnter();

            }
            else if (choice == 8) {
                clearAndHeader("ADD HOSPITAL");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built: ", 1900, 2025);
                double area = getDoubleInput("Area in sqm: ", 1.0);
                int floors = getIntInput("Floors: ", 1, 50);
                int beds = getIntInput("Number of Beds: ", 10, 2000);

                Hospital* h = city->addHospital(addr, year, area, floors, beds);
                h->hireDoctor();
                h->hireDoctor();
                h->hireNurse();
                h->hireNurse();
                cout << endl << "Hospital added (2 doctors, 2 nurses hired)!" << endl;
                h->displayDetails();
                pressEnter();

            }
            else if (choice == 9) {
                clearAndHeader("ADD FIRE STATION");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built: ", 1900, 2025);
                double area = getDoubleInput("Area in sqm: ", 1.0);

                FireStation* fs = city->addFireStation(addr, year, area);
                fs->hireFirefighter();
                fs->hireFirefighter();
                fs->hireFirefighter();
                fs->addFireTruck();
                fs->addFireTruck();
                cout << endl;
                cout << "Fire Station added!" << endl;
                cout << "  3 firefighters hired" << endl;
                cout << "  2 fire trucks added" << endl;
                fs->displayDetails();
                pressEnter();

            }
            else if (choice == 10) {
                clearAndHeader("ADD POLICE STATION");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string addr = getStringInput("Address: ");
                int year = getIntInput("Year Built: ", 1900, 2025);
                double area = getDoubleInput("Area in sqm: ", 1.0);

                PoliceStation* ps = city->addPoliceStation(addr, year, area);
                ps->hireOfficer();
                ps->hireOfficer();
                ps->hireOfficer();
                ps->addPatrolCar();
                ps->addPatrolCar();
                cout << endl;
                cout << "Police Station added!" << endl;
                cout << "  3 officers hired" << endl;
                cout << "  2 patrol cars added" << endl;
                ps->displayDetails();
                pressEnter();

            }
            else if (choice == 11) {
                clearAndHeader("ALL BUILDINGS");
                city->displayAllBuildings();
                pressEnter();
            }

        }
        catch (CityException& e) {
            cout << endl << "ERROR: " << e.what() << endl;
            cout << "Error Code: " << e.getErrorCode() << endl;
            pressEnter();
        }
        catch (exception& e) {
            cout << endl << "System Error: " << e.what() << endl;
            pressEnter();
        }
    }
}

// ============================================================
// CITIZEN MENU
// ============================================================

void citizenMenu(CityManager* city) {
    int choice = -1;
    while (choice != 0) {
        clearAndHeader("CITIZEN MANAGEMENT");

        cout << " 1.  Add Working Citizen" << endl;
        cout << " 2.  Add Student" << endl;
        cout << " 3.  Add Retiree" << endl;
        cout << " 4.  Create Household" << endl;
        cout << " 5.  List All Citizens" << endl;
        cout << " 6.  Simulate Daily Activities" << endl;
        cout << " 0.  Back to Main Menu" << endl;
        printLine();

        choice = getIntInput("Enter choice: ", 0, 6);

        try {
            if (choice == 1) {
                clearAndHeader("ADD WORKING CITIZEN");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string fname = getStringInput("First Name: ");
                string lname = getStringInput("Last Name: ");
                int age = getIntInput("Age (18-65): ", 18, 65);
                string gender = getStringInput("Gender (Male/Female/Other): ");
                string occ = getStringInput("Occupation: ");
                double income = getDoubleInput("Annual Income ($): ", 0.0);

                Citizen* c = city->addCitizen(
                    fname, lname, age, gender, occ, income);
                cout << endl << "Citizen added!" << endl;
                c->displayInfo();
                pressEnter();

            }
            else if (choice == 2) {
                clearAndHeader("ADD STUDENT");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string fname = getStringInput("First Name: ");
                string lname = getStringInput("Last Name: ");
                int age = getIntInput("Age (5-25): ", 5, 25);
                string gender = getStringInput("Gender: ");
                string level = getStringInput(
                    "Level (Elementary/Middle/High/College): ");

                cout << endl;
                cout << "Note: No school assigned." << endl;
                cout << "Use School menu to enroll later." << endl;

                Student* s = city->addStudent(
                    fname, lname, age, gender, nullptr, level);
                cout << endl << "Student added!" << endl;
                s->displayInfo();
                pressEnter();

            }
            else if (choice == 3) {
                clearAndHeader("ADD RETIREE");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string fname = getStringInput("First Name: ");
                string lname = getStringInput("Last Name: ");
                int age = getIntInput("Age (60-100): ", 60, 100);
                string gender = getStringInput("Gender: ");
                string formerJob = getStringInput("Former Occupation: ");
                double pension = getDoubleInput("Monthly Pension ($): ", 0.0);

                Retiree* r = city->addRetiree(
                    fname, lname, age, gender, formerJob, pension);
                cout << endl << "Retiree added!" << endl;
                r->displayInfo();
                pressEnter();

            }
            else if (choice == 4) {
                clearAndHeader("CREATE HOUSEHOLD");
                cout << "Note: Creating household with no home." << endl;
                cout << "A new single citizen household will be created." << endl;
                cout << endl;

                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string fname = getStringInput("Head of Household First Name: ");
                string lname = getStringInput("Head of Household Last Name: ");
                double income = getDoubleInput("Monthly Income ($): ", 0.0);

                Citizen* head = city->addCitizen(
                    fname, lname, 30, "Male", "Worker", income * 12);
                Household* hh = city->createHousehold(head, nullptr);
                hh->calculateCombinedIncome();
                hh->displayInfo();
                pressEnter();

            }
            else if (choice == 5) {
                clearAndHeader("ALL CITIZENS");
                city->displayAllCitizens();
                pressEnter();

            }
            else if (choice == 6) {
                clearAndHeader("SIMULATING DAILY ACTIVITIES");
                cout << "All citizens performing today's activities..." << endl;
                cout << endl;
                city->simulateDay();
                pressEnter();
            }

        }
        catch (CityException& e) {
            cout << endl << "ERROR: " << e.what() << endl;
            pressEnter();
        }
    }
}

// ============================================================
// VEHICLE MENU
// ============================================================

void vehicleMenu(CityManager* city) {
    int choice = -1;
    while (choice != 0) {
        clearAndHeader("VEHICLE AND TRANSPORT");

        cout << " 1.  Add Private Car" << endl;
        cout << " 2.  Add Bus" << endl;
        cout << " 3.  Add Taxi" << endl;
        cout << " 4.  Add Ambulance" << endl;
        cout << " 5.  Add Fire Truck" << endl;
        cout << " 6.  Add Road" << endl;
        cout << " 7.  Traffic Light State Demo" << endl;
        cout << " 8.  List All Vehicles" << endl;
        cout << " 0.  Back to Main Menu" << endl;
        printLine();

        choice = getIntInput("Enter choice: ", 0, 8);

        try {
            if (choice == 1) {
                clearAndHeader("ADD PRIVATE CAR");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string make = getStringInput("Make (Toyota/Honda/BMW etc): ");
                string model = getStringInput("Model: ");
                int year = getIntInput("Year: ", 1990, 2025);
                string fuel = getStringInput("Fuel Type (Petrol/Diesel/Electric): ");
                int cap = getIntInput("Passenger Capacity: ", 1, 10);
                double price = getDoubleInput("Purchase Price ($): ", 1000.0);

                PrivateCar* car = city->addPrivateCar(
                    make, model, year, fuel, cap, nullptr, price);
                cout << endl << "Car added!" << endl;
                car->displayInfo();
                pressEnter();

            }
            else if (choice == 2) {
                clearAndHeader("ADD BUS");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string num = getStringInput("Bus Number/Route (e.g. 42): ");
                int year = getIntInput("Year: ", 1990, 2025);
                int dbl = getIntInput("Double Decker? (1=Yes 0=No): ", 0, 1);

                Bus* bus = city->addBus(num, year, (dbl == 1));
                bus->addStop("City Center");
                bus->addStop("Hospital");
                bus->addStop("School");
                bus->addStop("Mall");
                bus->startService();
                cout << endl;
                cout << "Bus " << num << " added with 4 stops!" << endl;
                bus->displayInfo();
                pressEnter();

            }
            else if (choice == 3) {
                clearAndHeader("ADD TAXI");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string company = getStringInput("Company Name: ");
                int year = getIntInput("Year: ", 1990, 2025);
                double base = getDoubleInput("Base Fare ($): ", 0.5);
                double perKm = getDoubleInput("Rate Per Km ($): ", 0.1);

                Taxi* taxi = city->addTaxi(company, year, base, perKm);
                cout << endl << "Taxi added!" << endl;
                taxi->displayInfo();
                pressEnter();

            }
            else if (choice == 4) {
                clearAndHeader("ADD AMBULANCE");
                int year = getIntInput("Year: ", 1990, 2025);

                Ambulance* amb = city->addAmbulance(year);
                cout << endl;
                cout << "Ambulance added and assigned to Medical Service!" << endl;
                amb->displayInfo();
                pressEnter();

            }
            else if (choice == 5) {
                clearAndHeader("ADD FIRE TRUCK");
                int year = getIntInput("Year: ", 1990, 2025);
                double waterCap = getDoubleInput("Water Capacity (liters): ", 500.0);

                FireTruck* ft = city->addFireTruck(year, waterCap);
                cout << endl;
                cout << "Fire Truck added and assigned to Fire Department!" << endl;
                ft->displayInfo();
                pressEnter();

            }
            else if (choice == 6) {
                clearAndHeader("ADD ROAD");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string name = getStringInput("Road Name: ");
                string type = getStringInput("Type (Street/Avenue/Highway): ");
                int lanes = getIntInput("Number of Lanes: ", 1, 12);
                int limit = getIntInput("Speed Limit (km/h): ", 10, 130);

                Road* road = city->addRoad(
                    name, nullptr, nullptr, lanes, limit, type);
                cout << endl << "Road added!" << endl;
                road->displayInfo();
                pressEnter();

            }
            else if (choice == 7) {
                clearAndHeader("TRAFFIC LIGHT STATE PATTERN DEMO");
                cout << "This demonstrates the STATE PATTERN." << endl;
                cout << "Traffic light cycles: Red -> Green -> Yellow -> Red" << endl;
                cout << endl;

                int red = getIntInput("Red duration (seconds): ", 1, 60);
                int yellow = getIntInput("Yellow duration (seconds): ", 1, 10);
                int green = getIntInput("Green duration (seconds): ", 1, 60);

                TrafficLight tl(red, yellow, green);
                int totalTime = (red + yellow + green) * 2;

                cout << endl;
                cout << "Running for " << totalTime << " seconds..." << endl;
                cout << endl;

                for (int t = 0; t <= totalTime; t++) {
                    cout << "t=" << setw(3) << t << "s  State: "
                        << setw(8) << tl.getCurrentState();
                    if (tl.canVehiclesGo()) {
                        cout << "  (vehicles moving)";
                    }
                    else if (tl.isRed()) {
                        cout << "  (vehicles stopped)";
                    }
                    else {
                        cout << "  (vehicles slowing)";
                    }
                    cout << endl;
                    tl.update(1);
                    SLEEP(150);
                }

                cout << endl;
                cout << "Cycles completed: " << tl.getCycleCount() << endl;
                pressEnter();

            }
            else if (choice == 8) {
                clearAndHeader("ALL VEHICLES");
                city->displayAllVehicles();
                pressEnter();
            }

        }
        catch (CityException& e) {
            cout << endl << "ERROR: " << e.what() << endl;
            pressEnter();
        }
    }
}

// ============================================================
// UTILITIES MENU
// ============================================================

void utilitiesMenu(CityManager* city) {
    int choice = -1;
    while (choice != 0) {
        clearAndHeader("UTILITY MANAGEMENT");

        cout << " 1.  Power Service Status" << endl;
        cout << " 2.  Water Service Status" << endl;
        cout << " 3.  Run Power Service Cycle" << endl;
        cout << " 4.  Run Water Service Cycle" << endl;
        cout << " 5.  Trigger Power Outage" << endl;
        cout << " 6.  Trigger Water Main Break" << endl;
        cout << " 7.  Declare Drought" << endl;
        cout << " 8.  Lift Drought" << endl;
        cout << " 9.  Increase Power Capacity" << endl;
        cout << " 0.  Back to Main Menu" << endl;
        printLine();

        choice = getIntInput("Enter choice: ", 0, 9);

        try {
            PowerService* power = PowerService::getInstance();
            WaterService* water = WaterService::getInstance();

            if (choice == 1) {
                clearAndHeader("POWER SERVICE STATUS");
                power->displayInfo();
                pressEnter();

            }
            else if (choice == 2) {
                clearAndHeader("WATER SERVICE STATUS");
                water->displayInfo();
                pressEnter();

            }
            else if (choice == 3) {
                clearAndHeader("POWER SERVICE CYCLE");
                cout << "Running power service cycle..." << endl << endl;
                power->processService();
                cout << endl;
                power->displayInfo();
                pressEnter();

            }
            else if (choice == 4) {
                clearAndHeader("WATER SERVICE CYCLE");
                cout << "Running water service cycle..." << endl << endl;
                water->processService();
                cout << endl;
                water->displayInfo();
                pressEnter();

            }
            else if (choice == 5) {
                clearAndHeader("POWER OUTAGE SIMULATION");
                cout << "WARNING: Triggering city-wide power outage!" << endl;
                cout << "All buildings will be notified." << endl;
                cout << endl;
                SLEEP(500);
                city->triggerPowerOutage();
                pressEnter();

            }
            else if (choice == 6) {
                clearAndHeader("WATER MAIN BREAK SIMULATION");
                cout << "WARNING: Triggering water main break!" << endl;
                cout << "All buildings will be notified." << endl;
                cout << endl;
                SLEEP(500);
                city->triggerWaterShortage();
                pressEnter();

            }
            else if (choice == 7) {
                clearAndHeader("DROUGHT DECLARATION");
                cout << "Declaring drought conditions..." << endl;
                cout << "Water supply will be reduced by 30%." << endl;
                cout << endl;
                city->declareDrought();
                water->displayInfo();
                pressEnter();

            }
            else if (choice == 8) {
                clearAndHeader("LIFT DROUGHT");
                cout << "Lifting drought conditions..." << endl;
                water->setDrought(false);
                water->displayInfo();
                pressEnter();

            }
            else if (choice == 9) {
                clearAndHeader("INCREASE POWER CAPACITY");
                double mw = getDoubleInput("Additional capacity (MW): ", 10.0);
                power->addCapacity(mw);
                cout << endl;
                power->displayInfo();
                pressEnter();
            }

        }
        catch (CityException& e) {
            cout << endl << "ERROR: " << e.what() << endl;
            pressEnter();
        }
    }
}

// ============================================================
// ECONOMY MENU
// ============================================================

void economyMenu(CityManager* city) {
    int choice = -1;
    while (choice != 0) {
        clearAndHeader("ECONOMY AND BUDGET");

        cout << " 1.  City Budget Report" << endl;
        cout << " 2.  View Tax Rates" << endl;
        cout << " 3.  Collect All Taxes" << endl;
        cout << " 4.  Allocate Department Budgets" << endl;
        cout << " 5.  Full Economy Report" << endl;
        cout << " 6.  Add Retail Business" << endl;
        cout << " 7.  Add Industrial Business" << endl;
        cout << " 0.  Back to Main Menu" << endl;
        printLine();

        choice = getIntInput("Enter choice: ", 0, 7);

        try {
            if (choice == 1) {
                clearAndHeader("CITY BUDGET REPORT");
                CityBudget::getInstance()->generateReport();
                pressEnter();

            }
            else if (choice == 2) {
                clearAndHeader("TAX RATES");
                city->displayEconomyReport();
                pressEnter();

            }
            else if (choice == 3) {
                clearAndHeader("COLLECTING ALL TAXES");
                cout << "Collecting taxes from all citizens and businesses..." << endl;
                cout << endl;
                city->collectAllTaxes();
                cout << endl;
                cout << "Tax collection complete!" << endl;
                cout << "New balance: $"
                    << CityBudget::getInstance()->getCurrentBalance() << endl;
                pressEnter();

            }
            else if (choice == 4) {
                clearAndHeader("ALLOCATE DEPARTMENT BUDGETS");
                cout << "Allocating current balance to departments..." << endl;
                cout << endl;
                city->allocateDepartmentBudgets();
                cout << endl;
                CityBudget::getInstance()->generateReport();
                pressEnter();

            }
            else if (choice == 5) {
                clearAndHeader("FULL ECONOMY REPORT");
                city->displayEconomyReport();
                pressEnter();

            }
            else if (choice == 6) {
                clearAndHeader("ADD RETAIL BUSINESS");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string name = getStringInput("Business Name: ");
                string type = getStringInput("Type (Grocery/Electronics/Clothing/General): ");
                double capital = getDoubleInput("Startup Capital ($): ", 1000.0);

                RetailBusiness* rb = city->addRetailBusiness(
                    name, type, nullptr, nullptr, capital);
                cout << endl << "Retail business added!" << endl;
                rb->displayInfo();
                pressEnter();

            }
            else if (choice == 7) {
                clearAndHeader("ADD INDUSTRIAL BUSINESS");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string name = getStringInput("Business Name: ");
                string type = getStringInput("Type (Manufacturing/Processing/Assembly): ");
                double capital = getDoubleInput("Startup Capital ($): ", 10000.0);

                IndustrialBusiness* ib = city->addIndustrialBusiness(
                    name, type, nullptr, nullptr, capital);
                cout << endl << "Industrial business added!" << endl;
                ib->displayInfo();
                pressEnter();
            }

        }
        catch (CityException& e) {
            cout << endl << "ERROR: " << e.what() << endl;
            pressEnter();
        }
    }
}

// ============================================================
// EMERGENCY MENU
// ============================================================

void emergencyMenu(CityManager* city) {
    int choice = -1;
    while (choice != 0) {
        clearAndHeader("EMERGENCY SERVICES");

        cout << " 1.  Report Fire Incident" << endl;
        cout << " 2.  Report Crime Incident" << endl;
        cout << " 3.  Report Medical Emergency" << endl;
        cout << " 4.  Emergency Services Status" << endl;
        cout << " 5.  Full Emergency Report" << endl;
        cout << " 6.  Chain of Responsibility Demo" << endl;
        cout << " 0.  Back to Main Menu" << endl;
        printLine();

        choice = getIntInput("Enter choice: ", 0, 6);

        try {
            if (choice == 1) {
                clearAndHeader("REPORT FIRE INCIDENT");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string fireType = getStringInput(
                    "Fire Type (Residential/Commercial/Industrial): ");
                int alarm = getIntInput("Alarm Level (1-5): ", 1, 5);

                cout << endl;
                cout << "FIRE REPORTED - Dispatching Fire Department..." << endl;
                cout << endl;
                SLEEP(500);
                city->reportFireIncident(nullptr, fireType, alarm);
                pressEnter();

            }
            else if (choice == 2) {
                clearAndHeader("REPORT CRIME INCIDENT");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string crimeType = getStringInput(
                    "Crime Type (Theft/Assault/Burglary/Vandalism): ");
                int severity = getIntInput("Severity (1-10): ", 1, 10);

                cout << endl;
                cout << "CRIME REPORTED - Dispatching Police Department..." << endl;
                cout << endl;
                SLEEP(500);
                city->reportCrimeIncident(nullptr, crimeType, severity);
                pressEnter();

            }
            else if (choice == 3) {
                clearAndHeader("REPORT MEDICAL EMERGENCY");
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                string medType = getStringInput(
                    "Emergency Type (HeartAttack/Injury/Illness/Overdose): ");
                int severity = getIntInput("Severity (1-10): ", 1, 10);

                cout << endl;
                cout << "EMERGENCY REPORTED - Dispatching Medical Service..." << endl;
                cout << endl;
                SLEEP(500);
                city->reportMedicalIncident(nullptr, medType, severity);
                pressEnter();

            }
            else if (choice == 4) {
                clearAndHeader("EMERGENCY SERVICES STATUS");
                city->displayEmergencyReport();
                pressEnter();

            }
            else if (choice == 5) {
                clearAndHeader("FULL EMERGENCY REPORT");
                city->displayEmergencyReport();
                pressEnter();

            }
            else if (choice == 6) {
                clearAndHeader("CHAIN OF RESPONSIBILITY DEMONSTRATION");

                cout << "This demonstrates the CHAIN OF RESPONSIBILITY pattern." << endl;
                cout << endl;
                cout << "Chain setup:" << endl;
                cout << "  FireDepartment --> PoliceDepartment --> MedicalService" << endl;
                cout << endl;
                cout << "Each service checks if it CAN HANDLE the incident." << endl;
                cout << "If NO, it passes to the next in chain." << endl;
                cout << endl;
                printLine();

                SLEEP(1000);

                cout << "TEST 1 - Fire Incident sent to chain:" << endl;
                cout << "  FireDept: canHandle(fire) = YES -> Responds" << endl;
                cout << endl;
                SLEEP(500);
                city->reportFireIncident(nullptr, "Commercial", 2);

                cout << endl;
                printLine();
                SLEEP(1000);

                cout << "TEST 2 - Crime Incident sent to chain:" << endl;
                cout << "  FireDept: canHandle(crime) = NO  -> Pass" << endl;
                cout << "  PoliceDept: canHandle(crime) = YES -> Responds" << endl;
                cout << endl;
                SLEEP(500);
                city->reportCrimeIncident(nullptr, "Theft", 3);

                cout << endl;
                printLine();
                SLEEP(1000);

                cout << "TEST 3 - Medical Incident sent to chain:" << endl;
                cout << "  FireDept: canHandle(medical) = NO  -> Pass" << endl;
                cout << "  PoliceDept: canHandle(medical) = NO  -> Pass" << endl;
                cout << "  MedicalService: canHandle(medical) = YES -> Responds" << endl;
                cout << endl;
                SLEEP(500);
                city->reportMedicalIncident(nullptr, "HeartAttack", 8);

                pressEnter();
            }

        }
        catch (CityException& e) {
            cout << endl << "ERROR: " << e.what() << endl;
            pressEnter();
        }
    }
}

// ============================================================
// SIMULATION MENU
// ============================================================

void simulationMenu(CityManager* city) {
    int choice = -1;
    while (choice != 0) {
        clearAndHeader("SIMULATION CONTROL");

        cout << " Current Year  : " << city->getCurrentYear() << endl;
        cout << " Buildings     : " << city->getBuildingCount() << endl;
        cout << " Citizens      : " << city->getCitizenCount() << endl;
        cout << " Businesses    : " << city->getBusinessCount() << endl;
        cout << endl;

        cout << " 1.  Simulate 1 Day" << endl;
        cout << " 2.  Simulate 1 Month" << endl;
        cout << " 3.  Simulate 1 Year" << endl;
        cout << " 4.  Simulate 5 Years" << endl;
        cout << " 5.  Run Full Demo Scenario" << endl;
        cout << " 0.  Back to Main Menu" << endl;
        printLine();

        choice = getIntInput("Enter choice: ", 0, 5);

        try {
            if (choice == 1) {
                clearAndHeader("SIMULATING 1 DAY");
                city->simulateDay();
                pressEnter();

            }
            else if (choice == 2) {
                clearAndHeader("SIMULATING 1 MONTH");
                printLoading("Running 30 days");
                city->simulateMonth();
                cout << endl;
                city->displayCityStats();
                pressEnter();

            }
            else if (choice == 3) {
                clearAndHeader("SIMULATING 1 YEAR");
                printLoading("Running annual simulation");
                city->simulateYear();
                cout << endl;
                city->displayCityStats();
                pressEnter();

            }
            else if (choice == 4) {
                clearAndHeader("SIMULATING 5 YEARS");
                for (int y = 1; y <= 5; y++) {
                    cout << "Year " << y << " of 5..." << endl;
                    printLoading("Simulating");
                    city->simulateYear();
                    cout << endl;
                }
                city->displayCityStats();
                pressEnter();

            }
            else if (choice == 5) {
                clearAndHeader("FULL DEMO SCENARIO");

                cout << "Running a complete city scenario..." << endl;
                cout << endl;

                cout << "STEP 1: Year passes..." << endl;
                SLEEP(300);
                city->simulateYear();
                cout << endl;

                cout << "STEP 2: Fire breaks out at a commercial building!" << endl;
                SLEEP(500);
                city->reportFireIncident(nullptr, "Commercial", 3);
                cout << endl;

                cout << "STEP 3: Crime wave in the district!" << endl;
                SLEEP(500);
                city->reportCrimeIncident(nullptr, "Burglary", 5);
                cout << endl;

                cout << "STEP 4: Medical emergency reported!" << endl;
                SLEEP(500);
                city->reportMedicalIncident(nullptr, "HeartAttack", 8);
                cout << endl;

                cout << "STEP 5: Power outage hits the city!" << endl;
                SLEEP(500);
                city->triggerPowerOutage();
                cout << endl;

                cout << "STEP 6: Annual tax collection..." << endl;
                SLEEP(500);
                city->collectAllTaxes();
                cout << endl;

                cout << "STEP 7: Second year of recovery..." << endl;
                SLEEP(300);
                city->simulateYear();
                cout << endl;

                cout << "Demo scenario complete!" << endl;
                cout << endl;
                city->displayCityStats();
                pressEnter();
            }

        }
        catch (CityException& e) {
            cout << endl << "ERROR: " << e.what() << endl;
            pressEnter();
        }
    }
}

// ============================================================
// OOP CONCEPTS SHOWCASE
// ============================================================

void oopShowcase(CityManager* city) {
    int choice = -1;
    while (choice != 0) {
        clearAndHeader("OOP CONCEPTS SHOWCASE");

        cout << " 1.  Abstraction and Polymorphism Demo" << endl;
        cout << " 2.  Singleton Pattern Demo" << endl;
        cout << " 3.  Chain of Responsibility Demo" << endl;
        cout << " 4.  Observer Pattern Demo" << endl;
        cout << " 5.  Template Method Pattern Demo" << endl;
        cout << " 6.  State Pattern Demo (Traffic Light)" << endl;
        cout << " 7.  Exception Handling Demo" << endl;
        cout << " 8.  Friend Classes Explanation" << endl;
        cout << " 9.  Show All OOP Concepts Summary" << endl;
        cout << " 0.  Back to Main Menu" << endl;
        printLine();

        choice = getIntInput("Enter choice: ", 0, 9);

        if (choice == 1) {
            clearAndHeader("ABSTRACTION AND POLYMORPHISM");

            cout << "Creating different building types..." << endl;
            cout << "Storing them all in Building* pointers." << endl;
            cout << endl;

            House* h = new House("Poly Lane 1", 2020, 400, 2, 3, 2);
            Shop* s = new Shop("Poly Lane 2", 2021, 300, 1,
                "Test Shop", "Grocery");
            Restaurant* r = new Restaurant("Poly Lane 3", 2022, 250, 1,
                "Test Diner", "American", 5, 4);

            Building* buildings[3] = { h, s, r };
            string    labels[3] = { "House", "Shop", "Restaurant" };

            cout << "Calling same functions on different types:" << endl;
            cout << endl;
            printLine();
            cout << left
                << setw(14) << "Type"
                << setw(20) << "getBuildingType()"
                << setw(18) << "getMaintCost()"
                << "getDailyVisitors()" << endl;
            printLine();

            for (int i = 0; i < 3; i++) {
                cout << left
                    << setw(14) << labels[i]
                    << setw(20) << buildings[i]->getBuildingType()
                    << setw(18)
                    << (int)buildings[i]->calculateMaintenanceCost()
                    << buildings[i]->getDailyVisitors() << endl;
            }

            cout << endl;
            cout << "RESULT: Same function calls behave DIFFERENTLY" << endl;
            cout << "based on the ACTUAL object type at runtime." << endl;
            cout << "This is RUNTIME POLYMORPHISM (vtable)." << endl;

            delete h;
            delete s;
            delete r;
            pressEnter();

        }
        else if (choice == 2) {
            clearAndHeader("SINGLETON PATTERN");

            cout << "Only ONE instance of PowerService can exist." << endl;
            cout << endl;

            cout << "Call 1: PowerService::getInstance()" << endl;
            PowerService* p1 = PowerService::getInstance();
            cout << "  Address returned: " << p1 << endl;

            cout << "Call 2: PowerService::getInstance()" << endl;
            PowerService* p2 = PowerService::getInstance();
            cout << "  Address returned: " << p2 << endl;

            cout << endl;
            if (p1 == p2) {
                cout << "SAME address! Singleton is working correctly." << endl;
                cout << "No matter how many times you call getInstance()," << endl;
                cout << "you always get the SAME object." << endl;
            }
            else {
                cout << "Different addresses - this should not happen!" << endl;
            }

            cout << endl;
            cout << "Same pattern used for:" << endl;
            cout << "  - WaterService" << endl;
            cout << "  - CityBudget" << endl;
            cout << "  - CityManager" << endl;
            pressEnter();

        }
        else if (choice == 3) {
            clearAndHeader("CHAIN OF RESPONSIBILITY");

            cout << "Each emergency service handles ONLY its incident type." << endl;
            cout << "If it cannot handle, it PASSES to the next in chain." << endl;
            cout << endl;
            cout << "Chain: FireDept -> PoliceDept -> MedicalService" << endl;
            cout << endl;

            cout << "Sending FIRE to chain..." << endl;
            SLEEP(300);
            city->reportFireIncident(nullptr, "Residential", 1);
            cout << endl;

            cout << "Sending CRIME to chain..." << endl;
            SLEEP(300);
            city->reportCrimeIncident(nullptr, "Vandalism", 2);
            cout << endl;

            cout << "Sending MEDICAL to chain..." << endl;
            SLEEP(300);
            city->reportMedicalIncident(nullptr, "Injury", 4);
            pressEnter();

        }
        else if (choice == 4) {
            clearAndHeader("OBSERVER PATTERN");

            cout << "Buildings SUBSCRIBE to utility services." << endl;
            cout << "When utility has news, it NOTIFIES all subscribers." << endl;
            cout << endl;
            cout << "Currently " << city->getBuildingCount()
                << " buildings connected to PowerService." << endl;
            cout << endl;
            cout << "Sending notification to all buildings..." << endl;
            cout << endl;

            PowerService::getInstance()->notifyBuildings(
                "Scheduled maintenance tonight 2AM-4AM");
            cout << endl;
            PowerService::getInstance()->notifyBuildings(
                "Power rate increase: 5% from next month");
            cout << endl;

            cout << "All connected buildings received the notifications." << endl;
            cout << "Buildings can react (turn off equipment, save data etc)." << endl;
            pressEnter();

        }
        else if (choice == 5) {
            clearAndHeader("TEMPLATE METHOD PATTERN");

            cout << "UtilityService::processService() defines the SKELETON:" << endl;
            cout << endl;
            cout << "Step 1: Check if operational" << endl;
            cout << "Step 2: generateResource()   <- VIRTUAL (each implements)" << endl;
            cout << "Step 3: distributeResource() <- VIRTUAL (each implements)" << endl;
            cout << "Step 4: collectRevenue()     <- common for all" << endl;
            cout << endl;
            cout << "Calling processService() on PowerService:" << endl;
            cout << endl;
            PowerService::getInstance()->processService();
            cout << endl;
            cout << "Calling processService() on WaterService:" << endl;
            cout << endl;
            WaterService::getInstance()->processService();
            cout << endl;
            cout << "Same SKELETON, different IMPLEMENTATIONS." << endl;
            pressEnter();

        }
        else if (choice == 6) {
            clearAndHeader("STATE PATTERN - TRAFFIC LIGHT");

            cout << "TrafficLight has 3 STATES: Red, Yellow, Green" << endl;
            cout << "Each state has different BEHAVIOR." << endl;
            cout << "update() triggers STATE TRANSITIONS." << endl;
            cout << endl;

            TrafficLight tl(8, 3, 6);

            cout << "Initial state: " << tl.getCurrentState() << endl;
            cout << endl;
            cout << "Running 20 time steps..." << endl;
            cout << endl;

            for (int t = 0; t <= 20; t++) {
                cout << "t=" << setw(2) << t << "s  ["
                    << tl.getCurrentState() << "]";
                if (tl.isGreen())  cout << "  -> GO";
                if (tl.isRed())    cout << "  -> STOP";
                if (tl.isYellow()) cout << "  -> SLOW";
                cout << endl;
                tl.update(1);
                SLEEP(100);
            }

            cout << endl;
            cout << "Total cycles: " << tl.getCycleCount() << endl;
            pressEnter();

        }
        else if (choice == 7) {
            clearAndHeader("EXCEPTION HANDLING DEMO");

            cout << "Custom exception hierarchy:" << endl;
            cout << endl;
            cout << "exception (std)" << endl;
            cout << "  CityException" << endl;
            cout << "    BuildingException" << endl;
            cout << "    CitizenException" << endl;
            cout << "    VehicleException" << endl;
            cout << "    BudgetException" << endl;
            cout << "    UtilityException" << endl;
            cout << endl;
            printLine();

            cout << "Test 1: Throwing BuildingException..." << endl;
            try {
                throw BuildingException("Invalid year: 1650");
            }
            catch (BuildingException& e) {
                cout << "  Caught BuildingException: " << e.what() << endl;
                cout << "  Code: " << e.getErrorCode() << endl;
            }
            cout << endl;

            cout << "Test 2: Catching by BASE class (polymorphism)..." << endl;
            try {
                throw VehicleException("Vehicle out of fuel");
            }
            catch (CityException& e) {
                cout << "  Caught via CityException: " << e.what() << endl;
                cout << "  Code: " << e.getErrorCode() << endl;
                cout << "  (VehicleException caught by CityException base)" << endl;
            }
            cout << endl;

            cout << "Test 3: Invalid building year..." << endl;
            try {
                House* bad = new House("X", 1600, 100, 1, 2, 1);
                delete bad;
            }
            catch (BuildingException& e) {
                cout << "  Caught: " << e.what() << endl;
            }
            cout << endl;

            cout << "Test 4: Invalid student age..." << endl;
            try {
                Student* bad = new Student("X", "Y", 200, "Male",
                    nullptr, "High");
                delete bad;
            }
            catch (CitizenException& e) {
                cout << "  Caught: " << e.what() << endl;
            }
            pressEnter();

        }
        else if (choice == 8) {
            clearAndHeader("FRIEND CLASSES EXPLANATION");

            cout << "Friend classes can access PRIVATE members." << endl;
            cout << endl;
            printLine();
            cout << "Class           Friend Of" << endl;
            printLine();
            cout << "Building        CityManager" << endl;
            cout << "  (CityManager reads private buildingCounter)" << endl;
            cout << endl;
            cout << "Citizen         Household" << endl;
            cout << "  (Household updates private bankBalance)" << endl;
            cout << endl;
            cout << "Hospital        MedicalService" << endl;
            cout << "  (MedicalService calls admitPatient on Hospital)" << endl;
            cout << endl;
            cout << "FireStation     FireDepartment" << endl;
            cout << "  (FireDepartment dispatches trucks)" << endl;
            cout << endl;
            cout << "PoliceStation   PoliceDepartment" << endl;
            cout << "  (PoliceDept dispatches patrol cars)" << endl;
            cout << endl;
            cout << "PowerService    CityManager" << endl;
            cout << "  (CityManager connects buildings)" << endl;
            cout << endl;
            cout << "Business        CityBudget" << endl;
            cout << "  (CityBudget reads profit for taxation)" << endl;
            printLine();
            cout << endl;
            cout << "Why friend instead of public getter?" << endl;
            cout << "  Some data should be HIDDEN from general use" << endl;
            cout << "  but accessible to specific trusted classes." << endl;
            pressEnter();

        }
        else if (choice == 9) {
            clearAndHeader("ALL OOP CONCEPTS SUMMARY");

            printLine();
            cout << "CONCEPT              WHERE USED" << endl;
            printLine();
            cout << "Abstraction          Building, Person, Vehicle base classes" << endl;
            cout << "Inheritance          Building->Residential->House (3 levels)" << endl;
            cout << "Polymorphism         Virtual functions, base class pointers" << endl;
            cout << "Encapsulation        Private/Protected/Public + accessors" << endl;
            cout << "Composition          Mall owns Shops (Mall destructs Shops)" << endl;
            cout << "Aggregation          Buildings have employees (no ownership)" << endl;
            cout << "Association          Citizens live in Buildings (weak link)" << endl;
            cout << "Self-Reference       Person has Person* (family tree)" << endl;
            cout << "Static Members       ID counters in Building, Person, Vehicle" << endl;
            cout << "Friend Classes       CityManager, Household, Departments" << endl;
            cout << "Constructor Overload Retiree (fresh or from Citizen)" << endl;
            cout << "Virtual Destructor   All base classes have virtual ~" << endl;
            cout << "Override keyword     All derived classes use override" << endl;
            cout << "Exception Handling   CityException hierarchy" << endl;
            cout << endl;
            cout << "DESIGN PATTERNS:" << endl;
            printLine();
            cout << "Singleton            PowerService, WaterService, CityBudget" << endl;
            cout << "Observer             Utilities notify connected Buildings" << endl;
            cout << "Chain of Resp.       Emergency: Fire->Police->Medical" << endl;
            cout << "Template Method      UtilityService::processService()" << endl;
            cout << "State Pattern        TrafficLight (Red/Yellow/Green)" << endl;
            cout << "Facade               CityManager simplifies all subsystems" << endl;
            printLine();
            pressEnter();
        }
    }
}

// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    CLEAR();

    cout << endl;
    cout << "============================================" << endl;
    cout << "    SMART CITY AUTOMATION SYSTEM" << endl;
    cout << "    Final Project - OOP (C++)" << endl;
    cout << "============================================" << endl;
    cout << endl;
    cout << "Initializing city systems" << endl;
    cout << endl;

    printLoading("Loading Building Module");
    printLoading("Loading Citizen Module");
    printLoading("Loading Transport Module");
    printLoading("Loading Utilities Module");
    printLoading("Loading Economy Module");
    printLoading("Loading Emergency Module");

    cout << endl;
    cout << "All systems online!" << endl;
    cout << endl;

    // Get city name
    string cityName;
    int startYear;

    cout << "Enter city name: ";
    getline(cin, cityName);

    if (cityName.empty()) {
        cityName = "SmartCity";
    }

    cout << "Enter start year (e.g. 2020): ";
    cin >> startYear;
    cin.ignore();

    if (startYear < 2000 || startYear > 2025) {
        startYear = 2020;
        cout << "Invalid year, using 2020." << endl;
    }

    // Create city (Singleton)
    CityManager* city = CityManager::getInstance(cityName, startYear);

    SLEEP(500);

    // Offer demo setup
    cout << endl;
    cout << "Load demo city with pre-built buildings," << endl;
    cout << "citizens, vehicles, and businesses? (y/n): ";
    char demoChoice;
    cin >> demoChoice;
    cin.ignore();

    if (demoChoice == 'y' || demoChoice == 'Y') {
        setupDemoCity(city);
    }

    // MAIN MENU LOOP
    int choice = -1;
    while (choice != 0) {
        CLEAR();
        cout << endl;
        cout << "============================================" << endl;
        cout << "    SMART CITY: " << cityName << endl;
        cout << "    Year: " << city->getCurrentYear()
            << "   Buildings: " << city->getBuildingCount()
            << "   Population: " << city->getCitizenCount() << endl;
        cout << "============================================" << endl;
        cout << endl;
        cout << " 1.  Building Management" << endl;
        cout << " 2.  Citizen Management" << endl;
        cout << " 3.  Vehicle and Transport" << endl;
        cout << " 4.  Utility Services" << endl;
        cout << " 5.  Economy and Budget" << endl;
        cout << " 6.  Emergency Services" << endl;
        cout << " 7.  Simulation Control" << endl;
        cout << " 8.  City Statistics" << endl;
        cout << " 9.  OOP Concepts Showcase" << endl;
        cout << " 0.  Exit" << endl;
        cout << endl;
        printLine();

        choice = getIntInput("Enter choice: ", 0, 9);

        switch (choice) {
        case 1: buildingMenu(city);    break;
        case 2: citizenMenu(city);     break;
        case 3: vehicleMenu(city);     break;
        case 4: utilitiesMenu(city);   break;
        case 5: economyMenu(city);     break;
        case 6: emergencyMenu(city);   break;
        case 7: simulationMenu(city);  break;
        case 8:
            clearAndHeader("CITY STATISTICS");
            city->displayCityStats();
            pressEnter();
            break;
        case 9: oopShowcase(city);     break;
        case 0:
            CLEAR();
            cout << endl;
            cout << "============================================" << endl;
            cout << "    SHUTTING DOWN " << cityName << endl;
            cout << "============================================" << endl;
            cout << endl;
            printLoading("Saving data");
            printLoading("Shutting down services");
            cout << endl;
            city->displayCityStats();
            cout << endl;
            cout << "Thank you. Goodbye!" << endl;
            cout << endl;
            break;
        default:
            cout << endl;
            cout << "Invalid choice. Try again." << endl;
            SLEEP(500);
        }
    }

    // Destroy singleton
    CityManager::destroyInstance();
    return 0;
}