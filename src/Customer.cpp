#include "../include/Customer.h"
#include <iostream>

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders) : id(id),name(name),locationDistance(locationDistance),maxOrders(maxOrders){}

Customer::Customer(const Customer& copyThis): id(copyThis.id), name(copyThis.name), locationDistance(copyThis.locationDistance),maxOrders(copyThis.maxOrders), ordersId(copyThis.ordersId){}

const string &Customer::getName() const
{
    return name;
}
Customer::~Customer(){}
int Customer::getId() const
{
    return id;
}

int Customer::getCustomerDistance() const
{
    return locationDistance;
}

int Customer::getMaxOrders() const
{
    return maxOrders;
}

int Customer::getNumOrders() const
{
    return ordersId.size();
}

bool Customer::canMakeOrder() const
{
    if(getNumOrders()<maxOrders)
    {
        return true;
    }
    return false;
}

const vector<int> &Customer::getOrdersIds() const
{
    return ordersId;
}

int Customer::addOrder(int orderId)
{
    if(canMakeOrder())
    {
        ordersId.push_back(orderId);
        return orderId;
    }
    return -1;
}

SoldierCustomer::SoldierCustomer(int id, string name, int locationDistance, int maxOrders) : Customer(id,name,locationDistance,maxOrders){}
SoldierCustomer::SoldierCustomer(const SoldierCustomer& copyThis): Customer(copyThis){}


SoldierCustomer *SoldierCustomer::clone() const
{
    return new SoldierCustomer(*this);
}
SoldierCustomer::~SoldierCustomer(){}

CivilianCustomer::CivilianCustomer(int id, string name, int locationDistance, int maxOrders): Customer(id,name,locationDistance,maxOrders){}
CivilianCustomer::CivilianCustomer(const CivilianCustomer& copyThis): Customer(copyThis){}

CivilianCustomer *CivilianCustomer::clone() const
{
    return new CivilianCustomer(*this);
}
CivilianCustomer::~CivilianCustomer(){}
