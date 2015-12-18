//// 
//// Autogenerated by xlw 
//// Do not edit this file, it will be overwritten 
//// by InterfaceGenerator 
////

#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include "cppinterface.h"
#include <xlw/xlw.h>
#include <xlw/XlFunctionRegistration.h>
#include <stdexcept>
#include <xlw/XlOpenClose.h>
#include <xlw/HiResTimer.h>
using namespace xlw;

namespace {
const char* LibraryName = "MyCurveStrippingLibrary";
};


// registrations start here


namespace
{
XLRegistration::Arg
EchoShortArgs[]=
{
{ "x"," number to be echoed ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoShort("xlEchoShort",
"EchoShort",
" echoes a short ",
LibraryName,
EchoShortArgs,
1
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoShort(
LPXLFOPER xa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xb(
	(xa));
short x(
	xb.AsShort("x"));

short result(
	EchoShort(
		x)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoDoubleArgs[]=
{
{ "x"," number to be echoed ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoDouble("xlEchoDouble",
"EchoDouble",
" echoes a double ",
LibraryName,
EchoDoubleArgs,
1
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoDouble(
double x)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);


double result(
	EchoDouble(
		x)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
fitCurveArgs[]=
{
{ "knot_points"," Format: One column in Excel. Knot points you want to place ","XLF_OPER"},
{ "guess"," Format: Two column, first column, LIBOR guess, second column, OIS guess ","XLF_OPER"},
{ "LIBORForward"," Format: Three column, start date, end date, market rate ","XLF_OPER"},
{ "OISForward"," Format: Three column, start date, end date, market rate ","XLF_OPER"},
{ "EDFutures"," Format: Three column, start date, end date, market rate ","XLF_OPER"},
{ "Swap"," Format: Three column, start date, end date, market rate ","XLF_OPER"},
{ "BasisSwap"," Format: Three column, start date, end date, market rate ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerfitCurve("xlfitCurve",
"fitCurve",
" Read market data, return a the fitted coeff, first col: LIBOR, second col: OIS ",
LibraryName,
fitCurveArgs,
7
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlfitCurve(
LPXLFOPER knot_pointsa,
LPXLFOPER guessa,
LPXLFOPER LIBORForwarda,
LPXLFOPER OISForwarda,
LPXLFOPER EDFuturesa,
LPXLFOPER Swapa,
LPXLFOPER BasisSwapa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper knot_pointsb(
	(knot_pointsa));
MyMatrix knot_points(
	knot_pointsb.AsMatrix("knot_points"));

XlfOper guessb(
	(guessa));
MyMatrix guess(
	guessb.AsMatrix("guess"));

XlfOper LIBORForwardb(
	(LIBORForwarda));
MyMatrix LIBORForward(
	LIBORForwardb.AsMatrix("LIBORForward"));

XlfOper OISForwardb(
	(OISForwarda));
MyMatrix OISForward(
	OISForwardb.AsMatrix("OISForward"));

XlfOper EDFuturesb(
	(EDFuturesa));
MyMatrix EDFutures(
	EDFuturesb.AsMatrix("EDFutures"));

XlfOper Swapb(
	(Swapa));
MyMatrix Swap(
	Swapb.AsMatrix("Swap"));

XlfOper BasisSwapb(
	(BasisSwapa));
MyMatrix BasisSwap(
	BasisSwapb.AsMatrix("BasisSwap"));

MyMatrix result(
	fitCurve(
		knot_points,
		guess,
		LIBORForward,
		OISForward,
		EDFutures,
		Swap,
		BasisSwap)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
InstantaneousRateArgs[]=
{
{ "time"," The time point to calculate instantaneous rate ","B"},
{ "tenors"," The knot points you place to fit LIBOR and OIS curves ","XLF_OPER"},
{ "curveCoeff"," Corresponding curve fitted coefficients ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerInstantaneousRate("xlInstantaneousRate",
"InstantaneousRate",
" Calculate the instantaneous rate of given time ",
LibraryName,
InstantaneousRateArgs,
3
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlInstantaneousRate(
double time,
LPXLFOPER tenorsa,
LPXLFOPER curveCoeffa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);


XlfOper tenorsb(
	(tenorsa));
MyMatrix tenors(
	tenorsb.AsMatrix("tenors"));

XlfOper curveCoeffb(
	(curveCoeffa));
MyMatrix curveCoeff(
	curveCoeffb.AsMatrix("curveCoeff"));

double result(
	InstantaneousRate(
		time,
		tenors,
		curveCoeff)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
discFactorArgs[]=
{
{ "start"," Starting time ","B"},
{ "end"," Ending time ","B"},
{ "tenors"," The knot points you place to fit LIBOR and OIS curves ","XLF_OPER"},
{ "oisCoeff"," OIS fitted coefficient ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerdiscFactor("xldiscFactor",
"discFactor",
" Calculate the discount factor between any two dates ",
LibraryName,
discFactorArgs,
4
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xldiscFactor(
double start,
double end,
LPXLFOPER tenorsa,
LPXLFOPER oisCoeffa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);



XlfOper tenorsb(
	(tenorsa));
MyMatrix tenors(
	tenorsb.AsMatrix("tenors"));

XlfOper oisCoeffb(
	(oisCoeffa));
MyMatrix oisCoeff(
	oisCoeffb.AsMatrix("oisCoeff"));

double result(
	discFactor(
		start,
		end,
		tenors,
		oisCoeff)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
LIBORForwardRateArgs[]=
{
{ "start"," Starting time ","B"},
{ "end"," Ending time ","B"},
{ "tenors"," The knot points you place to fit LIBOR and OIS curves ","XLF_OPER"},
{ "liborCoeff"," LIBOR fitted coefficient ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerLIBORForwardRate("xlLIBORForwardRate",
"LIBORForwardRate",
" Calculate the forward LIBOR rate for any settlement and underlying tenor ",
LibraryName,
LIBORForwardRateArgs,
4
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlLIBORForwardRate(
double start,
double end,
LPXLFOPER tenorsa,
LPXLFOPER liborCoeffa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);



XlfOper tenorsb(
	(tenorsa));
MyMatrix tenors(
	tenorsb.AsMatrix("tenors"));

XlfOper liborCoeffb(
	(liborCoeffa));
MyMatrix liborCoeff(
	liborCoeffb.AsMatrix("liborCoeff"));

double result(
	LIBORForwardRate(
		start,
		end,
		tenors,
		liborCoeff)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
swapRateArgs[]=
{
{ "start"," Starting time ","B"},
{ "end"," Ending time ","B"},
{ "tenors"," The knot points you place to fit LIBOR and OIS curves ","XLF_OPER"},
{ "liborCoeff"," LIBOR fitted coefficient ","XLF_OPER"},
{ "oisCoeff"," OIS fitted coefficient ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerswapRate("xlswapRate",
"swapRate",
" Calculate the swap rate for any settlement and underlying ternor ",
LibraryName,
swapRateArgs,
5
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlswapRate(
double start,
double end,
LPXLFOPER tenorsa,
LPXLFOPER liborCoeffa,
LPXLFOPER oisCoeffa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);



XlfOper tenorsb(
	(tenorsa));
MyMatrix tenors(
	tenorsb.AsMatrix("tenors"));

XlfOper liborCoeffb(
	(liborCoeffa));
MyMatrix liborCoeff(
	liborCoeffb.AsMatrix("liborCoeff"));

XlfOper oisCoeffb(
	(oisCoeffa));
MyMatrix oisCoeff(
	oisCoeffb.AsMatrix("oisCoeff"));

double result(
	swapRate(
		start,
		end,
		tenors,
		liborCoeff,
		oisCoeff)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
swapPVArgs[]=
{
{ "start"," Starting time ","B"},
{ "end"," Ending time ","B"},
{ "tenors"," The knot points you place to fit LIBOR and OIS curves ","XLF_OPER"},
{ "liborCoeff"," LIBOR fitted coefficient ","XLF_OPER"},
{ "oisCoeff"," OIS fitted coefficient ","XLF_OPER"},
{ "marketRate"," Market quote ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerswapPV("xlswapPV",
"swapPV",
" Calculate the PV of any spot or forward starting swap based on the fitted curves ",
LibraryName,
swapPVArgs,
6
,false
,false
,""
,""
,false
,false
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlswapPV(
double start,
double end,
LPXLFOPER tenorsa,
LPXLFOPER liborCoeffa,
LPXLFOPER oisCoeffa,
double marketRate)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);



XlfOper tenorsb(
	(tenorsa));
MyMatrix tenors(
	tenorsb.AsMatrix("tenors"));

XlfOper liborCoeffb(
	(liborCoeffa));
MyMatrix liborCoeff(
	liborCoeffb.AsMatrix("liborCoeff"));

XlfOper oisCoeffb(
	(oisCoeffa));
MyMatrix oisCoeff(
	oisCoeffb.AsMatrix("oisCoeff"));


double result(
	swapPV(
		start,
		end,
		tenors,
		liborCoeff,
		oisCoeff,
		marketRate)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

//////////////////////////
// Methods that will get registered to execute in AutoOpen
//////////////////////////

//////////////////////////
// Methods that will get registered to execute in AutoClose
//////////////////////////
