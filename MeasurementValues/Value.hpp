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
#include <iostream>         /**< Note: Optional! If you don't need this in your project, comment it out, same for the friend functions below */
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
    class Value
    {
        public:
            Value(void) : val(std::numeric_limits<T>::max())
            {}

            Value(std::initializer_list<T> list) : val(*(list.begin()))
            {}

            // Copy c'tor - we accept any compatible type, i.e. there should be a valid conversion.
            template<typename S>
            Value(const Value< S, unit >& other) : val(static_cast<T>(other.Get()))
            {}

            T Get() const
            {
                return this->val;
            }

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

            // Additions are ok, as long as the unit is the same are the numeric values are compatible.
            // Note that S may be larger or smaller than T, we're automatically deducing the resulting type.
            template<typename S>
            auto operator+(const Value<S, unit>& other) -> Value<decltype(this->Get()+other.Get()), unit>
            {
                return Value<decltype(this->Get()+other.Get()), unit> {this->Get() + other.Get()};
            }

            // Note: For internal value change, we need to ensure that S can be casted to T.
            template<typename S>
            void operator+=(const Value<S, unit>& other)
            {
                this->val += static_cast<T>(other.Get());
            }

            // Subtracts are ok, as long as the unit is the same are the numeric values are compatible.
            // Note that S may be larger or smaller than T, we're automatically deducing the resulting type.
            template<typename S>
            auto operator-(const Value<S, unit>& other) -> Value<decltype(this->Get()-other.Get()), unit>
            {
                return Value<decltype(this->Get()-other.Get()), unit> {this->Get() - other.Get()};
            }

            // Note: For internal value change, we need to ensure that S can be casted to T.
            template<typename S>
            void operator-=(const Value<S, unit>& other)
            {
                this->val -= static_cast<T>(other.Get());
            }

            /** \brief Friend function for native ostream support. Note that, for the moment (!),
             *         this function only puts the value to the stream. Maybe I will change this
             *         in a later version.
             *
             * \param to Stream to write the value to, anything that derives from std::ostream is ok.
             * \param value Value to write to the stream.
             * \return Stream 'to', with the newly added value.
             *
             */
            friend std::ostream& operator<<(std::ostream& to, const Value<T, unit>& value)
            {
                to << value.Get();
                return to;
            }

             /** \brief Friend function for native istream support. Note that, for the moment (!),
             *          this function only picks the internal value from the stream. Maybe I will
             *          change this in a later version.
             *
             * \param to Stream to pick the value from, anything deriving from std::istream is ok.
             * \param value Value to be filled from the stream.
             * \return Stream 'from', with value cut off.
             *
             */
            friend std::istream& operator>>(std::istream& from, Value<T, unit>& value)
            {
                from >> value.val;
                return from;
            }
        private:
            T val;
    };
}




#endif /* VALUE_HPP_ */
