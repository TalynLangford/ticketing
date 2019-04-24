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
    cout << TICKET_PREFIX << " tests passed" << endl;
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

    cout << TICKET_PREFIX << " constructor test(s) passed" << endl;
}

/*
    Confirms getTicket() works as intended.
*/
void Testing::ticketingGetTicket(TicketingSystem &t, int target)
{
    assert(t.getTicket() == target);
    cout << TICKET_PREFIX << " decrement test passed." << endl;
}