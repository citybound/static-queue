//
// Copyright 2013 (C). Alex Robenko. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software
// is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//
// original source: https://github.com/arobenko/embxx/blob/master/embxx/util/SizeToType.h
// original license: GPLv3
// relicensed to MIT with explicit permission from Alex Robenko
//

/// @file embxx/util/SizeToType.h
/// Contains specialisation of SizeToType class for several sizes.

#ifndef SQUEUE_SIZETOTYPE_H
#define SQUEUE_SIZETOTYPE_H

#include <array>
#include <cstdint>

namespace squeue
{

namespace details
{

template <std::size_t TSize>
struct SizeToTypeHelper {
    typedef std::array<std::uint8_t, TSize> Type;
};

template <>
struct SizeToTypeHelper<1>
{
    typedef std::uint8_t Type;
};

template <>
struct SizeToTypeHelper<2>
{
    typedef std::uint16_t Type;
};

template <>
struct SizeToTypeHelper<4>
{
    typedef std::uint32_t Type;
};

template <>
struct SizeToTypeHelper<8>
{
    typedef std::uint64_t Type;
};

template <>
struct SizeToTypeHelper<3>
{
    typedef typename SizeToTypeHelper<4>::Type Type;
};

template <>
struct SizeToTypeHelper<5>
{
    typedef typename SizeToTypeHelper<8>::Type Type;
};

template <>
struct SizeToTypeHelper<6>
{
    typedef typename SizeToTypeHelper<8>::Type Type;
};

template <>
struct SizeToTypeHelper<7>
{
    typedef typename SizeToTypeHelper<8>::Type Type;
};


}  // namespace details

/// @addtogroup util
/// @{

/// @brief Type information based on size known at compile time.
/// @details Maps size to unsigned integral type. If signed type is
///          needed, set TSigned teplate parameter to true.
///          The types are as following:
///          @li SizeToType<1>::Type is std::uint8_t
///          @li SizeToType<1, true>::Type is std::int8_t
///          @li SizeToType<2>::Type is std::uint16_t
///          @li SizeToType<2, true>::Type is std::int16_t
///          @li SizeToType<3>::Type is std::uint32_t
///          @li SizeToType<3, true>::Type is std::int32_t
///          @li SizeToType<4>::Type is std::uint32_t
///          @li SizeToType<4, true>::Type is std::int32_t
///          @li SizeToType<5>::Type is std::uint64_t
///          @li SizeToType<5, true>::Type is std::int64_t
///          @li SizeToType<6>::Type is std::uint64_t
///          @li SizeToType<6, true>::Type is std::int64_t
///          @li SizeToType<7>::Type is std::uint64_t
///          @li SizeToType<7, true>::Type is std::int64_t
///          @li SizeToType<8>::Type is std::uint64_t
///          @li SizeToType<8, true>::Type is std::int64_t
///          @li All other sizes are typedefed to std::array<std::uint8_t, Size>
///              or std::array<std::int8_t, Size> based on TSigned parameter
/// @tparam TSize Size, compile time constant
/// @tparam TSigned Specifies whether the type must be signed. False by default
/// @headerfile embxx/util/SizeToType.h
template <std::size_t TSize, bool TSigned = false>
class SizeToType
{
    typedef typename SizeToType<1, TSigned>::Type ByteType;

public:
    /// Generic type definition
    typedef std::array<ByteType, TSize> Type;
};

/// @cond DOCUCMENT_SIZE_TO_TYPE_SPECIALISATION
template <std::size_t TSize>
struct SizeToType<TSize, false>
{
    typedef typename details::SizeToTypeHelper<TSize>::Type Type;
};

template <std::size_t TSize>
struct SizeToType<TSize, true>
{
    typedef typename
        std::make_signed<
            typename SizeToType<TSize, false>::Type
        >::type Type;
};

/// @endcond

/// @}

}  // namespace squeue

#endif //SQUEUE_SIZETOTYPE_H