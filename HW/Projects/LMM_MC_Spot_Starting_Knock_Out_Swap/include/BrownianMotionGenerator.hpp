#ifndef BROWNIANMOTIONGENERATOR_HPP
#define BROWNIANMOTIONGENERATOR_HPP

#include <vector>
#include <utility>

typedef std::pair<double, std::vector<double> > EigenPair;

class BrownianMotionGenerator
{
  public:

    BrownianMotionGenerator(const std::vector<double> & steps);

    void simulate(std::vector<double> & path) const;

    void dump() const;
    
  private:

    std::vector<std::vector<double> > _eigen_vectors;
    std::vector<double> _eigen_values;
};


#endif
