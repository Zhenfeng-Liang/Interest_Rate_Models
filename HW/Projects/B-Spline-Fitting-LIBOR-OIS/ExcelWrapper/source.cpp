
#include<cppinterface.h>
#pragma warning (disable : 4996)

#include <algorithm>

#include "../../include/ExcelInner.hpp"

short // echoes a short
EchoShort(short x // number to be echoed
           )
{
    return x;
}

double	// echoes a double
EchoDouble(double x  // number to be echoed
			)
{
	return x;
}


std::vector<std::vector< double> > 
XLWMatrixToSTLVecOfVec( const MyMatrix & m	// Matrix need to be changed
	)
{
	size_t row = m.rows();
	size_t col = m.columns();

	std::vector< std::vector<double> > stlvec;

	for (size_t c_iter = 0; c_iter < col; c_iter++)
	{
		std::vector<double> column;
		for (size_t r_iter = 0; r_iter < row; r_iter++)
		{
			column.push_back(m(r_iter, c_iter));
		}
		stlvec.push_back(column);
	}

	return stlvec;
}

std::vector<double> 
XLWMatrixToSTLVec( const MyMatrix & m	// Matrix need to be changed
	)
{
	size_t row = m.rows();
	size_t col = m.columns();

	size_t size = std::max(row, col);

	std::vector<double> vec;
	for (size_t i = 0; i < size; i++)
	{
		if (row > col)
			vec.push_back(m(i, 0));
		else
			vec.push_back(m(0, i));
	}
	return vec;
}


MyMatrix			// Change a vector of vector to XLW Matrix
STLVecOfVecToXLWMatrix( const std::vector<std::vector<double> > & VecOfVec  
)
{
	size_t col = VecOfVec.size();
	size_t row = VecOfVec[0].size();

	MyMatrix result(row, col);

	for (size_t i = 0; i < col; i++)
	{
		for (size_t j = 0; j < row; j++)
		{
			// DOUBLE CHECK HERE
			result(j, i) = VecOfVec[i][j];
		}
	}

	return result;
}

MyMatrix											// Read market data, return a the fitted coeff, first col: LIBOR, second col: OIS 
fitCurve(	const MyMatrix & knot_points,			// Format: One column in Excel. Knot points you want to place
			const MyMatrix & guess,					// Format: Two column, first column, LIBOR guess, second column, OIS guess
			const MyMatrix & LIBORForward,			// Format: Three column, start date, end date, market rate
			const MyMatrix & OISForward,			// Format: Three column, start date, end date, market rate
			const MyMatrix & EDFutures,				// Format: Three column, start date, end date, market rate
			const MyMatrix & Swap,					// Format: Three column, start date, end date, market rate
			const MyMatrix & BasisSwap				// Format: Three column, start date, end date, market rate
)
{
	// Change the data format
	std::vector<double> tenors = XLWMatrixToSTLVec(knot_points);
	std::vector<std::vector<double> > coeffGuess = XLWMatrixToSTLVecOfVec(guess);
	std::vector<std::vector<double> > liborParam = XLWMatrixToSTLVecOfVec(LIBORForward);
	std::vector<std::vector<double> > oisParam = XLWMatrixToSTLVecOfVec(OISForward);
	std::vector<std::vector<double> > EDFuturesParam = XLWMatrixToSTLVecOfVec(EDFutures);
	std::vector<std::vector<double> > swapParam = XLWMatrixToSTLVecOfVec(Swap);
	std::vector<std::vector<double> > basisSwapParam = XLWMatrixToSTLVecOfVec(BasisSwap);

	CurveCoeff fittedCoeff = fitCurve(tenors,
									coeffGuess,
									liborParam,
									oisParam,
									EDFuturesParam,
									swapParam,
									basisSwapParam
									);
	
	MyMatrix result = STLVecOfVecToXLWMatrix(fittedCoeff);

	return result;
}

double
InstantaneousRate(const double time,
					const MyMatrix & tenors,
					const MyMatrix & curveCoeff
				 )
{
	std::vector<double> knot_points = XLWMatrixToSTLVec(tenors);
	std::vector<double> CoeffVec = XLWMatrixToSTLVec(curveCoeff);

	double result;
	result = cal_InstantaneousRate(time, knot_points, CoeffVec);
	return result;
}

double
discFactor(const double start,
			const double end,
			const MyMatrix & tenors,
			const MyMatrix & oisCoeff
			)
{
	std::vector<double> knot_points = XLWMatrixToSTLVec(tenors);
	std::vector<double> OISCoeffVec = XLWMatrixToSTLVec(oisCoeff);

	double result;
	result = cal_discountFactor(start, end, knot_points, OISCoeffVec);
	return result;
}

double
LIBORForwardRate(const double start,
				const double end,
				const MyMatrix & tenors,
				const MyMatrix & liborCoeff
				)
{
	std::vector<double> knot_points = XLWMatrixToSTLVec(tenors);
	std::vector<double> LIBORCoeffVec = XLWMatrixToSTLVec(liborCoeff);

	double result;
	result = cal_forwardLIBORrate(start, end, knot_points, LIBORCoeffVec);
	return result;
}


double
swapRate(const double start,
		const double end,
		const MyMatrix & tenors,
		const MyMatrix & liborCoeff,
		const MyMatrix & oisCoeff
		)
{
	std::vector<double> knot_points = XLWMatrixToSTLVec(tenors);
	std::vector<double> LIBORCoeffVec = XLWMatrixToSTLVec(liborCoeff);
	std::vector<double> OISCoeffVec = XLWMatrixToSTLVec(oisCoeff);

	double result;
	result = cal_swapRate(start, end, knot_points, LIBORCoeffVec, OISCoeffVec);
	return result;
}


double
swapPV(const double start,
	const double end,
	const MyMatrix & tenors,
	const MyMatrix & liborCoeff,
	const MyMatrix & oisCoeff,
	const double marketRate
	)
{
	std::vector<double> knot_points = XLWMatrixToSTLVec(tenors);
	std::vector<double> LIBORCoeffVec = XLWMatrixToSTLVec(liborCoeff);
	std::vector<double> OISCoeffVec = XLWMatrixToSTLVec(oisCoeff);

	double result;
	result = cal_swapPV(start, end, knot_points, LIBORCoeffVec, OISCoeffVec, marketRate);
	return result;
}
