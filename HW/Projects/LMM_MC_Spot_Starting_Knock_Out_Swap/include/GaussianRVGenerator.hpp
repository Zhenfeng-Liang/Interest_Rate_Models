#ifndef GAUSSIANRVGENERATOR_HPP
#define GAUSSIANRVGENERATOR_HPP

class GaussianRVGenerator
{
  public:

    static double random();

  private:

    GaussianRVGenerator();

    static double _inv_norm_cdf(
        const double x
        );
    
};


#endif
