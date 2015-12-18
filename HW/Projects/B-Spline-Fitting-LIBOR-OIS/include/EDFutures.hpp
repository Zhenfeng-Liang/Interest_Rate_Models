/*
 * EDFutures.hpp
 *
 *  Created on: Mar 22, 2015
 *      Author: jose
 */

#ifndef EDFUTURES_HPP_
#define EDFUTURES_HPP_

#include "IRInstruments.hpp"

class EDFutures : public IRInstruments
{/* Following date convention: act/360
	startDate of EDFutures is the maturity day of EDFutures
	endDate of EDFutures is S + act/360
*/

public:

	EDFutures(double startDate, double endDate
			  ) : IRInstruments(startDate, endDate){}

	double CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const;

};

inline double
EDFutures::CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const
{
	return LIBOR.forward_rate(_startDate, _endDate);
}

#endif /* EDFUTURES_HPP_ */
