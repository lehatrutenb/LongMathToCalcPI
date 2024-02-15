#include "gtest/gtest.h"
#include <cstdio>
#include <random>

#include "../include/long_math.hpp"
#include "../src/long_math.cpp"

#define TEST_EPS 1e-5
using namespace long_math;

class GenIntData { // generated
    public:
        std::vector<std::pair<long long, long long>> inp;
        std::vector<std::pair<long_number_t, long_number_t>> long_inp;
};

class GenDoubleData { // generated
    public:
        std::vector<std::pair<long double, long double>> inp;
        std::vector<std::pair<long_number_t, long_number_t>> long_inp;
};

class GenIntDataTest : public testing::Test {
    protected:
        void SetUp() override {
            inp.resize(50000);
            long_inp.resize(50000);
            // cover just lots of test cases
            for (int i = 0; i < inp.size(); i++) {
                long long x1 = rand() % (long long) 1e9, x2 = rand() % (long long) 1e9;
                if (rand() % 3 == 0) {
                    x1 *= -1;
                }
                if (rand() % 3 == 0) {
                    x2 *= -1;
                }

                inp[i] = std::make_pair(x1, x2);
                long_inp[i] = std::make_pair(long_number_t(x1), long_number_t(x2));
            }

            // cover every small int test
            for (int x1 = -100; x1 < 100; x1++) {
                for (int x2 = -100; x2 < 100; x2++) {
                    inp.push_back(std::make_pair(x1, x2));
                    long_inp.push_back(std::make_pair(long_number_t((long long) x1), long_number_t((long long) x2)));
                }
            }
        }
        std::vector<std::pair<long long, long long>> inp;
        std::vector<std::pair<long_number_t, long_number_t>> long_inp;
};

class GenDoubleDataTest : public testing::Test {
    protected:
        void SetUp() override {
            long double lower_bound = -1e9;
            long double upper_bound = 1e9;
            std::uniform_real_distribution<long double> unif(lower_bound, upper_bound);
            std::default_random_engine re;

            inp.resize(50000);
            long_inp.resize(50000);
            // cover just lots of test cases
            for (int i = 0; i < inp.size(); i++) {
                long double x1 = unif(re), x2 = unif(re);
                if (rand() % 3 == 0) {
                    x1 *= -1;
                }
                if (rand() % 3 == 0) {
                    x2 *= -1;
                }

                inp[i] = std::make_pair(x1, x2);
                long_inp[i] = std::make_pair(long_number_t((long double) x1), long_number_t((long double) x2));
            }

            // cover small double tests
            for (int x1 = -100; x1 < 100; x1++) {
                for (int x2 = -100; x2 < 100; x2++) {
                    inp.push_back(std::make_pair((long double) x1 / 100.0, (long double) x2 / 100.0));
                    long_inp.push_back(std::make_pair(long_number_t((long double) x1 / 100.0), long_number_t((long double) x2 / 100.0)));
                }
            }
        }
        std::vector<std::pair<long double, long double>> inp;
        std::vector<std::pair<long_number_t, long_number_t>> long_inp;
};

TEST_F(GenIntDataTest, Equal) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ((x1 == x2), (l_x1 == l_x2));
    }
}

TEST_F(GenDoubleDataTest, Equal) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ((x1 == x2), (l_x1 == l_x2));
    }
}

TEST_F(GenIntDataTest, NotEqual) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ((x1 != x2), (l_x1 != l_x2));
    }
}

TEST_F(GenDoubleDataTest, NotEqual) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ((x1 != x2), (l_x1 != l_x2));
    }
}

TEST_F(GenIntDataTest, Less) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ((x1 < x2), (l_x1 < l_x2));
    }
}

TEST_F(GenDoubleDataTest, Less) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ((x1 < x2), (l_x1 < l_x2));
    }
}

TEST_F(GenIntDataTest, Bigger) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ((x1 > x2), (l_x1 > l_x2));
    }
}

TEST_F(GenDoubleDataTest, Bigger) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ((x1 > x2), (l_x1 > l_x2));
    }
}


TEST_F(GenIntDataTest, ToString) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first;
        auto l_x1 = long_inp[i].first;

        EXPECT_EQ(stoll(l_x1.convert_to_str()), x1);
    }
}

TEST_F(GenDoubleDataTest, ToString) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = (long double) (round(inp[i].first * 1000000.0)) / 1000000.0; // such accuracy because of to_string acc
        auto l_x1 = long_number_t((long double) x1);

        EXPECT_EQ(stold(l_x1.convert_to_str()), x1);
    }
}

TEST_F(GenIntDataTest, Add) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ(long_number_t(x1 + x2), l_x1 + l_x2);
    }
}

