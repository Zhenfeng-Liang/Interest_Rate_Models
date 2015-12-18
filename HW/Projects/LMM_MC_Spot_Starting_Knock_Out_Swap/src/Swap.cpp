/*
 * Swap.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: jose
 */


#include <Swap.hpp>
#include <iostream>
using namespace std;

double
Swap::cal_fixed_rate(
        const ForwardRateSeries & libor,
        const ForwardRateSeries & ois,
        bool NoSpread
        ) const
{
    double result = 0;
    double sumDiscountFactor = 0;

    double epsilon = 0.000000001;
    size_t numPoints = size_t (_tenor / _delta_floating + epsilon);

    if(NoSpread){
        double discountFactor = 1;

        for(size_t i = 0; i < numPoints - 1; i = i+2){

            discountFactor *= 1 / (1 + _delta_floating * ois.rate(i)) * 1 / (1 + _delta_floating * ois.rate(i+1));
            sumDiscountFactor += discountFactor;
        }
        result = (1 - discountFactor) / (_delta_fixed * sumDiscountFactor);
    }
    else{ // If there is some spread here, we can not use the formula above,
      // add implementation
        sumDiscountFactor = 1;
    }

    return result;
}

// We use the martingale property here, use the Floating leg expected PV divided by the fixed leg
// expected annuity
double
KnockOutSwap::MC_Cal_fixed_rate(
        const std::vector<RatePath> & libor_path,
        const std::vector<RatePath> & ois_path
        ) const
{
    size_t numSim = libor_path.size();
    double expectedFloatingLegPV = 0.0;
    double expectedFixedLegAnnuity = 0.0;

    for(size_t i = 0; i < numSim; i++)
    {
        const std::vector<ForwardRateSeries> & libor_vec = libor_path[i].forward_series_vec();
        const std::vector<ForwardRateSeries> & ois_vec = ois_path[i].forward_series_vec();
        size_t terminateIndex = terminate_time_index(libor_vec, ois_vec);
        expectedFloatingLegPV += cal_floatingLegPV(terminateIndex, libor_vec, ois_vec);
        expectedFixedLegAnnuity += cal_fixedLegAnnuity(terminateIndex, ois_vec);
    }


    // We could delete these two lines of codes since we are going to divide these two statements.
//    expectedFloatingLegPV /= numSim;
//    expectedFixedLegAnnuity /= numSim;

    double r_fixed = expectedFloatingLegPV / expectedFixedLegAnnuity;

    return r_fixed;
}

size_t
KnockOutSwap::terminate_time_index(
        const std::vector<ForwardRateSeries> & libor_vec,
        const std::vector<ForwardRateSeries> & ois_vec
        ) const
{
    size_t len = libor_vec.size();

    // Index to store when to terminate
    size_t i;

    // Only check for the fixed coupon date
    for(i = 2; i < len; i = i + 2)
    {
        const ForwardRateSeries & liborSeries = libor_vec[i];
        const ForwardRateSeries & oisSeries = ois_vec[i];

        double _innerFixedRate = _innerSwap.cal_fixed_rate(liborSeries, oisSeries);

        if(_innerFixedRate < _barrier){
            break;
        }
    }

    // If not terminate earlier, it would terminate at maturity
    if(i > len || i == len){
        i = len - 1;
    }

    return i;
}

double
KnockOutSwap::terminal_discount_factor(
		const ForwardRateSeries & oisSeries
		) const
{
    double discFactor = 1.0;
    size_t numRatesToTerminal = oisSeries.length();
    for(size_t i = 0; i < numRatesToTerminal; i++)
    {
        discFactor *= 1/(1 + _delta_floating * oisSeries.rate(i));
    }

    return discFactor;
}

// Calculate one path of floating leg PV, for the purpose of using martingale property
double
KnockOutSwap::cal_floatingLegPV(
		const size_t terminateIndex,
		const std::vector<ForwardRateSeries> & libor_vec,
		const std::vector<ForwardRateSeries> & ois_vec
		) const
{
    double floatingLegPV = 0.0;
    for(size_t i = 0; i < terminateIndex; i++)
    {
        double resetRate = libor_vec[i].rate(0);
        floatingLegPV += resetRate / terminal_discount_factor(ois_vec[i+1]);
    }
    floatingLegPV *= _delta_floating;

    // This could be deleted because this will cancel out once I divide this by the fixedLegAnnuity
//    floatingLegPV *= terminal_discount_factor(ois_vec[0]);

    return floatingLegPV;
}


