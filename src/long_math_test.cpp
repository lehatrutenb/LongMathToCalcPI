#include "../include/long_math.hpp"

#include <cstdio>
#include <iostream>
#include "long_math.cpp"

void print_bad_result() {
	printf("\033[1;31mFAILED\033[0m\n");
	fflush(stdout);
}

void print_good_result() {
	printf("\033[1;32mOK\033[0m\n");
	fflush(stdout);
}

void test_add(std::vector<std::pair<long long, long long>> long_long_inp, std::vector<std::pair<double, double>> double_inp) {
    std::cout << "Testing +:" << std::endl;
    std::cout << "Int:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if (x1 + x2 != std::stoi((long_number1 + long_number2).convert_to_str())) {
            std::cout << x1 << ' ' << x2 << std::endl;
            std::cout << x1 + x2 << std::endl;
            std::cout << std::stoi((long_number1 + long_number2).convert_to_str()) << std::endl;

            print_bad_result();
            return;
        }
    }

    std::cout << "Float:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if (std::abs(x1 + x2 - std::stod((long_number1 + long_number2).convert_to_str())) > TEST_EPS) {
            std::cout << x1 << ' ' << x2 << std::endl;
            std::cout << x1 + x2 << std::endl;
            std::cout << (long_number1 + long_number2).convert_to_str() << std::endl;

            print_bad_result();
            return;
        }
    }

    print_good_result();
}

void test_subtract(std::vector<std::pair<long long, long long>> long_long_inp, std::vector<std::pair<double, double>> double_inp) {
    std::cout << "Testing -:" << std::endl;
    std::cout << "Int:" << std::endl;
     for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if (x1 - x2 != std::stoi((long_number1 - long_number2).convert_to_str())) {
            std::cout << x1 << ' ' << x2 << std::endl;
            std::cout << x1 - x2 << std::endl;
            std::cout << std::stoi((long_number1 - long_number2).convert_to_str()) << std::endl;

            print_bad_result();
            return;
        }
    }

     std::cout << "Float:" << std::endl;
     for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if (std::abs(x1 - x2 - std::stod((long_number1 - long_number2).convert_to_str())) > TEST_EPS) {
            std::cout << x1 << ' ' << x2 << std::endl;
            std::cout << x1 - x2 << std::endl;
            std::cout << std::stod((long_number1 - long_number2).convert_to_str()) << std::endl;

            print_bad_result();
            return;
        }
    }

    print_good_result();
}

void test_mult(std::vector<std::pair<long long, long long>> long_long_inp, std::vector<std::pair<double, double>> double_inp) {
    std::cout << "Testing *:" << std::endl;
    std::cout << "Int:" << std::endl;
     for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);

        if (x1 * x2 != std::stoll((long_number1 * long_number2).convert_to_str())) {
            std::cout << x1 << ' ' << x2 << std::endl;
            std::cout << x1 * x2 << std::endl;
            std::cout << std::stoll((long_number1 * long_number2).convert_to_str()) << std::endl;

            print_bad_result();
            return;
        }
    }

    std::cout << "Float:" << std::endl;
    for (auto p : long_long_inp) {
        double x1 = p.first, x2 = p.second;

        x1 *= ((long double) ((long long) (x1 * 1000))) / 1000.0;
        x2 *= ((long double) ((long long) (x2 * 1000))) / 1000.0;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        x1 = std::stod(long_number1.convert_to_str());
        x2 = std::stod(long_number2.convert_to_str());
        if (std::abs(std::abs(x1 * x2) - std::abs(std::stod((long_number1 * long_number2).convert_to_str()))) > TEST_EPS) {
            std::cout << x1 << ' ' << x2 << std::endl;
            std::cout << x1 * x2 << std::endl;
            std::cout << std::stod((long_number1 * long_number2).convert_to_str()) << std::endl;

            print_bad_result();
            return;
        }
    }

    print_good_result();
}

void test_divide(std::vector<std::pair<long long, long long>> long_long_inp, std::vector<std::pair<double, double>> double_inp) {
    std::cout << "Testing /:" << std::endl;
    std::cout << "Int:" << std::endl;
	
	int test_index = 0;
    for (auto p : long_long_inp) {
		if (test_index++ == 100) {
			break;
		}
        double x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);

		long_number_t expect = long_number_t(x1 / x2);
		long_number_t abs_diff = expect - (long_number1 / long_number2);
		if (abs_diff < long_number_t(0)) {
			abs_diff = abs_diff * long_number_t(-1);
		}

        if (abs_diff > long_number_t(TEST_EPS)) {
            std::cout << x1 << ' ' << x2 << std::endl;
            std::cout << x1 / x2 << std::endl;
            std::cout << (long_number1 / long_number2).convert_to_str() << std::endl;

            print_bad_result();
            return;
        }
    }

	test_index = 0;
    std::cout << "Float:" << std::endl;
    for (auto p : long_long_inp) {
		if (test_index++ == 100) {
			break;
		}

        double x1 = p.first, x2 = p.second;

        x1 *= ((long double) ((long long) (x1 * 1000))) / 1000.0;
        x2 *= ((long double) ((long long) (x2 * 1000))) / 1000.0;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        x1 = std::stod(long_number1.convert_to_str());
        x2 = std::stod(long_number2.convert_to_str());

        if (std::abs(std::abs(x1 / x2) - std::abs(std::stod((long_number1 / long_number2).convert_to_str()))) > TEST_EPS) {
            std::cout << x1 << ' ' << x2 << std::endl;
            std::cout << x1 / x2 << std::endl;
            std::cout << std::stod((long_number1 * long_number2).convert_to_str()) << std::endl;

            print_bad_result();
            return;
        }
    }

    print_good_result();
}

