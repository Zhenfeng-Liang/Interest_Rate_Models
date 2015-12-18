/*
 * OISForwardRate.hpp
 *
 *  Created on: Mar 22, 2015
 *      Author: jose
 */

#ifndef OISFORWARDRATE_HPP_
#define OISFORWARDRATE_HPP_


#include "IRInstruments.hpp"

class OISForwardRate : public IRInstruments
{
public:

	OISForwardRate(double startDate, double endDate)
					: IRInstruments(startDate, endDate) {}

	double CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const;
};

inline double
OISForwardRate::CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const
{
	return OIS.forward_rate(_startDate, _endDate);
}


#endif /* OISFORWARDRATE_HPP_ */
