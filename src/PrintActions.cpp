#include "../include/Action.h"
#include <iostream>
#include "../include/Order.h"
#include "../include/Volunteer.h"

const char* ActionStatusString::toString(ActionStatus actionStatus)
{
    switch (actionStatus)
    {
        case ActionStatus::COMPLETED: return "COMPLETED";
        case ActionStatus::ERROR: return "ERROR";
    }
}


PrintActionsLog::PrintActionsLog(){}

void PrintActionsLog::act(WareHouse &wareHouse)
{
    const std::vector<BaseAction*> &actions =  wareHouse.getActions();
    for(std::vector<BaseAction *>::const_iterator it(actions.begin());it!=actions.end();++it)
    {
        cout << (*it)->toString();
    }
    complete();
    wareHouse.addAction(this);
}
PrintActionsLog::~PrintActionsLog(){}
PrintActionsLog *PrintActionsLog::clone() const
{
    return new PrintActionsLog();
}

string PrintActionsLog::toString() const
{
    string ans;
    ans.append("log ");
    ans.append(statusToString());
    ans.append("\n");
    return ans;
}

PrintVolunteerStatus::PrintVolunteerStatus(int id): volunteerId(id){}

PrintVolunteerStatus::PrintVolunteerStatus(const PrintVolunteerStatus &copyThis):volunteerId(copyThis.volunteerId){}

void PrintVolunteerStatus::act(WareHouse &wareHouse)  
{
    try{
        Volunteer& v = wareHouse.getVolunteer(volunteerId);
        std:: cout << v.toString();
        complete();
    }
    catch(const std:: exception& e){
        error("Volunteer doesn't exist");
    }
    wareHouse.addAction(this);
}
PrintVolunteerStatus::~PrintVolunteerStatus(){}
PrintVolunteerStatus *PrintVolunteerStatus::clone() const
{
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const
{
    string ans;
    ans.append("volunteerStatus ");
    ans.append(to_string(volunteerId) + " ");
    ans.append(statusToString());
    ans.append("\n");
    return ans;
}


PrintOrderStatus::PrintOrderStatus(int id): orderId(id) {}
PrintOrderStatus::PrintOrderStatus(const PrintOrderStatus &copyThis):orderId(copyThis.orderId) {}
void PrintOrderStatus::act(WareHouse &wareHouse)
{
    try
    {
        Order & order = wareHouse.getOrder(orderId);
        std::cout << order.toString();
        complete();
    }
    catch(const std::exception& e)
    {
        error("Order doesn't exist");
    }
    wareHouse.addAction(this);
}

PrintOrderStatus *PrintOrderStatus::clone() const
{
    return new PrintOrderStatus(*this);
}
PrintOrderStatus::~PrintOrderStatus(){}
string PrintOrderStatus::toString() const
{
    string ans;
    ans.append("orderStatus ");
    ans.append(to_string(orderId) + " ");
    ans.append(statusToString());
    ans.append("\n");
    return ans;

}

PrintCustomerStatus::~PrintCustomerStatus(){}
PrintCustomerStatus::PrintCustomerStatus(int customerId) : customerId(customerId){}

PrintCustomerStatus::PrintCustomerStatus(const PrintCustomerStatus &copyThis): customerId(copyThis.customerId){}

void PrintCustomerStatus::act(WareHouse &wareHouse)
{
    try{
        Customer& c = wareHouse.getCustomer(customerId);
        vector<int> ids = c.getOrdersIds();
        std::cout << "CustomerID: " << customerId << "\n";
        for(int id: ids){
            Order &order = wareHouse.getOrder(id);
            cout << "OrderID: " << (order.getId()) << "\n";
            cout << "OrderStatus: " << order.statusToString() << "\n";
        }
        std::cout << "numOrdersLeft: " << (c.getMaxOrders() - c.getNumOrders()) << "\n";
        complete();
    }
    catch(const std:: exception& e){
        error("Customer doesn't exist");
    }
    wareHouse.addAction(this);
}

PrintCustomerStatus *PrintCustomerStatus::clone() const
{
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const
{
    string ans;
    ans.append("customerStatus ");
    ans.append(to_string(customerId) + " ");
    ans.append(statusToString());
    ans.append("\n");
    return ans;
}