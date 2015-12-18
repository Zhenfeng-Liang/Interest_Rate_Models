#include "../include/CurveStripper.hpp"
//#include <CurveStripper.hpp>
#include <chrono>
#include <iostream>

using namespace std;


std::chrono::system_clock::time_point t0;
std::chrono::system_clock::time_point t1;
#define START_TIMER t0 = std::chrono::system_clock::now();
#define END_TIMER t1 = std::chrono::system_clock::now();
#define ELAPSED_TIME std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()

int main()
{
	START_TIMER
	// 20 knots points
    vector<double> tenors;
    tenors.push_back(-1.0);
    tenors.push_back(-0.7);
    tenors.push_back(-0.3);
    tenors.push_back(0.0);
    tenors.push_back(.25);
    tenors.push_back(.5);
    tenors.push_back(1.0);
    tenors.push_back(2.0);
    tenors.push_back(5.0);
    tenors.push_back(10.0);
    tenors.push_back(15.0);
    tenors.push_back(20.0);
    tenors.push_back(30.0);
    tenors.push_back(35.0);
    tenors.push_back(40.0);
    tenors.push_back(50.0);
    tenors.push_back(60.0);

    vector<double> guess;
    for(int i = 0; i < 17; i++) {
    	guess.push_back(0.05);
    }

    vector<InstrumentParam> instruments;
    InstrumentParam::InstrumentType type;
    InstrumentParam tmp;

    {
    	type = InstrumentParam::LIBORForwardRate;
    	tmp.setter(.0, 1.0/360, 0.0055, type);
        instruments.push_back(tmp);
    
        tmp.setter(.0, 90.0/360.0, 0.0055, type);
        instruments.push_back(tmp);

        type = InstrumentParam::OISForwardRate;
        tmp.setter(.0, 1.0/360.0, 0.0007, type);
        instruments.push_back(tmp);
    }

    {

        type = InstrumentParam::EDFuture;
        tmp.setter(8.0/360.0, (8.0 + 90.0)/360.0, 0.0056, type);
        instruments.push_back(tmp);

        tmp.setter(98.0/360.0, (98.0 + 90.0)/360.0, 0.0064, type);
        instruments.push_back(tmp);

        tmp.setter(187.0/360.0, (187.0 + 90.0)/360.0, 0.0069, type);
        instruments.push_back(tmp);

        tmp.setter(276.0/360.0, (276.0+90.0)/360.0, 0.0070, type);
        instruments.push_back(tmp);

        tmp.setter(1.0 + 6.0/360.0, 1.0 + (6.0+90.0)/360.0, 0.0070, type);
        instruments.push_back(tmp);

        tmp.setter(1.0 + 97.0/360.0, 1.0 + (90.0+90.7)/360.0, 0.0069, type);
        instruments.push_back(tmp);

        tmp.setter(1.5 + 6.0/360.0, 1.5 + 96.0/360.0, 0.0070, type);
        instruments.push_back(tmp);

        tmp.setter(1.5 + 95.0/360, 1.5 + 185.0/360.0, 0.0073, type);
        instruments.push_back(tmp);
    }

    {
        type = InstrumentParam::LIBORSwap;
        double start =  2.0 / 360.0;

        tmp.setter(start, 2.0 + start, 0.0069, type);
        instruments.push_back(tmp);

        tmp.setter(start, 3.0 + start, 0.0080, type);
        instruments.push_back(tmp);

        tmp.setter(start, 4.0 + start, 0.0101, type);
        instruments.push_back(tmp);

        tmp.setter(start, 5.0 + start, 0.0125, type);
        instruments.push_back(tmp);

        tmp.setter(start, 7.0 + start, 0.0169, type);
        instruments.push_back(tmp);

        tmp.setter(start, 10.0 + start, 0.0211, type);
        instruments.push_back(tmp);

        tmp.setter(start, 12.0 + start, 0.0230, type);
        instruments.push_back(tmp);

        tmp.setter(start, 15.0 + start, 0.0248, type);
        instruments.push_back(tmp);

        tmp.setter(start, 20.0 + start, 0.0260, type);
        instruments.push_back(tmp);

        tmp.setter(start, 25.0 + start, 0.0266, type);
        instruments.push_back(tmp);

        tmp.setter(start, 30.0 + start, 0.0269, type);
        instruments.push_back(tmp);
    }

    {

        type = InstrumentParam::BasisSwap;
        double start = 2.0 / 360.0;

        tmp.setter(start, 90.0/360.0 + start, 0.004588, type);
        instruments.push_back(tmp);

        tmp.setter(start, 180.0/360.0 + start, 0.004925, type);
        instruments.push_back(tmp);

        tmp.setter(start, 270.0/360.0 + start, 0.005113, type);
        instruments.push_back(tmp);

        tmp.setter(start, 1.0 + start, 0.005250, type);
        instruments.push_back(tmp);

        tmp.setter(start, 1.5 + start, 0.005350, type);
        instruments.push_back(tmp);

        tmp.setter(start, 2.0 + start, 0.005300, type);
        instruments.push_back(tmp);

        tmp.setter(start, 3.0 + start, 0.005163, type);
        instruments.push_back(tmp);

        tmp.setter(start, 4.0 + start, 0.004925, type);
        instruments.push_back(tmp);

        tmp.setter(start, 5.0 + start, 0.004625, type);
        instruments.push_back(tmp);

        tmp.setter(start, 7.0 + start, 0.004138, type);
        instruments.push_back(tmp);

        tmp.setter(start, 10.0 + start, 0.003450, type);
        instruments.push_back(tmp);

        tmp.setter(start, 12.0 + start, 0.003175, type);
        instruments.push_back(tmp);

        tmp.setter(start, 15.0 + start, 0.002880, type);
        instruments.push_back(tmp);

        tmp.setter(start, 20.0 + start, 0.002550, type);
        instruments.push_back(tmp);

        tmp.setter(start, 25.0 + start, 0.002338, type);
        instruments.push_back(tmp);

        tmp.setter(start, 30.0 + start, 0.002188, type);
        instruments.push_back(tmp);
    }

    CurveStripper fitter(
        instruments,
        tenors,
        guess,
        guess
        );

    std::vector< std::vector<double> > result;
    fitter.strip_curve(result);

    END_TIMER
    cout << "Total fitting time: " << ELAPSED_TIME << endl;

    return 0;
}
