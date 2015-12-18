#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
using namespace Eigen;

typedef std::pair<double, std::vector<double> > EigenPair;

struct EigenValueSorter
{
    bool operator()(const EigenPair & left, const EigenPair & right) {
        return left.first > right.first;
    }
};


int main(int argc, char ** argv)
{
    int size = 2;
    if (argc > 1)
    {
        size = atoi(argv[1]);
    }
    MatrixXd m(size, size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            m(i, j) = min(i, j);
        }
    }
    std::cout << m << std::endl;

    EigenSolver<MatrixXd> es(m);

    cout << "The eigenvalues of m are: " << endl << es.eigenvalues() << endl;
    cout << "The eigenvectors of m are: " << endl << es.eigenvectors() << endl;

    vector<double> eigen_vals;

    for (int i = 0; i < size; ++i)
    {
        const double val = es.eigenvalues().col(0)[i].real();
        eigen_vals.push_back(val);
    }

    vector<vector<double> > eigen_vecs;

    for (int col = 0; col < size; ++col)
    {
        vector<double> tmp;
        for (int row = 0; row < size; ++row)
        {
            tmp.push_back(es.eigenvectors().col(col)[row].real());
        }
        eigen_vecs.push_back(tmp);
    }

    cout << "Eigen values:" << endl;
    for (size_t i = 0; i < eigen_vals.size(); ++i)
    {
        cout << eigen_vals[i] << endl;
    }

    cout << "Eigen vectors:" << endl;
    for (size_t i = 0; i < eigen_vecs.size(); ++i)
    {
        const vector<double> & vec = eigen_vecs[i];
        for (size_t j = 0; j < vec.size(); ++j)
        {
            cout << vec[j] << ",";
        }
        cout << endl;
    }

    vector<EigenPair> sorting_vector;

    for (size_t i = 0; i < eigen_vecs.size(); ++i)
    {
        sorting_vector.push_back(
            make_pair(
                eigen_vals[i], eigen_vecs[i]
                )
            );
    }

    EigenValueSorter evs;
    sort(sorting_vector.begin(), sorting_vector.end(), evs);
    cout << "after sorting the results" << endl;
    for (size_t i = 0 ; i < sorting_vector.size(); ++i)
    {
        const double eigen_value = sorting_vector[i].first;
        const vector<double> & eigen_vector = sorting_vector[i].second;
        cout << eigen_value << "\t(";
        for (size_t j = 0; j < eigen_vector.size(); ++j)
        {
            cout << eigen_vector[j] << ",";
        }
        cout << ")" << endl;
    }
    
}
