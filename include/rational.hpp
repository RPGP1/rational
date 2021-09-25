#pragma once

#include <concepts>
#include <functional>
#include <ratio>
#include <type_traits>

template <std::signed_integral T>
struct Rational {
    using NumeratorType = T;
    using DenominatorType = std::make_unsigned_t<T>;

    explicit constexpr Rational(NumeratorType, DenominatorType = 1);
    explicit constexpr Rational(NumeratorType, NumeratorType);

    constexpr Rational(const Rational&) noexcept = default;
    constexpr Rational(Rational&&) noexcept = default;
    constexpr Rational& operator=(const Rational&) noexcept = default;
    constexpr Rational& operator=(Rational&&) noexcept = default;

    constexpr NumeratorType numer() const noexcept { return numer_; }
    constexpr DenominatorType denom() const noexcept { return denom_; }

    template <class U>
    explicit constexpr operator U() const noexcept;
    template <std::signed_integral U>
    requires(sizeof(T) <= sizeof(U)) constexpr operator Rational<U>() const noexcept
    {
        using ResultType = Rational<U>;
        return ResultType{simple_copy_, numer_, denom_};
    }
    template <std::signed_integral U>
    requires(sizeof(T) > sizeof(U)) constexpr explicit operator Rational<U>() const noexcept
    {
        using ResultType = Rational<U>;
        return ResultType{static_cast<ResultType::NumeratorType>(numer_), static_cast<ResultType::DenominatorType>(denom_)};
    }

    constexpr Rational operator+() const noexcept;
    constexpr Rational operator-() const noexcept;
    constexpr Rational inverse() const;

    constexpr Rational& operator+=(const Rational&) noexcept;
    constexpr Rational& operator-=(const Rational&) noexcept;
    constexpr Rational& operator*=(const Rational&) noexcept;
    constexpr Rational& operator/=(const Rational&);

    constexpr Rational& operator+=(T) noexcept;
    constexpr Rational& operator-=(T) noexcept;
    constexpr Rational& operator*=(T) noexcept;
    constexpr Rational& operator/=(T);

private:
    template <std::signed_integral U>
    friend class Rational;

    NumeratorType numer_;
    DenominatorType denom_;

    constexpr const Rational& check_zero_denominator() const;
    constexpr Rational& reduction() noexcept;

    using SimpleCopy = decltype(std::placeholders::_1);
    constexpr static SimpleCopy simple_copy_{};
    explicit constexpr Rational(SimpleCopy, NumeratorType, DenominatorType);
};

template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator==(const Rational<T>&, const Rational<U>&) noexcept;
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator!=(const Rational<T>&, const Rational<U>&) noexcept;

template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator<(const Rational<T>& lhs, const Rational<U>& rhs) noexcept;
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator>(const Rational<T>& lhs, const Rational<U>& rhs) noexcept;
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator<=(const Rational<T>& lhs, const Rational<U>& rhs) noexcept;
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator>=(const Rational<T>& lhs, const Rational<U>& rhs) noexcept;

template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr Rational<std::common_type_t<T, U>> operator+(const Rational<T>&, const Rational<U>&) noexcept;
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr Rational<std::common_type_t<T, U>> operator-(const Rational<T>&, const Rational<U>&) noexcept;
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr Rational<std::common_type_t<T, U>> operator*(const Rational<T>&, const Rational<U>&) noexcept;
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr Rational<std::common_type_t<T, U>> operator/(const Rational<T>&, const Rational<U>&);

#include "rational.ipp"
