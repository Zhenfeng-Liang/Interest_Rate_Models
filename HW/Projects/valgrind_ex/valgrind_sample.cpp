#include <iostream>
#include <vector>

using namespace std;

void print_vec(const vector<int> & vec, int len)
{
    cout << "Printing vec" << endl;
    for (int i = 0; i < len; ++i)
    {
        cout << i << " - " << vec[i] << endl;
    }
}

void foo()
{
    vector<int> tmp2;
    tmp2.push_back(1);
    tmp2.push_back(2);
    print_vec(tmp2, 3);
}

int main()
{
    foo();
    
    vector<int> tmp;
    tmp.push_back(1);
    tmp.push_back(2);

    for (int i = 0; i < 10; ++i)
    {
        cout << i << " - " << tmp[i] << endl;
    }

    for (int i = 0; i < 10; ++i)
    {
        tmp[i] = i;
    }
    
    return 0;
}
