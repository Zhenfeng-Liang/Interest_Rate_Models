/*
 * test_BasisSwap.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: jose
 */

#include <BasisSwap.hpp>
#include <InstaForwardCurve.hpp>
#include <vector>
#include <cmath>
#include <iostream>

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
    tenors.push_back(10.0);
    tenors.push_back(15.0);
    tenors.push_back(20.0);
    tenors.push_back(30.0);

    vector<double> guess;
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);
    guess.push_back(1.0);

    InstaForwardCurve LIBOR(tenors, guess, 3);
    InstaForwardCurve OIS(tenors, guess, 3);

    double start = 2.0 / 360.0;
    double end = 90.0/360.0 + start;

    BasisSwap bsw(start, end);
    cout << bsw.CalRate(LIBOR, OIS) << endl;

    double temp = 1.0;
    cout << "Check the result if it takes \"int\" to cast the number." << int(temp) << endl;
    cout << "Check the result if it takes \"floor\" to cast the number." << floor(temp) << endl;

	return 0;
}
