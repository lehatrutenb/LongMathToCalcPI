#include <cstdio> // ?

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <random>
#include <assert.h>

#define TEST_EPS 1e-5

// ToDo: include header
#include "../include/long_math.hpp"

// is it good solution??? - fix it

long_number_t::long_number_t(std::string number) {
    assert(number.size() > 0);
    positive = true;
    if (number[0] == '-') {
        positive = false;
    }
    bool is_float = false;
    for (char ch: number) {
        if (ch == '.' || ch == ',') {
            is_float = true;
        }
    }
    v_num.resize(number.size() - !positive - is_float);

    accuracy = 0;
    int v_ind = 0;
    is_float = false;
    for (int i = !positive; i < number.size(); i++) {
        if (number[i] == '.' || number[i] == ',') {
            is_float = true;
            continue;
        }
        if (is_float) {
            accuracy++;
        }
        v_num[v_ind++] = number[i] - '0';
    }
}

long_number_t::long_number_t(std::vector<uint8_t> base_vec, bool base_positive, int base_accuracy) {
    assert(base_accuracy >= 0); // bad - change positive to unsigned

    v_num.resize(base_vec.size());
    for (int i = 0; i < base_vec.size(); i++) {
        v_num[i] = base_vec[i];
    }
    positive = base_positive;
    accuracy = base_accuracy;
}

long_number_t::long_number_t(long double x) {
    *this = long_number_t(std::to_string(x));
}

std::string long_number_t::convert_to_str() {
    std::string number = "";
    number.reserve(v_num.size());
    bool non_zero = false;
    for (int i = 0; i < v_num.size(); i++) {
        if (i == v_num.size() - accuracy) {
            if (!non_zero) {
                number.push_back('0');
            }
            number.push_back('.');
        }
        if (v_num[i] != 0) {
            non_zero = true;
        }
        if (non_zero || i >= v_num.size() - accuracy) {
            number.push_back('0' + v_num[i]);
        }
    }
    std::string sign = positive ? "" : "-";
    return sign + number;
}

long_number_t long_number_t::operator+(long_number_t a)
{
    if (!a.positive && this->positive) {
        a.positive = true;
        long_number_t result = *this - a;
        a.positive = false;
        return result;
    }
    if (a.positive && !this->positive) {
        this->positive = true;
        long_number_t result = a - *this;
        this->positive = false;
        return result;
    }

    std::vector<uint8_t> new_num(this->v_num.size() + a.v_num.size() + 1, 0);

    long_number_t* first_num = this;
    long_number_t* second_num = &a;

    if (first_num->accuracy < second_num->accuracy) {
        std::swap(first_num, second_num);
    }

    for (int i = first_num->v_num.size() - 1; i >= 0; i--) {
        int diff = first_num->v_num.size() - 1 - i;
        new_num[new_num.size() - 1 - diff] = first_num->v_num[i];
    }

    bool need_to_add = false;
    int last = 0;
    for (int i = second_num->v_num.size() - 1; i >= 0; i--) {
        int diff = first_num->accuracy - second_num->accuracy + second_num->v_num.size() - 1 - i;
        int ind = new_num.size() - 1 - diff;
        last = ind;
        new_num[ind] += second_num->v_num[i] + need_to_add;
        need_to_add = false;
        if (new_num[ind] > 9) {
            new_num[ind] -= 10;
            need_to_add = true;
        }
    }

    if (need_to_add) {
        new_num[last - 1]++;
        last -= 1;
        while (new_num[last] == 10) {
            new_num[last] -= 10;
            new_num[last - 1]++;
            last--;
        }
    }

    return long_number_t(new_num, this->positive, first_num->accuracy);
}

bool long_number_t::operator<(long_number_t a) {
    if (!this->positive && a.positive) {
        return true;
    }
    if (this->positive && !a.positive) {
        return false;
    }
    if (!this->positive && !a.positive) {
        this->positive = true;
        a.positive = true;
        bool res = (*this > a);
        this->positive = false;
        a.positive = false;
        return res;
    }

    for (int i = (int) std::max(this->v_num.size(), a.v_num.size()); i >= -std::max(this->accuracy, a.accuracy); i--) {
        if (i == 0) {
            continue;
        }
        int x1 = this->get_ith_digit(i), x2 = a.get_ith_digit(i);
        if (x1 != x2) {
            return x1 < x2;
        }
    }
    return false;
}

bool long_number_t::operator==(long_number_t a) {
    if (this->positive != a.positive) {
        return false;
    }

    for (int i = (int) std::max(this->v_num.size(), a.v_num.size()); i >= -std::max(this->accuracy, a.accuracy); i--) {
        if (i == 0) {
            continue;
        }
        int x1 = this->get_ith_digit(i), x2 = a.get_ith_digit(i);
        if (x1 != x2) {
            return false;
        }
    }
    return true;
}

bool long_number_t::operator>(long_number_t a) {
    if (!this->positive && a.positive) {
        return false;
    }
    if (this->positive && !a.positive) {
        return true;
    }
    if (!this->positive && !a.positive) {
        this->positive = true;
        a.positive = true;
        bool res = (*this < a);
        this->positive = false;
        a.positive = false;
        return res;
    }

    return !(*this<a) && !(*this==a);
}

