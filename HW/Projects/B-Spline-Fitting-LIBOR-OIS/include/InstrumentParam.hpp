#ifndef INSTRUMENTPARAM_HPP
#define INSTRUMENTPARAM_HPP

struct InstrumentParam
{
     
    enum InstrumentType
    {
        OISForwardRate = 0,
        LIBORForwardRate,
        EDFuture,
        LIBORSwap,
        BasisSwap,
        Undef
    };
    
    double start;
    double end;
    double quote;
    InstrumentType type;

 //   InstrumentParam(const double start_, const double end_, const double quote_, const InstrumentType & type_)
  //  				: start(start_), end(end_), quote(quote_),type(type_) {}

    void setter(const double start_, const double end_, const double quote_, const InstrumentType & type_)
    {
    	start = start_;
    	end = end_;
    	quote = quote_;
    	type = type_;
    }
};

#endif
