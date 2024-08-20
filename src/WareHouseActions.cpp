#include "../include/Action.h"
#include <iostream>
#include <string>
#include <algorithm>

extern WareHouse* backup;
Close::Close(){}

void Close::act(WareHouse &wareHouse)
{
    vector<Order*> inProgressOrders = wareHouse.getInProccessOrders();
    vector<Order*> pendingOrders = wareHouse.getPendingOrders();
    vector<Order*> completedOrders = wareHouse.getCompletedOrders();
    string str;
    for(Order* o: inProgressOrders){
        str = o->toString();
        std::replace(str.begin(), str.end(), '\n', ',');
        std::cout << str << "\n";
    }
    for(Order* o: pendingOrders){
        str = o->toString();
        std::replace(str.begin(), str.end(), '\n', ',');
        std::cout << str << "\n";
    }
    for(Order* o: completedOrders){
        str = o->toString();
        std::replace(str.begin(), str.end(), '\n', ',');
        std::cout << str << "\n";
    }
    complete();
    wareHouse.addAction(this);
    //TODO: delete warehouse
}
Close::~Close(){}
Close *Close::clone() const
{
    return new Close();
}
string Close::toString() const
{
    string ans;
    ans.append("Close ");
    ans.append(statusToString());
    ans.append("\n");
    return ans;
}



BackupWareHouse::BackupWareHouse(){}
BackupWareHouse::~BackupWareHouse(){}
void BackupWareHouse::act(WareHouse &wareHouse)
{
    if(backup != nullptr)
    {
        delete backup;
    }
    backup = new WareHouse(wareHouse); // copy using copy constructor - deep copy
    complete();
    wareHouse.addAction(this);
}

BackupWareHouse *BackupWareHouse::clone() const
{
    return new BackupWareHouse();
}

string BackupWareHouse::toString() const
{
    string ans;
    ans.append("BackupWareHouse ");
    ans.append(statusToString());
    ans.append("\n");
    return ans;
}



RestoreWareHouse::RestoreWareHouse()
{
}
RestoreWareHouse::~RestoreWareHouse(){}
void RestoreWareHouse::act(WareHouse &wareHouse)
{
    if(backup == nullptr){
        error("No backup available");
    }
    else{
        wareHouse = *backup; // ????
        complete();
    }
    wareHouse.addAction(this);
}

RestoreWareHouse *RestoreWareHouse::clone() const
{
    return new RestoreWareHouse();
}

string RestoreWareHouse::toString() const
{
    string ans;
    ans.append("RestoreWareHouse ");
    ans.append(statusToString());
    ans.append("\n");
    return ans;
}
