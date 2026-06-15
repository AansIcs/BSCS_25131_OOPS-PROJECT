#pragma once
#include "CommercialBuilding.h"
using namespace std;
class Shop : public CommercialBuilding {

public:
    struct Product {
        string productID;
        string productName;
        string category;         
        double costPrice;       
        double sellingPrice;    
        int    quantityInStock;
        int    reorderLevel;   
        Product()
            : productID(""), productName(""), category(""),
            costPrice(0.0), sellingPrice(0.0),
            quantityInStock(0), reorderLevel(10) {
        }
        Product(string id, string name, string cat,
            double cost, double price, int qty)
            : productID(id), productName(name), category(cat),
            costPrice(cost), sellingPrice(price),
            quantityInStock(qty), reorderLevel(10) {
        }
        double getProfitMargin() const {
            if (sellingPrice == 0) return 0.0;
            return ((sellingPrice - costPrice) / sellingPrice) * 100.0;
        }
    };

private:
    string shopCategory;      
    vector<Product> inventory; 
    int    dailyCustomers;
    double dailySalesRevenue;
    double dailyInventoryCost;  
    bool   hasOnlineStore;
    double onlineRevenuePercent;
    double totalRevenueSinceOpen;
    int    totalItemsSold;

public:
    Shop(string addr, int year, double area,
        int floors, string shopName, string category);
    double calculateMaintenanceCost()const override;
    int    getDailyVisitors()         override;
    string getBuildingType()    const override;
    void   displayDetails()     const override;
    double calculateMonthlyRevenue()  override;
    void    addProduct(string id, string name, string cat,
        double cost, double price, int qty);
    void    removeProduct(string productID);
    bool    sellProduct(string productID, int quantity);
    void    restockProduct(string productID, int quantity);
    bool    needsRestock(string productID)    const;
    Product findProduct(string productID)     const;
    int     getTotalInventoryCount()          const;
    void    enableOnlineStore(double revenuePercent);
    double  getProfitMargin()          const;
    Product getBestSellerByStock()     const;
    void    displayInventory()         const;
    string  getShopCategory()          const { return shopCategory; }
    int     getProductCount()          const { return (int)inventory.size(); }
    ~Shop();
};
