/*
 * test_vec.cpp
 *
 *  Created on: May 1, 2015
 *      Author: jose
 */




#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<int> a = {1,2,3};
	vector<int> b = {4,5,6,7,8,9};
	vector<int> c = {10,11,12,13};

	b = a;
	a = c;

	for(vector<int>::iterator it = b.begin(); it != b.end(); it++)
	{
		cout << *it << ", ";
	}
	cout << "\n b size: " << b.size() << endl;

	for(vector<int>::iterator it = a.begin(); it != a.end(); it++)
	{
		cout << *it << ", ";
	}
	cout << "\n a size: " << a.size() << endl;

	vector<int> d = {1,2,3};
	vector<int> e = {4,5,6,7,8,9};

	e.clear();
	e.resize(10,0);
	for(vector<int>::iterator it = e.begin(); it != e.end(); it++){
	    cout << *it << ", " ;
	}
	cout << endl << e.size() << endl;

	d.resize(2,0);
    for(vector<int>::iterator it = d.begin(); it != d.end(); it++){
        cout << *it << ", " ;
    }
    cout << endl << d.size() << endl;
	return 0;
}
