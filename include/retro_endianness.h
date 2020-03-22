/* Copyright  (C) 2010-2020 The RetroArch team
 *
 * ---------------------------------------------------------------------------------------
 * The following license statement only applies to this file (retro_endianness.h).
 * ---------------------------------------------------------------------------------------
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __LIBRETRO_SDK_ENDIANNESS_H
#define __LIBRETRO_SDK_ENDIANNESS_H

#include <retro_inline.h>
#include <stdint.h>
#include <stdlib.h>

#if defined(_MSC_VER) && _MSC_VER > 1200
#define SWAP16 _byteswap_ushort
#define SWAP32 _byteswap_ulong
#else
#define SWAP16(x) ((uint16_t)(                  \
         (((uint16_t)(x) & 0x00ff) << 8)      | \
         (((uint16_t)(x) & 0xff00) >> 8)        \
          ))
#define SWAP32(x) ((uint32_t)(           \
         (((uint32_t)(x) & 0x000000ff) << 24) | \
         (((uint32_t)(x) & 0x0000ff00) <<  8) | \
         (((uint32_t)(x) & 0x00ff0000) >>  8) | \
         (((uint32_t)(x) & 0xff000000) >> 24)   \
         ))
#endif

#if defined(_MSC_VER) && _MSC_VER <= 1200
#define SWAP64(val)                                             \
	((((uint64_t)(val) & 0x00000000000000ff) << 56)      \
	 | (((uint64_t)(val) & 0x000000000000ff00) << 40)    \
	 | (((uint64_t)(val) & 0x0000000000ff0000) << 24)    \
	 | (((uint64_t)(val) & 0x00000000ff000000) << 8)     \
	 | (((uint64_t)(val) & 0x000000ff00000000) >> 8)     \
	 | (((uint64_t)(val) & 0x0000ff0000000000) >> 24)    \
	 | (((uint64_t)(val) & 0x00ff000000000000) >> 40)    \
	 | (((uint64_t)(val) & 0xff00000000000000) >> 56))
#else
#define SWAP64(val)                                             \
	((((uint64_t)(val) & 0x00000000000000ffULL) << 56)      \
	 | (((uint64_t)(val) & 0x000000000000ff00ULL) << 40)    \
	 | (((uint64_t)(val) & 0x0000000000ff0000ULL) << 24)    \
	 | (((uint64_t)(val) & 0x00000000ff000000ULL) << 8)     \
	 | (((uint64_t)(val) & 0x000000ff00000000ULL) >> 8)     \
	 | (((uint64_t)(val) & 0x0000ff0000000000ULL) >> 24)    \
	 | (((uint64_t)(val) & 0x00ff000000000000ULL) >> 40)    \
	 | (((uint64_t)(val) & 0xff00000000000000ULL) >> 56))
#endif


#if defined (LSB_FIRST) || defined (MSB_FIRST)
#warning Defining MSB_FIRST and LSB_FIRST in compile options is deprecated
#undef LSB_FIRST
#undef MSB_FIRST
#endif

#ifdef _MSC_VER
#include <winsock2.h>
#include <sys/param.h>
#endif

#if defined (BYTE_ORDER) && defined (BIG_ENDIAN) && defined (LITTLE_ENDIAN)
#if BYTE_ORDER == BIG_ENDIAN
#define MSB_FIRST 1
#elif BYTE_ORDER == LITTLE_ENDIAN
#define LSB_FIRST 1
#else
#error "Invalid endianness macros"
#endif
#elif defined (__BYTE_ORDER__) && defined (__ORDER_BIG_ENDIAN__) && defined (__ORDER_LITTLE_ENDIAN__)
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define MSB_FIRST 1
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define LSB_FIRST 1
#else
#error "Invalid endianness macros"
#endif
#elif defined (__i386__) || defined(__x86_64__)
#define LSB_FIRST 1
#else
#error "Unknown platform"
#endif

#if defined(MSB_FIRST) && defined(LSB_FIRST)
#error "Bug in LSB_FIRST/MSB_FIRST definition"
#endif

#if !defined(MSB_FIRST) && !defined(LSB_FIRST)
#error "Bug in LSB_FIRST/MSB_FIRST definition"
#endif

/**
 * is_little_endian:
 *
 * Checks if the system is little endian or big-endian.
 *
 * Returns: greater than 0 if little-endian,
 * otherwise big-endian.
 **/
