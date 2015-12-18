#include <GaussianRVGenerator.hpp>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    int count = 10;
    if (argc > 1)
    {
        count = atoi(argv[1]);
    }

    for (int idx = 0; idx < count; ++idx)
    {
        cout << idx << ", " << GaussianRVGenerator::random() << endl;
    }
}
