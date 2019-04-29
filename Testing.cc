#include "Testing.h"
#include "Server.h"
#include "Client.cc"

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
    testServerClient();
    cout << ticket_prefix << " tests passed" << endl;
}

/*
    Confirms constructors and functionHandle() work as intended.
*/
void Testing::ticketingConstructors()
{
    std::string resp = "";
    int ticketNum = 100;
    TicketingSystem noArgs;
    resp = noArgs.functionHandle("");
    assert(resp.compare(to_string((0))) == 0);

    TicketingSystem withArgs(ticketNum);
    resp = withArgs.functionHandle("");
    assert(resp.compare(to_string(ticketNum - 1)) == 0);

    cout << ticket_prefix << " constructor test(s) passed" << endl;
}

/*
    Confirms functionHandle() works as intended.
*/
void Testing::ticketingGetTicket(TicketingSystem &t, int target)
{
    assert(t.functionHandle("").compare(to_string(target)));
    cout << ticket_prefix << " decrement test passed." << endl;
}

void Testing::testServerClient()
{
    TicketingSystem t(255);
    int fork_flag = 0;
    if (fork())
        fork_flag = 1;
    if (fork_flag == 0)
        createServer(t);
    else
        ticketingClient();
}

int Testing::test(TicketingSystem &t)
{
    cout << "why" << endl;
}

void Testing::ticketingClient()
{
    queue<future<int> > q;
    for (int i = 0; i < 5; ++i)
    {
        string s = to_string(i);
        const char* c = s.c_str();
        q.push(async(createClient, c));
    }

    while(!q.empty())
    {
        cout << q.front().get() << ", ";
        q.pop();
    }
    cout << endl;

    createClient("end");
}

int Testing::createServer(TicketingSystem &t)
{
    Server s;
    s.startServer(t);
    return 0;
}

int Testing::createClient(const char* c)
{
    return runClient(c);
}
