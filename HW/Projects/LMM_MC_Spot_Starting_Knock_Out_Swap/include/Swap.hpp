/*
* Swap.hpp
*
*  Created on: Apr 28, 2015
*      Author: jose
*/

#ifndef SWAP_HPP_
#define SWAP_HPP_

#include <Rates.hpp>
#include <stdlib.h>

class Swap
{
public:

    Swap(const double tenor)
            : _tenor(tenor)
    {
        ;
    }

    double cal_fixed_rate(
            const ForwardRateSeries & libor,
            const ForwardRateSeries & ois,
            bool NoSpread = true
            ) const;

private:

    double _tenor;

    double _delta_fixed =0.5;
    double _delta_floating = 0.25;
};



class KnockOutSwap
{

public:

    KnockOutSwap(
            const double tenor,
            const double barrier,
            const double _innerSwap_tenor
            )
            : _tenor(tenor),
              _barrier(barrier),
              _innerSwap(_innerSwap_tenor)
    {
        double epsilon = 0.000000001;
        _numRateToTerminal = size_t(_tenor / _delta_floating + epsilon);
    }

    // We use the martingale property here, use the Floating leg expected PV divided by the fixed leg
    // expected annuity
    double MC_Cal_fixed_rate(
            const std::vector<RatePath> & libor_path,
            const std::vector<RatePath> & ois_path
            ) const;

private:

    double _tenor;
    double _barrier;
    Swap _innerSwap;
    size_t _numRateToTerminal;

    double _delta_fixed =0.5;
    double _delta_floating = 0.25;

    size_t terminate_time_index(
            const std::vector<ForwardRateSeries> & libor_vec,
            const std::vector<ForwardRateSeries> & ois_vec
            ) const;

    double terminal_discount_factor(
            const ForwardRateSeries & oisSeries
            ) const;


    // Calculate one path of floating leg PV, for the purpose of using martingale property
    double cal_floatingLegPV(
            const size_t terminateIndex,
            const std::vector<ForwardRateSeries> & libor_vec,
            const std::vector<ForwardRateSeries> & ois_vec
            ) const;

    double cal_fixedLegAnnuity(
            const size_t terminateIndex,
            const std::vector<ForwardRateSeries> & ois_vec
            ) const;
    };


/*
*  The following class is using the expectation of the fixed rate, which should be wrong.
*  I am leaving the code here for further verification
*/
/*
class KnockOutSwap
{
public:

    KnockOutSwap(
            const double tenor,
            const double barrier,
            const double _innerSwap_tenor
            )
            : _tenor(tenor),
              _barrier(barrier),
              _innerSwap(_innerSwap_tenor)
    {
        ;
    }

    double MC_Cal_fixed_rate(
            const std::vector<RatePath> & libor_path,
            const std::vector<RatePath> & ois_path
            ) const;

    private:

    double _tenor;
    double _barrier;
    Swap _innerSwap;

    double _delta_fixed =0.5;
    double _delta_floating = 0.25;

    size_t terminate_time_index(
            const std::vector<ForwardRateSeries> & libor_vec,
            const std::vector<ForwardRateSeries> & ois_vec
            ) const;

    double terminal_discount_factor(
            const size_t numRatesToTerminal,
            const ForwardRateSeries & oisSeries
            ) const;

    double cal_fixed_rate(
            const std::vector<ForwardRateSeries> & libor_vec,
            const std::vector<ForwardRateSeries> & ois_vec
            ) const;
};
*/

#endif /* SWAP_HPP_ */
