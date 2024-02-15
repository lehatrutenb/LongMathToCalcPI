#include <cstdio>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

#include "../LongMath/include/long_math.hpp"
#include "../include/calc_pi.h"

long_math::long_number_t calc_arctg(long_math::long_number_t x, const unsigned amt_iterations=10, const unsigned amt_of_digits=10) {
	x.set_min_divide_accuracy(amt_of_digits);
	x.set_max_divide_accuracy(amt_of_digits + 10);
	long_math::long_number_t sign = long_math::long_number_t((long long) 1);

	long_math::long_number_t x2 = x * x;
	long_math::long_number_t res = x;
	res.set_min_divide_accuracy(amt_of_digits);
	long_math::long_number_t x_power = x;
	for (int i = 3; i <= 2 * amt_iterations + 2; i += 2) {
		x_power = x_power * x2;
		sign = (-sign);

		long_math::long_number_t tmp = long_math::long_number_t((long long) i);
		res = res + (sign * x_power) / tmp;
	}

	return res;
}

long_math::long_number_t calc_pi_bpf_method(const unsigned amt_of_digits=10, const int max_amt_iterations=-1) {
	// formula koefs that are hard to recalc in for
	long_math::long_number_t power_koef = long_math::long_number_t((long long) 1);
	long_math::long_number_t linear_koef = long_math::long_number_t((long long) 0);

	// init numbers not to do it in for
	long_math::long_number_t c1 = long_math::long_number_t((long long) 1);
	long_math::long_number_t c2 = long_math::long_number_t((long long) 2);
	long_math::long_number_t c3 = long_math::long_number_t((long long) 3);
	long_math::long_number_t c4 = long_math::long_number_t((long long) 4);
	long_math::long_number_t c5 = long_math::long_number_t((long long) 5);
	long_math::long_number_t c8 = long_math::long_number_t((long long) 8);
	long_math::long_number_t c16 = long_math::long_number_t((long long) 16);
	long_math::long_number_t c47 = long_math::long_number_t((long long) 47);
	long_math::long_number_t c120 = long_math::long_number_t((long long) 120);
	long_math::long_number_t c151 = long_math::long_number_t((long long) 151);

	c1.set_min_divide_accuracy(amt_of_digits);
	c2.set_min_divide_accuracy(amt_of_digits);
	c3.set_min_divide_accuracy(amt_of_digits);
	c5.set_min_divide_accuracy(amt_of_digits);
	c8.set_min_divide_accuracy(amt_of_digits);
	c16.set_min_divide_accuracy(amt_of_digits);
	c47.set_min_divide_accuracy(amt_of_digits);
	c120.set_min_divide_accuracy(amt_of_digits);
	c151.set_min_divide_accuracy(amt_of_digits);

	std::string accuracy_string = "0.";
	for (int i = 0; i < amt_of_digits; i++) {
		accuracy_string += '0';
	}
	accuracy_string += '1';
	
	long_math::long_number_t accuracy_number = long_math::long_number_t(accuracy_string);

#ifdef PRINT_TIME_INFO
	std::clock_t c_start = std::clock();
	int clock_index = 0;
#endif


	long_math::long_number_t result = long_math::long_number_t((long long) 0);
	bool need_to_check_ind = false;
	if (max_amt_iterations != -1) {
		need_to_check_ind = true;
	}
	int ind = 0;
	for (;;) {
		if (need_to_check_ind) {
			if (ind == max_amt_iterations) {
				break;
			}
		}

#ifdef PRINT_TIME_INFO
		std::clock_t c_start = std::clock();
#endif
		auto t_start = std::chrono::high_resolution_clock::now();


		long_math::long_number_t testk = long_math::long_number_t((long double) ind);
		testk.set_min_divide_accuracy(amt_of_digits);
		auto to_add = (testk * testk * c120 + c151 * testk + c47);
		to_add = to_add / ((c2 * testk + c1)*(c4 * testk + c3)* (c8 * testk + c1)* (c8 * testk + c5));
		to_add = (to_add / power_koef);

		if (to_add < accuracy_number) {
			break;
		}

		result = result + to_add;

		power_koef = power_koef * c16;
		ind++;

#ifdef PRINT_TIME_INFO
		const std::clock_t c_end = std::clock();
    	const auto t_end = std::chrono::high_resolution_clock::now();
 
    	std::cout << std::fixed << "CPU time used: " << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << "ms  ";
		if (clock_index++ % 5 == 0) {
			std::cout << '\n';
		}
		c_start = std::clock();
#endif
	}

	return result;
}

long_math::long_number_t calc_pi_mechin_method(const unsigned amt_iterations=10, const unsigned amt_of_digits=10) {
	long_math::long_number_t one = long_math::long_number_t((long long) 1);
	long_math::long_number_t five = long_math::long_number_t((long long) 5);
	long_math::long_number_t contant = long_math::long_number_t((long long) 239);

	one.set_min_divide_accuracy(amt_of_digits);
	five.set_min_divide_accuracy(amt_of_digits);
	contant.set_min_divide_accuracy(amt_of_digits);

	long_math::long_number_t x1 = long_math::long_number_t(one / five);
	x1.set_min_divide_accuracy(amt_of_digits);
	long_math::long_number_t x2 = long_math::long_number_t(one / contant);
	x2.set_min_divide_accuracy(amt_of_digits);
	long_math::long_number_t atan1 = calc_arctg(x1, amt_iterations, amt_of_digits);
	long_math::long_number_t atan2 = calc_arctg(x2, amt_iterations, amt_of_digits);
	return long_math::long_number_t((long long) 4) * (long_math::long_number_t((long long) 4) * atan1 - atan2);
}
