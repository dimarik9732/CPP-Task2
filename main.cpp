#include "Set.h"
#include <iostream>
using namespace std;

int main(void)
{


	Set s, t;
	s.insert(80);
	s.insert(5);
	s.insert(1000);
	s.insert(40);
	s.insert(3);
	s.insert(49);
	s.insert(55);
	s.insert(50);
	s.insert(51);
	s.insert(30);
	s.insert(28);
	s.insert(29);
	s.insert(6);
	s.insert(10);
	s.insert(15);
	s.insert(9);
	cout << s.contains(5) << endl;
	cout << s.contains(10	)<< endl;
	// cout << t.contains(4) << endl;
	s.del(80);
	s.del(1000);
	s.del(5);
	cout << s << endl;
	s.clear();
	cout << s << endl;  		
	return 0;
}