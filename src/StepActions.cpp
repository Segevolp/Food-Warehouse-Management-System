#include "../include/Action.h"
#include "../include/Order.h"
#include "../include/Volunteer.h"
#include <iostream>



SimulateStep::SimulateStep(int numOfSteps): numOfSteps(numOfSteps) {}
SimulateStep::SimulateStep(const SimulateStep &copyThis): numOfSteps(copyThis.numOfSteps){}
SimulateStep::~SimulateStep(){}
void SimulateStep::act(WareHouse &wareHouse)
{
    vector<Order *> &pendingOrders = wareHouse.getPendingOrders();
    vector<Order*> &inProccesOrders = wareHouse.getInProccessOrders();
    vector<Order*> &completedOrders = wareHouse.getCompletedOrders();
    vector<Volunteer*> &volunteers =wareHouse.getVolunteers();
    for(int i = 0;i<numOfSteps;++i)
    {
        stepPart1(pendingOrders,inProccesOrders,volunteers);
        stepPart2And3And4(pendingOrders,inProccesOrders,volunteers,completedOrders);  
    }
    complete();
    wareHouse.addAction(this);
}

std::string SimulateStep::toString() const
{
    string ans;
    ans.append("simulateStep ");
    ans.append(to_string(numOfSteps) + " ");
    ans.append(statusToString());
    ans.append("\n");
    return ans;
}

SimulateStep *SimulateStep::clone() const
{
    return new SimulateStep(*this);
}

void SimulateStep::stepPart1(vector<Order *> &pendingOrders, vector<Order *> &inProccesOrders, vector<Volunteer *> &volunteers)
{
    for(vector<Order*>::iterator it1(pendingOrders.begin());it1!=pendingOrders.end();)
        {
            bool deletedElement = false;
            OrderStatus status = (*it1)->getStatus();
            for(vector<Volunteer*>::iterator it2(volunteers.begin());!deletedElement&&it2!=volunteers.end();++it2)
            {
                if(status == OrderStatus::PENDING){
                    //if(typeid(*it2) == typeid(CollectorVolunteer) || typeid(*it2) == typeid(LimitedCollectorVolunteer)){
                    if(dynamic_cast<CollectorVolunteer *>(*it2) !=nullptr ){
                        if((*it2)->canTakeOrder(**it1)){
                            (*it1)->setCollectorId((*it2)->getId());
                            (*it1)->setStatus(OrderStatus::COLLECTING);
                            (*it2)->acceptOrder((**it1));
                            inProccesOrders.push_back(*it1);
                            it1 = pendingOrders.erase(it1);
                            deletedElement = true;
                        }
                    }
                }
                else if(status == OrderStatus::COLLECTING){
                    //if(typeid(*it2) == typeid(DriverVolunteer) || typeid(*it2) == typeid(LimitedDriverVolunteer)){
                    if(dynamic_cast<DriverVolunteer *>(*it2) !=nullptr ){
                        if((*it2)->canTakeOrder(**it1)){
                            (*it1)->setDriverId((*it2)->getId());
                            (*it1)->setStatus(OrderStatus::DELIVERING);
                            (*it2)->acceptOrder((**it1));
                            inProccesOrders.push_back(*it1);
                            it1 = pendingOrders.erase(it1);
                            deletedElement = true;
                        }
                    }
                }
            }
            if(!deletedElement)
            {
                ++it1;
            }
        }
}
void SimulateStep::stepPart2And3And4(vector<Order *> &pendingOrders, vector<Order *> &inProccesOrders, vector<Volunteer *> &volunteers,vector<Order *> &completedOrders)
{
    for(vector<Volunteer*>::iterator it1(volunteers.begin());it1!=volunteers.end();)
    {
        bool limitedVolunteerNoOrdersLeft = false;
        if((**it1).isBusy())
        {
            (**it1).step();
            if(!(**it1).isBusy())
            {
                int orderId = (**it1).getCompletedOrderId();
                bool foundOrder = false;
                for(vector<Order*>::iterator it2(inProccesOrders.begin());!foundOrder&&it2!=inProccesOrders.end();)
                {
                    if((**it2).getId()==orderId)
                    {
                        foundOrder = true;
                        if(!(**it1).canTakeOrder(**it2))
                        {
                            limitedVolunteerNoOrdersLeft = true;
                            delete (*it1);
                            it1 = volunteers.erase(it1);
                        }
                        if((**it2).getStatus()== OrderStatus::COLLECTING)
                        {
                            pendingOrders.push_back(*it2);
                            it2 = inProccesOrders.erase(it2);
                        }
                        else if((**it2).getStatus()== OrderStatus::DELIVERING)
                        {
                            (**it2).setStatus(OrderStatus::COMPLETED);
                            completedOrders.push_back(*it2);
                            it2 = inProccesOrders.erase(it2);
                        }
                    }
                    else
                    {
                        ++it2;
                    }
                }   
            }
        }
        if(!limitedVolunteerNoOrdersLeft)
        {
            ++it1;
        }
    }
}