double
KnockOutSwap::cal_fixedLegAnnuity(
		const size_t terminateIndex,
		const std::vector<ForwardRateSeries> & ois_vec
		) const
{
    double fixedLegAnnuity = 0.0;
    for(size_t j = 2; j <= terminateIndex; j = j + 2)
    {
        fixedLegAnnuity += 1 / terminal_discount_factor(ois_vec[j]);
    }
    fixedLegAnnuity *= _delta_fixed;

    // This could be deleted because this will cancel out once I the floating leg PV divided by this one
//    fixedLegAnnuity *= terminal_discount_factor(ois_vec[0]);

    return fixedLegAnnuity;
}


/*
 *  The following class is using the expectation of the fixed rate, which should be wrong.
 *  I am leaving the code here for further verification
 */
/*
double
KnockOutSwap::MC_Cal_fixed_rate(
        const std::vector<RatePath> & libor_path,
        const std::vector<RatePath> & ois_path
		) const
{
	size_t numSim = libor_path.size();
	double sumResult = 0;

	for(size_t i = 0; i < numSim; i++)
	{
		const std::vector<ForwardRateSeries> & libor_vec = libor_path[i].forward_series_vec();
		const std::vector<ForwardRateSeries> & ois_vec = ois_path[i].forward_series_vec();
		sumResult += cal_fixed_rate(libor_vec, ois_vec);
	}
	double result = sumResult / numSim;

	return result;
}


size_t
KnockOutSwap::terminate_time_index(
		const std::vector<ForwardRateSeries> & libor_vec,
		const std::vector<ForwardRateSeries> & ois_vec
		) const
{
	size_t len = libor_vec.size();

	// Index to store when to terminate
	size_t i;

	for(i = 2; i < len; i = i + 2)
	{
		const ForwardRateSeries & liborSeries = libor_vec[i];
		const ForwardRateSeries & oisSeries = ois_vec[i];

		double _innerFixedRate = _innerSwap.cal_fixed_rate(liborSeries, oisSeries);

		if(_innerFixedRate < _barrier){
			break;
		}
	}

	return i;
}

double
KnockOutSwap::terminal_discount_factor(
		const size_t numRatesToTerminal,
		const ForwardRateSeries & oisSeries
		) const
{
	double discFactor = 1.0;

	for(size_t i = 0; i < numRatesToTerminal; i++)
	{
		discFactor *= 1/(1 + _delta_floating * oisSeries.rate(i));
	}

	// Need to be edited here.
	return discFactor;
}


double
KnockOutSwap::cal_fixed_rate(
		const std::vector<ForwardRateSeries> & libor_vec,
		const std::vector<ForwardRateSeries> & ois_vec
		) const
{
	size_t terminateIndex = terminate_time_index(libor_vec, ois_vec);

	double epsilon = 0.000000001;
	size_t numRateToTerminal = size_t(_tenor / _delta_floating + epsilon);

	double fixedLegDiscFactor_reciprocal = 0;
	double floatingLegPV = 0;

	for(size_t i = 0; i < terminateIndex; i++)
	{
		double resetRate = libor_vec[i].rate(0);
		floatingLegPV += resetRate / terminal_discount_factor(numRateToTerminal - (i + 1), ois_vec[i+1]);
	}
	floatingLegPV *= _delta_floating;

	for(size_t j = 2; j <= terminateIndex; j = j + 2)
	{
		fixedLegDiscFactor_reciprocal += 1 / terminal_discount_factor(numRateToTerminal - j, ois_vec[j]);
	}
	fixedLegDiscFactor_reciprocal *= _delta_fixed;

	double result = 0;
	result = floatingLegPV / fixedLegDiscFactor_reciprocal;


	return result;
}
*/
