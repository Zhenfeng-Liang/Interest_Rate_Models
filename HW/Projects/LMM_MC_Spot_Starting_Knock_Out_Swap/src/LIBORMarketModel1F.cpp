#include <LIBORMarketModel1F.hpp>
#include <BrownianMotionGenerator.hpp>

using namespace std;

LIBORMarketModel1F::LIBORMarketModel1F(
        const ForwardRateSeries & libor_forwards,
        const ForwardRateSeries & ois_forwards,
        const double sim_step_length,
        const double sim_end,
        const double sigma
        )
        : _libor(libor_forwards),
        _ois(ois_forwards),
        _sim_step_length(sim_step_length),
        _sim_end(sim_end),
        _sigma(sigma),
        _nodes()
{
    double tmp_tenor = .0;

    // Because we need to calculate the difference, we also need the last term of Z(t_n)
    while (tmp_tenor < _sim_end + 0.0001)
    {
        _nodes.push_back(tmp_tenor);
        tmp_tenor += _sim_step_length;
    }

    // Store the initial calculated drift for the frozen curve purpose
    size_t n = _libor.length();
    double tmp_drift;
    for(size_t j = 0; j < n - 1; j++)
    {
        tmp_drift = - _sigma * _sigma * _sim_step_length * drift_L_j(j, _libor);
        _initialWholeDriftTerm.push_back(tmp_drift);
    }
}

void
LIBORMarketModel1F::simulate_forward_paths(
        const int path_num,
        const bool exact,
        vector<RatePath> & LIBOR_results,
        vector<RatePath> & OIS_results,
        const bool antithetic_variate
        ) const
{
    LIBOR_results.clear();
    OIS_results.clear();

    for(int i = 0; i < path_num; i++)
    {
        RatePath libor_one_path;
        RatePath ois_one_path;
        RatePath libor_one_path_antithetic;
        RatePath ois_one_path_antithetic;
        simulate_one_path(exact, libor_one_path, ois_one_path,
                          libor_one_path_antithetic, ois_one_path_antithetic,
                          antithetic_variate);
        LIBOR_results.push_back(libor_one_path);
        OIS_results.push_back(ois_one_path);
        if (antithetic_variate)
        {
            LIBOR_results.push_back(libor_one_path_antithetic);
            OIS_results.push_back(ois_one_path_antithetic);
        }
    }
}

double
LIBORMarketModel1F::drift_L_j(
        const size_t j,
        const ForwardRateSeries & oisSeries_t
        ) const
{
    double drift = 0;

    // Terminal forward measure
    size_t k = oisSeries_t.length() - 1;

    for(size_t i = j+1; i <= k; i++)
    {
        drift += 1.0 / (1.0 + _fwd_rate_time_step * oisSeries_t.rate(i));
    }

    return drift;
}


// Single factor model
// Calculate a vector of dL_j at simulation time t, to time t + sim_step_length
void
LIBORMarketModel1F::delta_L_t(
        std::vector<double> & dL,
        const bool exact,
        const ForwardRateSeries & rateSeries_t,
        const double dW_t
        ) const
{
    size_t n = rateSeries_t.length();
    dL.clear();

    double sto_term = _sigma * dW_t;
    double drift_coeff = - _sigma * _sigma * _sim_step_length;

    if(exact)
    {
        double tmp_dL_j;

        // We only have n-1 rates in the next simulation time
        for(size_t j = 0; j < n - 1; j++)
        {
            tmp_dL_j = drift_coeff * drift_L_j(j, rateSeries_t) * _sim_step_length + sto_term;
            dL.push_back(tmp_dL_j);
        }
    }
    else
    {
        for(size_t j = 0; j < n - 1; j++)
        {
            dL.push_back(_initialWholeDriftTerm[j] * _sim_step_length + sto_term);
        }
    }
}

void
LIBORMarketModel1F::simulate_forward_one_time_step(
        const bool exact,
        ForwardRateSeries & rateSeries_next,
        const ForwardRateSeries & rateSeries_current,
        const double dW
        ) const
{
    // Calculate dL
    std::vector<double> dL;
    delta_L_t(dL, exact, rateSeries_current, dW);

    // Should be the size of the former series less one
    size_t len_t_next = rateSeries_current.length() - 1;

    vector<double> starts;
    vector<double> rates;
    for(size_t i = 0; i < len_t_next; i++)
    {
        starts.push_back(rateSeries_current.time(i));
        rates.push_back(rateSeries_current.rate(i+1) + dL[i]);
    }
    double tmp_tenor = rateSeries_current.tenor() - _fwd_rate_time_step;

    rateSeries_next.setter(starts, rates, tmp_tenor);
}

void
LIBORMarketModel1F::simulate_one_path(
        const bool exact,
        RatePath & LIBOR_one_path,
        RatePath & OIS_one_path,
        RatePath & LIBOR_one_path_antithetic,
        RatePath & OIS_one_path_antithetic,
        const bool antithetic_variate
        ) const
{
    // Generate Brownian Motion
    static BrownianMotionGenerator BMGenerator(_nodes);
    vector<double> W;
    BMGenerator.simulate(W);

    size_t steps = _nodes.size();
    double tmp_dW;
    ForwardRateSeries rateSeries_current;
    ForwardRateSeries rateSeries_next;
    rateSeries_current = _libor;

    LIBOR_one_path.add_slice(_nodes[0], rateSeries_current);
    for(size_t i = 0; i < steps - 1; i++)
    {
        // Calculate the difference for each step
        tmp_dW = W[i+1] - W[i];
        simulate_forward_one_time_step(exact, rateSeries_next, rateSeries_current, tmp_dW);
        LIBOR_one_path.add_slice(_nodes[i+1], rateSeries_next);
        rateSeries_current = rateSeries_next;
    }

    // Assume no spread between OIS and LIBOR
    OIS_one_path = LIBOR_one_path;

    if (antithetic_variate)
    {
        ForwardRateSeries rateSeries_current_antithetic;
        ForwardRateSeries rateSeries_next_antithetic;
        rateSeries_current_antithetic = _libor;
        
        LIBOR_one_path_antithetic.add_slice(_nodes[0], rateSeries_current_antithetic);
        for(size_t i = 0; i < steps - 1; i++)
        {
            // Calculate the difference for each step
            tmp_dW = -W[i+1] + W[i];
            simulate_forward_one_time_step(exact, rateSeries_next_antithetic,
                                           rateSeries_current_antithetic, tmp_dW);
            LIBOR_one_path_antithetic.add_slice(_nodes[i+1], rateSeries_next_antithetic);
            rateSeries_current_antithetic = rateSeries_next_antithetic;
        }
        OIS_one_path_antithetic = LIBOR_one_path_antithetic;
    }
}
