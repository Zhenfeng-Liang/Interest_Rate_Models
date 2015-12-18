/*
 * Swap.hpp
 *
 *  Created on: Mar 22, 2015
 *      Author: jose
 */

#ifndef SWAP_HPP_
#define SWAP_HPP_

#include <vector>
#include <cmath>

#include "IRInstruments.hpp"

class Swap : public IRInstruments
{
public:

	Swap(double startDate, double endDate)
		: IRInstruments(startDate, endDate) {

		generateDate();
	}

	double CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const;

	// Fixed rate receiver
	double CalSwapPV(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS, const double marketFixedRate) const;

private:
	std::vector<double> floatingLegDate;
	std::vector<double> fixedLegDate;
	void generateDate();
};


#endif /* SWAP_HPP_ */
