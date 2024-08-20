#include "../include/WareHouse.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Volunteer.h"
#include "../include/Action.h"



WareHouse::WareHouse(const std::string &configFilePath):isOpen(false),orderCounter(0),customerCounter(0),volunteerCounter(0) {
    std::ifstream file;
    file.open(configFilePath);
    std::string line;
    if(file.is_open())
    {
        while(file.good())
        {
            getline(file,line);
            clean_line(line);
            if(line.size() != 0)
            {
                std::vector<std::string> words = to_words(line);
                if(words[0] == "customer")
                {
                    int id = getAvailableCustomerID();
                    if(words[2] == "soldier")
                    {
                    customers.push_back(new SoldierCustomer(id,words[1],stoi(words[3]),stoi(words[4])));
                    }
                    else if(words[2] == "civilian")
                    {
                        customers.push_back(new CivilianCustomer(id,words[1],stoi(words[3]),stoi(words[4])));
                    }
                }
                else if(words[0] == "volunteer")
                {
                    int id = getAvailableVolunteerID();
                    if(words[2] == "collector")
                    {
                        volunteers.push_back(new CollectorVolunteer(id,words[1],stoi(words[3])));
                    }
                    else if(words[2] == "limited_collector")
                    {
                        volunteers.push_back(new LimitedCollectorVolunteer(id,words[1],stoi(words[3]),stoi(words[4])));
                    }
                    else if(words[2] == "driver")
                    {
                        volunteers.push_back(new DriverVolunteer(id,words[1],stoi(words[3]),stoi(words[4])));
                    }
                    else if(words[2] == "limited_driver")
                    {
                        volunteers.push_back(new LimitedDriverVolunteer(id,words[1],stoi(words[3]),stoi(words[4]),stoi(words[5])));
                    }
                }
            }
        }
    }
    else
    {
        throw std::runtime_error("cannot open file!");
    }
    open();
}
WareHouse::WareHouse(const WareHouse &copyThis):isOpen(copyThis.isOpen), orderCounter(copyThis.orderCounter), customerCounter(copyThis.customerCounter), volunteerCounter(copyThis.volunteerCounter)
{

    for (BaseAction* action : copyThis.actionsLog) {
        actionsLog.push_back((*action).clone());
    }

    for (Volunteer* volunteer : copyThis.volunteers) {
        volunteers.push_back((*volunteer).clone());
    }

    for (Order* order : copyThis.pendingOrders) {
        pendingOrders.push_back((*order).clone()); 
    }

    for (Order* order : copyThis.inProcessOrders) {
        inProcessOrders.push_back((*order).clone());
    }

    for (Order* order : copyThis.completedOrders) {
        completedOrders.push_back((*order).clone());
    }

    for (Customer* customer : copyThis.customers) {
        customers.push_back((*customer).clone());
    }
    

}
WareHouse::WareHouse(WareHouse &&other): isOpen(other.isOpen),orderCounter(other.orderCounter),
customerCounter(other.customerCounter),volunteerCounter(other.volunteerCounter)
{
    for(BaseAction* ba: other.actionsLog){
        actionsLog.push_back(ba);
    }
    for(Volunteer* v: other.volunteers){
        volunteers.push_back(v);
    }
    
    for(Order* o: other.pendingOrders){
        pendingOrders.push_back(o);
    }
    for(Order* o : other.inProcessOrders){
        inProcessOrders.push_back(o);
    }
    for(Order* o : other.completedOrders){
        completedOrders.push_back(o);
    }
    for(Customer* c: other.customers){
        customers.push_back(c);
    }
    other.completedOrders.clear();
    other.inProcessOrders.clear();
    other.pendingOrders.clear();
    other.volunteers.clear();
    other.actionsLog.clear();
    other.customers.clear();
}
WareHouse &WareHouse::operator=(const WareHouse &other)
{
    if( &other != this)
    {
        isOpen = other.isOpen;
        orderCounter = other.orderCounter;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        for(BaseAction* ba: actionsLog){
            delete(ba);
        }
        actionsLog.clear();
        for(Volunteer* v: volunteers){
            delete(v);
        }
        volunteers.clear();
        for(Order* o: pendingOrders){
            delete(o);
        }
        pendingOrders.clear();
        for(Order* o :inProcessOrders){
            delete(o);
        }
        inProcessOrders.clear();
        for(Order* o :completedOrders){
            delete(o);
        }
        completedOrders.clear();
        for(Customer* c: customers){
            delete(c);
        }
        customers.clear();
        //
        for(BaseAction* ba: other.actionsLog){
            actionsLog.push_back((*ba).clone());
        }
        for(Volunteer* v: other.volunteers){
            volunteers.push_back((*v).clone());
        }
        for(Order* o: other.pendingOrders){
            pendingOrders.push_back((*o).clone());
        }
        for(Order* o : other.inProcessOrders){
            inProcessOrders.push_back((*o).clone());
        }
        for(Order* o : other.completedOrders){
            completedOrders.push_back((*o).clone());
        }
        for(Customer* c: other.customers){
            customers.push_back((*c).clone());
        }
    }
    return *this;
}
WareHouse &WareHouse::operator=(WareHouse &&other)
{
    if( &other != this)
    {
        isOpen = other.isOpen;
        orderCounter = other.orderCounter;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        for(BaseAction* ba: actionsLog){
            delete(ba);
        }
        actionsLog.clear();
        for(Volunteer* v: volunteers){
            delete(v);
        }
        volunteers.clear();
        for(Order* o: pendingOrders){
            delete(o);
        }
        pendingOrders.clear();
        for(Order* o :inProcessOrders){
            delete(o);
        }
        inProcessOrders.clear();
        for(Order* o :completedOrders){
            delete(o);
        }
        completedOrders.clear();
        for(Customer* c: customers){
            delete(c);
        }
        customers.clear();
        for(BaseAction* ba: other.actionsLog){
            actionsLog.push_back(ba);
        }
        for(Volunteer* v: other.volunteers){
            volunteers.push_back(v);
        }
        for(Order* o: other.pendingOrders){
            pendingOrders.push_back(o);
        }
        for(Order* o : other.inProcessOrders){
            inProcessOrders.push_back(o);
        }
        for(Order* o : other.completedOrders){
            completedOrders.push_back(o);
        }
        for(Customer* c: other.customers){
            customers.push_back(c);
        }
        other.completedOrders.clear();
        other.inProcessOrders.clear();
        other.pendingOrders.clear();
        other.volunteers.clear();
        other.actionsLog.clear();
        other.customers.clear();
    }
    return *this;
}
void WareHouse::clean_line(std::string &line)
{
    std::size_t place = line.find_first_of('#');
    if(place!=std::string::npos)
    {
        line = line.substr(0,place);
    }
}
std::vector<std::string> WareHouse::to_words(std::string &line)
{
    istringstream str(line);
    vector<string> words;
    string word;
    while(str>>word)
    {
        words.push_back(word);
    }
    return words;
}
void WareHouse::start()
{
    while(isOpen)
    {
        string input; 
        getline(cin,input);
        vector<string> words = to_words(input);
        if(words.size()>0)
        {
            if(words[0] == "step")
            {
                try
                {
                    if(words.size()==2)
                    {
                        int steps = stoi(words[1]);
                        SimulateStep *step = new SimulateStep(steps);
                        (*step).act(*this);
                    }
                    else
                    {
                        cout << "Invalid usage! syntax: step <number of steps>" << "\n" ;
                    }
                }
                catch(const std::exception& e)
                {
                    cout << "Invalid usage! syntax: step <number_of_steps>" << "\n" ;
                }
                
            }
            else if(words[0] == "order")
            {
                try
                {
                    if(words.size()==2)
                    {
                        int customerId = stoi(words[1]);
                        AddOrder *addOrder = new AddOrder(customerId);
                        (*addOrder).act(*this);
                    }
                    else
                    {
                        cout << "Invalid usage! syntax: order <customer_id>" << "\n" ;
                    }
                }
                catch(const std::exception& e)
                {
                    cout << "Invalid usage! syntax: order <customer_id>" << "\n" ;
                }
            }
            else if(words[0] == "customer")
            {
                try
                {
                    if(words.size()==5)
                    {
                        int distance = stoi(words[3]);
                        int maxOrders = stoi(words[4]);
                        AddCustomer *addCustomer = new AddCustomer(words[1],words[2],distance,maxOrders);
                        (*addCustomer).act(*this);
                    }
                    else
                    {
                        cout << "Invalid usage! syntax: customer <customer_name> <customer_type> <customer_distance> <max_orders>" << "\n" ;
                    }
                }
                catch(const std::exception& e)
                {
                    cout << "Invalid usage! syntax: customer <customer_name> <customer_type> <customer_distance> <max_orders>" << "\n" ;
                }
            }
            else if(words[0] == "orderStatus")
            {
                try
                {
                    if(words.size()==2)
                    {
                        int orderId = stoi(words[1]);
                        PrintOrderStatus *printOrderStatus = new PrintOrderStatus(orderId);
                        (*printOrderStatus).act(*this);
                    }
                    else
                    {
                        cout << "Invalid usage! syntax: orderStatus <order_id>" << "\n" ;
                    }
                }
                catch(const std::exception& e)
                {
                    cout << "Invalid usage! syntax: orderStatus <order_id>" << "\n" ;
                }
            }
            else if(words[0] == "customerStatus")
            {
                try
                {
                    if(words.size()==2)
                    {
                        int customerId = stoi(words[1]);
                        PrintCustomerStatus *printCustomerStatus = new PrintCustomerStatus(customerId);
                        (*printCustomerStatus).act(*this);
                    }
                    else
                    {
                        cout << "Invalid usage! syntax: customerStatus <customer_id>" << "\n" ;
                    }
                }
                catch(const std::exception& e)
                {
                    cout << "Invalid usage! syntax: customerStatus <customer_id>" << "\n" ;
                }
            }
            else if(words[0] == "volunteerStatus")
            {
                try
                {
                    if(words.size()==2)
                    {
                        int volunteerId = stoi(words[1]);
                        PrintVolunteerStatus *printVolunteerStatus = new PrintVolunteerStatus(volunteerId);
                        (*printVolunteerStatus).act(*this);
                    }
                    else
                    {
                        cout << "Invalid usage! syntax: volunteerStatus <volunteer_id>" << "\n" ;
                    }
                }
                catch(const std::exception& e)
                {
                    cout << "Invalid usage! syntax: volunteerStatus <volunteer_id>" << "\n" ;
                }
            }
            else if(words[0] == "log")
            {
                PrintActionsLog *printActionsLog = new PrintActionsLog();
                (*printActionsLog).act(*this);
            }
            else if(words[0] == "backup")
            {
                BackupWareHouse *backupAction = new BackupWareHouse();
                (*backupAction).act(*this);
            }
            else if(words[0] == "restore")
            {
                RestoreWareHouse *restoreAction = new RestoreWareHouse();
                (*restoreAction).act(*this);
            }
            else if(words[0] == "close")
            {
                close();
            }
            else
            {
                cout << "Invalid input!" << endl ;
            }
        }
        else
        {
            cout << "Invalid input!" << endl ;
        }
    }
}
void WareHouse::addOrder(Order* order)
{
    pendingOrders.push_back(order);
}
void WareHouse::addAction(BaseAction* action)
{
    actionsLog.push_back(action);
}
void WareHouse::addCustomer(Customer* customerToAdd)
{
    customers.push_back(customerToAdd);
}
Customer& WareHouse::getCustomer(int customerId) const
{
    for(std::vector<Customer*>::const_iterator it(customers.begin());it != customers.end(); ++it)
    {
        if((**it).getId()==customerId)
        {
            return (**it);
        }
    }
    throw std::runtime_error("Customer not found");
}
Volunteer& WareHouse::getVolunteer(int volunteerId) const
{
    for(std::vector<Volunteer*>::const_iterator it(volunteers.begin());it != volunteers.end(); ++it)
    {
        if((**it).getId()==volunteerId)
        {
            return (**it);
        }
    }
    throw std::runtime_error("Volunteer not found");
}
Order& WareHouse::getOrder(int orderId) const
{
    for(std::vector<Order*>::const_iterator it(pendingOrders.begin());it != pendingOrders.end(); ++it)
    {
        if((**it).getId()==orderId)
        {
            return (**it);
        }
    }
    for(std::vector<Order*>::const_iterator it(inProcessOrders.begin());it != inProcessOrders.end(); ++it)
    {
        if((**it).getId()==orderId)
        {
            return (**it);
        }
    }
    for(std::vector<Order*>::const_iterator it(completedOrders.begin());it != completedOrders.end(); ++it)
    {
        if((**it).getId()==orderId)
        {
            return (**it);
        }
    }
    throw std::runtime_error("no such order!");
}
const vector<BaseAction*> & WareHouse::getActions() const
{
    return actionsLog;
}
void WareHouse::close()
{
    isOpen=false;
    Close *closeAction = new Close();
    (*closeAction).act(*this);
}
void WareHouse::open()
{
    isOpen=true;
    cout << "Warehouse is open!\n";
}
int WareHouse::getAvailableOrderID()
{
    int temp = orderCounter;
    orderCounter++;
    return temp;
}

int WareHouse::getAvailableCustomerID()
{
    int temp = customerCounter;
    customerCounter++;
    return temp;
}

int WareHouse::getAvailableVolunteerID()
{
    int temp = volunteerCounter;
    volunteerCounter++;
    return temp;
}
vector<Order *> &WareHouse::getPendingOrders()
{
    return pendingOrders;
}

vector<Order *> &WareHouse::getInProccessOrders()
{
    return inProcessOrders;
}

vector<Order *> &WareHouse::getCompletedOrders()
{
    return completedOrders;
}
vector<Volunteer *> &WareHouse::getVolunteers()
{
    return volunteers;
}
WareHouse::~WareHouse()
{
    for(BaseAction* ba: actionsLog){
        delete(ba);
    }
    //actionsLog.clear();
    for(Volunteer* v: volunteers){
        delete(v);
    }
    //volunteers.clear();
    for(Order* o: pendingOrders){
        delete(o);
    }
    //pendingOrders.clear();
    for(Order* o :inProcessOrders){
        delete(o);
    }
    //inProcessOrders.clear();
    for(Order* o :completedOrders){
        delete(o);
    }
    //completedOrders.clear();
    for(Customer* c: customers){
        delete(c);
    }
    //customers.clear();

}
