#include "../include/Volunteer.h"
#include <iostream>

Volunteer::Volunteer(int id, const string &name) : id(id),name(name),completedOrderId(NO_ORDER),activeOrderId(NO_ORDER){}

Volunteer::Volunteer(const Volunteer &copyThis) : id(copyThis.id), name(copyThis.name),completedOrderId(copyThis.completedOrderId),
activeOrderId(copyThis.activeOrderId) {}

int Volunteer::getId() const
{
    return id;
}
Volunteer::~Volunteer(){}
const string &Volunteer::getName() const
{
    return name;
}

int Volunteer::getActiveOrderId() const
{
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const
{
    return completedOrderId;
}

bool Volunteer::isBusy() const
{
    if(activeOrderId == NO_ORDER)
    {
        return false;
    }
    return true;
}

CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown): Volunteer(id,name) , coolDown(coolDown),timeLeft(0){}

CollectorVolunteer::CollectorVolunteer(const CollectorVolunteer &copyThis): Volunteer(copyThis.getId(),copyThis.getName()), coolDown(copyThis.coolDown), timeLeft(copyThis.timeLeft){}

CollectorVolunteer::~CollectorVolunteer(){}
CollectorVolunteer *CollectorVolunteer::clone() const
{
    return new CollectorVolunteer(*this);
}

void CollectorVolunteer::step()
{
    if(decreaseCoolDown())
    {
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}

int CollectorVolunteer::getCoolDown() const
{
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const
{
    return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown()
{
    if(timeLeft>0)
    {
        --timeLeft;
        if(timeLeft==0)
        {
            return true;
        }
        return false;
    }
    return true; // valid?
}

bool CollectorVolunteer::hasOrdersLeft() const
{
    return true;
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const
{
    if(activeOrderId == NO_ORDER)
    {
        return true;
    }
    return false;
}

void CollectorVolunteer::acceptOrder(const Order &order)
{
    if(canTakeOrder(order))
    {
        activeOrderId = order.getId();
        timeLeft = coolDown;
    }
    else
    {
        throw std::runtime_error("this volunteer cannot accept this order!");
    }
}

string CollectorVolunteer::toString() const
{
    string str = "VolunteerID: " + std::to_string(getId()) + "\n";
    bool busy = isBusy();
    str += "isBusy: ";
    if(busy){
        str += "True\n";
        str += "OrderID: " + std::to_string(getActiveOrderId()) + "\n";
    }
    else{
        str += "False\n";
        str += "OrderID: None \n";

    }
    str += "TimeLeft: " + std::to_string(timeLeft) + "\n";
    str += "OrdersLeft: No Limit\n";
    return str;
}

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, string name, int coolDown, int maxOrders): CollectorVolunteer(id,name,coolDown),
 maxOrders(maxOrders),ordersLeft(maxOrders){}

LimitedCollectorVolunteer::LimitedCollectorVolunteer(const LimitedCollectorVolunteer &copyThis):CollectorVolunteer(copyThis.getId(),copyThis.getName(),copyThis.getCoolDown()),
maxOrders(copyThis.maxOrders),ordersLeft(copyThis.ordersLeft) {}
LimitedCollectorVolunteer::~LimitedCollectorVolunteer(){}
LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const
{
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const
{
    if(ordersLeft>0)
    {
        return true;
    }
    return false;
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const
{
    if(hasOrdersLeft()&&activeOrderId==NO_ORDER)
    {
        return true;
    }
    return false;
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order)
{
    CollectorVolunteer::acceptOrder(order);
    --ordersLeft;

}

int LimitedCollectorVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const
{
    string str = CollectorVolunteer::toString();
    str = str.substr(0,str.size() -9);
    str +=  std::to_string(ordersLeft)+ "\n";
    return str;
}
DriverVolunteer::DriverVolunteer(int id, string name, int maxDistance, int distancePerStep): Volunteer(id,name),maxDistance(maxDistance),distancePerStep(distancePerStep),distanceLeft(0){}
DriverVolunteer::~DriverVolunteer(){}
DriverVolunteer::DriverVolunteer(const DriverVolunteer &copyThis): Volunteer(copyThis.getId(),copyThis.getName())
, maxDistance(copyThis.maxDistance), distancePerStep(copyThis.distancePerStep),distanceLeft(copyThis.distanceLeft){}

DriverVolunteer *DriverVolunteer::clone() const
{
    return new DriverVolunteer(*this);
}

int DriverVolunteer::getDistanceLeft() const
{
    return distanceLeft;
}

int DriverVolunteer::getMaxDistance() const
{
    return maxDistance;
}

int DriverVolunteer::getDistancePerStep() const
{
    return distancePerStep;
}

bool DriverVolunteer::decreaseDistanceLeft()
{
    if(distanceLeft>0)
    {
        distanceLeft -= distancePerStep;
        if(distanceLeft>0)
        {
            return false;
        }
        distanceLeft = 0;
        return true;
    }
    return true;
}

bool DriverVolunteer::hasOrdersLeft() const
{
    return true;
}

bool DriverVolunteer::canTakeOrder(const Order &order) const
{
    if(order.getDistance()<=maxDistance&&activeOrderId == NO_ORDER)
    {
        return true;
    }
    return false;
}

void DriverVolunteer::acceptOrder(const Order &order)
{
    if(canTakeOrder(order))
    {
        activeOrderId = order.getId();
        distanceLeft = order.getDistance();
    }
    else
    {
        throw std::runtime_error("this volunteer cannot accept this order!");
    }
}

void DriverVolunteer::step()
{
    if(decreaseDistanceLeft())
    {
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}

string DriverVolunteer::toString() const
{
    string str = "VolunteerID: " + std::to_string(getId()) + "\n";
    bool busy = isBusy();
    str += "isBusy: ";
    if(busy){
        str += "True\n";
        str += "OrderID: " + std::to_string(getActiveOrderId()) + "\n";
    }
    else{
        str += "False\n";
        str += "OrderID: None \n";

    }
    str += "DistanceLeft: " + std::to_string(distanceLeft) + "\n";
    str += "OrdersLeft: No Limit\n";
    return str;
}

LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep, int maxOrders): DriverVolunteer(id,name,maxDistance,distancePerStep),
 maxOrders(maxOrders),ordersLeft(maxOrders){}

LimitedDriverVolunteer::LimitedDriverVolunteer(const LimitedDriverVolunteer &copyThis): DriverVolunteer(copyThis.getId(),copyThis.getName(),copyThis.getMaxDistance(),copyThis.getDistancePerStep()), 
maxOrders(copyThis.maxOrders), ordersLeft(copyThis.maxOrders){}
LimitedDriverVolunteer::~LimitedDriverVolunteer(){}
LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const
{
    return new LimitedDriverVolunteer(*this);
}

int LimitedDriverVolunteer::getMaxOrders() const
{
    return maxOrders;
}

int LimitedDriverVolunteer::getNumOrdersLeft() const
{
    return ordersLeft;
}

bool LimitedDriverVolunteer::hasOrdersLeft() const
{
    if(ordersLeft>0)
    {
        return true;
    }
    return false;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const
{
    if(order.getDistance()<=getMaxDistance()&&ordersLeft>0&&activeOrderId == NO_ORDER)
    {
        return true;
    }
    return false;
}

void LimitedDriverVolunteer::acceptOrder(const Order &order)
{
    DriverVolunteer::acceptOrder(order);
    --ordersLeft;
}

string LimitedDriverVolunteer::toString() const
{
    string str = DriverVolunteer::toString();
    str = str.substr(0,str.size() -9);
    str +=  std::to_string(ordersLeft)+ "\n";
    return str;
}
