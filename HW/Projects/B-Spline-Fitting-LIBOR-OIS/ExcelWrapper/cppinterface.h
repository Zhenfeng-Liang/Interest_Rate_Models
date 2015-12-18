//
//
//                                                                    Test.h
//

#ifndef TEST_H
#define TEST_H

#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include <xlw/DoubleOrNothing.h>
#include <xlw/ArgList.h>

using namespace xlw;

//<xlw:libraryname=MyCurveStrippingLibrary


short // echoes a short
EchoShort(short x // number to be echoed
       );

double	// echoes a double
EchoDouble(double x  // number to be echoed
		);

MyMatrix											// Read market data, return a the fitted coeff, first col: LIBOR, second col: OIS
fitCurve(	const MyMatrix & knot_points,			// Format: One column in Excel. Knot points you want to place
			const MyMatrix & guess,					// Format: Two column, first column, LIBOR guess, second column, OIS guess
			const MyMatrix & LIBORForward,			// Format: Three column, start date, end date, market rate
			const MyMatrix & OISForward,			// Format: Three column, start date, end date, market rate
			const MyMatrix & EDFutures,				// Format: Three column, start date, end date, market rate
			const MyMatrix & Swap,					// Format: Three column, start date, end date, market rate
			const MyMatrix & BasisSwap				// Format: Three column, start date, end date, market rate
		);


double												// Calculate the instantaneous rate of given time						
InstantaneousRate(const double time,				// The time point to calculate instantaneous rate
					const MyMatrix & tenors,		// The knot points you place to fit LIBOR and OIS curves
					const MyMatrix & curveCoeff		// Corresponding curve fitted coefficients
					);

double												// Calculate the discount factor between any two dates
discFactor(	const double start,						// Starting time
			const double end,						// Ending time
			const MyMatrix & tenors,				// The knot points you place to fit LIBOR and OIS curves
			const MyMatrix & oisCoeff				// OIS fitted coefficient
			);


double												// Calculate the forward LIBOR rate for any settlement and underlying tenor
LIBORForwardRate(const double start,				// Starting time
				const double end,					// Ending time
				const MyMatrix & tenors,			// The knot points you place to fit LIBOR and OIS curves
				const MyMatrix & liborCoeff			// LIBOR fitted coefficient
				);


double												// Calculate the swap rate for any settlement and underlying ternor
swapRate(const double start,						// Starting time
		const double end,							// Ending time
		const MyMatrix & tenors,					// The knot points you place to fit LIBOR and OIS curves
		const MyMatrix & liborCoeff,				// LIBOR fitted coefficient
		const MyMatrix & oisCoeff					// OIS fitted coefficient
		);

double												// Calculate the PV of any spot or forward starting swap based on the fitted curves
swapPV(const double start,							// Starting time
	const double end,								// Ending time
	const MyMatrix & tenors,						// The knot points you place to fit LIBOR and OIS curves
	const MyMatrix & liborCoeff,					// LIBOR fitted coefficient
	const MyMatrix & oisCoeff,						// OIS fitted coefficient
	const double marketRate							// Market quote
);


#endif