void test_to_string(std::vector<std::pair<long long, long long>> long_long_inp, std::vector<std::pair<double, double>> double_inp) {
    std::cout << "Testing to_string:" << std::endl;
    std::cout << "Int:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first;

        long_number_t long_number2(std::to_string(x1));
        if (stoi(long_number2.convert_to_str()) != x1) {
            std::cout << x1 << std::endl;
            std::cout << long_number2.convert_to_str() << std::endl;

            print_bad_result();
            return;
        }
    }

    
    std::cout << "Float:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first;
        long_number_t long_number2(std::to_string(x1));
        if (long_number2.convert_to_str() != std::to_string(x1)) { // dangerous !!!!!!!!!!!!!
            std::cout << x1 << std::endl;
            std::cout << long_number2.convert_to_str() << std::endl;

            print_bad_result();
            return;
        }
    }

    print_good_result();
}

void test_cmp(std::vector<std::pair<long long, long long>> long_long_inp, std::vector<std::pair<double, double>> double_inp) {
    bool correct = true;
    std::cout << "Testing Comprassions:" << std::endl;

    std::cout << "Int:" << std::endl;
    std::cout << "Testing <:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if (x1 < x2 != long_number1 < long_number2) {
            std::cout << x1 << ' ' << x2 << std::endl;
            correct = true;
            break;
        }
    }

    std::cout << "Testing >:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if (x1 > x2 != long_number1 > long_number2) {
            std::cout << x1 << ' ' << x2 << std::endl;
            correct = true;
            break;
        }
    }

    std::cout << "Testing ==:" << std::endl;
    std::cout << "==" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if ((x1 == x2) != (long_number1 == long_number2)) {
            std::cout << x1 << ' ' << x2 << std::endl;
            correct = true;
            break;
        }
    }

    std::cout << "Testing !=:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if ((x1 != x2) != (long_number1 != long_number2)) {
            std::cout << x1 << ' ' << x2 << std::endl;
            correct = true;
            break;
        }
    }

    std::cout << "Float:" << std::endl;

    std::cout << "Testing <:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if (x1 < x2 != long_number1 < long_number2) {
            std::cout << x1 << ' ' << x2 << std::endl;
            correct = true;
            break;
        }
    }

    std::cout << "Testing >:" << std::endl;
   for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if (x1 > x2 != long_number1 > long_number2) {
            std::cout << x1 << ' ' << x2 << std::endl;
            correct = true;
            break;
        }
    }

    std::cout << "Testing ==:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if ((x1 == x2) != (long_number1 == long_number2)) {
            std::cout << x1 << ' ' << x2 << std::endl;
            correct = true;
            break;
        }
    }

    std::cout << "Testing !=:" << std::endl;
    for (auto p : long_long_inp) {
        long long x1 = p.first, x2 = p.second;

        long_number_t long_number1(x1);
        long_number_t long_number2(x2);
        if ((x1 != x2) != (long_number1 != long_number2)) {
            std::cout << x1 << ' ' << x2 << std::endl;
            correct = true;
            break;
        }
    }

    if (correct) {
        print_good_result();
    } else {
        print_bad_result();
    }
}

void test_all() {
    double lower_bound = -1e9;
    double upper_bound = 1e9;

    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);

    std::default_random_engine re;


    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);
    srand(1303);//std::time(nullptr);

    std::vector<std::pair<double, double>> double_inp(5000);
    std::vector<std::pair<long long, long long>> long_long_inp(5000);
    for (int i = 0; i < long_long_inp.size(); i++) {
        long long x1 = rand() % (long long) 1e9, x2 = rand() % (long long) 1e9;
        if (rand() % 3 == 0) {
            x1 *= -1;
        }
        if (rand() % 3 == 0) {
            x2 *= -1;
        }

        long_long_inp[i] = std::make_pair(x1, x2);
    }

    for (int i = 0; i < double_inp.size(); i++) {
        long long x1 = unif(re), x2 = unif(re);
        if (rand() % 3 == 0) {
            x1 *= -1;
        }
        if (rand() % 3 == 0) {
            x2 *= -1;
        }

        double_inp[i] = std::make_pair(x1, x2);
    }

    test_to_string(long_long_inp, double_inp);
    test_cmp(long_long_inp, double_inp);
	test_add(long_long_inp, double_inp);
    test_subtract(long_long_inp, double_inp);
    test_mult(long_long_inp, double_inp);
	test_divide(long_long_inp, double_inp);
}

int main() {
	std::cout << (long_number_t(1) != long_number_t(2)) << std::endl;
	test_all();
}