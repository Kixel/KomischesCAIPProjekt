#pragma once
#include <string>
#include <fstream>

using namespace std;

class Tools
{
public:
	static int Type_Q2CV(int t);
	static int Type_CV2Q(int t);
	static bool PathValid(string p);

	static string readableformats;
	static string writeableformats;
};

