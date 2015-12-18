#include "../include/BSpline.hpp"
//#include <BSpline.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

using namespace std;

double
BSpline::value(
    const double t,
    const int d,
    const int k
    ) const
{
    static BSplineCache cache;
    
    const int bucket = time_to_bucket(t);
    
    if (d == 0)
    {
        return k == bucket ? 1.0 : .0;
    }

    if (bucket < k || bucket > bucket + d)
    {
        return .0;
    }

    BSplineCacheKey key(t, d, k);
    BSplineCacheIter iter = cache.find(key);
    if (_cache && iter != cache.end())
    {
        return iter->second;
    }
    
    const double t_k = _tenors[k];
    const double t_kd = _tenors[k + d];
    const double t_kd1 = _tenors[k + d + 1];
    const double t_k1 = _tenors[k + 1];
    const double B_k = value(t, d-1, k);
    const double B_k1 = value(t, d-1, k+1);
    
    const double result =
        (t - t_k) / (t_kd - t_k) * B_k
        + (t_kd1 - t) / (t_kd1 - t_k1) * B_k1;

    if (_cache)
    {
        cache.insert(make_pair(key, result));
    }
    
    return result;
}

double
BSpline::first_deriv(
    const double t,
    const int d,
    const int k
    ) const
{
    static BSplineCache cache;
    
    if (d == 0)
    {
        return .0;
    }
    
    const int bucket = time_to_bucket(t);

    if (bucket < k || bucket > bucket + d)
    {
        return .0;
    }

    BSplineCacheKey key(t, d, k);
    BSplineCacheIter iter = cache.find(key);
    if (_cache && iter != cache.end())
    {
        return iter->second;
    }
    
    const double t_k = _tenors[k];
    const double t_kd = _tenors[k + d];
    const double t_k1 = _tenors[k + 1];
    const double t_kd1 = _tenors[k + d + 1];
    const double B_k = value(t, d-1, k);
    const double B_k1 = value(t, d-1, k+1);

    const double result =
        d / (t_kd - t_k) * B_k - d / (t_kd1 - t_k1) * B_k1;

    if (_cache)
    {
        cache.insert(make_pair(key, result));
    }
    
    return result;
}

double
BSpline::second_deriv(
    const double t,
    const int d,
    const int k
    ) const
{
    static BSplineCache cache;
    if (d == 0)
    {
        return .0;
    }
    
    const int bucket = time_to_bucket(t);

    if (bucket < k || bucket > bucket + d)
    {
        return .0;
    }

    BSplineCacheKey key(t, d, k);
    BSplineCacheIter iter = cache.find(key);
    if (_cache && iter != cache.end())
    {
        return iter->second;
    }
    
    const double t_k = _tenors[k];
    const double t_kd = _tenors[k + d];
    const double t_k1 = _tenors[k + 1];
    const double t_kd1 = _tenors[k + d + 1];
    const double B_k_deriv = first_deriv(t, d-1, k);
    const double B_k1_deriv = first_deriv(t, d-1, k+1);

    const double result =
        d / (t_kd - t_k) * B_k_deriv - d / (t_kd1 - t_k1) * B_k1_deriv;

    if (_cache)
    {
        cache.insert(make_pair(key, result));
    }
    
    return result;
}

double
BSpline::third_deriv(
    const double t,
    const int d,
    const int k
    ) const
{
    static BSplineCache cache;
    
    if (d == 0)
    {
        return .0;
    }
    
    const int bucket = time_to_bucket(t);

    if (bucket < k || bucket > bucket + d)
    {
        return .0;
    }

    BSplineCacheKey key(t, d, k);
    BSplineCacheIter iter = cache.find(key);
    if (_cache && iter != cache.end())
    {
        return iter->second;
    }
    
    const double t_k = _tenors[k];
    const double t_kd = _tenors[k + d];
    const double t_k1 = _tenors[k + 1];
    const double t_kd1 = _tenors[k + d + 1];
    const double B_k_sec_deriv = second_deriv(t, d-1, k);
    const double B_k1_sec_deriv = second_deriv(t, d-1, k+1);

    const double result =
        d / (t_kd - t_k) * B_k_sec_deriv - d / (t_kd1 - t_k1) * B_k1_sec_deriv;

    if (_cache)
    {
        cache.insert(make_pair(key, result));
    }
    
    return result;
}


int
BSpline::time_to_bucket(
    const double t
    ) const
{
    static map<double, int> cache;
    map<double, int>::const_iterator iter = cache.find(t);
    if (_cache && iter != cache.end())
    {
        return iter->second;
    }
    
    static string func_name("BSpline::time_to_bucket");
    vector<double>::const_iterator lb = lower_bound(_tenors.begin(), _tenors.end(), t);
    vector<double>::const_iterator ub = upper_bound(_tenors.begin(), _tenors.end(), t);

    if (ub == _tenors.begin())
    {
        cout << "Warning " << func_name
             << ": hitting the lower bound with t = "
             << t << endl;
        return 0;
    }
    else if (lb == _tenors.end())
    {
        cout << "Warning " << func_name
             << ": hitting the upper bound with t = "
             << t << endl;
        return _tenors.size() - 1;
    }
    else if (lb != ub)
    {
        return lb - _tenors.begin();
    }
    
    --lb;
    const int result = lb - _tenors.begin();

    if (_cache)
    {
        cache.insert(make_pair(t, result));
    }

    return result;
}


