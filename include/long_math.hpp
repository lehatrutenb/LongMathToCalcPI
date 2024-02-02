#ifndef LONGMATH_HPP_INCLUDED
#define LONGMATH_HPP_INCLUDED

class long_number_t {
private:
    int accuracy;
    int get_ith_ind(int i, int now_size, int now_accuracy);
    uint8_t get_ith_digit(int i);
    long_number_t base_mult(long_number_t a);

public:
    bool positive;
    std::vector<uint8_t> v_num;
    explicit long_number_t(std::string number);
    explicit long_number_t(std::vector<uint8_t> base_vec, bool base_positive, int base_accuracy);
    explicit long_number_t(long double x);

    std::string convert_to_str();

    bool operator<(long_number_t a); // ToDo: const for *this;
    bool operator==(long_number_t a); // add & reference everywhere
    bool operator>(long_number_t a);
    bool operator!=(long_number_t a);

    long_number_t operator+(long_number_t a);
    long_number_t operator-(const long_number_t a);
    long_number_t operator*(long_number_t a);
    long_number_t operator/(long_number_t a);
};

//long_number_t operator"" _to_long_num(long double x);

#endif // LONGMATH_HPP_INCLUDED