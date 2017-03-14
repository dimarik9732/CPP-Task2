#include "Set.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	Set s1("{(1), (2), (3), (4), (5), (6), (7), (8), (9), (10), (11), (12), (13), (14), (15)}");

	Set s2("{(17), (34), (5)}");

	Set s3;

	s1 += s2;

	bool res = s1 == s2;
	cout << res << endl;
	cout << (s1 == s3) << endl;
	return 0;
}