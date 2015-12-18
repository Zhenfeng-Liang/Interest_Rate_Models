#include "../include/CurveStripper.hpp"
#include "../include/OISForwardRate.hpp"
#include "../include/LIBORForwardRate.hpp"
#include "../include/EDFutures.hpp"
#include "../include/Swap.hpp"
#include "../include/BasisSwap.hpp"

/*
#include <CurveStripper.hpp>
#include <OISForwardRate.hpp>
#include <LIBORForwardRate.hpp>
#include <EDFutures.hpp>
#include <Swap.hpp>
#include <BasisSwap.hpp>
*/

#include <iostream>

using namespace std;
using namespace alglib;

namespace
{
    void
        obj_func(
            const real_1d_array &x,
            double &func,
            void *ptr
            )
    {
        CurveStripper * data = reinterpret_cast<CurveStripper *>(ptr);
        const vector<double> & knot_points = data->knot_points;
        const int num_knot_pts = knot_points.size();
        const bool debug = false;
        
        InstaForwardCurve & libor = data->libor;
        InstaForwardCurve & ois = data->ois;

        if (x.length() != num_knot_pts * 2)
        {
            cout << "Error CurveStripper::_obj_func: mismatch length."
                 << " passed-in param length = " << x.length()
                 << ", # knot points per line = " << num_knot_pts << endl;
            return;
        }

        vector<double> libor_coeffs;
        vector<double> ois_coeffs;

        for (ae_int_t i = 0; i < num_knot_pts; ++i)
        {
            libor_coeffs.push_back(x[i]);
            ois_coeffs.push_back(x[i + num_knot_pts]);
        }

        libor.set_coeffs(libor_coeffs);
        ois.set_coeffs(ois_coeffs);

        func = .0;
        const vector<IRInstrumentPtr> & instruments = data->instruments;
        const vector<double> & quotes = data->quotes;

        for (size_t i = 0; i < instruments.size(); ++i)
        {
            const double px = quotes[i];
            const double model_px = instruments[i]->CalRate(libor, ois);
            func += (px - model_px) * (px - model_px);
            if (debug)
            {
                cout << "instrument " << i << ": model px = "
                     << model_px << ", market px = " << px << endl;
            }
        }

        if (debug)
        {
            cout << "error from px diff = " << func << endl;
        }
        
        const int first_bucket = data->first_bucket;
        const int last_bucket = data->last_bucket;
        const double lamda = 0.00001;
        const double t_lower = knot_points[first_bucket];
        const double t_upper = knot_points[last_bucket + 1];
        func += lamda * libor.integral_second_deriv_square(t_lower, t_upper);
        func += lamda * ois.integral_second_deriv_square(t_lower, t_upper);

        if (debug)
        {
            cout << "penalization term for libor = "
                 << lamda * libor.integral_second_deriv_square(t_lower, t_upper)
                 << ", penalization term for ois = "
                 << lamda * ois.integral_second_deriv_square(t_lower, t_upper)
                 << endl;
        }
        
        func *= 0.5;

        if (debug)
        {
            cout << "guess: " << x.tostring(5) << endl;
            cout << "error: " << func << endl;
        }
        else
        {
        //    cout << "error: " << func << "\n";
        }
    }
};


CurveStripper::CurveStripper(
    const vector<InstrumentParam> & params,
    const vector<double> & knot_points_rhs,
    const vector<double> & libor_init_guess,
    const vector<double> & ois_init_guess
    )
    : libor(knot_points_rhs, libor_init_guess, 3),
      ois(knot_points_rhs, ois_init_guess, 3),
      knot_points(knot_points_rhs)
{    
    instruments.clear();
    quotes.clear();

    double first_start(999.0);
    double last_end(-1.0);
    
    for (size_t i = 0; i < params.size(); ++i)
    {
        const InstrumentParam & param = params[i];
        const double start = param.start;
        const double end = param.end;
        const InstrumentParam::InstrumentType type = param.type;
        
        if (start < first_start)
        {
            first_start = start;
        }
        if (end > last_end)
        {
            last_end = end;
        }
        
        if (type == InstrumentParam::OISForwardRate)
        {
            instruments.push_back(
                IRInstrumentPtr(
                    new OISForwardRate(start, end)
                    )
                );
        }
        else if (type == InstrumentParam::LIBORForwardRate)
        {
            instruments.push_back(
                IRInstrumentPtr(
                    new LIBORForwardRate(start, end)
                    )
                );
        }
        else if (type == InstrumentParam::EDFuture)
        {
            instruments.push_back(
                IRInstrumentPtr(
                    new EDFutures(start, end)
                    )
                );
        }
        else if (type == InstrumentParam::LIBORSwap)
        {
            instruments.push_back(
                IRInstrumentPtr(
                    new Swap(start, end)
                    )
                );
        }
        else if (type == InstrumentParam::BasisSwap)
        {
            instruments.push_back(
                IRInstrumentPtr(
                    new BasisSwap(start, end)
                    )
                );
        }
        else
        {
            cout << "Warning CurveStripper::CurveStripper:"
                 << " Invalid instrument types" << endl;
            continue;
        }
        
        quotes.push_back(param.quote);
    }

    BSpline spline(knot_points_rhs);
    first_bucket = spline.time_to_bucket(first_start);
    last_bucket = spline.time_to_bucket(last_end);
}

bool
CurveStripper::strip_curve(std::vector< std::vector<double> > & fittedCoeff) const
{
    real_1d_array init_guess;
    const int num_knot_pts = knot_points.size();
    
    init_guess.setlength(num_knot_pts * 2);
    const vector<double> & libor_coeffs = libor.get_coeffs();
    const vector<double> & ois_coeffs = ois.get_coeffs();
    for (int i = 0; i < num_knot_pts; ++i)
    {
        init_guess[i] = libor_coeffs[i];
        init_guess[i + num_knot_pts] = ois_coeffs[i];
    }

    double epsg = 0.00001;
    double epsf = 0;
    double epsx = 0;
    double diffstep = 1.0e-4;
    ae_int_t maxits = 0;
    minlbfgsstate state;
    minlbfgsreport rep;
    
    minlbfgscreatef(1, init_guess, diffstep, state);
    minlbfgssetcond(state, epsg, epsf, epsx, maxits);
    alglib::minlbfgsoptimize(state, obj_func, NULL, (void *)this);
    minlbfgsresults(state, init_guess, rep);
    
    cout << "min value: " << int(rep.terminationtype) << endl;
    cout << "coeffs: " << init_guess.tostring(2) << endl;

	std::vector<double> liborCoeffTemp;
	for (int i = 0; i < num_knot_pts; i++)
	{
		liborCoeffTemp.push_back(init_guess[i]);
	}

	std::vector<double> oisCoeffTemp;
	for (int i = 0; i < num_knot_pts; i++)
	{
		oisCoeffTemp.push_back(init_guess[i + num_knot_pts]);
	}
	fittedCoeff.push_back(liborCoeffTemp);
	fittedCoeff.push_back(oisCoeffTemp);

    return true;
}


