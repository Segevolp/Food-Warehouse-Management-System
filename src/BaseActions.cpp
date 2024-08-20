#include "../include/Action.h"
#include <iostream>
//#include "Action.h"

BaseAction::BaseAction(): status(), errorMsg(){}

ActionStatus BaseAction::getStatus() const
{
        return status;
}
BaseAction::~BaseAction(){}
void BaseAction::complete()
{
        status = ActionStatus::COMPLETED;

}

void BaseAction::error(string errorMsg)
{
        status = ActionStatus::ERROR;
        this->errorMsg = errorMsg;
        cout << errorMsg + "\n";

}

string BaseAction::getErrorMsg() const
{
        return errorMsg;
}
const char *BaseAction::statusToString() const
{
        switch (status)
        {
                case ActionStatus::COMPLETED: return "COMPLETED";
                case ActionStatus::ERROR: return "ERROR";
        }
        throw std::runtime_error("Impossible senario");
}
