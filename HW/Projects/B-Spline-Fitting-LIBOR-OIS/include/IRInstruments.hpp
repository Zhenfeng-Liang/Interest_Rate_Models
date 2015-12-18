/*
 * IRInstruments.hpp
 *
 *  Created on: Mar 22, 2015
 *      Author: jose
 */

#ifndef IRINSTRUMENTS_HPP_
#define IRINSTRUMENTS_HPP_

#include "InstaForwardCurve.hpp"

class IRInstruments
{
public:

	IRInstruments(double startDate, double endDate)
				: _startDate(startDate), _endDate(endDate){}

	virtual double CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const = 0;

	virtual ~IRInstruments() {}

	// Member data
	// "Public" makes it easier for access the member data,
	// but be careful
	double _startDate;
	double _endDate;
};


#endif /* IRINSTRUMENTS_HPP_ */
