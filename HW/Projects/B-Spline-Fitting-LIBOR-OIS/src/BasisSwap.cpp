#include "../include/BasisSwap.hpp"
//#include <BasisSwap.hpp>
#include <iostream>
#include <cmath>
using namespace std;

void
BasisSwap::generateDate()
{
	size_t paymentTimes;
	double epson = 0.0000000001;

	paymentTimes = floor((_endDate - _startDate) / 0.25 + epson);

	for (size_t i = 1; i <= paymentTimes; i++)
	{
		paymentDate.push_back(_startDate + i*0.25);
	}
}

double
BasisSwap::CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const
{
	double diffLiborOisDistcountSum = 0;
	for(std::vector<double>::const_iterator it = paymentDate.begin(); it != paymentDate.end(); it++)
	{
		diffLiborOisDistcountSum += (LIBOR.forward_rate(*it - 0.25, *it) - OIS.forward_rate(*it - 0.25, *it))
				* OIS.forward_discount_factor(0, *it);
	}

	double discountFactorsum = 0;
	for(std::vector<double>::const_iterator it = paymentDate.begin(); it != paymentDate.end(); it++)
	{
		discountFactorsum += OIS.forward_discount_factor(0, *it);
	}

	if(discountFactorsum == 0)
	{
		cout << "For basis swap, the sum of the spread leg's discount factor is zero. "
				"It means it doesn't pay anything before it expires."
				"Returning ZERO as the spread rate" << endl;
		return 0;
	}

	double result = diffLiborOisDistcountSum / discountFactorsum;

	return result;
}

