/*
 * TypeChecks.hpp
 *
 *  Created on: 16.06.2012
 *      Author: doriangrey
 */

#ifndef TYPECHECKS_HPP_
#define TYPECHECKS_HPP_

#include <cstdint>

//===
template<bool condition, typename TrueType, typename FalseType>
struct IF
{
        typedef TrueType type_t;
};

template<typename TrueType, typename FalseType>
struct IF<false, TrueType, FalseType>
{
        typedef FalseType type_t;
};
//===
//===
template<bool condition, typename Enabled>
struct enable_if
{
        typedef Enabled type;
};
template<typename Enabled>
struct enable_if<false, Enabled>
{

};
//===
//===
template<typename T1, typename T2>
class is_convertible
{
        typedef char Yes;
        class No
        {
            char dummy[2];
        };
        static Yes Test(T2);
        static No Test(...);
        static T1 Make();

    public:
        enum
        {
            result = sizeof(Test(Make()) == sizeof(Yes))
        };
        enum
        {
            sameType = false
        };
};

template<typename T1>
class is_convertible<T1, T1>
{
    public:
        enum
        {
            result = true
        };
        enum
        {
            sameType = true
        };
};
//===
//===
template<typename T1, typename T2>
struct size_check
{
        typedef typename IF<(sizeof(T1) > sizeof(T2)), T1, T2>::type_t bigger_t;
        typedef typename IF<(sizeof(T1) > sizeof(T2)), T2, T1>::type_t smaller_t;
};

// Specialization: If both have equal size, but one is floating-point, the floating-point
// is considered as "bigger"
// First step: 32Bit
template<>
struct size_check<float, std::uint32_t>
{
    typedef float bigger_t;
    typedef std::uint32_t smaller_t;
};

template<>
struct size_check<std::uint32_t, float>
{
    typedef float bigger_t;
    typedef std::uint32_t smaller_t;
};

template<>
struct size_check<float, std::int32_t>
{
    typedef float bigger_t;
    typedef std::uint32_t smaller_t;
};

template<>
struct size_check<std::int32_t, float>
{
    typedef float bigger_t;
    typedef std::uint32_t smaller_t;
};

// Second step: 64Bit
template<>
struct size_check<double, std::uint64_t>
{
        typedef float bigger_t;
        typedef std::uint32_t smaller_t;
};

template<>
struct size_check<std::uint64_t, double>
{
    typedef float bigger_t;
    typedef std::uint32_t smaller_t;
};

template<>
struct size_check<double, std::int64_t>
{
    typedef float bigger_t;
    typedef std::uint32_t smaller_t;
};

template<>
struct size_check<std::int64_t, double>
{
    typedef float bigger_t;
    typedef std::uint32_t smaller_t;
};
#endif /* TYPECHECKS_HPP_ */
