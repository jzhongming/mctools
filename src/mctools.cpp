//============================================================================
// Name        : mctools.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "MathUtil.h"

using namespace std;
using namespace mctools;

int main() {
	for(int i=0; i<10; ++i) {
		cout << i<< " : " << MathUtil::is_pow_of_2(i) << " : " << MathUtil::next_pow_of_2(i)<< endl;
		cout << MathUtil::signum(i) << endl;
		cout << MathUtil::isEven(i) << " : " << MathUtil::isOdd(i) << endl;
	}
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	cout << MathUtil::E << ": " << MathUtil::PI << endl;
		cout << MathUtil::signum(-3) << endl;
		cout << MathUtil::signum(0) << endl;
		cout << MathUtil::signum(31323) << endl;
	return 0;
}
