#pragma once
#include "TicketingSystem.h"
#include <iostream>
#include <assert.h>
#include <string>
#include <future>
#include <queue>
#include <sys/types.h>
#include <unistd.h>

class Testing
{
public:
    static void runTests();

private:
    // TicketingSystem tests
    static void ticketingTests();
    static void ticketingConstructors();
    static void ticketingGetTicket(TicketingSystem &t, int target);
    static void ticketingClient();
    // Server tests
    static void testServerClient();
    static int createClient(const char* c);
    static int createServer(TicketingSystem &t);
    static int test(TicketingSystem &t);
};