/*
 * Value.hpp
 *
 *  Created on: 22.08.2012
 *      Author: doriangrey
 */
#ifndef VALUE_HPP_
#define VALUE_HPP_

/// Project-includes
#include "Units.hpp"
/// std-includes
#include <initializer_list>
#include <limits>

namespace Measurement
{
    /** \brief This is the basic value class. It supports a default c'tor
    *         (using std::numeric_limits), an initializer-list c'tor,
    *         a general copy c'tor and an assingment operator.
    *         Note that the internal value is _not_ covered directly, due
    *         to some technical restrictions. So be careful :)
    *
    * \param T Numeric value type.
    * \param unit One of Measurement::Unit.
    *
    */
    template<typename T, Measurement::Unit unit>
    struct Value
    {
        Value(void) : val(std::numeric_limits<T>::max())
        {}

        Value(std::initializer_list<T> list) : val(*(list.begin()))
        {}

        // Copy c'tor - we accept any compatible type, i.e. there should be a valid conversion.
        template<typename S>
        Value(const Value< S, unit >& other) : val(static_cast<T>(other.val))
        {}

        // Assingment operator - we accept any compatible type, i.e. there should be a valid conversion.
        template<typename S>
        Value& operator=(const Value< S, unit >& other)
        {
            this->val = static_cast<T>(other.val);
            return *this;
        }

        // Multiplying with any compatible integral value is ok.
        Value operator*(const T other)
        {
            return Value<T, unit> {this->val * other};
        }

        void operator*=(const T other)
        {
            this->val *= other;
        }

        // Division with any compatible integral value is ok.
        Value operator/(const T other)
        {
            return Value<T, unit> {this->val / other};
        }

        void operator/=(const T other)
        {
            this->val /= other;
        }

        T val;
    };
}




#endif /* VALUE_HPP_ */
