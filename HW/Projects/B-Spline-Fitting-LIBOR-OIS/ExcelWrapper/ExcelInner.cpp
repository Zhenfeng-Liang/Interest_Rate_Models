
#include <vector>

#include "ExcelInner.hpp"
#include "../include/CurveStripper.hpp"
#include "../include/InstaForwardCurve.hpp"
#include "../include/Swap.hpp"

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
typedef std::vector<double> KnotPoints;
typedef std::vector< std::vector<double> > CurveCoeff;
typedef std::vector< std::vector<double> > InstrumentsParam;


CurveCoeff fitCurve(const KnotPoints & knot_points,
	const CurveCoeff & guess,
	const InstrumentsParam & LIBORForward,
	const InstrumentsParam & OISForward,
	const InstrumentsParam & EDFutures,
	const InstrumentsParam & Swap,
	const InstrumentsParam & BasisSwap
	)
{
	// Initialization
	KnotPoints tenors = knot_points;

	std::vector<double> LIBORGuess;
	std::vector<double> OISGuess;

	std::vector<std::vector<double> >::const_iterator coeffIter = guess.begin();

	// Initialiaze LIBOR guess
	for (std::vector<double>::const_iterator liborIter = coeffIter->begin(); liborIter != coeffIter->end(); liborIter++)
	{
		LIBORGuess.push_back(*liborIter);
	}

	// Advanced to the OIS coeff
	coeffIter++;

	for (std::vector<double>::const_iterator oisIter = coeffIter->begin(); oisIter != coeffIter->end(); oisIter++)
	{
		OISGuess.push_back(*oisIter);
	}


	std::vector<InstrumentParam> instruments;
	InstrumentParam::InstrumentType type;
	InstrumentParam tmp;

	{
		// Initialize LIBORForwardRate
		type = InstrumentParam::LIBORForwardRate;
		size_t numOfIntruments = LIBORForward[0].size();
		for (unsigned int i = 0; i < numOfIntruments; i++)
		{
			tmp.setter(LIBORForward[0][i], LIBORForward[1][i], LIBORForward[2][i], type);
			instruments.push_back(tmp);
		}
	}


	{
		// Initialize OISForwardRate
		type = InstrumentParam::OISForwardRate;
		size_t numOfIntruments = OISForward[0].size();
		for (unsigned int i = 0; i < numOfIntruments; i++)
		{
			tmp.setter(OISForward[0][i], OISForward[1][i], OISForward[2][i], type);
			instruments.push_back(tmp);
		}
	}


	{
		// Initialize EDFutures
		type = InstrumentParam::EDFuture;
		size_t numOfIntruments = EDFutures[0].size();
		for (unsigned int i = 0; i < numOfIntruments; i++)
		{
			tmp.setter(EDFutures[0][i], EDFutures[1][i], EDFutures[2][i], type);
			instruments.push_back(tmp);
		}
	}


	{
		// Initialize Swap
		type = InstrumentParam::LIBORSwap;
		size_t numOfIntruments = Swap[0].size();
		for (size_t i = 0; i < numOfIntruments; i++)
		{
			tmp.setter(Swap[0][i], Swap[1][i], Swap[2][i], type);
			instruments.push_back(tmp);
		}
	}


	{
		// Initialize Basis Swap
		type = InstrumentParam::BasisSwap;
		size_t numOfIntruments = BasisSwap[0].size();
		for (size_t i = 0; i < numOfIntruments; i++)
		{
			tmp.setter(BasisSwap[0][i], BasisSwap[1][i], BasisSwap[2][i], type);
			instruments.push_back(tmp);
		}
	}

	CurveStripper fitter(
		instruments,
		tenors,
		LIBORGuess,
		OISGuess
		);

	CurveCoeff optimizedCoeff;

	fitter.strip_curve(optimizedCoeff);

	return optimizedCoeff;
}

double
cal_InstantaneousRate(const double time,
					const std::vector<double> & tenors,
					const std::vector<double> & curveCoeff
					)
{
	InstaForwardCurve ois(tenors, curveCoeff, 3);

	double result;
	result = ois.value(time);
	return result;
}

double
cal_discountFactor(const double start,
				const double end,
				const std::vector<double> & tenors,
				const std::vector<double> & oisCoeff
				)
{
	InstaForwardCurve ois(tenors, oisCoeff, 3);

	double result;
	result = ois.forward_discount_factor(start, end);
	return result;
}

double
cal_forwardLIBORrate(const double start,
				const double end,
				const std::vector<double> & tenors,
				const std::vector<double> & LIBORCoeff
				)
{
	InstaForwardCurve libor(tenors, LIBORCoeff, 3);

	double result;
	result = libor.forward_rate(start, end);
	return result;
}


double
cal_swapRate(const double start,
			const double end,
			const std::vector<double> & tenors,
			const std::vector<double> & LIBORCoeff,
			const std::vector<double> & OISCoeff
			)
{
	InstaForwardCurve libor(tenors, LIBORCoeff, 3);
	InstaForwardCurve ois(tenors, OISCoeff, 3);

	Swap tmp(start, end);
	
	double result;
	result = tmp.CalRate(libor, ois);
	return result;
}

double 
cal_swapPV(const double start,
		const double end,
		const std::vector<double> & tenors,
		const std::vector<double> & LIBORCoeff,
		const std::vector<double> & OISCoeff,
		const double martetRate
		)
{
	InstaForwardCurve libor(tenors, LIBORCoeff, 3);
	InstaForwardCurve ois(tenors, OISCoeff, 3);
	Swap tmp(start, end);
	double result;
	result = tmp.CalSwapPV(libor, ois, martetRate);
	return result;
}