/*
 * InstaForwardCurve.cpp
 *
 *  Created on: Mar 22, 2015
 *      Author: jose
 */


//#include "InstaForwardCurve.hpp"
#include "../include/InstaForwardCurve.hpp"
#include <cmath>
#include <map>

using namespace std;

/*
InstaForwardCurve::InstaForwardCurve(
    const std::vector<double> & tenors,
    const std::vector<double> & coeff,
    const unsigned int order,
    const bool cache = true
    )
    : _tenors(tenors), _coeff(coeff), _order(order), B(tenors), _cache(cache)
{
}
*/

double
InstaForwardCurve::value(const double time) const
{
	double key = time;
	OneBoundPropertyCacheIter iter = valueCache.find(key);
    if (_cache && iter != valueCache.end())
    {
        return iter->second;
    }

	double result = 0;
	size_t n = _tenors.size();

	for (size_t k = 0; k < n; k++)
	{
		result += _coeff[k] * B.value(time, _order, k);
	}

    if (_cache)
    {
    	valueCache.insert(make_pair(key, result));
    }

	return result;
}


double
InstaForwardCurve::integral(
		const double lowerBound,
		const double upperBound
		) const
{
	InstaCurveDoubleBoundsPropertyCacheKey key(lowerBound, upperBound);
	DoubleBoundPropertyCacheIter iter = integralCache.find(key);

    if (_cache && iter != integralCache.end())
    {
        return iter->second;
    }

	size_t n = _tenors.size();

	double result = 0;
	for (size_t i = 0; i < n; i++)
	{
		result += _coeff[i] * integralBSplineWithBounds(lowerBound, upperBound, i);
	}

    if (_cache)
    {
    	integralCache.insert(make_pair(key, result));
    }

	return result;
}

double
InstaForwardCurve::first_deriv(const double time) const
{
	double key = time;
	OneBoundPropertyCacheIter iter = firstDerivCache.find(key);
    if (_cache && iter != firstDerivCache.end())
    {
        return iter->second;
    }


	double result = 0;
	const size_t n = _tenors.size();

	for(unsigned int k = 0; k < n; k++)
	{
		result += _coeff[k] * B.first_deriv(time, _order, k);
	}

    if (_cache)
    {
    	firstDerivCache.insert(make_pair(key, result));
    }

	return result;
}

double
InstaForwardCurve::second_deriv(const double time) const
{
	double key = time;
	OneBoundPropertyCacheIter iter = secondDerivCache.find(key);
    if (_cache && iter != secondDerivCache.end())
    {
        return iter->second;
    }

	double result = 0;
	const size_t n = _tenors.size();

	for(unsigned int k = 0; k < n; k++)
	{
		result += _coeff[k] * B.second_deriv(time, _order, k);
	}

	if (_cache)
    {
		secondDerivCache.insert(make_pair(key, result));
    }

	return result;
}

double
InstaForwardCurve::integral_second_deriv_square(
		const double lowerBound,
		const double upperBound
		) const
{

	InstaCurveDoubleBoundsPropertyCacheKey key(lowerBound, upperBound);
	DoubleBoundPropertyCacheIter iter = integralSecondDerivSquareCache.find(key);

    if (_cache && iter != integralSecondDerivSquareCache.end())
    {
        return iter->second;
    }

	double result = 0;

	size_t n = _tenors.size();
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			result += _coeff[i] * _coeff[j] * integralTwoBSplineSecondDerivProduct(lowerBound, upperBound, i, j);
		}
	}

    if (_cache)
    {
    	integralSecondDerivSquareCache.insert(make_pair(key, result));
    }

	return result;
}


double
InstaForwardCurve::forward_rate(
		const double S,
		const double T) const
{
	InstaCurveDoubleBoundsPropertyCacheKey key(S, T);
	DoubleBoundPropertyCacheIter iter = forwardRateCache.find(key);

    if (_cache && iter != forwardRateCache.end())
    {
        return iter->second;
    }

	double delta = T - S;
	double result = (exp(integral(S, T)) - 1) / delta;

    if (_cache)
    {
    	forwardRateCache.insert(make_pair(key, result));
    }

	return result;
}

double
InstaForwardCurve::forward_discount_factor(
		const double S,
		const double T
		) const
{
	InstaCurveDoubleBoundsPropertyCacheKey key(S, T);
	DoubleBoundPropertyCacheIter iter = forwardDiscountFactorCahe.find(key);

	if (_cache && iter != forwardDiscountFactorCahe.end())
    {
        return iter->second;
    }

	double delta = T - S;
	double result = 1 / (1 + delta * forward_rate(S, T));

    if (_cache)
    {
    	forwardDiscountFactorCahe.insert(make_pair(key, result));
    }

	return result;
}

double
InstaForwardCurve::integralTwoBSplineSecondDerivProduct(
		const double lowerBound,
		const double upperBound,
		const int k,
		const int l
		) const
{
	double first_term = B.first_deriv(upperBound, _order, k) * B.second_deriv(upperBound, _order, l);
	double second_term = B.first_deriv(lowerBound, _order, k) * B.second_deriv(lowerBound, _order, l);

	unsigned int lowerIndex = 0;
	unsigned int upperIndex = 0;

	// Return the first index larger than lowerBound
	while(_tenors[lowerIndex] < lowerBound)
		lowerIndex++;

	// upperIndex is larger or equal to the lowerIndex
	upperIndex = lowerIndex;

	// Return the first index larger than upperBound
	while(_tenors[upperIndex] < upperBound)
		upperIndex++;

	double sum_term = 0;

	for(unsigned int j = lowerIndex; j <= upperIndex; j++)
	{
		sum_term += (B.value(_tenors[j], _order, k) - B.value(_tenors[j-1], _order, k)) * B.third_deriv(_tenors[j-1], _order, l);
	}

	double result = first_term - second_term - sum_term;

	return result;
}


double
InstaForwardCurve::integralBSplineFromInfinite(
		const double upperBound,
		const int k
		) const
{
	unsigned int upperIndex = 0;

	// Return the first index whose argument is larger than the upperBound
	// equivalent to (n + 1) from the note
	while(_tenors[upperIndex] < upperBound)
		upperIndex++;

	upperIndex += _order;

	double result = 0;

	for(unsigned int i = k; i <= upperIndex; i++)
	{
		result += (_tenors[k+_order+1] - _tenors[k])/(_order + 1) * B.value(upperBound, _order + 1, i);
	}

	// Need to be edited here.
	return result;
}

double
InstaForwardCurve::integralBSplineWithBounds(
		const double lowerBound,
		const double upperBound,
		const int k
		) const
{
	return integralBSplineFromInfinite(upperBound, k) - integralBSplineFromInfinite(lowerBound, k);
}
