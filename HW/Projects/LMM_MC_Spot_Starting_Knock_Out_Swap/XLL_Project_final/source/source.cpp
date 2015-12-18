
#include<cppinterface.h>
#pragma warning (disable : 4996)

#include <algorithm>
#include <vector>
#include <chrono>

#include <Rates.hpp>
#include <Swap.hpp>
#include <LIBORMarketModel1F.hpp>

using namespace std;

short // echoes a short
EchoShort(short x // number to be echoed
           )
{
    return x;
}

vector<double> XLWMatrixToSTLVec(const MyMatrix & m);

double cal_knock_out_swap_inner(
    const vector<double> starts,
    const vector<double> rates,
    const double series_tenor,
    const double sigma,
    const double sim_step_length,
    const double sim_end_knockOut_tenor,
    const int path_num,
    const bool exact_calculation,
    const double barrier,
    const double innerSwapTenor,
	const bool antithetic_variate
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
    )
{
    vector<double> starts_vec = XLWMatrixToSTLVec(starts);
    vector<double> rates_vec = XLWMatrixToSTLVec(rates);

    double result;

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    result = cal_knock_out_swap_inner(
        starts_vec,
        rates_vec,
        series_tenor,
        sigma,
        sim_step_length,
        sim_end_knockOut_tenor,
        path_num,
        exact_calculation,
        barrier,
        innerSwapTenor,
		antithetic_variate
        );
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	double time = 0.0;
	time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0;

	MyMatrix mat_result(1, 2);
	mat_result(0, 0) = result;
	mat_result(0, 1) = time;

	return mat_result;
}


double cal_normal_swap_fixed_rate(
    const MyMatrix starts,                  // 3 months forward rate starting time
    const MyMatrix rates,                   // 3 months forward rate
    const double series_tenor,              // Forward series tenor
    const double swap_tenor                 // Swap's tenor
    )
{
    vector<double> starts_vec = XLWMatrixToSTLVec(starts);
    vector<double> rates_vec = XLWMatrixToSTLVec(rates);

    ForwardRateSeries libor(starts_vec, rates_vec, series_tenor);

    Swap sw(swap_tenor);
    
    return (sw.cal_fixed_rate(libor, libor));
}



double 
cal_knock_out_swap_inner(
    const vector<double> starts,
    const vector<double> rates,
    const double series_tenor,
    const double sigma,
    const double sim_step_length,
    const double sim_end_knockOut_tenor,
    const int path_num,
    const bool exact_calculation,
    const double barrier,
    const double innerSwapTenor,
	const bool antithetic_variate
    )
{
    ForwardRateSeries libor(starts, rates, series_tenor);

    LIBORMarketModel1F lmm_1F(libor, libor, sim_step_length, sim_end_knockOut_tenor, sigma);

    vector<RatePath> LIBOR_results;
    vector<RatePath> OIS_results;

	int tmp_path_num = path_num;
	if (antithetic_variate)
	{
		tmp_path_num /= 2;
	}

    lmm_1F.simulate_forward_paths(
		tmp_path_num, exact_calculation, LIBOR_results, OIS_results, antithetic_variate
        );

    KnockOutSwap koSwap(sim_end_knockOut_tenor, barrier, innerSwapTenor);
    
    double result = koSwap.MC_Cal_fixed_rate(LIBOR_results, OIS_results);

    return result;
}



std::vector<double> 
XLWMatrixToSTLVec(
    const MyMatrix & m	// Matrix need to be changed
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

