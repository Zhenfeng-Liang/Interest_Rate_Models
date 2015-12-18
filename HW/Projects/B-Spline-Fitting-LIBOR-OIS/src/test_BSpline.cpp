#include <iostream>
#include <BSpline.hpp>

#include <vector>

using namespace std;

int main()
{
    vector<double> tenors;
    tenors.push_back(-5.0);
    tenors.push_back(-3.0);
    tenors.push_back(-1.0);
    tenors.push_back(0.0);
    tenors.push_back(.25);
    tenors.push_back(.5);
    tenors.push_back(1.0);
    tenors.push_back(2.0);
    tenors.push_back(3.0);
    tenors.push_back(5.0);
    tenors.push_back(7.0);

    BSpline bs(tenors, true);

    // Test for the value function
    {
        // Test for order 0
        cout << "Test for order 0" << endl;
        cout << "value (0.1, 0, 3) = " << bs.value(0.1, 0, 3) << endl;
        cout << "value (-0.1, 0, 3) = " << bs.value(-0.1, 0, 3) << endl;
        cout << "value (0.1, 0, 4) = " << bs.value(0.1, 0, 4) << endl;
        cout << "value (0.25, 0, 3) = " << bs.value(0.25, 0, 3) << endl;
        cout << "value (0.25, 0, 4) = " << bs.value(0.25, 0, 4) << endl;
        cout << endl;
        
        // Test for order 1
        cout << "Test for order 1" << endl;
        cout << "value (0.1, 1, 3) = " << bs.value(0.1, 1, 3) << endl;
        cout << "value (0.25, 1, 3) = " << bs.value(0.25, 1, 3) << endl;
        cout << "value (0.49, 1, 3) = " << bs.value(0.49, 1, 3) << endl;
        cout << "value (0.51, 1, 3) = " << bs.value(0.51, 1, 3) << endl;
        cout << "value (0.51, 1, 4) = " << bs.value(0.51, 1, 4) << endl;
        cout << endl;

        // Test for order 2
        cout << "Test for order 1" << endl;
        cout << "value (0.1, 2, 3) = " << bs.value(0.1, 2, 3) << endl;
        cout << "value (0.26, 2, 3) = " << bs.value(0.26, 2, 3) << endl;
        cout << endl;

        // Test for derivative
        cout << "Test for derivative" << endl;
        cout << "deriv (0.1, 0, 3) = " << bs.first_deriv(0.1, 0, 3) << endl;
        cout << "deriv (0.1, 1, 3) = " << bs.first_deriv(0.1, 1, 3) << endl;
        cout << "deriv (0.25, 1, 3) = " << bs.first_deriv(0.25, 1, 3) << endl;
        cout << "deriv (0.26, 1, 3) = " << bs.first_deriv(0.26, 1, 3) << endl;
        cout << "second deriv (0.26, 1, 3) = " << bs.second_deriv(0.26, 1, 3) << endl;
        cout << endl;
        
        // Test for boundry values
        cout << "Test for boundary values" << endl;
        cout << "value (-5.0, 0, 3) = " << bs.value(-5.0, 0, 3) << endl;
        cout << "value (-6.0, 0, 3) = " << bs.value(-6.0, 0, 3) << endl;
        cout << endl;
    }
    
}
