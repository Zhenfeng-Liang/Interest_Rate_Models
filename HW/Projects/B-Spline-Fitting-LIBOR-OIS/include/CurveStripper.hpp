#ifndef CURVESTRIPPER_H
#define CURVESTRIPPER_H

#include <vector>
#include <memory>

#include "InstrumentParam.hpp"
#include "InstaForwardCurve.hpp"
#include "IRInstruments.hpp"
#include "../ext_lib/alglib/optimization.h"
#include "../ext_lib/alglib/stdafx.h"

/*
#include <InstrumentParam.hpp>
#include <InstaForwardCurve.hpp>
#include <IRInstruments.hpp>
#include <alglib/optimization.h>
#include <alglib/stdafx.h>
*/

typedef std::unique_ptr<IRInstruments> IRInstrumentPtr;

class CurveStripper
{
  public:

    CurveStripper(
        const std::vector<InstrumentParam> & params,
        const std::vector<double> & knot_points_rhs,
        const std::vector<double> & libor_init_guess,
        const std::vector<double> & ois_init_guess
        );

    bool strip_curve(std::vector< std::vector<double> > & fittedCoeff) const;
    
    InstaForwardCurve libor;
    InstaForwardCurve ois;
    std::vector<IRInstrumentPtr> instruments;
    std::vector<double> quotes;
    std::vector<double> knot_points;
    int first_bucket;
    int last_bucket;
};

#endif
