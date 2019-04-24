#include "TicketingSystem.h"
#include "Testing.h"
#include <iostream>
#include <stack>

using namespace std;

int main()
{
    Testing::runTests();
    /*
    stack<TicketingSystem*> to_destruct;

    // no args constructor
    TicketingSystem* no_args = new TicketingSystem();
    to_destruct.push(no_args);
    cout << "No args ticketing system get ticket: " 
        << no_args->getTicket() << endl;
    cout << "New call to verify ticketing non-update: "
        << no_args->getTicket() << endl;

    cout << endl;

    // single args constructor
    TicketingSystem* with_args = new TicketingSystem(255);
    to_destruct.push(with_args);
    cout << "With args ticketing system get ticket: " 
        << with_args->getTicket() << endl;
    cout << "New call to verify ticketing update: "
        << with_args->getTicket() << endl;


    while(!to_destruct.empty())
    {
        TicketingSystem* to_delete = to_destruct.top();
        to_destruct.pop();
        delete to_delete;
    }
    // delete no_args;
    // delete with_args;
    */
}