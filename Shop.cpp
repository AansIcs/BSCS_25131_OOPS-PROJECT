#include "Shop.h"
#include "CityExceptions.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
Shop::Shop(string addr, int year, double area,
    int floors, string shopName, string category): CommercialBuilding(addr, year, area, floors, shopName, "Retail")
{
    shopCategory = category;
    dailyCustomers = 0;
    dailySalesRevenue = 0.0;
    dailyInventoryCost = 0.0;
    hasOnlineStore = false;
    onlineRevenuePercent = 0.0;
    totalRevenueSinceOpen = 0.0;
    totalItemsSold = 0;

    cout << "Shop '" << businessName << "' opened ("
        << shopCategory << ")" << endl;
}

double Shop::calculateMaintenanceCost() const{
    double cost = 0.0;

    cost += landArea * 4.0;                     
    cost += (int)inventory.size() * 10.0;      
    cost += 500.0;                          
    cost += 200.0;                            

    if (hasOnlineStore) {
        cost += 300.0;                         
    }

    int age = getAge();
    if (age > 20) cost *= 1.5;
    else if (age > 10) cost *= 1.2;

    return cost;
}

int Shop::getDailyVisitors() {
    double visitors = landArea / 10.0;  

    if (shopCategory == "Grocery")     visitors *= 3.0;
    else if (shopCategory == "Clothing") visitors *= 1.5;
    else if (shopCategory == "Electronics") visitors *= 1.2;
    if (hasOnlineStore) visitors *= 1.1;

    return max(1, static_cast<int>(visitors));
}
string Shop::getBuildingType() const {
    return "Shop";
}
void Shop::displayDetails() const {
    cout << "\n========== SHOP ==========" << endl;
    cout << "Name:       " << businessName << endl;
    cout << "Category:   " << shopCategory << endl;
    cout << "ID:         " << buildingID << endl;
    cout << "Address:    " << address << endl;
    cout << "Built:      " << buildYear << " (Age: " << getAge() << " yrs)" << endl;
    cout << "Area:       " << landArea << " sqm" << endl;
    cout << "Status:     " << (isOpen ? "OPEN" : "CLOSED") << endl;
    cout << "Employees:  " << employees.size()
        << "/" << employeeCapacity << endl;
    cout << "Products:   " << inventory.size() << " items" << endl;
    if (hasOnlineStore) {
        cout << "Online:     Yes (" << onlineRevenuePercent << "% revenue)" << endl;
    }
    cout << "\n--- Financials ---" << endl;
    cout << "Monthly Revenue: $"
        << fixed << setprecision(2) << monthlyRevenue << endl;
    cout << "Monthly Expenses:$"
        << fixed << setprecision(2) << monthlyExpenses << endl;
    cout << "Monthly Profit:  $"
        << fixed << setprecision(2) << monthlyProfit << endl;
    cout << "==========================\n" << endl;
}
double Shop::calculateMonthlyRevenue() {
    double avgTransactionValue = landArea * 0.5;
    double dailyRevenue = getDailyVisitors() * avgTransactionValue * 0.3;
    // 0.3 = only 30% of visitors actually buy

    double monthly = dailyRevenue * 30;
    if (hasOnlineStore) {
        monthly += monthly * (onlineRevenuePercent / 100.0);
    }

    totalRevenueSinceOpen += monthly;
    return monthly;
}
void Shop::addProduct(string id, string name, string cat,
    double cost, double price, int qty) {
    if (id.empty()) {
        throw BuildingException("Product ID cannot be empty");
    }
    if (price < cost) {
        throw BuildingException("Selling price cannot be less than cost price");
    }
    if (qty < 0) {
        throw BuildingException("Quantity cannot be negative");
    }
    for (const Product& p : inventory) {
        if (p.productID == id) {
            throw BuildingException("Product ID " + id + " already exists");
        }
    }

    inventory.push_back(Product(id, name, cat, cost, price, qty));
    cout << "Product '" << name << "' added to " << businessName << endl;
}

void Shop::removeProduct(string productID) {
    auto it = find_if(inventory.begin(), inventory.end(),
        [&](const Product& p) {
            return p.productID == productID;
        });

    if (it == inventory.end()) {
        throw BuildingException("Product ID " + productID + " not found");
    }

    cout << "Product '" << it->productName << "' removed from inventory" << endl;
    inventory.erase(it);
}

