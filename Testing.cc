#include "Testing.h"

using namespace std;

static const string ticket_prefix = "Ticketing";

void Testing::runTests()
{
    ticketingTests();
    cout << "All tests passed." << endl;
}

/*
    Runs all TicketingSystem tests.
*/
void Testing::ticketingTests()
{
    ticketingConstructors();
    cout << ticket_prefix << " tests passed" << endl;
}

/*
    Confirms constructors and getTicket() work as intended.
*/
void Testing::ticketingConstructors()
{
    int ticketNum = 100;
    TicketingSystem noArgs;
    assert(noArgs.getTicket() == 0);

    TicketingSystem withArgs(ticketNum);
    assert(withArgs.getTicket() == ticketNum - 1);

    cout << ticket_prefix << " constructor test(s) passed" << endl;
}

/*
    Confirms getTicket() works as intended.
*/
void Testing::ticketingGetTicket(TicketingSystem &t, int target)
{
    assert(t.getTicket() == target);
    cout << ticket_prefix << " decrement test passed." << endl;
}