/*
 * TestInstaForwardCurve.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: jose
 */



#include "InstaForwardCurve.hpp"
#include <vector>
#include <iostream>

#include "LIBORForwardRate.hpp"
#include "OISForwardRate.hpp"
#include "EDFutures.hpp"
#include "Swap.hpp"
#include "BasisSwap.hpp"

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

    std::vector<double> coeff;
    coeff.push_back(1);
    coeff.push_back(2);
    coeff.push_back(3);
    coeff.push_back(1);
    coeff.push_back(1);
    coeff.push_back(1);
    coeff.push_back(1);
    coeff.push_back(1);
    coeff.push_back(1);
    coeff.push_back(1);
    coeff.push_back(2);

    InstaForwardCurve LIBOR(tenors, coeff, 3);

/*    cout << LIBOR.value(0.5) << endl;
    cout << LIBOR.first_deriv(0.5) << endl;
    cout << LIBOR.second_deriv(0.5 ) << endl;
    cout << LIBOR.integral(1,3) << endl;

    cout << LIBOR.forward_rate(1, 3) << endl;
    cout << LIBOR.forward_discount_factor(1, 3) << endl;*/

    InstaForwardCurve OIS = LIBOR;

    LIBORForwardRate libor3M(0, 0.25);
    cout << libor3M.CalRate( LIBOR, OIS) << endl;

    OISForwardRate fedfund(0, 1.0/360);
    cout << fedfund.CalRate( LIBOR, OIS) << endl;

    EDFutures fd(1.0/360, 0.25);
    cout << fd.CalRate( LIBOR, OIS) << endl;

    Swap sw(1.0/360, 5);
    cout << sw.CalRate( LIBOR, OIS) << endl;

    BasisSwap bsw(1.0/360, 5);
    cout << bsw.CalRate( LIBOR, OIS) << endl;

	return 0;
}
