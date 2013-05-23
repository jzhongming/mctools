//============================================================================
// Name        : mctools.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "MathUtil.h"
#include "UTF8Util.h"

using namespace std;
using namespace mctools;

int main() {
	for (int i = 0; i < 10; ++i) {
		cout << i << " : " << MathUtil::is_pow_of_2(i) << " : "
				<< MathUtil::next_pow_of_2(i) << endl;
		cout << MathUtil::signum(i) << endl;
		cout << MathUtil::isEven(i) << " : " << MathUtil::isOdd(i) << endl;
	}
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	cout << MathUtil::E << ": " << MathUtil::PI << endl;
	cout << MathUtil::signum(-3) << endl;
	cout << MathUtil::signum(0) << endl;
	cout << MathUtil::signum(31323) << endl;
	uint32_t len = 0;
	string s("姜");
	cout << MathUtil::ReadUTF8(s.c_str(), len) << " : " << len << endl;

	size_t c = UTF8UTIL::getWordNum("我是123ABC");
	std::cout << "count: " << c << std::endl;
	std::cout << "getMaxEndOfUtf8: " << UTF8UTIL::getMaxEndOfUtf8("民了发以经")<< std::endl;

	return 0;
}
