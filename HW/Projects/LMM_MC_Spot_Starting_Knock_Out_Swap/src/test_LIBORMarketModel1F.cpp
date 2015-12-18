#include <LIBORMarketModel1F.hpp>

#include <iostream>

using namespace std;

int main()
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
    int path_num = 2;
    bool exact = false;


    ForwardRateSeries libor(starts, rates, series_tenor);
    LIBORMarketModel1F lmm_1F(libor, libor, sim_step_length, sim_end_knockOut_tenor, sigma);

    vector<RatePath> LIBOR_results;
    vector<RatePath> OIS_results;

    lmm_1F.simulate_forward_paths(
        path_num, exact, LIBOR_results, OIS_results
        );

//    vector<double> starts;
//    double tmp = 0.0;
//    for(int i = 0; i < 5; i++)
//    {
//        starts.push_back(tmp);
//        tmp += 0.25;
//    }
//
//    const vector<double> rates = {
//            0.00548223386378,
//            0.00639695124192,
//            0.00689929801769,
//            0.0070555691603,
//            0.00703034045456,
//    };
//
//    const double tenor = 1.5;
//
//    ForwardRateSeries libor(starts, rates, tenor);
//
//    const double sigma = 0.0085;
//    const double sim_step_length = 0.25;
//    const double sim_end = 0.5;
//    LIBORMarketModel1F lmm_1F(libor, libor, sim_step_length, sim_end, sigma);
//
//    vector<RatePath> LIBOR_results;
//    vector<RatePath> OIS_results;
//    int path_num = 2;
//    bool exact = true;
//
//    lmm_1F.simulate_forward_paths(
//        path_num, exact, LIBOR_results, OIS_results
//        );

    int i = 1;
    for(vector<RatePath>::iterator it = LIBOR_results.begin(); it != LIBOR_results.end(); it++)
    {
        cout << endl << "The " << i++ << " th path: \n";
        it->printOnePath();
        cout << endl;
    }
}
