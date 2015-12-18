
#ifndef EXCELINNER_HPP_
#define EXCELINNER_HPP_

#include <vector>

typedef std::vector<double> KnotPoints;
typedef std::vector< std::vector<double> > CurveCoeff;
typedef std::vector< std::vector<double> > InstrumentsParam;


/*
KnotPoints:
		One dimentional vector with knotPoints

	CurveCoeff:  (Notice: Make sure you have same number of coeff and knot points)
		First col: LIBOR coeff
		Second col: OIS coeff

	InstrumentsParam:	(Notice: your date input should be fraction number from the value date)
		LIBORForward, OISForward, Swap, Basis Swap, EDFutures:
		First col: start date
		Second col: end date
		Third col: market rate
*/
CurveCoeff 
fitCurve(const KnotPoints & knot_points,
	const CurveCoeff & guess,
	const InstrumentsParam & LIBORForward,
	const InstrumentsParam & OISForward,
	const InstrumentsParam & EDFutures,
	const InstrumentsParam & Swap,
	const InstrumentsParam & BasisSwap
	);


double
cal_InstantaneousRate(const double time,
				const std::vector<double> & tenors,
				const std::vector<double> & curveCoeff
				);

double
cal_discountFactor(const double start,
				const double end,
				const std::vector<double> & tenors,
				const std::vector<double> & oisCoeff
				);

double
cal_forwardLIBORrate(const double start,
				const double end,
				const std::vector<double> & tenors,
				const std::vector<double> & LIBORCoeff
				);

double
cal_swapRate(const double start,
				const double end,
				const std::vector<double> & tenors,
				const std::vector<double> & LIBORCoeff,
				const std::vector<double> & OISCoeff
				);

double 
cal_swapPV(const double start,
	const double end,
	const std::vector<double> & tenors,
	const std::vector<double> & LIBORCoeff,
	const std::vector<double> & OISCoeff,
	const double martetRate
	);

#endif