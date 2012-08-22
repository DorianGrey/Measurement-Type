/*
 * Value.hpp
 *
 *  Created on: 22.08.2012
 *      Author: doriangrey
 */
#ifndef UNITS_H
#define UNITS_H

namespace Measurement
{
    /** \brief Enum that includes supported basic types. Note that this is an enum class,
               i.e. it enforces access like Unit::WATT, and a numeric value cannot be used
               directly.
    */
    enum class Unit
    {
        WATT,
        SEC,
        WS,
        WpS,
        Square_SEC     // WS / WpS = WS * (S/W) = S*S
    };
}




#endif // MEASUREMENTUNIT_H
