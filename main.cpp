#include "controller.h"

#include <iostream>
#include <sstream>

using namespace std;

void showUsage(bool showConditions = false)
{
    const string message = "Usage: ThreadBenchmark resourceSize threadCount";
    const string conditions = "Conditions: resourceSize > 0, threadCount > 0";
    cout << message << endl;
    if(showConditions)
    {
        cout << conditions << endl;
    }
}

int main(int argv, const char *argc[])
{
    if(argv < 3)
    {
        showUsage();
        return 0;
    }

    ostringstream out;
    out << argc[1] << " " << argc[2];
    istringstream in(out.str());

    long resourceSize = 0;
    long threadCount = 0;
    in >> resourceSize >> threadCount;

    if(resourceSize <= 0 || threadCount <= 0)
    {
        showUsage(true);
        return 0;
    }

    Controller controller;
    controller.init(resourceSize, threadCount);
    controller.run();

    cout << "Resource size " << controller.resourceSize() << ", threads count " << controller.workersCount()
         << ", duration " << controller.duration() << ", result " << controller.result() << endl;

    return 0;
}
