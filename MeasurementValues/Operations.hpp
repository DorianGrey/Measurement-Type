/*
 * Operations.hpp
 *
 *  Created on: 16.06.2012
 *      Author: doriangrey
 */

#ifndef OPERATIONS_HPP_
#define OPERATIONS_HPP_

#include "TypeChecks.hpp"
#include "Value.hpp"

/**
 * This struct only exists for simplyfing reasons, since... well, it's huge :D
 * Note that it is _only_ required or useful if the decltype() thing in the templates below does not work,
 * or if you prefer this kind.
 * Note that the following expressions are technically equivalent:
 *      value<typename SelectValid<T1, T2>::type_t, Measurement::Unit::WpS>
 *      value<decltype(v1.val/v2.val), Measurement::Unit::WpS>
 * I.e., SelectValid selects the bigger type of the given ones, checks if the smaller one is convertible
 * to the bigger one and activates the typedef only if this constraint is fulfilled. For most cases, this
 * is automatically performed through the numeric cast. I.e., using decltype for deducing the correct result
 * type is preferable.
 */
template<typename T1, typename T2>
struct SelectValid
{
    typedef typename enable_if<is_convertible<typename size_check<T1, T2>::smaller_t, typename size_check<T1, T2>::bigger_t>::result,
            typename size_check<T1, T2>::bigger_t>::type type_t;
};

// Allowed operators for division
//
template<typename T1, typename T2>
auto operator/(const Measurement::Value<T1, Measurement::Unit::WATT>& v1, const Measurement::Value<T2, Measurement::Unit::SEC>& v2) -> Measurement::Value<decltype(v1.val/v2.val), Measurement::Unit::WpS>
{
    return Measurement::Value<decltype(v1.val/v2.val), Measurement::Unit::WpS>{ v1.val/v2.val };
}

// Allowed operators for multiplication

/**
 * For WATT*SEC
 */
template<typename T1, typename T2>
auto operator*(const Measurement::Value<T1, Measurement::Unit::WATT>& v1, const Measurement::Value<T2, Measurement::Unit::SEC>& v2) -> Measurement::Value<decltype(v1.val* v2.val), Measurement::Unit::WS>
{
    return Measurement::Value<decltype(v1.val* v2.val), Measurement::Unit::WS>{ v1.val*v2.val };
}
template<typename T1, typename T2>
auto operator*(const Measurement::Value<T1, Measurement::Unit::SEC>& v1, const Measurement::Value<T2, Measurement::Unit::WATT>& v2) -> Measurement::Value<decltype(v1.val* v2.val), Measurement::Unit::WS>
{
    return Measurement::Value<decltype(v1.val* v2.val), Measurement::Unit::WS>{ v1.val*v2.val };
}

/**
 * For WS / WpS -> SQUARE_SEC
 *
 */
template<typename T1, typename T2>
auto operator/(const Measurement::Value<T1, Measurement::Unit::WS>& v1, const Measurement::Value<T2, Measurement::Unit::WpS>& v2) -> Measurement::Value<decltype(v1.val* v2.val), Measurement::Unit::Square_SEC>
{
    return Measurement::Value<decltype(v1.val* v2.val), Measurement::Unit::Square_SEC>{ v1.val*v2.val };
}
#endif /* OPERATIONS_HPP_ */
