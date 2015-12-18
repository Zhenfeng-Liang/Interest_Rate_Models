#ifndef LIBORMARKETMODEL1F_HPP
#define LIBORMARKETMODEL1F_HPP

#include <vector>

#include <Rates.hpp>
#include <stdlib.h>

class LIBORMarketModel1F
{
public:

    LIBORMarketModel1F(
            const ForwardRateSeries & libor_forwards,
            const ForwardRateSeries & ois_forwards,
            const double sim_step_length,
            const double sim_end,
            const double sigma
            );

    void simulate_forward_paths(
            const int path_num,
            const bool exact,
            std::vector<RatePath> & LIBOR_results,
            std::vector<RatePath> & OIS_results,
            const bool antithetic_variate=false
            ) const;

private:

    ForwardRateSeries _libor;
    ForwardRateSeries _ois;
    double _sim_step_length;
    double _sim_end;
    double _sigma;
    
    std::vector<double> _nodes; 	// Store the simulation time step

    const double _fwd_rate_time_step = 0.25;

    std::vector<double> _initialWholeDriftTerm;

    // Given the parameters at time t, calculate the j th drift at that simulation column
    double drift_L_j(
            const size_t j,
            const ForwardRateSeries & oisSeries_t
            ) const;

    // Single factor model
    // Calculate a vector of dL_j at simulation time t, to time t + sim_step_length
    void delta_L_t(
            std::vector<double> & dL,
            const bool exact,
            const ForwardRateSeries & rateSeries_t,
            const double dW_t
            ) const;

    void simulate_forward_one_time_step(
            const bool exact,
            ForwardRateSeries & rateSeries_next,
            const ForwardRateSeries & rateSeries_current,
            const double dW
            ) const;

    void simulate_one_path(
            const bool exact,
            RatePath & LIBOR_one_path,
            RatePath & OIS_one_path,
            RatePath & LIBOR_one_path_antithetic,
            RatePath & OIS_one_path_antithetic,
            const bool antithetic_variate
            ) const;
};

#endif
