/*
 * LIBORForwardRate.hpp
 *
 *  Created on: Mar 22, 2015
 *      Author: jose
 */

#ifndef LIBORFORWARDRATE_HPP_
#define LIBORFORWARDRATE_HPP_

#include "IRInstruments.hpp"

class LIBORForwardRate : public IRInstruments
{
public:

	LIBORForwardRate(double startDate, double endDate)
					: IRInstruments(startDate, endDate) {}

	double CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const;
};

inline double
LIBORForwardRate::CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const
{
	return LIBOR.forward_rate(_startDate, _endDate);
}

#endif /* LIBORFORWARDRATE_HPP_ */
