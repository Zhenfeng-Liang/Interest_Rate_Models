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

//<xlw:libraryname=MyTestLibrary


short // echoes a short
EchoShort(short x // number to be echoed
       );


double 
cal_normal_swap_fixed_rate(
    const MyMatrix starts,                  // 3 months forward rate starting time
    const MyMatrix rates,                   // 3 months forward rate
    const double series_tenor,              // Forward series tenor
    const double swap_tenor                 // Swap's tenor
    );


MyMatrix cal_knock_out_swap_fixed_rate(
	const MyMatrix starts,                  // 3 months forward rate starting time
	const MyMatrix rates,                   // 3 months forward rate
	const double series_tenor,              // Forward series tenor
	const double sigma,                     // LIBOR market 1 fator model's constant volatility
	const double sim_step_length,           // Simulation time step
	const double sim_end_knockOut_tenor,    // Simulation ending time
	const int path_num,                     // Paths to generated for Monte Carlo
	const bool exact_calculation,           // Boolean value, 1 for exact_calculation, 0 for frozen curve approximation
	const double barrier,                   // Knock out swap tenor
	const double innerSwapTenor,            // The inner swap's tenor of the knock out swap
	const bool antithetic_variate			// Boolean value, 1 for anti variable, 0 for normal generation
	);

#endif
