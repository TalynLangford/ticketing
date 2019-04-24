#include "TicketingSystem.h"

TicketingSystem::TicketingSystem() : tickets(0) {}
TicketingSystem::TicketingSystem(int t) : tickets(t) {}
TicketingSystem::~TicketingSystem()
{
    std::cout << "Destructing TicketingSystem" << std::endl;
}

int TicketingSystem::getTicket()
{
    if (tickets > 0)
        --tickets;

    return tickets;
}
