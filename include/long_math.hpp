#ifndef LONGMATH_HPP_INCLUDED
#define LONGMATH_HPP_INCLUDED

class long_number_t {
private:
    std::vector<uint8_t> v_num;
    unsigned accuracy;
    bool positive;

    explicit long_number_t(const std::vector<uint8_t>& base_vec, bool base_positive, unsigned base_accuracy);

    int get_ith_ind(int i, int now_size, unsigned now_accuracy) const;
    uint8_t get_ith_digit(int i) const;

    long_number_t base_mult(const long_number_t& a) const;
    bool positive_less(const long_number_t& a) const;
    long_number_t positive_add(const long_number_t& a) const;
    long_number_t positive_subtract(const long_number_t& a) const;

public:
    explicit long_number_t(const std::string& number);
    explicit long_number_t(long double x);

    std::string convert_to_str();

    bool operator<(const long_number_t& a) const;
    bool operator==(const long_number_t& a) const;
    std::strong_ordering operator<=>(const long_number_t& a) const;

    long_number_t operator+(const long_number_t& a) const;
    long_number_t operator-(const long_number_t& a) const;
    long_number_t operator*(const long_number_t& a) const;
    long_number_t operator/(const long_number_t& a) const;
};

#endif // LONGMATH_HPP_INCLUDED