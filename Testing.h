#pragma once
#include "TicketingSystem.h"
#include <iostream>
#include <assert.h>
#include <string>

class Testing
{
public:
    static void runTests();

private:
    // TicketingSystem tests
    static void ticketingTests();
    static void ticketingConstructors();
    static void ticketingGetTicket(TicketingSystem &t, int target);
    // Server tests
};