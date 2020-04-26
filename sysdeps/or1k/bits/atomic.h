/* Copyright (C) 2020 Free Software Foundation, Inc.

   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _OR1K_BITS_ATOMIC_H
#define _OR1K_BITS_ATOMIC_H     1

#include <stdint.h>

typedef int8_t  atomic8_t;
typedef int16_t atomic16_t;
typedef int32_t atomic32_t;

typedef uint8_t  uatomic8_t;
typedef uint16_t uatomic16_t;
typedef uint32_t uatomic32_t;

typedef intptr_t atomicptr_t;
typedef uintptr_t uatomicptr_t;
typedef intmax_t atomic_max_t;
typedef uintmax_t uatomic_max_t;

#define atomic_compare_and_exchange_val_acq(mem, newval, oldval) \
  ({                                                                    \
    typeof (*mem) __oldval = (oldval);                                  \
    __atomic_compare_exchange_n (mem, (void *) &__oldval, newval, 0,    \
                                 __ATOMIC_ACQUIRE, __ATOMIC_RELAXED);   \
    __oldval;                                                           \
  })

#define atomic_exchange_acq(mem, value) \
  __atomic_exchange_n(mem, value, __ATOMIC_ACQUIRE)

#define atomic_exchange_and_add_acq(mem, value) \
  __atomic_fetch_add(mem, value, __ATOMIC_ACQUIRE)

#endif
