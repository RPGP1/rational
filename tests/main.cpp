#include "rational.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("construct")
{
    REQUIRE_NOTHROW(Rational{2});
    REQUIRE_NOTHROW(Rational{2, 3});
    REQUIRE_NOTHROW(Rational{2, 3u});
    REQUIRE_NOTHROW(static_cast<Rational<int>>(2));

    REQUIRE_NOTHROW(Rational{2l});
    REQUIRE_NOTHROW(Rational{2l, 3l});
    REQUIRE_NOTHROW(Rational{2l, 3ul});
    REQUIRE_NOTHROW(static_cast<Rational<long>>(2l));

    REQUIRE_THROWS(Rational{2, 0});
}

TEST_CASE("compare")
{
    REQUIRE(Rational{1, 3} == Rational{1, 3});
    REQUIRE_FALSE(Rational{1, 3} == Rational{2, 5});
    REQUIRE(Rational{1, 3} != Rational{2, 5});
    REQUIRE_FALSE(Rational{1, 3} != Rational{1, 3});

    REQUIRE(Rational{1, 3} < Rational{2, 5});
    REQUIRE_FALSE(Rational{2, 5} < Rational{1, 3});
    REQUIRE_FALSE(Rational{1, 3} < Rational{1, 3});
    REQUIRE(Rational{2, 5} > Rational{1, 3});
    REQUIRE_FALSE(Rational{1, 3} > Rational{2, 5});
    REQUIRE_FALSE(Rational{1, 3} > Rational{1, 3});
    REQUIRE(Rational{1, 3} <= Rational{2, 5});
    REQUIRE_FALSE(Rational{2, 5} <= Rational{1, 3});
    REQUIRE(Rational{1, 3} <= Rational{1, 3});
    REQUIRE(Rational{2, 5} >= Rational{1, 3});
    REQUIRE_FALSE(Rational{1, 3} >= Rational{2, 5});
    REQUIRE(Rational{1, 3} >= Rational{1, 3});
}

TEST_CASE("reduction")
{
    REQUIRE(Rational{2} == Rational{2, 1});
    REQUIRE(Rational{4, 2} == Rational{2, 1});
    REQUIRE(Rational{-4, -2} == Rational{2, 1});

    REQUIRE(Rational{-2} == Rational{-2, 1});
    REQUIRE(Rational{-4, 2} == Rational{-2, 1});
    REQUIRE(Rational{4, -2} == Rational{-2, 1});

    REQUIRE(Rational{0, 2} == Rational{0, 1});
    REQUIRE(Rational{0, -2} == Rational{0, 1});
}

TEST_CASE("convert")
{
    REQUIRE((signed char){Rational{3, 2}} == (signed char){1});
    REQUIRE(short{Rational{3, 2}} == short{1});
    REQUIRE(int{Rational{3, 2}} == int{1});
    REQUIRE(long{Rational{3, 2}} == long{1});
    REQUIRE((long long){Rational{3, 2}} == (long long){1});
    REQUIRE((unsigned char){Rational{3, 2}} == (unsigned char){1});
    REQUIRE((unsigned short){Rational{3, 2}} == (unsigned short){1});
    REQUIRE((unsigned int){Rational{3, 2}} == (unsigned int){1});
    REQUIRE((unsigned long){Rational{3, 2}} == (unsigned long){1});
    REQUIRE((unsigned long long){Rational{3, 2}} == (unsigned long long){1});

    REQUIRE((signed char){Rational{-3, 2}} == (signed char){-1});
    REQUIRE(short{Rational{-3, 2}} == short{-1});
    REQUIRE(int{Rational{-3, 2}} == int{-1});
    REQUIRE(long{Rational{-3, 2}} == long{-1});
    REQUIRE((long long){Rational{-3, 2}} == (long long){-1});

    REQUIRE((signed char){Rational{2}} == (signed char){2});
    REQUIRE(short{Rational{2}} == short{2});
    REQUIRE(int{Rational{2}} == int{2});
    REQUIRE(long{Rational{2}} == long{2});
    REQUIRE((long long){Rational{2}} == (long long){2});
    REQUIRE((unsigned char){Rational{2}} == (unsigned char){2});
    REQUIRE((unsigned short){Rational{2}} == (unsigned short){2});
    REQUIRE((unsigned int){Rational{2}} == (unsigned int){2});
    REQUIRE((unsigned long){Rational{2}} == (unsigned long){2});
    REQUIRE((unsigned long long){Rational{2}} == (unsigned long long){2});

    using namespace Catch::literals;
    REQUIRE(float{Rational{1, 2}} == 0.5_a);
    REQUIRE(double{Rational{1, 2}} == 0.5_a);
    REQUIRE((long double){Rational{1, 2}} == 0.5_a);
    REQUIRE(float{Rational{-1, 2}} == -0.5_a);
    REQUIRE(double{Rational{-1, 2}} == -0.5_a);
    REQUIRE((long double){Rational{-1, 2}} == -0.5_a);
    REQUIRE(float{Rational{2}} == 2_a);
    REQUIRE(double{Rational{2}} == 2_a);
    REQUIRE((long double){Rational{2}} == 2_a);
    REQUIRE(float{Rational{-2}} == -2_a);
    REQUIRE(double{Rational{-2}} == -2_a);
    REQUIRE((long double){Rational{-2}} == -2_a);


    REQUIRE(static_cast<Rational<int>>(Rational{3l, 2ul}) == Rational{3, 2});

    // implicit conversion
    REQUIRE(Rational{3l, 2l} == []() -> Rational<long> { return Rational{3, 2}; }());
}

