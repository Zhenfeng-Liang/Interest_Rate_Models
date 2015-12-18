/*
 * test_Swap.cpp
 *
 *  Created on: May 2, 2015
 *      Author: jose
 */


#include <iostream>
#include <vector>
#include <LIBORMarketModel1F.hpp>
#include <Swap.hpp>
#include <Rates.hpp>
#include <string>
#include <chrono>

using namespace std;

int main(int argc, char ** argv)
{
    vector<double> starts;
    double tmp = 0.0;
    int numRate = 80;
    for(int i = 0; i < numRate; i++)
    {
        starts.push_back(tmp);
        tmp += 0.25;
    }

    const vector<double> rates = {
            0.005471644,
            0.006416425,
            0.006872247,
            0.007039568,
            0.007024085,
            0.006964006,
            0.007004167,
            0.007292701,
            0.007956632,
            0.009029066,
            0.010441768,
            0.01208422,
            0.013853024,
            0.015688169,
            0.017510869,
            0.019228528,
            0.020808975,
            0.022258961,
            0.023584337,
            0.024781236,
            0.025857247,
            0.026844492,
            0.027752558,
            0.028577406,
            0.029328014,
            0.030031694,
            0.030696076,
            0.031321838,
            0.031917661,
            0.032502579,
            0.033072462,
            0.033618952,
            0.034145251,
            0.034657137,
            0.035150901,
            0.03562088,
            0.036066472,
            0.036500583,
            0.036915985,
            0.037307249,
            0.037674399,
            0.038029522,
            0.038364128,
            0.038674287,
            0.038960636,
            0.03923432,
            0.039485714,
            0.039712398,
            0.039918906,
            0.040108041,
            0.040276377,
            0.04042345,
            0.040552499,
            0.040674065,
            0.040778515,
            0.040867682,
            0.040945047,
            0.041020385,
            0.041083704,
            0.041137619,
            0.041185707,
            0.0412373,
            0.041282256,
            0.041323574,
            0.041367405,
            0.041415667,
            0.041465077,
            0.041516509,
            0.041573326,
            0.041645078,
            0.041721741,
            0.041805935,
            0.041900735,
            0.042016418,
            0.042143121,
            0.042282721,
            0.042437898,
            0.042619794,
            0.042817023,
            0.043028101,
    };

    cout << "starts and rates vectors' size: " << starts.size() << "," << rates.size() << endl;

    const double series_tenor = 20.0;

    // Simulation arguments
    const double sigma = 0.0085;
    const double sim_step_length = 0.25;
    const double sim_end_knockOut_tenor = 10.0;
    int path_num = 5000;
    bool exact = false;
    bool antithetic_variate = false;
    
    if (argc > 1)
    {
        const string exact_switch(argv[1]);
        if (exact_switch == "Y")
        {
            exact = true;
        }
        else
        {
            exact = false;
        }
    }

    if (argc > 2)
    {
        const string path_switch(argv[2]);
        path_num = atoi(path_switch.c_str());
    }

    if (argc > 3)
    {
        const string antithetic_switch(argv[3]);
        if (antithetic_switch == "Y")
        {
            antithetic_variate = true;
        }
        else
        {
            antithetic_variate = false;
        }
    }
    
    // Knock out swap property
    const double barrier = 0.0095;
    const double innerSwapTenor = 10.0;

    ForwardRateSeries libor(starts, rates, series_tenor);

    // Calculate the normal ten year swap
    Swap sw(10.0);
    cout << "Normal 10 year swap fixed rate is: " << sw.cal_fixed_rate(libor, libor) << endl;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    LIBORMarketModel1F lmm_1F(libor, libor, sim_step_length, sim_end_knockOut_tenor, sigma);

    vector<RatePath> LIBOR_results;
    vector<RatePath> OIS_results;

    lmm_1F.simulate_forward_paths(
        path_num, exact, LIBOR_results, OIS_results, antithetic_variate
        );

    KnockOutSwap koSwap(sim_end_knockOut_tenor, barrier, innerSwapTenor);
    double result = koSwap.MC_Cal_fixed_rate(LIBOR_results, OIS_results);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    cout << "Monte Carlo Simulation Result:" << endl
         << "exact drift term calculation?: " << (exact ? "True" : "False") << endl
         << "path num: " << path_num << endl
         << "antithetic variate: " << (antithetic_variate ? "True" : "False") << endl
         << "knockout swap fixed rate: " << result << endl
         << "Time spent: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
         << " ms." << endl;

    return 0;
}

