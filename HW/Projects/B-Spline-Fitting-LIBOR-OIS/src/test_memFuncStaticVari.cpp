/*
 * test_memFuncStaticVari.cpp
 *
 *  Created on: Mar 25, 2015
 *      Author: jose
 */

#include <iostream>

using namespace std;

class foo
{
public:
	int add() const
	{
		static int a = 1;
		a += 1;
		return a;
	}
};

int main()
{
	foo temp;

	cout << "Expect 2: " << temp.add() << endl;
	cout << "Expect 3: " << temp.add() << endl;
	cout << "Expect 4: " << temp.add() << endl;

	foo temp1;
	cout << "Expect 2: " << temp1.add() << endl;
	cout << "Expect 3: " << temp1.add() << endl;
	cout << "Expect 4: " << temp1.add() << endl;

	cout << "It doesn't match. So, static variables in a normal member function is still a class variable." << endl;

	return 0;
}
