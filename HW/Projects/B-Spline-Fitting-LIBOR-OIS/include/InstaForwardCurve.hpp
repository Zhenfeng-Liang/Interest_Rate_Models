/*
 * InstaForwardCurve.hpp
 *
 *  Created on: Mar 22, 2015
 *      Author: jose
 */

#ifndef InstaForwardCurve_HPP_
#define InstaForwardCurve_HPP_

#include <vector>
#include <map>

#include "BSpline.hpp"

class InstaForwardCurve
{
public:

    struct InstaCurveDoubleBoundsPropertyCacheKey
    {
    	InstaCurveDoubleBoundsPropertyCacheKey(
            const double rlowerBound,
            const double rupperBound
            )
            : lowerBound(rlowerBound),
              upperBound(rupperBound)
            {}

        bool operator<(const InstaCurveDoubleBoundsPropertyCacheKey & rhs) const {
            return value() < rhs.value();
        }

        double value() const {
            return lowerBound + upperBound * 10.0;
        }

        double lowerBound;
        double upperBound;
    };

    // Data type to cache two variables property
    typedef std::map<InstaCurveDoubleBoundsPropertyCacheKey, double> DoubleBoundPropertyCache;
    typedef DoubleBoundPropertyCache::const_iterator DoubleBoundPropertyCacheIter;

    // Data type to cache one variable property
    typedef std::map<double, double> OneBoundPropertyCache;
    typedef OneBoundPropertyCache::const_iterator OneBoundPropertyCacheIter;


	InstaForwardCurve(
            const std::vector<double> & tenors,
            const std::vector<double> & coeff,
            const unsigned int order,
            const bool cache = true
		 )
    	 : _tenors(tenors),
		   _coeff(coeff),
		   _order(order),
		   B(tenors),
		   _cache(cache)
    	{
			forwardRateCache.clear();
			forwardDiscountFactorCahe.clear();
			integralCache.clear();
			valueCache.clear();
			firstDerivCache.clear();
			secondDerivCache.clear();
    	}


	double value(const double time) const;

	double integral(
			const double lowerBound,
			const double upperBound
			) const;

	double first_deriv(const double time) const;

	double second_deriv(const double time) const;

	double integral_second_deriv_square(
			const double lowerBound,
			const double upperBound
			) const;

	double forward_rate(
			const double S,
			const double T
			) const;

	double forward_discount_factor(
			const double S,
			const double T
			) const;

    void set_coeffs(const std::vector<double> & rhs)
        {
			forwardRateCache.clear();
			forwardDiscountFactorCahe.clear();
			integralCache.clear();
			valueCache.clear();
			firstDerivCache.clear();
			secondDerivCache.clear();
            _coeff = rhs;
        }

    const std::vector<double> & get_coeffs() const
        {
            return _coeff;
        }

private:

	std::vector<double> _tenors;
	std::vector<double> _coeff;
	unsigned int _order;
	BSpline B;

	bool _cache;

	// Cache we use to store the double boundaries properties
	mutable DoubleBoundPropertyCache forwardRateCache;
	mutable DoubleBoundPropertyCache forwardDiscountFactorCahe;
	mutable DoubleBoundPropertyCache integralCache;
	mutable DoubleBoundPropertyCache integralSecondDerivSquareCache;

	// Cache we use to store the one boundary property
	mutable OneBoundPropertyCache valueCache;
	mutable OneBoundPropertyCache firstDerivCache;
	mutable OneBoundPropertyCache secondDerivCache;

	double integralTwoBSplineSecondDerivProduct (
			const double lowerBound,
			const double upperBound,
			const int k,
			const int l
			) const;

	double integralBSplineFromInfinite(
			const double upperBound,
			const int k
			) const;

	double integralBSplineWithBounds(
			const double lowerBound,
			const double upperBound,
			const int k
			) const;

};


#endif /* InstaForwardCurve_HPP_ */
