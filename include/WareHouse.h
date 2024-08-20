#pragma once
#include <string>
#include <vector>
using namespace std;

#include "Order.h"
#include "Customer.h"
//#include "Action.h"

class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        WareHouse(const WareHouse& copyThis);
        WareHouse(WareHouse &&other);
        WareHouse& operator=(const WareHouse& other);
        WareHouse& operator=(WareHouse&& other);
        void start();
        void addOrder(Order* order);
        void addAction(BaseAction* action);
        void addCustomer(Customer* customerToAdd);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        void close();
        void open();
        int getAvailableOrderID();
        int getAvailableCustomerID();
        int getAvailableVolunteerID();
        vector<Order*> & getPendingOrders();
        vector<Order*> & getInProccessOrders();
        vector<Order*> & getCompletedOrders();
        vector<Volunteer*> & getVolunteers();
        ~WareHouse();

    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int orderCounter; // For assigning unique order IDs
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        void clean_line(std::string& line);
        std::vector<std::string> to_words(std::string& line);
};