#include "generate/bmgenerator.h"

#include <cmath>
#include <random>
#include <fstream>

namespace generate {

BMGenerator::BMGenerator() {}

BMGenerator::~BMGenerator() {}

void BMGenerator::generate(std::string file_name) {
	std::ofstream file;
	file.open(file_name);
	std::random_device rd;
	std::mt19937 mt(rd());

	auto t = 0.0;
	auto u = 0.021;
	auto sigma = 0.2;
	auto S0 = 100;

	auto p1 = std::log(S0);
	auto p2 = u - 0.5 * sigma * sigma;
	auto p3 = sigma * sigma;

	std::uniform_real_distribution<double> random_t(0.01, 0.05);
	std::uniform_int_distribution<int> random_size(1000, 2000);

	for (auto i = 0; i < 80000000; ++i) {
		auto dt = random_t(mt);
		t += dt;

		auto a = p1 + p2 * t;
		auto b = p3 * t;

		std::normal_distribution<double> d(a, b);
		auto log_St = d(mt);
		auto St = std::exp(log_St);

		auto ask_price = std::round(St*10)/10;
		auto bid_price = ask_price - 0.1;
		auto ask_size = random_size(mt);
		auto bid_size = random_size(mt);

		file << std::round(dt*1000)/10 << "\t" << bid_price << "\t" << ask_price << "\t" << bid_size << "\t" << ask_size << "\n";
	}

	file.close();
}

}

