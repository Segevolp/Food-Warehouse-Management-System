#include "../include/Action.h"
#include <iostream>


AddOrder::AddOrder(int id): customerId(id) {}
AddOrder::AddOrder(const Order &copyThis):customerId(copyThis.getCustomerId()){}
void AddOrder::act(WareHouse &wareHouse)
{
    try
    {
        Customer& c = wareHouse.getCustomer(customerId);
        if(c.canMakeOrder())
        {
            int orderCounter = wareHouse.getAvailableOrderID();
            int temp = c.addOrder(orderCounter);
            wareHouse.addOrder(new Order(orderCounter,customerId,c.getCustomerDistance()));
            complete();
        }
        else
        {
            error("Cannot place this order. This customer reached max orders!");
        }
    }
    catch(const std::exception& e)
    {
        error("Cannot place this order. This customer doesn't exist!");
    }
    wareHouse.addAction(this);
}
AddOrder::~AddOrder(){}

string AddOrder::toString() const
{
    string ans("order " + to_string(customerId) + " " + statusToString() + "\n");
    return ans;
}

AddOrder *AddOrder::clone() const
{
    return new AddOrder(*this);
}

AddCustomer::AddCustomer(string customerName, string customerType, int distance, int maxOrders): 
customerName(customerName), customerType(convertToCustomerType(customerType)),
distance(distance), maxOrders(maxOrders){}
AddCustomer::~AddCustomer(){}
AddCustomer::AddCustomer(const AddCustomer &copyThis): 
customerName(copyThis.customerName), customerType(copyThis.customerType),
 distance(copyThis.distance), maxOrders(copyThis.maxOrders){}

void AddCustomer::act(WareHouse &wareHouse)
{
    int customerCounter = wareHouse.getAvailableCustomerID();
    if(customerType == CustomerType::Soldier){
        
        wareHouse.addCustomer(new SoldierCustomer(customerCounter, customerName,distance, maxOrders));
    }
    else{
       wareHouse.addCustomer(new CivilianCustomer(customerCounter, customerName,distance, maxOrders));
    }
    complete();
    wareHouse.addAction(this);
}

AddCustomer *AddCustomer::clone() const
{
    return new AddCustomer(*this);
}

string AddCustomer::toString() const
{
    string ans;
    ans.append("AddCustomer " + customerName + " " +  to_string(distance) + " " + std::to_string(maxOrders) + " ");
    ans.append(statusToString());
    ans.append("\n");
    return ans;

}
const CustomerType AddCustomer::convertToCustomerType(const string &customerType)
{
    if (customerType == "soldier") {
        return CustomerType::Soldier;
    } 
    else {
        return CustomerType::Civilian;
    }
}
