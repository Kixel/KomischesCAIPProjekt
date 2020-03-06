#pragma once
#include <string>
#include <fstream>
#include <random>
#include <QMainWindow>
#include <QStatusBar>

using namespace std;

class Tools
{
public:
	static int Type_Q2CV(int t);
	static int Type_CV2Q(int t);
	static bool PathValid(string p);

	//Stuff for random numbers
	/*static random_device rd;
	static mt19937_64 eng;
	static uniform_int_distribution<unsigned int> distr;*/

	static unsigned int GetRandomUint();

	//Benchmark stuff
	static uint64_t benchstart;
	static uint64_t systemtime();
	static void startBenchmark(bool doBenchmark);
	static void endBenchmark(bool doBenchmark, QStatusBar* status);


	static string readableformats;
	static string writeableformats;
};

