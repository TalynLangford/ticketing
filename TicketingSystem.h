#pragma once
#include "IService.h"
#include <iostream>

class TicketingSystem : public IService 
{
public:
    TicketingSystem();
    TicketingSystem(int t);
    ~TicketingSystem();

    std::string functionHandle(std::string func);

private:
    int tickets;
    
    int getTicket();
};