#if defined(MSB_FIRST)
#define is_little_endian() (0)
#elif defined(LSB_FIRST)
#define is_little_endian() (1)
#endif

/**
 * swap_if_big64:
 * @val        : unsigned 64-bit value
 *
 * Byteswap unsigned 64-bit value if system is big-endian.
 *
 * Returns: Byteswapped value in case system is big-endian,
 * otherwise returns same value.
 **/

#if defined(MSB_FIRST)
#define swap_if_big64(val) (SWAP64(val))
#elif defined(LSB_FIRST)
#define swap_if_big64(val) (val)
#endif

/**
 * swap_if_big32:
 * @val        : unsigned 32-bit value
 *
 * Byteswap unsigned 32-bit value if system is big-endian.
 *
 * Returns: Byteswapped value in case system is big-endian,
 * otherwise returns same value.
 **/

#if defined(MSB_FIRST)
#define swap_if_big32(val) (SWAP32(val))
#elif defined(LSB_FIRST)
#define swap_if_big32(val) (val)
#endif

/**
 * swap_if_little64:
 * @val        : unsigned 64-bit value
 *
 * Byteswap unsigned 64-bit value if system is little-endian.
 *
 * Returns: Byteswapped value in case system is little-endian,
 * otherwise returns same value.
 **/

#if defined(MSB_FIRST)
#define swap_if_little64(val) (val)
#elif defined(LSB_FIRST)
#define swap_if_little64(val) (SWAP64(val))
#endif

/**
 * swap_if_little32:
 * @val        : unsigned 32-bit value
 *
 * Byteswap unsigned 32-bit value if system is little-endian.
 *
 * Returns: Byteswapped value in case system is little-endian,
 * otherwise returns same value.
 **/

#if defined(MSB_FIRST)
#define swap_if_little32(val) (val)
#elif defined(LSB_FIRST)
#define swap_if_little32(val) (SWAP32(val))
#endif

/**
 * swap_if_big16:
 * @val        : unsigned 16-bit value
 *
 * Byteswap unsigned 16-bit value if system is big-endian.
 *
 * Returns: Byteswapped value in case system is big-endian,
 * otherwise returns same value.
 **/

#if defined(MSB_FIRST)
#define swap_if_big16(val) (SWAP16(val))
#elif defined(LSB_FIRST)
#define swap_if_big16(val) (val)
#endif

/**
 * swap_if_little16:
 * @val        : unsigned 16-bit value
 *
 * Byteswap unsigned 16-bit value if system is little-endian.
 *
 * Returns: Byteswapped value in case system is little-endian,
 * otherwise returns same value.
 **/

#if defined(MSB_FIRST)
#define swap_if_little16(val) (val)
#elif defined(LSB_FIRST)
#define swap_if_little16(val) (SWAP16(val))
#endif

/**
 * store32be:
 * @addr        : pointer to unsigned 32-bit buffer
 * @data        : unsigned 32-bit value to write
 *
 * Write data to address. Endian-safe. Byteswaps the data
 * first if necessary before storing it.
 **/
static INLINE void store32be(uint32_t *addr, uint32_t data)
{
   *addr = swap_if_little32(data);
}

/**
 * load32be:
 * @addr        : pointer to unsigned 32-bit buffer
 *
 * Load value from address. Endian-safe.
 *
 * Returns: value from address, byte-swapped if necessary.
 **/
static INLINE uint32_t load32be(const uint32_t *addr)
{
   return swap_if_little32(*addr);
}

#endif
