#include "../include/Swap.hpp"
//#include <Swap.hpp>
#include <cmath>
#include <iostream>

using namespace std;

void
Swap::generateDate()
{
	unsigned int floatingCouponTimes;
	double epson = 0.0000000001;

	floatingCouponTimes = floor((_endDate - _startDate) / 0.25 + epson);

	for(unsigned int i = 1; i <= floatingCouponTimes; i++)
	{
		floatingLegDate.push_back(_startDate + i*0.25);
	}

	unsigned int fixedCouponTimes;
	fixedCouponTimes = int((_endDate - _startDate) / 0.5);
	for(unsigned int i = 1; i <= fixedCouponTimes; i++)
	{
		fixedLegDate.push_back(_startDate + i * 0.5);
	}
}

double
Swap::CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const
{
	double floatingLegDelta_t = 0.25;
	double fixedLegDelta_t = 0.5;

	double fixedLegDistcountSum = 0;

	for(std::vector<double>::const_iterator it = fixedLegDate.begin(); it != fixedLegDate.end(); it++)
	{
		fixedLegDistcountSum += OIS.forward_discount_factor(0, *it);
	}

	double floatingLegDistcountSum = 0;

	for(std::vector<double>::const_iterator it = floatingLegDate.begin(); it != floatingLegDate.end(); it++)
	{
		floatingLegDistcountSum += LIBOR.forward_rate((*it - 0.25), *it) * OIS.forward_discount_factor(0, *it);
	}

	if(fixedLegDistcountSum == 0){
		cout << "For LIBORSwap, the fixed leg discount factors' sum is zero, which means the fixing leg doesn't need"
				" to pay anything. So, we return the Swap rate as ZERO." << endl;
		return 0;
	}

	double result = 0;
	result = floatingLegDelta_t * floatingLegDistcountSum / (fixedLegDelta_t * fixedLegDistcountSum);

	return result;
}

double 
Swap::CalSwapPV(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS, const double marketFixedRate) const
{	// Fixed rate receiver.

	double floatingLegDelta_t = 0.25;
	double fixedLegDelta_t = 0.5;

	double fixedLegPV = 0;

	for (std::vector<double>::const_iterator it = fixedLegDate.begin(); it != fixedLegDate.end(); it++)
	{
		fixedLegPV += OIS.forward_discount_factor(0, *it);
	}
	fixedLegPV *= fixedLegDelta_t * marketFixedRate;

	double floatingLegPV = 0;

	for (std::vector<double>::const_iterator it = floatingLegDate.begin(); it != floatingLegDate.end(); it++)
	{
		floatingLegPV += LIBOR.forward_rate((*it - 0.25), *it) * OIS.forward_discount_factor(0, *it);
	}
	floatingLegPV *= floatingLegPV;

	double result = 0;
	result = fixedLegPV - floatingLegPV;

	return result;
}