#pragma once
#include <string>
#include <vector>
#include "WareHouse.h"
using std::string;
using std::vector;

// extern WareHouse* backup;

enum class ActionStatus{
    COMPLETED, ERROR
};

class ActionStatusString{
    public:
    static const char* toString(ActionStatus actionStatus);
};

enum class CustomerType{
    Soldier, Civilian
};


class Customer;

class BaseAction{
    public:
        BaseAction();
        ActionStatus getStatus() const;
        virtual void act(WareHouse& wareHouse)=0;
        virtual string toString() const=0;
        virtual BaseAction* clone() const=0;
        virtual ~BaseAction() = 0;

    protected:
        void complete();
        void error(string errorMsg);
        string getErrorMsg() const;
        const char* statusToString() const;

    private:
        string errorMsg;
        ActionStatus status;
};

class SimulateStep : public BaseAction {

    public:
        SimulateStep(int numOfSteps);
        SimulateStep(const SimulateStep& copyThis);

        void act(WareHouse &wareHouse) override;
        std::string toString() const override;
        SimulateStep *clone() const override;
        virtual ~SimulateStep();
    private:
        const int numOfSteps;
        void stepPart1(vector<Order *> &pendingOrders, vector<Order *> &inProccesOrders, vector<Volunteer *> &volunteers);
        void stepPart2And3And4(vector<Order *> &pendingOrders, vector<Order *> &inProccesOrders, vector<Volunteer *> &volunteers,vector<Order *> &completedOrders);
};

class AddOrder : public BaseAction {
    public:
        AddOrder(int id);
        AddOrder(const Order& copyThis);
        void act(WareHouse &wareHouse) override;
        string toString() const override;
        AddOrder *clone() const override;
        virtual ~AddOrder();
    private:
        const int customerId;
};


class AddCustomer : public BaseAction {
    public:
        AddCustomer(string customerName, string customerType, int distance, int maxOrders);
        AddCustomer(const AddCustomer& copyThis);
        void act(WareHouse &wareHouse) override;
        AddCustomer *clone() const override;
        string toString() const override;
        virtual ~AddCustomer();
    private:const 
        static CustomerType convertToCustomerType(const string& customerType);
        const string customerName;
        const CustomerType customerType;
        const int distance;
        const int maxOrders;
};



class PrintOrderStatus : public BaseAction {
    public:
        PrintOrderStatus(int id);
        PrintOrderStatus(const PrintOrderStatus& copyThis);
        void act(WareHouse &wareHouse) override;
        void actWithoutLog(WareHouse &wareHouse);
        PrintOrderStatus *clone() const override;
        string toString() const override;
        virtual ~PrintOrderStatus();
    private:
        //const char* statusToString(const OrderStatus& orderStatus);
        const int orderId;
};

class PrintCustomerStatus: public BaseAction {
    public:
        PrintCustomerStatus(int customerId);
        PrintCustomerStatus(const PrintCustomerStatus& copyThis);
        void act(WareHouse &wareHouse) override;
        PrintCustomerStatus *clone() const override;
        string toString() const override;
        virtual ~PrintCustomerStatus();
    private:
        const int customerId;
};


class PrintVolunteerStatus : public BaseAction {
    public:
        PrintVolunteerStatus(int id);
        PrintVolunteerStatus(const PrintVolunteerStatus& copyThis);
        void act(WareHouse &wareHouse) override;
        PrintVolunteerStatus *clone() const override;
        string toString() const override;
        virtual ~PrintVolunteerStatus();
    private:
        const int volunteerId;
};


class PrintActionsLog : public BaseAction {
    public:
        PrintActionsLog();
        void act(WareHouse &wareHouse) override;
        PrintActionsLog *clone() const override;
        string toString() const override;
        virtual ~PrintActionsLog();
    private:
};

class Close : public BaseAction {
    public:
        Close();
        void act(WareHouse &wareHouse) override;
        Close *clone() const override;
        string toString() const override;
        virtual ~Close();
    private:
};

class BackupWareHouse : public BaseAction {
    public:
        BackupWareHouse();
        void act(WareHouse &wareHouse) override;
        BackupWareHouse *clone() const override;
        string toString() const override;
        virtual ~BackupWareHouse();
    private:
};


class RestoreWareHouse : public BaseAction {
    public:
        RestoreWareHouse();
        void act(WareHouse &wareHouse) override;
        RestoreWareHouse *clone() const override;
        string toString() const override;
        virtual ~RestoreWareHouse();
    private:
};