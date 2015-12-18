#ifndef BSPLINE_HPP
#define BSPLINE_HPP

#include <vector>
#include <map>

class BSpline
{
  public:

    struct BSplineCacheKey
    {
        BSplineCacheKey(
            const double rt,
            const int rd,
            const int rk
            )
            : t(rt),
              d(rd),
              k(rk)
            {}

        bool operator<(const BSplineCacheKey & rhs) const {
            return value() < rhs.value();
        }

        double value() const {
            return t + d * 100 + (k + 3) * 1000;
        }
        
        double t;
        int d;
        int k;
    };

    typedef std::map<BSplineCacheKey, double> BSplineCache;
    typedef std::map<BSplineCacheKey, double>::const_iterator BSplineCacheIter;
    
    BSpline(
        const std::vector<double> & tenors,
        const bool cache = true
        )
        : _tenors(tenors),
          _cache(cache)
        {;}

    double value(
        const double t,
        const int d,
        const int k
        ) const;

    double first_deriv(
        const double t,
        const int d,
        const int k
        ) const;

    double second_deriv(
        const double t,
        const int d,
        const int k
        ) const;

    double third_deriv(
        const double t,
        const int d,
        const int k
        ) const;

    int time_to_bucket(
        const double time
        ) const;
    
  private:    
    
    std::vector<double> _tenors;
    bool _cache;

};

#endif
