#ifndef RATES_HPP
#define RATES_HPP

#include <vector>

class ForwardRateSeries
{
  public:

    ForwardRateSeries()
    {
        _tenor = 0.0;
    }

    ForwardRateSeries(
        const std::vector<double> & starts,
        const std::vector<double> & rates,
        const double tenor
        )
        : _starts(starts),
          _rates(rates),
          _tenor(tenor)
        {
            ;
        }

    double tenor() const {
        return _tenor;
    }

    double time(const int i) const {
        return _starts[i];
    }

    double rate(const int i) const {
        return _rates[i];
    }

    int length() const {
        return _rates.size();
    }

    void setter(
    		const std::vector<double> & starts,
            const std::vector<double> & rates,
            const double tenor
            );

    void printRate() const;

  private:
    
    std::vector<double> _starts;
    std::vector<double> _rates;
    double _tenor;
};


class RatePath
{
  public:

    RatePath () {;}

    void add_slice(
        const double time,
        const ForwardRateSeries & fwd_rate
        );

    std::vector<ForwardRateSeries> forward_series_vec() const{
    	return _forward_series_vec;
    }

    void printOnePath() const;

  private:

    std::vector<double> _starts;
    std::vector<ForwardRateSeries> _forward_series_vec;
};

#endif
