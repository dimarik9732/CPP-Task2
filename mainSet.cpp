#include "Set.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	Set s1("{(1), (2), (3), (4), (5), (6), (7), (8), (9), (10), (11), (12), (13), (14), (15)}");

	Set s2("{(17), (34), (5)}");

	s1 += s2;
	cout << s1 << endl;
	return 0;
}