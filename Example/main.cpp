/*
 * Main.cpp
 *
 *  Created on: 16.06.2012
 *      Author: doriangrey
 */

#include "MeasurementValues/Operations.hpp"
#include <iostream>
#include <string>
#include <sstream>

int main(int /*argc*/, char** /*argv*/)
{
    Measurement::Value<float, Measurement::Unit::WATT> val1{ 5.1234f };            /**< Immediate initialization using initializer list */
    Measurement::Value<float, Measurement::Unit::SEC> val2 = { 11.0f };            /**< Create object from initializer list and assign it */
    Measurement::Value<float, Measurement::Unit::WpS> val3 = val1 / val2;          /**< Assignment operator */
    Measurement::Value<float, Measurement::Unit::WS> val4 = val2 * val1;           /**< Assignment operator */
    Measurement::Value<float, Measurement::Unit::Square_SEC> val6 = val4 / val3;   /**< Assignment operator */
    Measurement::Value<double, Measurement::Unit::Square_SEC> val5 = val6;         /**< Assignment operator with internal conversion float->double*/

    /// Testing istream support.
    std::stringstream blabbel;
    blabbel << "54.3f";
    blabbel >> val2;

    /// Testing integral scaling.
    std::cout << "<Test1::Begin> Testing integral scaling..." << std::endl;
    Measurement::Value<float, Measurement::Unit::SEC> val7{ 12.34f };
    val7 = val2*3;

    std::cout << val7 << std::endl;
    val7 *= 4;
    std::cout << val7 << std::endl;
    val7 = val2/4;
    std::cout << val7 << std::endl;
    val7 /= 3;
    std::cout << val7 << std::endl;
    std::cout << "<Test1::End> Testing integral scaling finished..." << std::endl;

    std::cout << val1 << std::endl;
    std::cout << val3 << std::endl;
    std::cout << val4 << std::endl;
    std::cout << val5 << std::endl;
    std::cout << val6 << std::endl;
    std::cout << val5+val6 << std::endl;
    std::cout << val5-val6 << std::endl;

    return 0;
}
