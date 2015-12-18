#include <Rates.hpp>
#include <iostream>

using namespace std;

void
ForwardRateSeries::setter(
		const std::vector<double> & starts,
        const std::vector<double> & rates,
        const double tenor
        )
{
    _starts.clear();
    _rates.clear();

    _starts = starts;
    _rates = rates;
    _tenor = tenor;
}

void
RatePath::add_slice(
        const double time,
        const ForwardRateSeries & fwd_rate
        )
{
    _starts.push_back(time);
    _forward_series_vec.push_back(fwd_rate);
}

void
ForwardRateSeries::printRate() const
{
    for(vector<double>::const_iterator it = _rates.begin(); it != _rates.end(); it++)
    {
        cout << *it << ",";
    }
    cout << endl << endl;
}

void
RatePath::printOnePath() const
{
    for(vector<ForwardRateSeries>::const_iterator it = _forward_series_vec.begin(); it != _forward_series_vec.end(); it++)
    {
        it->printRate();
    }
}
