#include <cstdio>
#include <random>

#include "gtest/gtest.h"

#include "../LongMath/include/long_math.hpp"
#include "../LongMath/src/long_math.cpp"
#include "../src/calc_pi.cpp"

#define TEST_EPS 1e-5

std::string get_pi_digits(const long_math::long_number_t& pi, int accuracy) {
	std::ifstream file_stream("pi.txt");
    if (file_stream) {
        std::ostringstream string_stream;
        string_stream << file_stream.rdbuf();

		std::string to_check_pi = pi.convert_to_str();
		std::string correct_pi = string_stream.str();
        std::string need_part = "";
        for (int i = 0; i < std::min((int) to_check_pi.size(), accuracy + 2); i++) {
            need_part += correct_pi[i];
			if (to_check_pi[i] != need_part.back()) {
				return need_part;
			}
		}
        return need_part;
    }
    return "";
}

TEST(CheckPiCalulation, First100Accuracy) {
    int accuracy = 100;

    const long_math::long_number_t pi = calc_pi_bpf_method(accuracy);
    std::string pi_str = pi.convert_to_str();
    while (pi_str.size() > accuracy + 2) {
        pi_str.pop_back();
    }

    EXPECT_EQ(get_pi_digits(pi, accuracy), pi_str);
}

TEST(CheckPiCalulation, First200Accuracy) {
    int accuracy = 200;

    const long_math::long_number_t pi = calc_pi_bpf_method(accuracy);
    std::string pi_str = pi.convert_to_str();
    while (pi_str.size() > accuracy + 2) {
        pi_str.pop_back();
    }

    EXPECT_EQ(get_pi_digits(pi, accuracy), pi_str);
}

TEST(CheckPiCalulation, First500Accuracy) {
    int accuracy = 500;

    const long_math::long_number_t pi = calc_pi_bpf_method(accuracy);
    std::string pi_str = pi.convert_to_str();
    while (pi_str.size() > accuracy + 2) {
        pi_str.pop_back();
    }

    EXPECT_EQ(get_pi_digits(pi, accuracy), pi_str);
}

int main(int argc, char **argv) {
    srand(1303);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);

    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}