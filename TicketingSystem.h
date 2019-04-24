#pragma once
#include <iostream>

class TicketingSystem
{
public:

    TicketingSystem();
    TicketingSystem(int t);
    ~TicketingSystem();

    int getTicket();

private:

    int tickets;
};