bool long_number_t::operator!=(long_number_t a) {
    return !(*this==a);
}

long_number_t long_number_t::operator-(long_number_t a) {
    if (!a.positive && this->positive) {
        a.positive = true;
        long_number_t result = *this + a;
        a.positive = false;
        return result;
    }
    if (a.positive && !this->positive) {
        this->positive = true;
        long_number_t result = a + *this;
        this->positive = false;
        result.positive = false;
        return result;
    }
    if (!a.positive && !this->positive) {
        a.positive = true;
        long_number_t result = a + *this;
        a.positive = false;
        return result;
    }
    if (*this < a) {
        long_number_t result = a - *this;
        result.positive = false;
        return result;
    }

    std::vector<uint8_t> new_num(this->v_num.size() + a.v_num.size() + 1, 0);

    bool need_to_add = false;
    for (int i = -std::max(this->accuracy, a.accuracy); i <= (int) std::max(this->v_num.size(), a.v_num.size()); i++) {
        if (i == 0) {
            continue;
        }
        int8_t x = this->get_ith_digit(i) - a.get_ith_digit(i) - need_to_add;
        need_to_add = false;

        if (x < 0) {
            need_to_add = true;
            x += 10;
        }
        int ind = get_ith_ind(i, new_num.size(), this->accuracy);
        if (ind >= new_num.size() || ind < 0) { // is it good solution???
            continue;
        }
        new_num[get_ith_ind(i, new_num.size(), this->accuracy)] =  x;
    }

    return long_number_t(new_num, this->positive, this->accuracy);
}



long_number_t long_number_t::operator*(long_number_t a) {
    return this->base_mult(a);
}

long_number_t long_number_t::operator/(long_number_t a) {
    bool sign = a.positive;
    a.positive = true;
    assert(a != long_number_t(0));
    if ((*this) == long_number_t(0)) {
        return long_number_t(0);
    }
    if (a == long_number_t(1)) {
        return *this;
    }

    std::vector<uint8_t> new_num(0);
    new_num.push_back(0);
    long_number_t now(1);
    long_number_t ten = long_number_t(10);
    int new_accuracy = 0;
    for (int i = 0; i < a.v_num.size() + this->v_num.size() + 1; i++) {
        while (now < a) {
            now = now * ten;
            new_num.push_back(0);
            new_accuracy++;
        }

        for (int digit = 0; digit < 10; digit++) { // =1..9?
            if (long_number_t(digit + 1) * a > now) {
                now = now - long_number_t(digit) * a;
                new_num.push_back(digit);
                break;
            }
        }

        if (i == (int) a.v_num.size() - 1) {
            break;
        }

        if (now == long_number_t(0)) {
            now = now + long_number_t(1);
        }
        now = now * ten;
        new_accuracy++;
    }

    a.positive = sign;

    //std::cout << a.convert_to_str() << ' ' << long_number_t(new_num, sign, new_num.size() - 1).convert_to_str() << std::endl;
    return *this * long_number_t(new_num, a.positive, new_accuracy);
}

int long_number_t::get_ith_ind(int i, int now_size, int now_accuracy) {
    assert(i != 0);
    if (i > 0) {
        i--;
    }

    return now_size - 1 - now_accuracy - i;
}

uint8_t long_number_t::get_ith_digit(int i) {
    int ind = get_ith_ind(i, v_num.size(), accuracy);
    if (ind < 0 || ind >= v_num.size()) {
        return 0;
    }
    return v_num[ind];
}

long_number_t long_number_t::base_mult(long_number_t a) {
    std::vector<uint8_t> new_num(this->v_num.size() + a.v_num.size() + 1, 0);
    int new_num_accuracy = this->accuracy + a.accuracy;

    for (int i = -this->accuracy; i <= (int) this->v_num.size(); i++) {
        for (int j = -a.accuracy; j <= (int) a.v_num.size(); j++) {
            if (i == 0 || j == 0) {
                continue;
            }
            if (i == -1 && j == -1) {
                int g;
            }
            int rind = 0;
            if (i > 0 && j > 0) {
                rind = i + j - 1;
            } else if (i < 0 && j < 0) {
                rind = i + j;
            } else {
                if (i + j == 0) {
                    rind = i - 1 + j;
                } else if (i + j < 0) {
                    rind = i + j - 1;
                } else {
                    rind = i + j;
                }
            }
            if (rind == 0) {
                int g;
            }
            int ind = get_ith_ind(rind, new_num.size(), new_num_accuracy);
            if (ind >= new_num.size() || ind < 0) { // is it good solution???
                continue;
            }
            new_num[ind] += this->get_ith_digit(i) * a.get_ith_digit(j);

            while (new_num[ind] > 9) {
                new_num[ind - 1] += new_num[ind] / 10;
                new_num[ind] %= 10;
                ind--;
            }
        }
    }

    return long_number_t(new_num, 1 - (this->positive ^ a.positive), new_num_accuracy);
}

long_number_t operator"" _to_long_num(long double x) {
    return long_number_t(x);
}