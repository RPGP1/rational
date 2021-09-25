#pragma once

#include "rational.hpp"

#include <cmath>
#include <concepts>
#include <numeric>
#include <stdexcept>

template <std::signed_integral T>
constexpr auto Rational<T>::check_zero_denominator() const -> const Rational&
{
    if (denom_ == 0) {
        throw std::range_error{"0 is given as denom of Rational"};
    }
    return *this;
}
template <std::signed_integral T>
constexpr auto Rational<T>::reduction() noexcept -> Rational&
{
    const auto gcd = std::gcd(numer_, static_cast<NumeratorType>(denom_));
    numer_ = static_cast<NumeratorType>(numer_ / gcd);
    denom_ = static_cast<DenominatorType>(denom_ / gcd);
    return *this;
}

template <std::signed_integral T>
constexpr Rational<T>::Rational(NumeratorType numer, DenominatorType denom) : Rational{simple_copy_, numer, denom}
{
    check_zero_denominator();
    reduction();
}
template <std::signed_integral T>
constexpr Rational<T>::Rational(NumeratorType numer, NumeratorType denom)
    : Rational{static_cast<NumeratorType>(std::signbit(denom) ? -numer : numer), static_cast<DenominatorType>(std::abs(denom))}
{
}
template <std::signed_integral T>
constexpr Rational<T>::Rational(SimpleCopy, NumeratorType numer, DenominatorType denom)
    : numer_{numer}, denom_{denom}
{
}

template <std::signed_integral T>
template <class U>
constexpr Rational<T>::operator U() const noexcept
{
    return static_cast<U>(static_cast<U>(numer_) / static_cast<U>(denom_));
}

template <std::signed_integral T>
constexpr auto Rational<T>::operator+() const noexcept -> Rational
{
    return *this;
}
template <std::signed_integral T>
constexpr auto Rational<T>::operator-() const noexcept -> Rational
{
    return Rational{simple_copy_, static_cast<NumeratorType>(-numer_), denom_};
}
template <std::signed_integral T>
constexpr auto Rational<T>::inverse() const -> Rational
{
    auto tmp = static_cast<NumeratorType>(denom_);
    return Rational{simple_copy_, static_cast<NumeratorType>(numer_ < 0 ? -tmp : tmp), static_cast<DenominatorType>(std::abs(numer_))}.check_zero_denominator();
}

template <std::signed_integral T>
constexpr auto Rational<T>::operator+=(const Rational& other) noexcept -> Rational&
{
    const auto gcd = std::gcd(denom_, other.denom_);
    const auto this_denom_coeff = denom_ / gcd, other_denom_coeff = other.denom_ / gcd;

    return *this = Rational{simple_copy_,
               static_cast<NumeratorType>(
                   numer_ * static_cast<NumeratorType>(other_denom_coeff)
                   + static_cast<NumeratorType>(this_denom_coeff) * other.numer_),
               static_cast<DenominatorType>(denom_ * other_denom_coeff)}
                       .reduction();
}
template <std::signed_integral T>
constexpr auto Rational<T>::operator-=(const Rational& other) noexcept -> Rational&
{
    return *this += (-other);
}
template <std::signed_integral T>
constexpr auto Rational<T>::operator*=(const Rational& other) noexcept -> Rational&
{
    return *this = Rational{simple_copy_, static_cast<NumeratorType>(numer_ * other.numer_), static_cast<DenominatorType>(denom_ * other.denom_)}.reduction();
}
template <std::signed_integral T>
constexpr auto Rational<T>::operator/=(const Rational& other) -> Rational&
{
    return *this *= other.inverse();
}

template <std::signed_integral T>
constexpr auto Rational<T>::operator+=(T other) noexcept -> Rational&
{
    numer_ = static_cast<NumeratorType>(numer_ + static_cast<NumeratorType>(denom_) * other);
    return *this;
}
template <std::signed_integral T>
constexpr auto Rational<T>::operator-=(T other) noexcept -> Rational&
{
    return *this += (-other);
}
template <std::signed_integral T>
constexpr auto Rational<T>::operator*=(T other) noexcept -> Rational&
{
    return *this = Rational{simple_copy_, static_cast<NumeratorType>(numer_ * other), denom_}.reduction();
}
template <std::signed_integral T>
constexpr auto Rational<T>::operator/=(T other) -> Rational&
{
    return *this = Rational{numer_, static_cast<NumeratorType>(static_cast<NumeratorType>(denom_) * other)};
}

template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator==(const Rational<T>& lhs, const Rational<U>& rhs) noexcept
{
    return lhs.numer() == rhs.numer() && lhs.denom() == rhs.denom();
}
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator!=(const Rational<T>& lhs, const Rational<U>& rhs) noexcept
{
    return !(lhs == rhs);
}

template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator<(const Rational<T>& lhs, const Rational<U>& rhs) noexcept
{
    using NumeratorType = std::common_type_t<T, U>;
    return lhs.numer() * static_cast<NumeratorType>(rhs.denom()) < rhs.numer() * static_cast<NumeratorType>(lhs.denom());
}
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator>(const Rational<T>& lhs, const Rational<U>& rhs) noexcept
{
    return rhs < lhs;
}
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator<=(const Rational<T>& lhs, const Rational<U>& rhs) noexcept
{
    return !(lhs > rhs);
}
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr bool operator>=(const Rational<T>& lhs, const Rational<U>& rhs) noexcept
{
    return !(lhs < rhs);
}

template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr Rational<std::common_type_t<T, U>> operator+(const Rational<T>& lhs, const Rational<U>& rhs) noexcept
{
    return Rational<std::common_type_t<T, U>>{lhs} += rhs;
}
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr Rational<std::common_type_t<T, U>> operator-(const Rational<T>& lhs, const Rational<U>& rhs) noexcept
{
    return Rational<std::common_type_t<T, U>>{lhs} -= rhs;
}
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr Rational<std::common_type_t<T, U>> operator*(const Rational<T>& lhs, const Rational<U>& rhs) noexcept
{
    return Rational<std::common_type_t<T, U>>{lhs} *= rhs;
}
template <std::signed_integral T, std::signed_integral U>
requires std::common_with<T, U> constexpr Rational<std::common_type_t<T, U>> operator/(const Rational<T>& lhs, const Rational<U>& rhs)
{
    return Rational<std::common_type_t<T, U>>{lhs} /= rhs;
}