TEST_CASE("unary_ops")
{
    Rational a{-1, 3};
    REQUIRE(+a == a);
    REQUIRE(-a == Rational{1, 3});
    REQUIRE(a.inverse() == Rational{-3, 1});

    REQUIRE_THROWS(Rational{0}.inverse());
}

TEST_CASE("binary_ops")
{
    REQUIRE(Rational{1, 3} + Rational{1, 6} == Rational{1, 2});
    REQUIRE(Rational{-1, 3} + Rational{-1, 6} == Rational{-1, 2});
    REQUIRE(Rational{1, 2} + Rational{-1, 3} == Rational{1, 6});

    REQUIRE(Rational{1, 2} - Rational{1, 3} == Rational{1, 6});
    REQUIRE(Rational{-1, 2} - Rational{-1, 3} == Rational{-1, 6});
    REQUIRE(Rational{1, 3} - Rational{-1, 6} == Rational{1, 2});

    REQUIRE(Rational{1, 4} * Rational{2, 3} == Rational{1, 6});
    REQUIRE(Rational{-1, 4} * Rational{2, 3} == Rational{-1, 6});
    REQUIRE(Rational{1, 4} * Rational{-2, 3} == Rational{-1, 6});
    REQUIRE(Rational{-1, 4} * Rational{-2, 3} == Rational{1, 6});

    REQUIRE(Rational{1, 4} / Rational{3, 2} == Rational{1, 6});
    REQUIRE(Rational{-1, 4} / Rational{3, 2} == Rational{-1, 6});
    REQUIRE(Rational{1, 4} / Rational{-3, 2} == Rational{-1, 6});
    REQUIRE(Rational{-1, 4} / Rational{-3, 2} == Rational{1, 6});

    REQUIRE_THROWS(Rational{1} / Rational{0});

    REQUIRE(Rational{1, 3} + 1 == Rational{4, 3});
    REQUIRE(Rational{-1, 3} + 1 == Rational{2, 3});
    REQUIRE(1 + Rational{1, 3} == Rational{4, 3});
    REQUIRE(1 + Rational{-1, 3} == Rational{2, 3});

    REQUIRE(Rational{1, 2} - 1 == Rational{-1, 2});
    REQUIRE(Rational{-1, 2} - 1 == Rational{-3, 2});
    REQUIRE(1 - Rational{1, 2} == Rational{1, 2});
    REQUIRE(1 - Rational{-1, 2} == Rational{3, 2});

    REQUIRE(Rational{1, 4} * 2 == Rational{1, 2});
    REQUIRE(Rational{-1, 4} * 2 == Rational{-1, 2});
    REQUIRE(Rational{1, 4} * -2 == Rational{-1, 2});
    REQUIRE(Rational{-1, 4} * -2 == Rational{1, 2});
    REQUIRE(2 * Rational{1, 4} == Rational{1, 2});
    REQUIRE(2 * Rational{-1, 4} == Rational{-1, 2});
    REQUIRE(-2 * Rational{1, 4} == Rational{-1, 2});
    REQUIRE(-2 * Rational{-1, 4} == Rational{1, 2});

    REQUIRE(Rational{9, 4} / 6 == Rational{3, 8});
    REQUIRE(Rational{-9, 4} / 6 == Rational{-3, 8});
    REQUIRE(Rational{9, 4} / -6 == Rational{-3, 8});
    REQUIRE(Rational{-9, 4} / -6 == Rational{3, 8});
    REQUIRE(6 / Rational{9, 4} == Rational{8, 3});
    REQUIRE(6 / Rational{-9, 4} == Rational{-8, 3});
    REQUIRE(-6 / Rational{9, 4} == Rational{-8, 3});
    REQUIRE(-6 / Rational{-9, 4} == Rational{8, 3});
}

using my_ratio = ratio<Rational{1, 1000}>;
static_assert(std::is_same_v<my_ratio, std::ratio<1, 1000>>);
static_assert(std::is_same_v<std::ratio<1, 1000>, ratio<Rational{std::ratio<1, 1000>{}}>>);
