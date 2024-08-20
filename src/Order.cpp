#include "../include/Order.h"
#include <iostream>

Order::Order(int id, int customerId, int distance):id(id),customerId(customerId),distance(distance),collectorId(NO_VOLUNTEER),driverId(NO_VOLUNTEER),status(OrderStatus::PENDING) {}

Order::Order(const Order &copyThis):id(copyThis.id), customerId(copyThis.customerId), distance(copyThis.distance)
, collectorId(copyThis.collectorId), driverId(copyThis.driverId), status(copyThis.status){}

Order *Order::clone() const
{
   return new Order(*this);
}
int Order::getId() const
{
    return id;
}

int Order::getCustomerId() const
{
    return customerId;
}

void Order::setStatus(OrderStatus status)
{
    (*this).status = status;
}

void Order::setCollectorId(int collectorId)
{
    (*this).collectorId = collectorId;
}

void Order::setDriverId(int driverId)
{
    (*this).driverId = driverId;
}

int Order::getCollectorId() const
{
    return collectorId;
}

int Order::getDriverId() const
{
    return driverId;
}

int Order::getDistance() const
{
    return distance;
}
OrderStatus Order::getStatus() const
{
    return status;
}

const char *Order::statusToString() const
{
    switch(status)
    {
        case OrderStatus::COLLECTING: return "Collecting";
        case OrderStatus::PENDING: return "Pending";
        case OrderStatus::COMPLETED: return "Completed";
        case OrderStatus::DELIVERING: return "Delivering";
    }
    throw std::runtime_error("Impossible senario");
}
const string Order::toString() const
{
    string str = "OrderId: " + std::to_string(id) + "\n";
    OrderStatus os = status;
    if(os == OrderStatus::PENDING){
        str += "OrderStatus: Pending\n" ;
        str += "CustomerID: " + std::to_string(customerId) + "\n";
        str += "CollectorID: None\n";
        str += "Driver: None\n";
    }
    else if(os == OrderStatus::COMPLETED){
        str += "OrderStatus: Completed\n";
        str += "CustomerID: " + std::to_string(customerId) + "\n";
        str += "CollectorID: " + std::to_string(collectorId) + "\n";
        str += "Driver: "+ std::to_string(driverId) + "\n";
    }
    else if(os == OrderStatus::COLLECTING){
        str += "OrderStatus: Collecting\n";
        str += "CustomerID: " + std::to_string(customerId) +"\n";
        str += "CollectorID: " + std::to_string(collectorId) +"\n";
        str += "Driver: None\n";
    }
    else if(os == OrderStatus::DELIVERING){
        str += "OrderStatus: Delivering\n";
        str += "CustomerID: " + std::to_string(customerId) +"\n";
        str += "CollectorID: " + std::to_string(collectorId) +"\n";
        str += "Driver: " + std::to_string(driverId) + "\n";
    }
    return str;
}
