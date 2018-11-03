#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	string tmp = "acvb123";
	char* c;
	c = &tmp[0];
	cout << c;
	return 0;
}