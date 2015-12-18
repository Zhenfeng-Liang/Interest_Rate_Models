#include <BrownianMotionGenerator.hpp>

#include <iostream>

using namespace std;

int main()
{
    vector<double> steps = {0.25, 0.5, 0.75, 1.0};
    BrownianMotionGenerator bm_simulator(steps);
    bm_simulator.dump();

    vector<double> steps2;

    for (int t = 0; t < 100; ++t)
    {
        steps2.push_back(0.25 * (t + 1.0));
    }
    BrownianMotionGenerator simulator2(steps2);

    for (int i = 0; i < 5; ++i)
    {        
        vector<double> path;
        simulator2.simulate(path);

        for (size_t t = 0; t < path.size(); ++t)
        {
            cout << path[t] << ",";
        }

        cout << endl << endl;
    }


    cout << "Check if the seeds are the same for each simulation, if they are the same, the following outputs are the same" << endl;
    vector<double> steps3 = {0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2.0};
    BrownianMotionGenerator simulator3(steps3);
    {
        vector<double> path;
        simulator3.simulate(path);

        for (size_t t = 0; t < path.size(); ++t)
        {
            cout << path[t] << ",";
        }

        cout << endl;
    }

    //BrownianMotionGenerator simulator4(steps3);
    {
        vector<double> path;
        simulator3.simulate(path);

        for (size_t t = 0; t < path.size(); ++t)
        {
            cout << path[t] << ",";
        }

        cout << endl;
    }
}