bool Shop::sellProduct(string productID, int quantity) {
    auto it = find_if(inventory.begin(), inventory.end(),[&](const Product& p) {
           return p.productID == productID; });

    if (it == inventory.end()) {
        throw BuildingException("Product not found: " + productID);
    }
    if (quantity <= 0) {
        throw BuildingException("Quantity must be positive");
    }

    // Check stock
    if (it->quantityInStock < quantity) {
        cout << "Insufficient stock for " << it->productName
            << " (have " << it->quantityInStock
            << ", need " << quantity << ")" << endl;
        return false;
    }

    // Process sale
    it->quantityInStock -= quantity;
    double saleValue = it->sellingPrice * quantity;
    double costValue = it->costPrice * quantity;

    dailySalesRevenue += saleValue;
    dailyInventoryCost += costValue;
    totalItemsSold += quantity;

    cout << "Sold " << quantity << "x " << it->productName
        << " for $" << saleValue << endl;

    // Auto-restock check
    if (needsRestock(productID)) {
        cout << " Low stock warning for " << it->productName << endl;
    }

    return true;
}
void Shop::restockProduct(string productID, int quantity) {
    auto it = find_if(inventory.begin(), inventory.end(),
        [&](const Product& p) {
            return p.productID == productID;
        });

    if (it == inventory.end()) {
        throw BuildingException("Product not found: " + productID);
    }
    if (quantity <= 0) {
        throw BuildingException("Restock quantity must be positive");
    }

    it->quantityInStock += quantity;
    cout << "Restocked " << it->productName
        << " +" << quantity
        << " (Total: " << it->quantityInStock << ")" << endl;
}
bool Shop::needsRestock(string productID) const {
    for (const Product& p : inventory) {
        if (p.productID == productID) {
            return p.quantityInStock <= p.reorderLevel;
        }
    }
    return false;
}
Shop::Product Shop::findProduct(string productID) const {
    for (const Product& p : inventory) {
        if (p.productID == productID) {
            return p; 
        }
    }
    throw BuildingException("Product not found: " + productID);
}

int Shop::getTotalInventoryCount() const {
    int total = 0;
    for (const Product& p : inventory) {
        total += p.quantityInStock;
    }
    return total;
}

void Shop::enableOnlineStore(double revenuePercent) {
    if (revenuePercent < 0 || revenuePercent > 100) {
        throw BuildingException("Revenue percent must be 0-100");
    }
    hasOnlineStore = true;
    onlineRevenuePercent = revenuePercent;
    cout << businessName << " online store enabled ("
        << revenuePercent << "% revenue)" << endl;
}
double Shop::getProfitMargin() const {
    if (inventory.empty()) return 0.0;

    double totalMargin = 0.0;
    for (const Product& p : inventory) {
        totalMargin += p.getProfitMargin();
    }
    return totalMargin / inventory.size();
}
Shop::Product Shop::getBestSellerByStock() const {
    if (inventory.empty()) {
        throw BuildingException("Inventory is empty");
    }

    auto it = max_element(inventory.begin(), inventory.end(),
        [](const Product& a, const Product& b) {
            return a.quantityInStock < b.quantityInStock;
        });
    return *it;
}
void Shop::displayInventory() const {
    cout << "\n--- " << businessName << " Inventory ---" << endl;
    cout << left << setw(8) << "ID"<< setw(20) << "Name"<< setw(12) << "Category"<< setw(10) << "Cost"<< setw(10) << "Price"<< setw(8) << "Stock"<< "Margin" << endl;
    cout << string(72, '-') << endl;

    for (const Product& p : inventory) {
        cout << left << setw(8) << p.productID << setw(20) << p.productName << setw(12) << p.category << setw(10) << ("$" + to_string((int)p.costPrice)) << setw(10) << ("$" + to_string((int)p.sellingPrice))
            << setw(8) << p.quantityInStock<< fixed << setprecision(1) << p.getProfitMargin() << "%" << endl;
    }
    cout << "Total items in stock: " << getTotalInventoryCount() << endl;
}
Shop::~Shop() {
    inventory.clear();
    cout << "Shop '" << businessName << "' closed permanently" << endl;
}