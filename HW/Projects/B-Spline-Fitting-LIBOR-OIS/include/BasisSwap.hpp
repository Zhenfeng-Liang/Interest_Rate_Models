/*
 * BasisSwap.hpp
 *
 *  Created on: Mar 22, 2015
 *      Author: jose
 */

#ifndef BASISSWAP_HPP_
#define BASISSWAP_HPP_

#include "IRInstruments.hpp"

class BasisSwap : public IRInstruments
{
public:

	BasisSwap(double startDate, double endDate)
            : IRInstruments(startDate, endDate) {
            generateDate();
	}

	double CalRate(const InstaForwardCurve& LIBOR, const InstaForwardCurve& OIS) const;

private:
	std::vector<double> paymentDate;
	void generateDate();
};

#endif /* BASISSWAP_HPP_ */
