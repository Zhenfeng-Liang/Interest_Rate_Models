#include <BrownianMotionGenerator.hpp>
#include <GaussianRVGenerator.hpp>

#include <Eigen/Dense>

#include <algorithm>
#include <iostream>

using namespace std;
using namespace Eigen;

struct EigenValueSorter
{
    bool operator() (const EigenPair & left, const EigenPair & right) const {
        return left.first > right.first;
    }
};


BrownianMotionGenerator::BrownianMotionGenerator(
    const vector<double> & steps
    )
{
    const size_t step_size = steps.size();
    MatrixXd corr_matrix(step_size, step_size);

    for (size_t i = 0; i < step_size; ++i)
    {
        for (size_t j = 0; j < step_size; ++j)
        {
            corr_matrix(i, j) = min(steps[i], steps[j]);
        }
    }

    EigenSolver<MatrixXd> solver(corr_matrix);

    for (size_t i = 0; i < step_size; ++i)
    {
        const double val = solver.eigenvalues().col(0)[i].real();
        _eigen_values.push_back(val);
    }

    for (size_t col = 0; col < step_size; ++col)
    {
        vector<double> eigen_vec;
        for (size_t row = 0; row < step_size; ++row)
        {
            const double val = solver.eigenvectors().col(col)[row].real();
            eigen_vec.push_back(val);
        }
        _eigen_vectors.push_back(eigen_vec);
    }

    vector<EigenPair> sorting_vector;
    for (size_t i = 0; i < step_size; ++i)
    {
        sorting_vector.push_back(
            make_pair(
                _eigen_values[i], _eigen_vectors[i]
                )
            );
    }

    EigenValueSorter evs;
    sort(sorting_vector.begin(), sorting_vector.end(), evs);

    _eigen_values.clear();
    _eigen_vectors.clear();

    for (size_t i = 0; i < sorting_vector.size(); ++i)
    {
        const EigenPair & eigen_pair = sorting_vector[i];
        _eigen_values.push_back(eigen_pair.first);
        _eigen_vectors.push_back(eigen_pair.second);
    }
    
}

void
BrownianMotionGenerator::dump() const
{
    cout << "eigenvalues and eigenvectors:" << endl;

    for (size_t i = 0; i < _eigen_values.size(); ++i)
    {
        cout << _eigen_values[i] << "\t(";
        const vector<double> & eigen_vec = _eigen_vectors[i];
        for (size_t j = 0; j < eigen_vec.size(); ++j)
        {
            cout << eigen_vec[j] << ",";
        }
        cout << ")" << endl;
    }
}

void
BrownianMotionGenerator::simulate(
    vector<double> & path
    ) const
{
    path.clear();
    const size_t path_len = _eigen_values.size();
    path.resize(path_len, .0);
    for (size_t j = 0; j < path_len; ++j)
    {
        const double norm_rv = GaussianRVGenerator::random();
        const double sqrt_eigen_val = sqrt(_eigen_values[j]);
        const vector<double> & eigen_vec = _eigen_vectors[j];
        for (size_t n = 0; n < path_len; ++n)
        {
            path[n] += sqrt_eigen_val * eigen_vec[n] * norm_rv;
        }
    }
}