TEST_F(GenDoubleDataTest, Add) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_NEAR(x1 + x2, stold((l_x1 + l_x2).convert_to_str()), TEST_EPS);
    }
}

TEST_F(GenIntDataTest, Decr) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ(long_number_t(x1 - x2), l_x1 - l_x2);
    }
}

TEST_F(GenDoubleDataTest, Decr) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_NEAR(x1 - x2, stold((l_x1 - l_x2).convert_to_str()), TEST_EPS);
    }
}

TEST_F(GenIntDataTest, Mult) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_EQ(long_number_t(x1 * x2), (l_x1 * l_x2));
    }
}

TEST_F(GenDoubleDataTest, Mult) {
    for (int i = inp.size() - (int) 4e4; i < inp.size(); i++) { // cut tests ! because c++ can't calc x1 * x2 accure enough
        auto x1 = inp[i].first, x2 = inp[i].second;
        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;

        EXPECT_NEAR(x1 * x2, stold((l_x1 * l_x2).convert_to_str()), TEST_EPS);
    }
}

TEST_F(GenIntDataTest, Divide) {
    for (int i = 0; i < inp.size(); i += 10) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        if (x2 == 0) {
            continue;
        }

        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;
        l_x1.set_min_divide_accuracy(10);
        l_x2.set_min_divide_accuracy(10);

        EXPECT_NEAR((long double) x1 / x2, stold((l_x1 / l_x2).convert_to_str()), TEST_EPS);
    }
}

TEST_F(GenDoubleDataTest, Divide) {
    for (int i = 0; i < inp.size(); i += 10) {
        auto x1 = inp[i].first, x2 = inp[i].second;
        if (abs(x2) < TEST_EPS) {
            continue;
        }

        auto l_x1 = long_inp[i].first, l_x2 = long_inp[i].second;
        l_x1.set_min_divide_accuracy(10);
        l_x2.set_min_divide_accuracy(10);

        EXPECT_NEAR(x1 / x2, stold((l_x1 / l_x2).convert_to_str()), TEST_EPS);
    }
}

TEST_F(GenIntDataTest, GetNegative) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first;
        auto l_x1 = long_inp[i].first;

        EXPECT_EQ(long_number_t(-x1), -l_x1);
    }
}

TEST_F(GenDoubleDataTest, GetNegative) {
    for (int i = 0; i < inp.size(); i++) {
        auto x1 = inp[i].first;
        auto l_x1 = long_inp[i].first;

        EXPECT_EQ(long_number_t(-x1), -l_x1);
    }
}

TEST(LiteralHandTest, 0) {
    EXPECT_EQ((123.123_lint).convert_to_str(), long_number_t("123.123").convert_to_str());
    EXPECT_EQ((0.000000_lint).convert_to_str(), long_number_t("0").convert_to_str());
    EXPECT_EQ((0.99999_lint).convert_to_str(), long_number_t("0.99999").convert_to_str());
}

TEST(AddHandTest, 0) {
    EXPECT_EQ(long_number_t((long double) .9999 + 0.0001).convert_to_str(), (0.9999_lint + 0.0001_lint).convert_to_str());
    EXPECT_EQ(long_number_t((long double) .9999 + 0.0001).convert_to_str(), (0.0001_lint + 0.9999_lint).convert_to_str());

    EXPECT_EQ(long_number_t((long double) -0.0000001 + 0.0000001).convert_to_str(), (-0.0000001_lint + 0.0000001_lint).convert_to_str());
    EXPECT_EQ(long_number_t((long double) -0.0000001 + 0.0000001).convert_to_str(), (0.0000001_lint + -0.0000001_lint).convert_to_str());

    EXPECT_EQ(long_number_t((long double) 0.909 + 0.0909).convert_to_str(), (0.909_lint + 0.0909_lint).convert_to_str());
    EXPECT_EQ(long_number_t((long double) 0.909 + 0.0909).convert_to_str(), (0.0909_lint + 0.909_lint).convert_to_str());
}

TEST(SetMinDivideAccHandTest, 0) {
    auto x1 = long_number_t("1");
    auto x2 = long_number_t("3");

    x1.set_min_divide_accuracy(100);

    EXPECT_TRUE((x1 / x2).convert_to_str().size() > 102);
}

TEST(SetMaxDivideAccHandTest, 0) {
    auto x1 = long_number_t("1");
    auto x2 = long_number_t("3");

    x1.set_max_divide_accuracy(10);

    EXPECT_TRUE((x1 / x2).convert_to_str().size() < 20);
}

int main(int argc, char **argv) {
    srand(1303);
    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);

    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}