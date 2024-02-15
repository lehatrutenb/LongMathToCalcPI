#include <string>
#include <vector>
#include "LongMath/include/long_math.hpp"

#ifndef CALCPI_HPP_INCLUDED
#define CALCPI_HPP_INCLUDED

namespace calc_pi {
long_math::long_number_t calc_pi_bpf_method(const unsigned amt_of_digits=10, const int max_amt_iterations=-1);
}

#endif // CALCPI_HPP_INCLUDED